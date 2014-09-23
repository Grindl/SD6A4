
#include "ProfileSection.hpp"
#include "../Systems/Time Utility.hpp"

#include "Memory Manager/MemoryManager.hpp"

std::map<const char*, double> ProfileSection::s_movingAverageTimeOverFrames;
std::map<const char*, double> ProfileSection::s_accumulatedTimeInSections;
std::map<const char*, double> ProfileSection::s_activeProfileSections;

//----------------------------------------------------------------------------------------
ProfileSection::ProfileSection()
	:m_profileName("UNNAMED")
{
	StartProfile(m_profileName);
}


//----------------------------------------------------------------------------------------
ProfileSection::ProfileSection(const char* sectionName)
	:m_profileName(sectionName)
{
	StartProfile(m_profileName);
}

//----------------------------------------------------------------------------------------
ProfileSection::~ProfileSection()
{
	StopProfile(m_profileName);
}

//----------------------------------------------------------------------------------------
void ProfileSection::StartProfile(const char* sectionName)
{
	initializeTimeUtility();
	//Intentionally skips looking for an existing section name for the sake of speed
	s_activeProfileSections[sectionName] = getCurrentTimeSeconds();
}

//----------------------------------------------------------------------------------------
void ProfileSection::StopProfile(const char* sectionName)
{
	double endTime = getCurrentTimeSeconds();
	if (s_activeProfileSections.find(sectionName) != s_activeProfileSections.end())
	{
		double startTime = s_activeProfileSections[sectionName];
		double timeDifference = endTime - startTime;
		if (s_accumulatedTimeInSections.find(sectionName) != s_accumulatedTimeInSections.end())
		{
			s_accumulatedTimeInSections[sectionName] += timeDifference;
		}
		else
		{
			s_accumulatedTimeInSections[sectionName] = timeDifference;
		}
		s_activeProfileSections.erase(sectionName);
	}
}

//----------------------------------------------------------------------------------------
void ProfileSection::Preframe()
{
	float movingAverageWeight = 0.9f;

	while(!s_accumulatedTimeInSections.empty())
	{
		auto currentSection = s_accumulatedTimeInSections.begin(); //an std iterator type
		const char* currentSectionName = currentSection->first;
		if (s_movingAverageTimeOverFrames.find(currentSectionName) != s_movingAverageTimeOverFrames.end())
		{
			s_movingAverageTimeOverFrames[currentSectionName] = s_movingAverageTimeOverFrames[currentSectionName] * movingAverageWeight + (1.f - movingAverageWeight) * currentSection->second;
		}
		else
		{
			s_movingAverageTimeOverFrames[currentSectionName] = currentSection->second;
		}
		s_accumulatedTimeInSections.erase(currentSection);
	}
}


//----------------------------------------------------------------------------------------
void ProfileSection::Postframe()
{
	//reserved for future use
}