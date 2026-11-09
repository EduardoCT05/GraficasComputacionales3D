#pragma once

// Proyect Headers
#include "Engine/Prerequisites.h"

/// Controla lo que contiene la tarjeta de video.
/// Si el Device fabrica las piezas, el DeviceContext es quien da las
/// ordenes: que pintar, con que colores, con que programas y en que
/// orden. Cada vez que el motor dibuja algo en pantalla, le da una serie
/// de instrucciones a esta clase.
class DeviceContext
{
public:
    DeviceContext() = default;
    ~DeviceContext();

    /// Prepara al director para empezar a dar ordenes.
    void
        init();

    /// Libera al director y todo el espacio que usaba.
    /// Hay que llamarla al cerrar el programa.
    void
        destroy();

    /// Entrega el puntero al director de la tarjeta de video.
    ID3D11DeviceContext*
        getDeviceContext() const noexcept
    {
        return m_deviceContext;
    }

    /// Entrega la direccion donde vive el director.
    /// Se usa cuando otra funcion necesita guardar ahi al director
    /// recien creado, por ejemplo, al arrancar DirectX.
    /// Devuelve la direccion donde se guarda el director.
    ID3D11DeviceContext**
        getDeviceContextAddress() noexcept
    {
        return &m_deviceContext;
    }

    /// Entrega al director asegurandose de que ya exista.
    /// A diferencia de getDeviceContext(), esta funcion espera que el
    /// director ya este listo, asi que no devuelve nulo.
    /// Devuelve la referencia al director de la tarjeta de video.
    ID3D11DeviceContext&
        requireContext() const noexcept;

    /// Pinta toda la superficie de dibujo de un solo color.
    /// Es como limpiar el pizarron antes de dibujar el siguiente cuadro.
    /// pRenderTargetView: La superficie que se quiere limpiar.
    /// colorRGBA: El color de fondo (rojo, verde, azul y transparencia,
    /// cada uno entre 0 y 1).
    void
        ClearRenderTargetView(
            ID3D11RenderTargetView* pRenderTargetView,
            const float colorRGBA[4]
        ) noexcept;

    /// Borra la informacion de que tan lejos esta cada cosa.
    /// Se hace al inicio de cada cuadro para empezar desde cero.
    /// pDepthStencilView: La vista de distancias que se limpia.
    /// clearFlags: Que se quiere borrar.
    /// depth: Valor de distancia con el que se rellena.
    /// stencil: Valor con el que se rellena la plantilla.
    void
        ClearDepthStencilView(
            ID3D11DepthStencilView* pDepthStencilView,
            unsigned int clearFlags,
            float depth,
            unsigned int stencil
        ) noexcept;

    /// Le dice a la tarjeta donde debe dibujar.
    /// numViews: Cuantas superficies de dibujo se usan.
    /// ppRenderTargetViews: Las superficies donde se va a pintar.
    /// pDepthStencilView: La vista que lleva el control de distancias.
    void
        OMSetRenderTargets(
            unsigned int numViews,
            ID3D11RenderTargetView* const* ppRenderTargetViews,
            ID3D11DepthStencilView* pDepthStencilView
        ) noexcept;

    /// Define en que parte de la pantalla se va a dibujar.
    /// Normalmente se usa toda la ventana, pero tambien puede ser solo
    /// un pedazo.
    /// numViewports: Cuantas zonas de dibujo se definen.
    /// pViewports: Las zonas con su posicion y su tamano.
    void
        RSSetViewports(
            unsigned int numViewports,
            const D3D11_VIEWPORT* pViewports
        ) noexcept;

    /// Entrega imagenes al programa que pinta los colores.
    /// Asi ese programa puede usar texturas.
    /// StartSlot: Primer lugar donde se colocan las imagenes.
    /// NumViews: Cuantas imagenes se entregan.
    /// ppShaderResourceViews: Las imagenes que se entregan.
    void
        PSSetShaderResources(
            unsigned int StartSlot,
            unsigned int NumViews,
            ID3D11ShaderResourceView* const* ppShaderResourceViews
        );

