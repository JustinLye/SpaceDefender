#ifndef UTILI_DEFS_HEADER_INCLUDED
#define UTILI_DEFS_HEADER_INCLUDED
#include<string>
#include<boost/lexical_cast.hpp>
#ifndef VEC3_TO_STRING
#define Vec3ToString(vec_3) std::string("[") + boost::lexical_cast<std::string>(vec_3.x) + std::string(", ") + boost::lexical_cast<std::string>(vec_3.y) + std::string(", ") + boost::lexical_cast<std::string>(vec_3.z) + std::string("]")
#endif
#ifndef VEC4_TO_STRING
#define Vec4ToString(vec_4) std::string("[") + boost::lexical_cast<std::string>(vec_4.x) + std::string(", ") + boost::lexical_cast<std::string>(vec_4.y) + std::string(", ") + boost::lexical_cast<std::string>(vec_4.z) + std::string(", ") + boost::lexical_cast<std::string>(vec_4.w) + std::string("]")
#endif
#ifndef MESSAGE_STR
#define MessageStr(msg) std::string(__FILE__) + std::string("    ") + std::string(__FUNCTION__) + std::string(" [") + std::string(__LINE__) + std::string("] ") + boost::lexical_cast<std::string>(msg)
#endif
#endif