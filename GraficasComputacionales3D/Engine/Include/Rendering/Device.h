#pragma once

// Proyect Headers
#include "Engine/Prerequisites.h"

/// La clase funciona como un fabricante de piezas para la tarjeta de video.
/// Para dibujar en pantalla, la tarjeta de video necesita muchas piezas:
/// imagenes, cajas de datos y programas de dibujo. Esta clase es la
/// encargada de fabricar todas esas piezas; casi todo lo que se crea en
/// el motor pasa primero por aqui.
class Device
{
public:
    Device() = default;
    ~Device();

    /// Prepara el fabricante para empezar a trabajar.
    void
        init();

    /// Libera el fabricante y todo el espacio que usaba.
    /// Hay que llamarla al cerrar el programa.
    void
        destroy();

    /// Entrega el fabricante real de la tarjeta de video.
    /// Devuelve el puntero al dispositivo de DirectX.
    ID3D11Device*
        getDevice() const noexcept
    {
        return m_device;
    }

    /// Entrega la direccion donde vive el fabricante.
    /// Se usa cuando otra funcion necesita guardar ahi al fabricante recien
    /// creado, por ejemplo, al arrancar DirectX.
    /// Devuelve la direccion donde se guarda el fabricante.
    ID3D11Device**
        getDeviceAddress() noexcept
    {
        return &m_device;
    }

    /// Crea una vista sobre una imagen.
    /// Es la superficie donde la tarjeta pinta lo que luego se ve en pantalla.
    /// pResource: Imagen sobre la que se va a pintar.
    /// pDesc: Descripcion de como se va a usar.
    /// ppRTView: Aqui se guarda la superficie creada.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        CreateRenderTargetView(
            ID3D11Resource* pResource,
            const D3D11_RENDER_TARGET_VIEW_DESC* pDesc,
            ID3D11RenderTargetView** ppRTView
        );

    /// Crea una imagen en la memoria de la tarjeta de video.
    /// pDesc: Caracteristicas de la imagen, tamano, formato y uso.
    /// pInitialData: Contenido inicial de la imagen.
    /// ppTexture2D: Aqui se guarda la imagen creada.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        CreateTexture2D(
            const D3D11_TEXTURE2D_DESC* pDesc,
            const D3D11_SUBRESOURCE_DATA* pInitialData,
            ID3D11Texture2D** ppTexture2D
        );

    /// Crea la vista que guarda que tan lejos o cerca esta cada cosa.
    /// pResource: Imagen donde se guarda esa informacion de distancia.
    /// pDesc: Descripcion de como se va a usar.
    /// ppDepthStencilView: Aqui se guarda la vista creada.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        CreateDepthStencilView(
            ID3D11Resource* pResource,
            D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc,
            ID3D11DepthStencilView** ppDepthStencilView
        );

    /// Crea un programa de vertices a partir del bytecode compilado.
    HRESULT
        CreateVertexShader(
            const void* pShaderBytecode,
            unsigned int BytecodeLength,
            ID3D11ClassLinkage* pClassLinkage,
            ID3D11VertexShader** ppVertexShader
        );

    /// Crea un programa de pixeles a partir del bytecode compilado.
    HRESULT
        CreatePixelShader(
            const void* pShaderBytecode,
            unsigned int BytecodeLength,
            ID3D11ClassLinkage* pClassLinkage,
            ID3D11PixelShader** ppPixelShader
        );

    /// Crea el diseno de entrada que describe la estructura de los vertices.
    HRESULT
        CreateInputLayout(
            const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs,
            unsigned int NumElements,
            const void* pShaderBytecodeWithInputSignature,
            unsigned int BytecodeLength,
            ID3D11InputLayout** ppInputLayout
        );

    /// Crea una caja de datos en la memoria de la tarjeta de video.
    /// pDesc: Descripcion de la caja de datos.
    /// pInitialData: Datos con los que se llena al inicio.
    /// ppBuffer: Aqui se guarda la caja creada.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        CreateBuffer(
            const D3D11_BUFFER_DESC* pDesc,
            const D3D11_SUBRESOURCE_DATA* pInitialData,
            ID3D11Buffer** ppBuffer
        );

    /// Crea la configuracion del estado de rasterizado.
    HRESULT
        CreateRasterizerState(
            const D3D11_RASTERIZER_DESC* pRasterizerDesc,
            ID3D11RasterizerState** ppRasterizerState
        );

private:
    ID3D11Device* m_device = nullptr;
    D3D_FEATURE_LEVEL* m_featureLevels = nullptr;
};