    /// Define el estado de rasterizado activo.
    void
        RSSetState(ID3D11RasterizerState* pRasterizerState) noexcept;

    /// Define el diseno de entrada para los vertices.
    void
        IASetInputLayout(ID3D11InputLayout* pInputLayout) noexcept;

    /// Define como se conectan los vertices para formar primitivas.
    void
        IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology) noexcept;

    /// Entrega a la tarjeta las cajas con los puntos de la figura.
    /// startSlot: Primer lugar donde se colocan las cajas.
    /// numBuffers: Cuantas cajas se entregan.
    /// ppVertexBuffers: Las cajas con los puntos.
    /// pStrides: Tamano en bytes de cada vertice.
    /// pOffsets: Cuantos bytes saltar al inicio de cada caja antes de leer.
    void
        IASetVertexBuffers(
            unsigned int startSlot,
            unsigned int numBuffers,
            ID3D11Buffer* const* ppVertexBuffers,
            const unsigned int* pStrides,
            const unsigned int* pOffsets
        ) noexcept;

    /// Entrega a la tarjeta la caja que dice en que orden unir los puntos.
    /// pIndexBuffer: La caja con ese orden.
    /// format: Tamano de cada numero de la lista.
    /// offset: Cuantos bytes saltar al inicio de la caja antes de leer.
    void
        IASetIndexBuffer(
            ID3D11Buffer* pIndexBuffer,
            DXGI_FORMAT format,
            unsigned int offset
        ) noexcept;

    /// Elige el programa que procesa los vertices de la figura.
    void
        VSSetShader(
            ID3D11VertexShader* pVertexShader,
            ID3D11ClassInstance* const* ppClassInstances = nullptr,
            unsigned int numClassInstances = 0
        ) noexcept;

    /// Elige el programa que decide de que color se pinta cada
    /// pedacito de la figura.
    /// pPixelShader: El programa que se quiere usar.
    /// ppClassInstances: Opcion avanzada; normalmente va vacia.
    /// numClassInstances: Cantidad de opciones avanzadas.
    void
        PSSetShader(
            ID3D11PixelShader* pPixelShader,
            ID3D11ClassInstance* const* ppClassInstances = nullptr,
            unsigned int numClassInstances = 0
        ) noexcept;

    /// Asigna las cajas de constantes para el programa de vertices.
    void
        VSSetConstantBuffers(
            unsigned int startSlot,
            unsigned int numBuffers,
            ID3D11Buffer* const* ppConstantBuffers
        ) noexcept;

    /// Cambia el contenido de una caja o imagen de la tarjeta de
    /// video por datos nuevos.
    /// pDstResource: La caja o imagen que se quiere actualizar.
    /// dstSubresource: Que parte se actualiza.
    /// pDstBox: Region de destino.
    /// pSrcData: Los datos nuevos que se copian.
    /// srcRowPitch: Tamano de cada fila de datos.
    /// srcDepthPitch: Tamano de cada capa de datos.
    void
        UpdateSubresource(
            ID3D11Resource* pDstResource,
            unsigned int dstSubresource,
            const D3D11_BOX* pDstBox,
            const void* pSrcData,
            unsigned int srcRowPitch,
            unsigned int srcDepthPitch
        ) noexcept;

    /// Dibuja la figura usando la lista que indica en que orden unir los puntos.
    /// Es la orden final: todo lo anterior prepara la escena y esta
    /// funcion hace que realmente aparezca en pantalla.
    void
        DrawIndexed(
            unsigned int indexCount,
            unsigned int startIndexLocation = 0,
            int baseVertexLocation = 0
        ) noexcept;

private:
    /// El director real de la tarjeta de video.
    /// Empieza vacio (nulo) y se llena al llamar a init().
    ID3D11DeviceContext* m_deviceContext = nullptr;
};