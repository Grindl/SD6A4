#pragma once
#ifndef include_GAMECLOCK
#define include_GAMECLOCK

#include <vector>

/*
2.	Hierarchical clocks (30 points)
a.	A Clock class which can have one or more children and thereby participate in a hierarchy of clocks.  Each clock should store its own concept of the current time, 
		the most recent delta time step, a float timescale, a maximum delta, and a paused/unpaused boolean state.
b.	Clocks should be able to be created and used from anywhere within game or engine code; clocks (except the root/master clock) should be born with a parent.
c.	Implement void Clock::AdvanceTime( double deltaSeconds ), taking paused/unpaused, timescale, maximum delta, and hierarchy into account.
d.	Clock hierarchy should be able to correctly handle runtime changes to the hierarchy, including the removal of clocks from the hierarchy.
*/

class GameClock
{
public:
	GameClock(GameClock* parent);

	GameClock* m_parent;
	std::vector<GameClock*> m_children;
	float m_currentInternalTime;
	float m_lastDeltaTime;
	float m_timescale;
	float m_maximumDeltaTime; //TODO QUESTION: ask if this is necessary, and what to do with it
	bool m_isPaused;

	void AdvanceTime(double deltaSeconds);
};

#endif