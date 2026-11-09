#pragma once

// C++ library
#include <array>
#include <string>

// Proyect Headers
#include "Engine/Prerequisites.h"

class Device;
class DeviceContext;

/// Texture2D funciona como una imagen que vive en la tarjeta de video.
/// Sirve para varias cosas: puede ser una foto o dibujo que cubre un
/// objeto (una textura), la imagen donde se va a pintar la escena, o
/// la imagen que guarda que tan lejos esta cada cosa. Esta clase crea
/// esa imagen, la entrega a la tarjeta y la borra al terminar.
class Texture2D
{
public:
    Texture2D() noexcept = default;
    ~Texture2D() noexcept;

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    Texture2D(Texture2D&&) = delete;
    Texture2D& operator=(Texture2D&&) = delete;

    /// Crea la imagen cargandola desde un archivo.
    /// device: Fabricante de la tarjeta de video.
    /// textureName: Nombre del archivo de imagen.
    /// extensionType: Formato de extension del archivo.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        init(
            Device& device,
            const std::string& textureName,
            ExtensionType extensionType
        );

    /// Crea una imagen vacia de un tamano determinado.
    /// Sirve, por ejemplo, para crear la imagen donde se va a dibujar
    /// o la imagen que guarda las distancias.
    /// device: Fabricante de la tarjeta de video.
    /// width: Ancho de la imagen, en pixeles.
    /// height: Alto de la imagen, en pixeles.
    /// Format: Como se guarda el color de cada pixel.
    /// BindFlags: Para que se usara la imagen.
    /// sampleCount: Cuantas muestras se toman por pixel para suavizar bordes.
    /// qualityLevels: Nivel de calidad de ese suavizado.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        init(
            Device& device,
            unsigned int width,
            unsigned int height,
            DXGI_FORMAT Format,
            unsigned int BindFlags,
            unsigned int sampleCount = 1,
            unsigned int qualityLevels = 0
        );

    /// Crea una imagen nueva con las mismas caracteristicas de
    /// otra imagen, pero con otro formato de color.
    /// device: Fabricante de la tarjeta de video.
    /// textureRef: La imagen que se toma como modelo.
    /// format: Como se guarda el color de cada pixel en la imagen nueva.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        init(Device& device, Texture2D& textureRef, DXGI_FORMAT format);

    /// Carga una imagen desde una ruta completa del disco.
    /// device: Fabricante de la tarjeta de video.
    /// fullPath: Ubicacion completa del archivo, con todo y carpetas.
    /// texture: La imagen donde se guarda lo cargado.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        InitTextureFromImage(
            Device& device,
            const std::string& fullPath,
            Texture2D& texture
        );

    /// Metodo para renderizar la textura.
    void
        render(
            DeviceContext& deviceContext,
            unsigned int StartSlot,
            unsigned int NumViews
        );

    /// Libera los recursos de la textura.
    void
        destroy();

    /// Crea un cubo de imagenes a partir de seis fotos.
    /// Un cubemap es una imagen formada por seis caras, como un dado.
    /// Se usa mucho para crear cielos o fondos que rodean toda la escena.
    /// device: Fabricante de la tarjeta de video.
    /// deviceContext: Envia las ordenes a la tarjeta de video.
    /// facePaths: Las seis rutas de las imagenes, una por cada cara del cubo.
    /// generateMips: Si es verdadero, se crean versiones mas pequenas de la
    /// imagen para que se vea mejor de lejos.
    /// Devuelve un resultado que indica si todo salio bien o hubo un error.
    HRESULT
        CreateCubemap(
            Device& device,
            DeviceContext& deviceContext,
            const std::array<std::string, 6>& facePaths,
            bool generateMips /*= false*/
        );

    /// Crea una ventana de lectura para ver una sola cara del cubo de imagenes.
    /// Sirve para que un programa de dibujo pueda leer solo una de las
    /// seis caras, sin necesidad de usar todo el cubo.
    /// device: Fabricante de la tarjeta de video.
    /// cubemapTex: El cubo de imagenes completo.
    /// format: Como se guarda el color de cada pixel.
    /// faceIndex: Numero de la cara que se quiere ver.
    /// mipLevels: Cuantas versiones reducidas de la imagen se pueden usar.
    /// Devuelve la ventana de lectura creada, o nulo si algo fallo.
    /// Quien la reciba debe liberarla cuando ya no la necesite.
    ID3D11ShaderResourceView*
        CreateCubemapFaceSRV(
            ID3D11Device* device,
            ID3D11Texture2D* cubemapTex,
            DXGI_FORMAT format,
            unsigned int faceIndex,
            unsigned int mipLevels = 1
        )
    {
        D3D11_SHADER_RESOURCE_VIEW_DESC d{};
        d.Format = format;
        d.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
        d.Texture2DArray.MostDetailedMip = 0;
        d.Texture2DArray.MipLevels = mipLevels;
        d.Texture2DArray.FirstArraySlice = faceIndex;
        d.Texture2DArray.ArraySize = 1;

        ID3D11ShaderResourceView* srv = nullptr;
        if (FAILED(device->CreateShaderResourceView(cubemapTex, &d, &srv)))
        {
            return nullptr;
        }

        return srv;
    }

    /// Entrega la imagen real guardada en la tarjeta de video.
    ID3D11Texture2D*
        GetTexture() const noexcept
    {
        return m_texture;
    }

    /// Entrega la direccion donde vive la imagen.
    /// Se usa cuando otra funcion necesita guardar ahi una imagen
    /// recien creada, por ejemplo, al obtener la imagen de la pantalla.
    /// Devuelve la direccion donde se guarda la imagen.
    ID3D11Texture2D**
        GetTextureAddress() noexcept
    {
        return &m_texture;
    }

public:
    ID3D11Texture2D* m_texture = nullptr;
    ID3D11ShaderResourceView* m_textureFromImg = nullptr;
    std::string m_textureName;
};