#ifndef included_Time_Utility
#define included_Time_Utility
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static double secondsPerCount = 0.0;

static void initializeTimeUtility()
{
	if(secondsPerCount == 0.0)
	{
		LARGE_INTEGER countsPerSecond;
		QueryPerformanceFrequency(&countsPerSecond);
		secondsPerCount = 1.0/(double)(LONGLONG)countsPerSecond.QuadPart;
	}
}

//timer functions should ALWAYS BE OPTIMIZED
static inline double getCurrentTimeSeconds()
{
#ifdef _WIN32
	LARGE_INTEGER myTime;
	QueryPerformanceCounter(&myTime);

	double currSecs = ((double) myTime.QuadPart)*secondsPerCount;
	return currSecs;

#endif //WIN32
}

#endif //Include Guard
