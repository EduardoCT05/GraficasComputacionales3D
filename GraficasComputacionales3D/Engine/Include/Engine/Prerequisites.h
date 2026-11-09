#pragma once

// C++ library
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <new>
#include <sstream>
#include <string>
#include <vector>

// Other libraries
#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// Proyect Headers
#include "API.h"

/// Macros de utilidad para liberacion de memoria y registro en consola
#define SAFE_RELEASE(x) \
  if (x != nullptr)     \
  {                     \
    x->Release();       \
    x = nullptr;        \
  }

#define MESSAGE(classObj, method, state)                      \
  {                                                           \
    std::wostringstream os_;                                  \
    os_ << classObj << "::" << method << " : "                \
        << "[CREATION OF RESOURCE : " << state << "] \n";     \
    OutputDebugStringW(os_.str().c_str());                    \
  }

#ifdef ERROR
#undef ERROR
#endif

#define ERROR(classObj, method, errorMSG)                         \
  {                                                               \
    try                                                           \
    {                                                             \
      std::wostringstream os_;                                    \
      os_ << L"ERROR : " << classObj << L"::" << method           \
          << L" : " << errorMSG << L"\n";                         \
      OutputDebugStringW(os_.str().c_str());                      \
    }                                                             \
    catch (...)                                                   \
    {                                                             \
      OutputDebugStringW(L"Failed to log error message.\n");      \
    }                                                             \
  }

/// Tipos de extensiones de texturas soportadas
enum ExtensionType
{
    DDS = 0,
    PNG = 1,
    JPG = 2
};

/// Estructura base de un vertice con posicion y color
struct Vertex
{
    float position[3];
    float color[4];
};

/// Libera de forma segura una interfaz COM de DirectX
template<typename T>
void
SafeRelease(T*& object) noexcept
{
    if (object != nullptr)
    {
        object->Release();
        object = nullptr;
    }
}

extern "C"
{
    ENGINE_API bool
        Engine_Initialize(HWND hwnd, int width, int height) noexcept;

    ENGINE_API void
        Engine_Update() noexcept;

    ENGINE_API void
        Engine_Render() noexcept;

    ENGINE_API void
        Engine_Shutdown() noexcept;
}