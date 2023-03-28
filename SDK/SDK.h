#pragma once

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif // __cplusplus

#ifdef _WIN32

#define EXPORT EXTERN __declspec(dllexport)
#define IMPORT EXTERN __declspec(dllimport)

#else

#define EXPORT EXTERN __attribute__((visibility("default")))
#define IMPORT

#endif // _WIN32
#include <string>
#include "deps/ConfigBase.h"
#include "IPackage.h"
#include "IResource.h"
#include "IScriptRuntime.h"
#include "ILocalStorage.h"
#include "ICore.h"

