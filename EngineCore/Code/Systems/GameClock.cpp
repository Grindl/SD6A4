#include "Time Utility.hpp"

#include "GameClock.hpp"

#include "Memory Manager/MemoryManager.hpp"

//----------------------------------------------------------------------------------------
GameClock::GameClock(GameClock* parent)
	:m_parent(parent)
	,m_currentInternalTime(0.f)
	,m_lastDeltaTime(0.f)
	,m_timescale(1.f)
	,m_isPaused(false)
{

}

//----------------------------------------------------------------------------------------
void GameClock::AdvanceTime(double deltaSeconds)
{
	float timeElapsed = deltaSeconds;
	if (!m_isPaused)
	{
		timeElapsed = deltaSeconds * m_timescale;
		m_lastDeltaTime = deltaSeconds;
		for (unsigned int childrenIndex = 0; childrenIndex < m_children.size(); childrenIndex++)
		{
			m_children[childrenIndex]->AdvanceTime(timeElapsed);
		}
		m_currentInternalTime += timeElapsed;
	}
}