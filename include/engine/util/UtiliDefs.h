#ifndef UTILI_DEFS_HEADER_INCLUDED
#define UTILI_DEFS_HEADER_INCLUDED
#include<iostream>
#include<string>
#include<boost/lexical_cast.hpp>
#include"engine/util/Constants.h"
using namespace Constants::Types;
/** @addtogroup EngineUtil */
/*@{*/
#ifndef VEC3_TO_STRING
#define Vec3ToString(vec_3) std::string("[") + boost::lexical_cast<std::string>(vec_3.x) + std::string(", ") + boost::lexical_cast<std::string>(vec_3.y) + std::string(", ") + boost::lexical_cast<std::string>(vec_3.z) + std::string("]")
#endif
#ifndef VEC4_TO_STRING
#define Vec4ToString(vec_4) std::string("[") + boost::lexical_cast<std::string>(vec_4.x) + std::string(", ") + boost::lexical_cast<std::string>(vec_4.y) + std::string(", ") + boost::lexical_cast<std::string>(vec_4.z) + std::string(", ") + boost::lexical_cast<std::string>(vec_4.w) + std::string("]")
#endif
#ifndef MESSAGE_STR
#define MessageStr(msg) std::string(std::string(__FILE__) + std::string("    ") + std::string(__FUNCTION__) + std::string(" [") + std::string(__LINE__) + std::string("] ") + boost::lexical_cast<std::string>(msg))
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


std::string TypeToString(const object_t& obj);
std::ostream& operator<<(std::ostream& os, const object_t& obj);
float VecToVecAngle(const glm::vec3&, const glm::vec3&);
/*@}*/
#endif