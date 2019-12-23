#pragma once
#if defined(PLATFORM_WINDOWS)

// Exclude extraneous Windows stuff
#define WIN32_LEAN_AND_MEAN
// Prevent Windows from creating min/max macros
#define NOMINMAX
// Initialize Windows
#include <Windows.h>
#undef NOMINMAX
#undef WIN32_LEAN_AND_MEAN
#include <xaudio2.h>
#endif