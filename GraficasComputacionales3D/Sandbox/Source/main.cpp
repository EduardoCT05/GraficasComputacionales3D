#include <Windows.h>                          // Other libraries (API del sistema)

#include "../../Engine/Include/Engine/Engine.h" // Project header
#include "../Include/Window.h"                  // Project header

int APIENTRY wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    // 1. Instanciar y crear la ventana
    Window window;

    // Le pasamos la instancia, el titulo, y el tamaño (800x600)
    if (!window.Create(hInstance, L"GuerreroEngine - Motor 3D", 800, 600))
    {
        return -1; // Si falla la creacion, salimos
    }

    // Mostramos la ventana en pantalla
    window.Show(nCmdShow);

    // 2. Instanciar e inicializar el motor
    Engine engine;

    // Le pasamos el identificador de la ventana (HWND) y las mismas medidas
    if (!engine.Initialize(window.GetHandle(), 800, 600))
    {
        return -1; // Si falla la inicializacion de DirectX, salimos
    }

    // 3. Bucle principal del juego (Game Loop)
    // Mientras la ventana siga recibiendo mensajes (no se haya cerrado)...
    while (window.ProcessMessages())
    {
        // ... el motor sigue dibujando cuadros
        engine.Render();
    }

    // 4. Limpieza al cerrar la ventana
    engine.Shutdown();

    return 0;
}