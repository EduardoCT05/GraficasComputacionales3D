#include "Window.h"

/// Se implementan las funciones de la clase Window,
/// encargada de crear, mostrar, procesar mensajes y destruir la ventana de la aplicacion.

/// Destructor de la clase Window.
Window::~Window()
{
    Destroy();
}

/// Crea la ventana de Windows y registra su clase.
bool
Window::Create(
    HINSTANCE instance,
    const wchar_t* tittle,
    UINT clientWidth,
    UINT clientHeight
) noexcept
{
    if (m_handle || !instance || !tittle || clientWidth == 0 || clientHeight == 0)
    {
        return false;
    }

    /// Configuracion de la clase de ventana.
    WNDCLASSEXW windowClass{};
    windowClass.cbSize = sizeof(windowClass);

    /// Funcion que recibira los mensajes de Windows.
    windowClass.lpfnWndProc = WindowProcedure;
    /// Instancia de la aplicacion.
    windowClass.hInstance = instance;
    /// Cursor que utilizara la ventana.
    windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    /// Nombre de la clase de la ventana.
    windowClass.lpszClassName = ClassName;

    /// Registra la clase de ventana en Windows.
    if (!RegisterClassExW(&windowClass))
    {
        return false;
    }

    m_instance = instance;
    m_classRegistered = true;

    /// Estilo de la ventana.
    constexpr DWORD style =
        WS_OVERLAPPED |
        WS_CAPTION |
        WS_SYSMENU |
        WS_MINIMIZEBOX;

    /// Define el tamaño del area interna de la ventana.
    RECT rectangle{
      0,
      0,
      static_cast<LONG>(clientWidth),
      static_cast<LONG>(clientHeight)
    };

    /// Ajusta el tamaño total de la ventana.
    if (!AdjustWindowRect(&rectangle, style, FALSE))
    {
        Destroy();
        return false;
    }

    const int ouerWidth = rectangle.right - rectangle.left;
    const int outerHeight = rectangle.bottom - rectangle.top;

    /// Crea la ventana de Windows.
    m_handle = CreateWindowExW(
        0,
        ClassName,
        tittle,
        style,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        ouerWidth,
        outerHeight,
        nullptr,
        nullptr,
        instance,
        this
    );

    /// Si no se pudo crear, elimina los recursos creados.
    if (!m_handle)
    {
        Destroy();
        return false;
    }

    return true;
}

/// Muestra la ventana en pantalla.
void
Window::Show(int showCommand) noexcept
{
    if (m_handle)
    {
        ShowWindow(m_handle, showCommand);
        UpdateWindow(m_handle);
    }
}

/// Destruye la ventana y libera sus recursos.
void
Window::Destroy() noexcept
{
    /// Verifica si existe la ventana y la destruye.
    if (m_handle)
    {
        DestroyWindow(m_handle);
        m_handle = nullptr;
    }

    if (m_classRegistered)
    {
        UnregisterClassW(ClassName, m_instance);
        m_classRegistered = false;
    }

    m_instance = nullptr;
}

/// Obtiene y procesa todos los mensajes pendientes de la ventana.
bool
Window::ProcessMessages() noexcept
{
    MSG message{};

    while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE))
    {
        if (message.message == WM_QUIT)
        {
            return false;
        }

        /// Traduce el mensaje antes de enviarlo al procedimiento.
        TranslateMessage(&message);
        /// Envia el mensaje al WindowProcedure.
        DispatchMessageW(&message);
    }
    return true;
}

/// Indica si la ventana se encuentra minimizada.
bool
Window::IsMinimized() const noexcept
{
    return m_handle && IsIconic(m_handle);
}

/// Obtiene el identificador nativo de la ventana.
HWND
Window::GetHandle() const noexcept
{
    return m_handle;
}

/// Procedimiento principal que procesa los mensajes de la ventana.
LRESULT CALLBACK
Window::WindowProcedure(
    HWND handle,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
)
{
    switch (message)
    {
    case WM_ERASEBKGND:
        /// DirectX limpia el back buffer.
        return 1;

    case WM_DESTROY:
        /// Indica a Windows que la aplicacion debe terminar.
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProcW(handle, message, wParam, lParam);
    }
}