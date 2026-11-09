#pragma once

#if defined(_WIN32)
/// Indica que estamos utilizando el DLL ya creado y que estamos
/// utilizando funciones que ya existen dentro de el.
#if defined(ENGINE_BUILD_DLL)
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif
/// Para sistemas que no son Windows no necesitamos estas instrucciones
/// especiales, por lo que ENGINE_API simplemente queda vacio.
#else
#define ENGINE_API
#endif