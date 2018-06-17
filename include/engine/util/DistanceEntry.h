#ifndef DISTANCE_ENTRY_HEADER_INCLUDED
#define DISTANCE_ENTRY_HEADER_INCLUDED

#include<glm/glm.hpp>
#include"engine/objects/GameObject.h"

struct DistanceEntry
{
	DistanceEntry(const int& = 0, const float& = 0.0f);
	DistanceEntry(const DistanceEntry&);
	DistanceEntry(DistanceEntry&&);

	bool operator<(const DistanceEntry&) const;
	DistanceEntry& operator=(const DistanceEntry&);

	int mIndex;
	float mDistance;
};

#endif // !DISTANCE_ENTRY_HEADER_INCLUDED
