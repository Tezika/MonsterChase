#include "stdafx.h"
#include "Timer.h"
#include "Windows.h"
#include "ConsolePrint.h"

#define DESIRED_FPS 60.0f
#define DESIRED_FRAMETIME_SEC ( 1.0f / DESIRED_FPS )
#define MIN_FRAMETIME_SEC   DESIRED_FRAMETIME_SEC 
#define MAX_FRAMETIME_SEC ( DESIRED_FRAMETIME_SEC * 2)
#define CLAMP_FRAMETIME

namespace Engine
{
	namespace Timing
	{
		float Clock()
		{
			static LARGE_INTEGER g_performanceFrequency;
			if (!g_performanceFrequency.QuadPart)
			{
				QueryPerformanceFrequency( &g_performanceFrequency );
			}
			LARGE_INTEGER g_curTickCount;
			QueryPerformanceCounter( &g_curTickCount );
			return static_cast< float >(g_curTickCount.QuadPart) / g_performanceFrequency.QuadPart;
		}

		float GetLastFrameTime()
		{
#ifdef CONSTANT_FRAMETIME
			return DESIRED_FRAMETIME_SEC;
#endif
			static LARGE_INTEGER g_performanceFrequency;
			static LARGE_INTEGER g_lastFrame_tickCount;
			LARGE_INTEGER g_curFrame_tickCount;
			float g_curFrame_elapsedTime;

			QueryPerformanceCounter( &g_curFrame_tickCount );

			if (g_lastFrame_tickCount.QuadPart)
			{
				// Cache the query frequency if it is never cached before.
				if (!g_performanceFrequency.QuadPart)
				{
					QueryPerformanceFrequency( &g_performanceFrequency );
				}
				// Avoid losing the precision and to multiply the 1000000, us.
				g_curFrame_elapsedTime = 1000000 * static_cast< float >(g_curFrame_tickCount.QuadPart - g_lastFrame_tickCount.QuadPart) / g_performanceFrequency.QuadPart;
				// Convert the result to sec.
				g_curFrame_elapsedTime /= 1000000;
			}
			else
			{
				g_curFrame_elapsedTime = 0.0167f;
			}

			g_lastFrame_tickCount.QuadPart = g_curFrame_tickCount.QuadPart;

#ifdef CLAMP_FRAMETIME
			if (g_curFrame_elapsedTime < MIN_FRAMETIME_SEC)
			{
				g_curFrame_elapsedTime = MIN_FRAMETIME_SEC;
			}
			if (g_curFrame_elapsedTime > MAX_FRAMETIME_SEC)
			{
				g_curFrame_elapsedTime = MAX_FRAMETIME_SEC;
			}
#endif // CLAMP_FRAMETIME
			return g_curFrame_elapsedTime;
		}
	}
}