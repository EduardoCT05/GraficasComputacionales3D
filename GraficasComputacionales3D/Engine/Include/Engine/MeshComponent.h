#pragma once

// C++ library
#include <string>
#include <vector>

// Proyect Headers
#include "Engine/Prerequisites.h"

/// Guarda la forma de un objeto 3D.
/// Una malla es como una figura armada con muchos triangulos pequenos.
/// Esta clase almacena todo lo necesario para dibujar esa figura:
/// sus puntos, como se conectan y donde esta colocada.
class MeshComponent
{
public:
    /// Crea una malla vacia, sin puntos ni conexiones todavia.
    MeshComponent() : m_numVertex(0), m_numIndex(0)
    {}

    /// Nombre de la malla, para identificarla facilmente.
    std::string m_name;

    /// Posicion, giro y tamano de la malla respecto a su objeto.
    /// Por defecto no mueve, no gira y no cambia el tamano de nada
    /// (es decir, la figura queda tal cual fue creada).
    DirectX::XMFLOAT4X4 m_localTransform = DirectX::XMFLOAT4X4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );

    /// Lista de vertices que conforman la malla
    std::vector<Vertex> m_vertex;

    /// Lista de indices que conectan los vertices
    std::vector<unsigned int> m_index;

    /// Cantidad total de vertices
    int m_numVertex;

    /// Cantidad total de indices
    int m_numIndex;
};