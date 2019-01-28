#include "stdafx.h"
#include "Timer.h"
#include "Windows.h"

#define DESIRED_FPS 60.0f;
#define DESIRED_FRAMETIME_SEC ( 1 / DESIRED_FPS )
#define MAX_FRAMETIME_SEC ( 2 * DESIRED_FRAMETIME_SEC )

namespace Timing
{
	float GetLastFrameTime()
	{
#ifdef CONSTANT_FRAMETIME
		return DESIRED_FRAMETIME_SEC;
#else
		static LARGE_INTEGER g_performanceFrequency;
		static LARGE_INTEGER g_lastFrame_tickCount;
		LARGE_INTEGER g_curFrame_tickCount;
		LARGE_INTEGER g_deltaTickCount;
		float g_curFrame_elapsedTime;

		QueryPerformanceCounter( &g_curFrame_tickCount );

		if ( g_lastFrame_tickCount.QuadPart )
		{
			g_deltaTickCount.QuadPart = g_curFrame_tickCount.QuadPart - g_lastFrame_tickCount.QuadPart;

			// Covert the us to sec.
			g_deltaTickCount.QuadPart *= 1000000;

			// Cache the query frequency if it is never cached before.
			QueryPerformanceFrequency( &g_performanceFrequency );

			g_curFrame_elapsedTime = (float) ( g_deltaTickCount.QuadPart / g_performanceFrequency.QuadPart );
			g_curFrame_elapsedTime /= 1000;
		}
		else
		{
			g_curFrame_elapsedTime = 0.1333f;
		}

		g_lastFrame_tickCount.QuadPart = g_curFrame_tickCount.QuadPart;

#ifdef CLAMP_FRAMETIME
		if ( g_curFrame_elapsedTime > MAX_FRAMETIME_SEC )
		{
			g_curFrame_elapsedTime = MAX_FRAMETIME_SEC;
		}
#endif // CLAMP_FRAMETIME
		return g_curFrame_elapsedTime;

#endif // CONSTANT_FRAMETIME
	}
}