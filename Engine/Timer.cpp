#include "stdafx.h"
#include "Timer.h"
#include "Windows.h"
#include "ConsolePrint.h"

#define DESIRED_FPS 60.0f
#define DESIRED_FRAMETIME_SEC ( 1.0f / DESIRED_FPS )
#define MAX_FRAMETIME_SEC ( 2 * DESIRED_FRAMETIME_SEC )
#define CLAMP_FRAMETIME

namespace Engine
{
	namespace Timing
	{
		float GetCurTime()
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
#else
			static float g_lastFrame_elapsedTime = -1.0f;
			float g_currentFrame_elapsedTime;

			float g_curTime = GetCurTime();
			if (g_lastFrame_elapsedTime == -1.0f)
			{
				g_lastFrame_elapsedTime = g_curTime;
				g_currentFrame_elapsedTime = 0.167f;
			}
			else
			{
				g_currentFrame_elapsedTime = g_curTime - g_lastFrame_elapsedTime;
				g_lastFrame_elapsedTime = g_curTime;
			}
#ifdef CLAMP_FRAMETIME
			if (g_currentFrame_elapsedTime > MAX_FRAMETIME_SEC)
			{
				g_currentFrame_elapsedTime = MAX_FRAMETIME_SEC;
			}
#endif // CLAMP_FRAMETIME
			return g_currentFrame_elapsedTime;

#endif // CONSTANT_FRAMETIME
		}
	}
}