#include "Rendering/DeviceContext.h"

/// Se implementan las funciones de la clase DeviceContext,
/// que es responsable de dar ordenes a la tarjeta de video para dibujar en pantalla.

/// Destructor de la clase DeviceContext.
DeviceContext::~DeviceContext()
{
    destroy();
}

/// Libera el contexto de dispositivo DirectX.
void
DeviceContext::destroy()
{
    if (m_deviceContext)
    {
        m_deviceContext->ClearState();
        m_deviceContext->Release();
        SafeRelease(m_deviceContext);
    }
}

/// Entrega al director asegurandose de que ya exista.
ID3D11DeviceContext&
DeviceContext::requireContext() const noexcept
{
    if (!m_deviceContext)
    {
        ERROR("DeviceContext", "RequireContext", "Device context is not initialized.");
    }

    return *m_deviceContext;
}

/// Pinta toda la superficie de dibujo de un solo color.
void
DeviceContext::ClearRenderTargetView(
    ID3D11RenderTargetView* pRenderTargetView,
    const float colorRGBA[4]
) noexcept
{
    if (!pRenderTargetView || !colorRGBA)
    {
        ERROR(
            "DeviceContext",
            "ClearRenderTargetView",
            "Invalid render target view or color parameters."
        );
        return;
    }

    requireContext().ClearRenderTargetView(pRenderTargetView, colorRGBA);
}

/// Borra la informacion de profundidad y plantilla.
void
DeviceContext::ClearDepthStencilView(
    ID3D11DepthStencilView* pDepthStencilView,
    unsigned int clearFlags,
    float depth,
    unsigned int stencil
) noexcept
{
    if (!pDepthStencilView)
    {
        ERROR(
            "DeviceContext",
            "ClearDepthStencilView",
            "Invalid depth-stencil view parameter."
        );
        return;
    }

    requireContext().ClearDepthStencilView(
        pDepthStencilView,
        clearFlags,
        depth,
        stencil
    );
}

/// Le dice a la tarjeta donde debe dibujar.
void
DeviceContext::OMSetRenderTargets(
    unsigned int numViews,
    ID3D11RenderTargetView* const* ppRenderTargetViews,
    ID3D11DepthStencilView* pDepthStencilView
) noexcept
{
    if (!ppRenderTargetViews || numViews == 0)
    {
        ERROR(
            "DeviceContext",
            "OMSetRenderTargets",
            "Invalid render target view parameters."
        );
        return;
    }

    requireContext().OMSetRenderTargets(
        numViews,
        ppRenderTargetViews,
        pDepthStencilView
    );
}

/// Define en que parte de la pantalla se va a dibujar.
void
DeviceContext::RSSetViewports(
    unsigned int numViewports,
    const D3D11_VIEWPORT* pViewports
) noexcept
{
    if (!pViewports || numViewports == 0)
    {
        ERROR("DeviceContext", "RSSetViewports", "Invalid viewport parameters.");
        return;
    }
    requireContext().RSSetViewports(numViewports, pViewports);
}

/// Entrega imagenes al programa que pinta los colores.
void
DeviceContext::PSSetShaderResources(
    unsigned int StartSlot,
    unsigned int NumViews,
    ID3D11ShaderResourceView* const* ppShaderResourceViews
)
{
    if (!ppShaderResourceViews || NumViews == 0)
    {
        ERROR(
            "DeviceContext",
            "PSSetShaderResources",
            "Invalid shader resource view parameters."
        );
        return;
    }

    requireContext().PSSetShaderResources(
        StartSlot,
        NumViews,
        ppShaderResourceViews
    );
}

/// Define el estado de rasterizado activo.
void
DeviceContext::RSSetState(ID3D11RasterizerState* pRasterizerState) noexcept
{
    if (!pRasterizerState)
    {
        ERROR("DeviceContext", "RSSetState", "Invalid rasterizer state parameter.");
        return;
    }
    requireContext().RSSetState(pRasterizerState);
}

/// Define el diseno de entrada para los vertices.
void
DeviceContext::IASetInputLayout(ID3D11InputLayout* pInputLayout) noexcept
{
    if (!pInputLayout)
    {
        ERROR(
            "DeviceContext",
            "IASetInputLayout",
            "Invalid input layout parameter."
        );
        return;
    }
    requireContext().IASetInputLayout(pInputLayout);
}

