#pragma once

#define PLATFORM_WIN 1
#define PLATFORM_OTHER 2

#if defined(__WIN32__) || defined(_WIN32) || defined(_WINDOWS) || defined(WIN) || defined(_WIN64) || defined(__WIN64__)
#define PLATFORM PLATFORM_WIN
#else
#define PLATFORM PLATFORM_OTHER
#endif

#if PLATFORM == PLATFORM_WIN
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EPXORT extern "C" __attribute ((visibility("default")))
#endif
