#include"engine/util/KeyMap.h"

KeyStateMap::KeyStateMap()
{

}

void KeyStateMap::AddKey(const int& key)
{
	if (mStateMap.find(key) == mStateMap.end())
	{
		mStateMap.insert({ key, { KEY_STATE::UNKNOWN, high_resolution_clock::now() } });
	}
}

void KeyStateMap::AddKey(const int& key, const KeyState& state)
{
	if (mStateMap.find(key) == mStateMap.end())
	{
		mStateMap.insert({ key, state });
	}
}

void KeyStateMap::RemoveKey(const int& key)
{
	mStateMap.erase(key);
}

KeyState& KeyStateMap::operator[](const int& key)
{
	return mStateMap[key];
}

KeyStateMap::iterator KeyStateMap::Begin()
{
	return mStateMap.begin();
}

KeyStateMap::const_iterator KeyStateMap::Begin() const
{
	return mStateMap.cbegin();
}

KeyStateMap::iterator KeyStateMap::End()
{
	return mStateMap.end();
}

KeyStateMap::const_iterator KeyStateMap::End() const
{
	return mStateMap.cend();
}

