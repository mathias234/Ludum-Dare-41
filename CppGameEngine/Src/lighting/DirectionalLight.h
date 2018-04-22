//
// Created by matha on 08/03/2018.
//

#pragma once

#include "../Common.h"
#include "../Shader.h"

class DirectionalLight {
public:
    DirectionalLight();
    DirectionalLight(Vector3f color, Vector3f direction, float ambientIntensity, float diffuseIntensity);


    void Bind(Shader& shader) const;

    const Vector3f &GetColor() const;
    void SetColor(const Vector3f &m_Color);

    const Vector3f GetDirection() const;

    const Vector3f &GetRotation() const;
    void SetRotation(const Vector3f &m_Rotation);

    float GetAmbientIntensity() const;
    void SetAmbientIntensity(float m_AmbientIntensity);

    float GetDiffuseIntensity() const;
    void SetDiffuseIntensity(float m_DiffuseIntensity);

    Matrix4f GetLightMatrix() const;



private:
    Vector3f m_Color;
    Vector3f m_Rotation;
    float m_AmbientIntensity;
    float m_DiffuseIntensity;
};

