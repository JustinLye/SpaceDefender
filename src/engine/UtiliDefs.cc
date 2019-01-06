#include"engine/util/UtiliDefs.h"
std::string TypeToString(const object_t& obj)
{
	std::string result;
	switch (obj)
	{
	case object_t::ASTEROID:
		result = "ASTEROID";
		break;
	case object_t::ENEMY_SHIP:
		result = "ENEMY_SHIP";
		break;
	case object_t::EXPLOSION_OBJECT:
		result = "EXPLOSION_OBJECT";
		break;
	case object_t::GENERIC_OBJECT:
		result = "GENERIC_OBJECT";
		break;
	case object_t::LASER:
		result = "LASER";
		break;
	case object_t::PLAYER:
		result = "PLAYER";
		break;
	case object_t::ASTEROID_COLLISION:
		result = "ASTEROID_COLLISION";
		break;
	default:
		result = "UNKNOWN";
		break;
	};
	return result;
}

std::ostream& operator<<(std::ostream& os, const object_t& obj)
{
	os << TypeToString(obj);
	return os;
}

float VecToVecAngle(const glm::vec3& u, const glm::vec3& v)
{
	float dot_uv = glm::dot(u, v);
	float len_u = glm::length(u);
	float len_v = glm::length(v);
	return std::acos(dot_uv / (len_u * len_v));
}