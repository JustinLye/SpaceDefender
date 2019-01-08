#ifndef UTILI_DEFS_HEADER_INCLUDED
#define UTILI_DEFS_HEADER_INCLUDED
#include<iostream>
#include<string>
#include"engine/util/Constants.h"

/** @addtogroup EngineUtil */
/*@{*/
#ifndef VEC3_TO_STRING
#define Vec3ToString(vec_3) std::string("[") + std::to_string(vec_3.x) + std::string(", ") + std::to_string(vec_3.y) + std::string(", ") + std::to_string(vec_3.z) + std::string("]")
#endif
#ifndef VEC4_TO_STRING
#define Vec4ToString(vec_4) std::string("[") + std::to_string(vec_4.x) + std::string(", ") + std::to_string(vec_4.y) + std::string(", ") + std::to_string(vec_4.z) + std::string(", ") + std::to_string(vec_4.w) + std::string("]")
#endif
#ifndef MESSAGE_STR
#define MessageStr(msg) std::string(std::string(__FILE__) + std::string("    ") + std::string(__FUNCTION__) + std::string(" [") + std::string(__LINE__) + std::string("] ") + std::to_string(msg))
#endif
#ifndef PI
#define	PI 3.14159265359
#endif // !PI
#ifndef DEG_TO_RAD
#define DegToRad(deg) (float)deg * ((float)PI/180.0f)
#endif // !DEG_TO_RAD
#ifndef RAD_TO_DEG
#define RadToDeg(rad) (float)rad * (180.0f/(float)PI)
#endif // !RAD_TO_DEG

namespace sd_app {
namespace engine {
namespace util {
using object_t = sd_app::engine::constants::types::object_t;
std::string TypeToString(const object_t& obj);
std::ostream& operator<<(std::ostream& os, const object_t& obj);
float VecToVecAngle(const glm::vec3&, const glm::vec3&);
} // namespace util
} // namespace engine
} // namespace sd_app

/*@}*/
#endif