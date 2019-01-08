#ifndef CONFIGURATION_HEADER_INCLUDED
#define CONFIGURATION_HEADER_INCLUDED

#include<string>
#include<fstream>

#include<json/json.h>

#include"core/NonCopyable.h"

namespace sd_app {
namespace core {
class Configuration :
  private NonCopyable {
public:
  Configuration(const char* file_path); ///< Constructor
  Configuration(const std::string& file_path); ///< Constructor
  virtual ~Configuration(); ///< Destructor

  // Modifiers
  void Load(); ///< Loads Configuration. Requires existing file path and empty configuration.
  void Clear(); ///< Clears current configuration.
  void Save(); ///< Saves current configuration.
  void Reload(); ///< Calls Clear() then Load()

  // Accessors
  template<class T> T Get(const char* setting_name) const; ///< Returns value. Does NOT check if setting exists or if a configuration has been loaded. Assumes all checks have been performed and passed before call.
  template<class T> T Get(const std::string& setting_name) const; ///< Returns value. Does NOT check if setting exists or if a configuration has been loaded. Assumes all checks have been performed and passed before call.
  template<class T> void Set(const char* setting_name, T setting_value); ///< Set value. Does NOT check if setting exists or if a configuration has been loaded. Assumes all checks have been performed and passed before call.
  template<class T> void Set(const std::string& setting_name, T setting_value); ///< Set value. Does NOT check if setting exists or if a configuration has been loaded. Assumes all checks have been performed and passed before call.

  // Observers
  bool Loaded() const; ///< True if a configuration has been loaded.
  bool HasSetting(const char* setting_name) const; ///< True if setting_name is found in configuration.
  bool HasSetting(const std::string& setting_name) const; ///< True if setting_name is found in configuration.
  bool UnsavedChanges() const; ///< Return true if settings have changed since last load

private:
  std::string FilePath_; ///< Configuration input file stream
  Json::Value SavedRoot_; ///< JSON original settings loaded
  Json::Value WorkingRoot_; ///< JSON root we actually use

  void SaveSettingsToFile(); ///< Saves settings to configuration file
};

inline void Configuration::Clear() {
  SavedRoot_.clear();
  WorkingRoot_.clear();
}

inline void Configuration::Save() {
  if (!Loaded()) {
    throw std::logic_error("Attempt to save configuration that has not been loaded.");
  }
  if (UnsavedChanges()) {
    SaveSettingsToFile();
  }
}

inline void Configuration::Reload() {
  SavedRoot_.clear();
  WorkingRoot_.clear();
  Load();
}

template<>
inline Json::Value Configuration::Get(const char* setting_name) const {
  return WorkingRoot_.get(setting_name, Json::Value());
}

template<class T>
inline T Configuration::Get(const std::string& setting_name) const {
  return Get<T>(setting_name.c_str());
}

template<>
inline bool Configuration::Get(const char* setting_name) const {
  return WorkingRoot_[setting_name].asBool();
}

template<>
inline const char* Configuration::Get(const char* setting_name) const {
  return WorkingRoot_[setting_name].asCString();
}

template<>
inline double Configuration::Get(const char* setting_name) const {
  return WorkingRoot_[setting_name].asDouble();
}

template<>
inline float Configuration::Get(const char* setting_name) const {
  return WorkingRoot_[setting_name].asFloat();
}

template<>
inline int Configuration::Get(const char* setting_name) const {
  return WorkingRoot_[setting_name].asInt();
}

template<>
inline __int64 Configuration::Get(const char* setting_name) const {
  return WorkingRoot_[setting_name].asInt64();
}

template<>
inline unsigned int Configuration::Get(const char* setting_name) const {
  return WorkingRoot_[setting_name].asUInt();
}

template<>
inline unsigned __int64 Configuration::Get(const char* setting_name) const {
  return WorkingRoot_[setting_name].asUInt64();
}

template<>
inline std::string Configuration::Get(const char* setting_name) const {
  return WorkingRoot_[setting_name].asString();
}

template<class T>
inline void Configuration::Set(const char* setting_name, T setting_value) {
  WorkingRoot_[setting_name] = setting_value;
}

template<class T>
inline void Configuration::Set(const std::string& setting_name, T setting_value) {
  Set(setting_name.c_str(), setting_value);
}


inline bool Configuration::Loaded() const {
  return !WorkingRoot_.empty();
}

inline bool Configuration::HasSetting(const char* setting_name) const {
  return Loaded() ? WorkingRoot_.isMember(setting_name) : false;
}

inline bool Configuration::HasSetting(const std::string& setting_name) const {
  return HasSetting(setting_name.c_str());
}

inline bool Configuration::UnsavedChanges() const {
  return (Loaded() ? WorkingRoot_ != SavedRoot_ : false);
}

} // namespace core
} // namespace sd_app

#endif // !CONFIGURATION_HEADER_INCLUDED
