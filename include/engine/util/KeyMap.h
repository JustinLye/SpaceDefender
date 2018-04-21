#ifndef KEY_MAP_HEADER_INCLUDED
#define KEY_MAP_HEADER_INCLUDED

#include<map>
#include<chrono>
#include"engine/util/Constants.h"

using namespace Constants::Input;
using namespace std::chrono;

struct KeyState
{
	KEY_STATE mState;
	time_point<steady_clock> mLastChanged;
};

class KeyStateMap
{
public:
	KeyStateMap();

	void AddKey(const int&);
	void AddKey(const int&, const KeyState&);
	void RemoveKey(const int&);
	KeyState& operator[](const int&);
	typedef std::map<int, KeyState>::iterator iterator;
	typedef std::map<int, KeyState>::const_iterator const_iterator;
	iterator Begin();
	const_iterator Begin() const;
	iterator End();
	const_iterator End() const;
protected:
	std::map<int, KeyState> mStateMap;
};

#endif