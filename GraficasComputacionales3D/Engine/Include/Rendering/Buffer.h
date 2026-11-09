#pragma once

// Proyect Headers
#include "Engine/MeshComponent.h"
#include "Engine/Prerequisites.h"

class Device;
class DeviceContext;

/// Funciona como una caja de memoria dentro de la tarjeta de video.
/// La tarjeta de video no puede leer directamente la memoria normal de
/// la computadora. Para que pueda usar los datos de una figura, primero
/// hay que copiarlos a una caja especial dentro de la tarjeta. Esta clase
/// se encarga de crear esa caja, llenarla, actualizarla, usarla para
/// dibujar y borrarla al terminar.
class Buffer
{
public:
    Buffer() = default;
    ~Buffer() = default;

    /// Crea la caja y la llena con los datos de una figura 3D.
    /// Toma los puntos o las conexiones de la malla y los copia a la
    /// tarjeta de video, listos para dibujar.
    /// device: La tarjeta de video con la que se va a trabajar.
    /// mesh: La figura 3D de donde se sacan los datos.
    /// bindFlag: Indica para que se usara la caja.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        init(Device& device, const MeshComponent& mesh, unsigned int bindFlag);

    /// Crea una caja vacia de un tamano determinado.
    /// Sirve para datos que cambian seguido y que se llenaran
    /// despues con update().
    /// device: La tarjeta de video con la que se va a trabajar.
    /// ByteWidth: El tamano de la caja, medido en bytes.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        init(Device& device, unsigned int ByteWidth);

    /// Actualiza los datos almacenados dentro de la caja en la tarjeta de video.
    /// deviceContext: El mensajero que envia las ordenes a la tarjeta de video.
    /// pDstResource: Recurso de destino que se va a actualizar.
    /// DstSubresource: Indice del subrecurso de destino.
    /// pDstBox: Region del recurso donde se copiaran los datos.
    /// pSrcData: Puntero a los datos nuevos que se van a copiar.
    /// SrcRowPitch: Tamano en bytes de una fila de datos.
    /// SrcDepthPitch: Tamano en bytes de una capa de profundidad.
    void
        update(
            DeviceContext& deviceContext,
            ID3D11Resource* pDstResource,
            unsigned int DstSubresource,
            const D3D11_BOX* pDstBox,
            const void* pSrcData,
            unsigned int SrcRowPitch,
            unsigned int SrcDepthPitch
        );

    /// Le dice a la tarjeta de video que use esta caja para dibujar.
    /// deviceContext: El mensajero que envia las ordenes a la tarjeta de video.
    /// StartSlot: El numero de lugar donde se va a colocar la caja.
    /// NumBuffers: Cuantas cajas se van a colocar.
    /// setPixelShader: Si es verdadero, la caja tambien se pone a disposicion
    /// del programa que pinta los colores.
    /// format: Forma en que estan escritos los datos.
    void
        render(
            DeviceContext& deviceContext,
            unsigned int StartSlot,
            unsigned int NumBuffers,
            bool setPixelShader = false,
            DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN
        );

    /// Libera la memoria de la caja en la tarjeta de video.
    void
        destroy();

    /// Fabrica la caja en la tarjeta de video a partir de una descripcion.
    /// Es el paso de bajo nivel que usan los dos init() para crear la caja.
    /// device: La tarjeta de video con la que se va a trabajar.
    /// desc: Descripcion de las propiedades del buffer.
    /// initData: Los datos con los que se llena al inicio.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        createBuffer(
            Device& device,
            D3D11_BUFFER_DESC& desc,
            D3D11_SUBRESOURCE_DATA* initData
        );

    /// Devuelve la caja de la tarjeta de video para usarla directamente.
    /// Devuelve un puntero a la caja.
    ID3D11Buffer*
        getBuffer() const
    {
        return m_buffer;
    }

public:
    ID3D11Buffer* m_buffer = nullptr;

private:
    unsigned int m_stride = 0;
    unsigned int m_offset = 0;
    unsigned int m_bindFlag = 0;
};