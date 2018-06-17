#include"engine/util/DistanceEntry.h"

DistanceEntry::DistanceEntry(const int& index, const float& dist) :
	mIndex(index),
	mDistance(dist)
{

}

DistanceEntry::DistanceEntry(const DistanceEntry& other) :
	mIndex(other.mIndex),
	mDistance(other.mDistance)
{

}

DistanceEntry::DistanceEntry(DistanceEntry&& other) :
	mIndex(std::move(other.mIndex)),
	mDistance(std::move(other.mDistance))
{

}

bool DistanceEntry::operator<(const DistanceEntry& other) const
{
	return mDistance < other.mDistance;
}

DistanceEntry& DistanceEntry::operator=(const DistanceEntry& other)
{
	mIndex = other.mIndex;
	mDistance = other.mDistance;
	return *this;
}