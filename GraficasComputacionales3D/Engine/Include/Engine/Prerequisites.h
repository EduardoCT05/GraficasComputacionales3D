#pragma once

#include <cstdint>   // 2. C++ library
#include <Windows.h> // 3. Other libraries (API del sistema)
#include "API.h"     // 4. Project header

// Funciones principales que forman parte de la API del Engine.
// Estas funciones permiten que codigo externo pueda
// inicializar, utilizar y cerrar el Engine.
extern "C" {

	ENGINE_API bool engine_Initialize(HWND hwnd, int width, int height) noexcept;

	ENGINE_API void Engine_Render() noexcept;

	ENGINE_API void Engine_Shutdown() noexcept;

}