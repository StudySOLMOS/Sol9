#pragma once

#include "Singleton.h"
#include <windows.h>

class TimeManager : public Singleton<TimeManager>
{
private:
	LARGE_INTEGER freq;

public:
	TimeManager()
	{
		QueryPerformanceFrequency(&freq);
	}

	unsigned int time()
	{
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		return (unsigned int)(t.QuadPart / (freq.QuadPart / 1000.0));
	}
};