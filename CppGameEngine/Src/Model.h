//
// Created by matha on 08/03/2018.
//
#pragma once

#include <vector>
#include <map>
#include "Common.h"
#include "Texture.h"
#include "Shader.h"

struct Vertex {
public:
    Vector3f Position;
    Vector3f Normal;
    Vector2f TexCoord;
    Vector3f Tangent;
    Vertex(Vector3f position, Vector3f normal, Vector2f texCoord, Vector3f Tangent);
};

struct Material {
public:
    Vector2f DiffuseTiling;
    Texture* Diffuse;
    Texture* NormalMap;
    Texture* SpecMap;

    Material();
};

struct Submesh {
public:
    std::string name;
    unsigned int m_Vbo, m_Ibo, m_IndexCount;
    Material* Material;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;


    void RecalculateTangents();
};

class Model {
private:
    static std::map<std::string, Model*> m_ModelCache;
    std::vector<Submesh*> m_Submeshes;

public:
    ~Model();

    static Model* GetModel(const std::string& path);

    void Draw(Shader& shader) const;

    Material* GetMaterial(int submesh);
    Submesh* GetSubmesh(int submesh);

    int SubmeshCount();
};

