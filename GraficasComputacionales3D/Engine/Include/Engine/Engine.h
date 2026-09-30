#pragma once

#include "Prerequisites.h" // Project Header

// Esta es la clase principal del motor
// Esta clase se encarga de controlar las partes principales
// del motor, como iniciar, dibujar y cerrar el programa.
class ENGINE_API Engine final {
public:
	// Instancias del motor
	Engine() noexcept;
	~Engine() noexcept;

	// Engine& = delete evita que se pueda copiar el motor
	Engine(const Engine&) = delete;

	// Evita asignar una copia del motor a otro objeto
	Engine& operator=(const Engine&) = delete;

	// Engine&& = delete evita mover el motor a otro objeto
	Engine(const Engine&&) = delete;

	// Evita asignar el motor mediante movimiento
	Engine& operator=(Engine&&) = delete;

	// Inicializa el motor
	// Recibe la ventana donde se mostrara el programa,
	// además de su ancho y alto
	// Parametros:
	// - nativeWindow: Ventana donde se mostrará el motor
	// - width: Ancho de la ventana
	// - height: Alto de la ventana
	// Retorna: true si la inicialización se realizó correctamente, 
	// false si ocurrió algún problema
	bool Initialize(
		void* nativeWindow,
		std::uint32_t width,
		std::uint32_t height
	) noexcept;

	// La funcion es la que se llama para renderizar
	void Render() noexcept;

	// Esta funcion es cuando dejamos de ejecutar, cierra y libera sus recursos
	void Shutdown() noexcept;

private:
	// Se usa para mantener los detalles internos del motor
	struct Implementation;

	// Se usa para apuntar y/o acceder a las partes internas del motor
	Implementation* m_implementation = nullptr;
};