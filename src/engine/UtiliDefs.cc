#include"engine/util/UtiliDefs.h"
const std::string& TypeToString(const object_t& obj)
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
