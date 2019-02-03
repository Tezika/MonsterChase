#pragma once

namespace Engine
{
	void LogPrint( const char * i_prefix, const char*  i_fmt, ... );
}

// This is how we handle variable argument pre-processor macros
// This is only supported by compilers that support the C99 standard
#if defined(_DEBUG) && !defined(DISABLE_DEBUG_PRINT)
#define DEBUG_PRINT_ENGINE(fmt,...) Engine::LogPrint("ENGINE LOG:",(fmt),__VA_ARGS__)
#define DEBUGE_PRINT_GAMEPLAY(fmt,...) Engine::LogPrint("GAMEPLAY LOG:",(fmt),__VA_ARGS__)

#else
// This is one way we create a do nothing (NO OP) macro that doesn't
// generate a compiler warning or error
#define DEBUG_PRINT(fmt,...) void(0)
#endif