/// Define como se conectan los vertices para formar primitivas.
void
DeviceContext::IASetPrimitiveTopology(
    D3D11_PRIMITIVE_TOPOLOGY topology
) noexcept
{
    requireContext().IASetPrimitiveTopology(topology);
}

/// Entrega a la tarjeta las cajas con los puntos de la figura.
void
DeviceContext::IASetVertexBuffers(
    unsigned int startSlot,
    unsigned int numBuffers,
    ID3D11Buffer* const* ppVertexBuffers,
    const unsigned int* pStrides,
    const unsigned int* pOffsets
) noexcept
{
    if (!ppVertexBuffers || numBuffers == 0)
    {
        ERROR(
            "DeviceContext",
            "IASetVertexBuffers",
            "Invalid vertex buffer parameters."
        );
        return;
    }

    requireContext().IASetVertexBuffers(
        startSlot,
        numBuffers,
        ppVertexBuffers,
        pStrides,
        pOffsets
    );
}

/// Entrega a la tarjeta la caja que dice en que orden unir los puntos.
void
DeviceContext::IASetIndexBuffer(
    ID3D11Buffer* pIndexBuffer,
    DXGI_FORMAT format,
    unsigned int offset
) noexcept
{
    if (!pIndexBuffer)
    {
        ERROR(
            "DeviceContext",
            "IASetIndexBuffer",
            "Invalid index buffer parameter."
        );
        return;
    }

    requireContext().IASetIndexBuffer(pIndexBuffer, format, offset);
}

/// Elige el programa que procesa los vertices de la figura.
void
DeviceContext::VSSetShader(
    ID3D11VertexShader* pVertexShader,
    ID3D11ClassInstance* const* ppClassInstances,
    unsigned int numClassInstances
) noexcept
{
    if (!pVertexShader)
    {
        ERROR("DeviceContext", "VSSetShader", "Invalid vertex shader parameter.");
        return;
    }
    requireContext().VSSetShader(
        pVertexShader,
        ppClassInstances,
        numClassInstances
    );
}

/// Elige el programa que decide de que color se pinta cada pixel.
void
DeviceContext::PSSetShader(
    ID3D11PixelShader* pPixelShader,
    ID3D11ClassInstance* const* ppClassInstances,
    unsigned int numClassInstances
) noexcept
{
    if (!pPixelShader)
    {
        ERROR("DeviceContext", "PSSetShader", "Invalid pixel shader parameter.");
        return;
    }
    requireContext().PSSetShader(
        pPixelShader,
        ppClassInstances,
        numClassInstances
    );
}

/// Asigna las cajas de constantes para el programa de vertices.
void
DeviceContext::VSSetConstantBuffers(
    unsigned int startSlot,
    unsigned int numBuffers,
    ID3D11Buffer* const* ppConstantBuffers
) noexcept
{
    if (!ppConstantBuffers || numBuffers == 0)
    {
        ERROR(
            "DeviceContext",
            "VSSetConstantBuffers",
            "Invalid constant buffer parameters."
        );
        return;
    }

    requireContext().VSSetConstantBuffers(
        startSlot,
        numBuffers,
        ppConstantBuffers
    );
}

/// Cambia el contenido de una caja o imagen de la tarjeta de video.
void
DeviceContext::UpdateSubresource(
    ID3D11Resource* pDstResource,
    unsigned int dstSubresource,
    const D3D11_BOX* pDstBox,
    const void* pSrcData,
    unsigned int srcRowPitch,
    unsigned int srcDepthPitch
) noexcept
{
    if (!pDstResource || !pSrcData)
    {
        ERROR(
            "DeviceContext",
            "UpdateSubresource",
            "Invalid destination resource or source data parameters."
        );
        return;
    }

    requireContext().UpdateSubresource(
        pDstResource,
        dstSubresource,
        pDstBox,
        pSrcData,
        srcRowPitch,
        srcDepthPitch
    );
}

/// Dibuja la figura usando la lista de indices.
void
DeviceContext::DrawIndexed(
    unsigned int indexCount,
    unsigned int startIndexLocation,
    int baseVertexLocation
) noexcept
{
    if (indexCount == 0)
    {
        ERROR(
            "DeviceContext",
            "DrawIndexed",
            "Index count must be greater than zero."
        );
        return;
    }

    requireContext().DrawIndexed(
        indexCount,
        startIndexLocation,
        baseVertexLocation
    );
}