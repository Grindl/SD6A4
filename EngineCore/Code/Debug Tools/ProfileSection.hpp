#pragma once
#ifndef include_PROFILESECTION
#define include_PROFILESECTION

#include <map>
#include <string>


/*
4.	Profiling (30 points)
a.	A ProfileSection class or equivalent which can be used to profile the amount of time spent in a given section (or scope-block) of code.
b.	The ability to name, or otherwise identify (with an enum, etc.) which profiling category each profile section falls under.
c.	The ability to display, using toggleable onscreen text rendering, the total and average amount of time spent per frame in each category referenced.
d.	The ability to profile a section of code both through explicit “start” and “stop” profiling commands as well as through a simple “scoped profile section” 
		object which is instantiated as a temporary stack local object (and begins profiling) and which automatically stops and submits profiling when it goes out of scope and dies.
*/

class ProfileSection
{
public:
	ProfileSection();
	ProfileSection(const char* sectionName);
	~ProfileSection();

	static std::map<const char*, double> s_movingAverageTimeOverFrames;
	static std::map<const char*, double> s_accumulatedTimeInSections;
	static std::map<const char*, double> s_activeProfileSections;
	double m_startTime;
	double m_endTime;
	const char* m_profileName;

	static void StartProfile(const char* sectionName);
	static void StopProfile(const char* sectionName);
	static void Preframe();
	static void Postframe();
};


#endif