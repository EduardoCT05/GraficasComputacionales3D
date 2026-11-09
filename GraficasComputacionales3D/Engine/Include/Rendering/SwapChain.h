#pragma once

// Proyect Headers
#include "Engine/Prerequisites.h"

class Window;
class Device;
class Texture2D;

/// Es el encargado de mostrar en pantalla lo que la tarjeta de video dibuja.
/// Para que la imagen no se vea cortada o parpadeando, la tarjeta de video
/// no dibuja directamente sobre lo que ves. Dibuja en una imagen oculta
/// y, cuando termina, la intercambia con la que esta en pantalla.
/// Esta clase se encarga de manejar ese intercambio.
class SwapChain
{
public:
    SwapChain() = default;
    ~SwapChain();

    /// No se permite hacer copias de este objeto.
    /// Solo puede existir un intercambiador por ventana.
    SwapChain(const SwapChain&) = delete;
    SwapChain& operator=(const SwapChain&) = delete;

    /// No se permite mover este objeto a otro lugar.
    SwapChain(SwapChain&&) = delete;
    SwapChain& operator=(SwapChain&&) = delete;

    /// Prepara el intercambiador para mostrar imagenes en una ventana.
    /// device: Fabricante de la tarjeta de video.
    /// window: La ventana donde se mostraran las imagenes.
    /// width: Ancho de la imagen, en pixeles.
    /// height: Alto de la imagen, en pixeles.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        init(
            Device device,
            Window window,
            unsigned int width,
            unsigned int height
        );

    /// Libera los recursos del intercambiador.
    void
        destroy();

    /// Muestra en pantalla el cuadro que ya termino de dibujarse.
    /// Es el momento en que la imagen oculta pasa a ser la visible.
    /// syncInterval: Cuantas veces espera la pantalla antes de mostrar el
    /// cuadro (con 1 se sincroniza mas suave, con 0 se muestra de inmediato).
    /// flags: Opciones adicionales de presentacion.
    HRESULT
        Present(unsigned int syncInterval = 1, unsigned int flags = 0);

    /// Obtiene la imagen oculta sobre la que se va a dibujar.
    /// bufferIndex: Numero de la imagen que se quiere.
    /// backBuffer: Aqui se guarda la imagen obtenida.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        GetBuffer(unsigned int bufferIndex, Texture2D backBuffer);

    /// Ajusta el tamano de las imagenes cuando cambia el tamano de la ventana.
    /// width: Nuevo ancho, en pixeles.
    /// height: Nuevo alto, en pixeles.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        ResizeBuffers(unsigned int width, unsigned int height);

    /// Entrega el intercambiador real de DirectX.
    /// Devuelve el puntero al intercambiador.
    IDXGISwapChain*
        getSwapChain()
    {
        return m_swapChain;
    }

private:
    /// El intercambiador real de DirectX.
    /// Empieza vacio (nulo) y se llena al llamar a init().
    IDXGISwapChain* m_swapChain = nullptr;
};