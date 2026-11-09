// Other libraries 
#include <Windows.h>

// Proyect Headers
#include <Engine/Engine.h>
#include "Window.h"

/// Punto de entrada principal de la aplicacion en Windows.
/// Se encarga de crear la ventana, inicializar el engine,
/// ejecutar el ciclo principal de la aplicación y liberar
/// los recursos cuando la ventana se cierra.
/// instance: Instancia actual de la aplicacion.
/// previousInstance: Instancia anterior de la aplicacion (siempre NULL).
/// commandLine: Argumentos recibidos desde la línea de comandos.
/// showCommand: Indica cómo se debe mostrar la ventana.
/// Devuelve 0 si la aplicación termina correctamente o 1 si ocurre un error.
int WINAPI
wWinMain(
    HINSTANCE instance,
    HINSTANCE previousInstance,
    PWSTR commandLine,
    int showCommand
)
{
    /// Estos parametros no se utilizan en esta aplicacion
    UNREFERENCED_PARAMETER(previousInstance);
    UNREFERENCED_PARAMETER(commandLine);

    /// Tamaño de la ventana
    constexpr UINT CLIENT_WIDTH = 1280;
    constexpr UINT CLIENT_HEIGHT = 720;

    Window window;

    /// Aqui se crea la ventana y configura el tamaño y titulo
    if (!window.Create(instance, L"Motor Grafico 3D", CLIENT_WIDTH, CLIENT_HEIGHT))
    {
        MessageBoxW(
            nullptr,
            L"No se pudo crear la ventana.",
            L"Sandbox Error",
            MB_OK | MB_ICONERROR
        );
        return 1;
    }

    Engine engine;

    /// Inicializa el engine utilizando la ventana creada
    if (!engine.Initialize(window.GetHandle(), CLIENT_WIDTH, CLIENT_HEIGHT))
    {
        MessageBoxW(
            window.GetHandle(),
            L"No se pudo inicializar el Engine.\n\n"
            L"Verifica que exista:\n"
            L"shaders\\Cube.hlsl\n\n"
            L"Revisa tambien la ventana Output.",
            L"Engine Error",
            MB_OK | MB_ICONERROR
        );

        return 1;
    }

    /// Muestra la ventana en la pantalla
    window.Show(showCommand);

    /// Ciclo principal de la aplicacion
    while (window.ProcessMessages())
    {
        /// Si se minimiza la ventana no es necesario renderizarla
        if (window.IsMinimized())
        {
            WaitMessage();
            continue;
        }
        engine.Render();
    }

    /// Libera los recursos utilizados por el engine
    engine.Shutdown();

    /// Destruye la ventana y libera sus recursos
    window.Destroy();

    return 0;
}