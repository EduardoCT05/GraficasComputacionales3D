#pragma once

// Proyect Headers
#include "Prerequisites.h"

/// Esta es la clase principal del motor.
/// Se encarga de controlar las partes principales del motor,
/// como iniciar, dibujar y cerrar el programa.
class ENGINE_API Engine final
{
public:
    /// Instancias del motor
    Engine() noexcept;
    ~Engine() noexcept;

    /// Evita que se pueda copiar el motor
    Engine(const Engine&) = delete;

    /// Evita asignar una copia del motor a otro objeto
    Engine& operator=(const Engine&) = delete;

    /// Evita mover el motor a otro objeto
    Engine(const Engine&&) = delete;

    /// Evita asignar el motor mediante movimiento
    Engine& operator=(Engine&&) = delete;

    /// Inicializa el motor.
    /// Recibe la ventana donde se mostrara el programa,
    /// ademas de su ancho y alto.
    /// nativeWindow: Ventana donde se mostrara el motor.
    /// width: Ancho de la ventana.
    /// height: Alto de la ventana.
    /// Devuelve true si la inicializacion se realizo correctamente,
    /// o false si ocurrio algun problema.
    bool
        Initialize(
            void* nativeWindow,
            std::uint32_t width,
            std::uint32_t height
        ) noexcept;

    /// Funcion que se llama en cada cuadro para renderizar
    void
        Render() noexcept;

    /// Funcion llamada al dejar de ejecutar; cierra y libera sus recursos
    void
        Shutdown() noexcept;

private:
    /// Se usa para mantener los detalles internos del motor
    struct Implementation;

    /// Se usa para apuntar y acceder a las partes internas del motor
    Implementation* m_implementation = nullptr;
};