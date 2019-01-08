#include"core/Configuration.h"

namespace sd_app {
namespace core {

Configuration::Configuration(const char* file_path) :
  FilePath_(file_path),
  SavedRoot_(),
  WorkingRoot_() {}

Configuration::Configuration(const std::string& file_path) :
  FilePath_(file_path),
  SavedRoot_(),
  WorkingRoot_() {}

Configuration::~Configuration() {}

void Configuration::Load() {
  // LOGIC CHECKS ON CURRENT STATE
  // WorkingRoot_ should be empty
  if (Loaded()) {
    throw std::logic_error("Configuration is already loaded. Reloading the configuration file would overwrite existing settings. Use Reload() instead.");
  }

  if (!SavedRoot_.empty()) {
    throw std::logic_error("LoadedRoot_ should be empty, but it is not.");
  }

  // OPEN INPUT FILE
  std::ifstream input_file;
  input_file.open(FilePath_.c_str());
  if (!input_file) {
    throw std::runtime_error("Failed to open configuration file '" + FilePath_ + "'.");
  }

  // LOAD CONFIG
  input_file >> SavedRoot_; // This will throw std::exception if there's a problem.
  input_file.close();
  WorkingRoot_ = SavedRoot_;
}

void Configuration::SaveSettingsToFile() {
  
  // LOGIC CHECKS ON CURRENT STATE
  // Do we really need to save?
  if (!UnsavedChanges()) {
    return;
  }

  if (!Loaded()) {
    throw std::logic_error("Configuration is has not been loaded. There is nothing to save.");
  }

  // OPEN OUTPUT FILE
  std::ofstream output_file(FilePath_.c_str());
  if (!output_file) {
    throw std::runtime_error("Failed to open configuration file '" + FilePath_ + "'. Could not save current settings.");
  }

  // WRITE CONFIG
  output_file << WorkingRoot_;
  output_file.close();
  SavedRoot_ = WorkingRoot_;

}

} // namespace core
} // namespace sd_app