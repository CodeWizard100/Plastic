#include "plastic_model_class.h"
#include <iostream>

ModelClass::ModelClass()
{
    m_vertexBuffer = 0;
    m_indexBuffer = 0;
    m_worldMatrix = XMMatrixIdentity(); // Initialize to identity
}

ModelClass::ModelClass(const ModelClass& other)
{
    // You could implement deep copy if needed, for now just initialize empty
    m_vertexBuffer = 0;
    m_indexBuffer = 0;
    m_worldMatrix = XMMatrixIdentity();
}

ModelClass::~ModelClass()
{
    Shutdown();
}

bool ModelClass::Initialize(ID3D11Device* device)
{
    bool result;

    // Initialize the vertex and index buffers.
    result = InitializeBuffers(device);
    if(!result)
    {
        return false;
    }

    return true;
}

void ModelClass::Shutdown()
{
    // Shutdown the vertex and index buffers.
    ShutdownBuffers();

    return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
    // Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
    RenderBuffers(deviceContext);

    return;
}

int ModelClass::GetIndexCount()
{
    return m_indexCount;
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
    VertexType* vertices;
    unsigned long* indices;
    D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
    D3D11_SUBRESOURCE_DATA vertexData, indexData;
    HRESULT result;

// Set the number of vertices in the vertex array.
m_vertexCount = 8;

// Set the number of indices in the index array.
m_indexCount = 36;

    // Create the vertex array.
    vertices = new VertexType[m_vertexCount];
    if(!vertices)
    {
        return false;
    }

    // Create the index array.
    indices = new unsigned long[m_indexCount];
    if(!indices)
    {
        delete[] vertices;
        return false;
    }

m_vertexCount = 8;
m_indexCount = 36;

// Define 8 corners of the cube
vertices[0].position = XMFLOAT3(-1.0f, -1.0f, -1.0f); // 0: left-bottom-back
vertices[1].position = XMFLOAT3(-1.0f,  1.0f, -1.0f); // 1: left-top-back
vertices[2].position = XMFLOAT3( 1.0f,  1.0f, -1.0f); // 2: right-top-back
vertices[3].position = XMFLOAT3( 1.0f, -1.0f, -1.0f); // 3: right-bottom-back
vertices[4].position = XMFLOAT3(-1.0f, -1.0f,  1.0f); // 4: left-bottom-front
vertices[5].position = XMFLOAT3(-1.0f,  1.0f,  1.0f); // 5: left-top-front
vertices[6].position = XMFLOAT3( 1.0f,  1.0f,  1.0f); // 6: right-top-front
vertices[7].position = XMFLOAT3( 1.0f, -1.0f,  1.0f); // 7: right-bottom-front

// Set all vertex colors to green for example
for (int i = 0; i < 8; i++) {
    vertices[i].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
}

// Indices for the 12 triangles (2 per face)
unsigned long inds[36] = {
    // Back face
    0,1,2,
    0,2,3,

    // Front face
    4,6,5,
    4,7,6,

    // Left face
    4,5,1,
    4,1,0,

    // Right face
    3,2,6,
    3,6,7,

    // Top face
    1,5,6,
    1,6,2,

    // Bottom face
    4,0,3,
    4,3,7
};

for(int i = 0; i < 36; i++) {
    indices[i] = inds[i];
}

    // Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
    vertexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
    vertexData.SysMemPitch = 0;
    vertexData.SysMemSlicePitch = 0;

    // Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
    if(FAILED(result))
    {
        delete[] vertices;
        delete[] indices;
        return false;
    }

    // Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
    indexBufferDesc.StructureByteStride = 0;

    // Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
    indexData.SysMemPitch = 0;
    indexData.SysMemSlicePitch = 0;

    // Create the index buffer.
    result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
    if(FAILED(result))
    {
        delete[] vertices;
        delete[] indices;
        return false;
    }

    // Release the arrays now that the vertex and index buffers have been created and loaded.
    delete[] vertices;
    delete[] indices;

    return true;
}

void ModelClass::ShutdownBuffers()
{
    // Release the index buffer.
    if(m_indexBuffer)
    {
        m_indexBuffer->Release();
        m_indexBuffer = 0;
    }

    // Release the vertex buffer.
    if(m_vertexBuffer)
    {
        m_vertexBuffer->Release();
        m_vertexBuffer = 0;
    }

    return;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
    unsigned int stride;
    unsigned int offset;

    // Set vertex buffer stride and offset.
    stride = sizeof(VertexType); 
    offset = 0;

    // Set the vertex buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
    deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    return;
}

XMMATRIX ModelClass::GetWorldMatrix() const
{
    return m_worldMatrix;
}

void ModelClass::SetWorldMatrix(const XMMATRIX& matrix)
{
    m_worldMatrix = matrix;
}
