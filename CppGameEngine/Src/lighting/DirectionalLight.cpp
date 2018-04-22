//
// Created by matha on 08/03/2018.
//

#include "../Common.h"

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vector3f color, Vector3f rotation, float ambientIntensity, float diffuseIntensity) {
    m_Color = color;

    m_Rotation = rotation;
    m_AmbientIntensity = ambientIntensity;
    m_DiffuseIntensity = diffuseIntensity;
}

DirectionalLight::DirectionalLight() = default;

void DirectionalLight::Bind(Shader &shader) const {
    shader.SetFloat3("u_DirectionalLight.Color", m_Color);
    shader.SetFloat3("u_DirectionalLight.Direction", GetDirection());
    shader.SetFloat("u_DirectionalLight.AmbientIntensity", m_AmbientIntensity);
    shader.SetFloat("u_DirectionalLight.DiffuseIntensity", m_DiffuseIntensity);
}

const Vector3f &DirectionalLight::GetColor() const {
    return m_Color;
}

void DirectionalLight::SetColor(const Vector3f &m_Color) {
    DirectionalLight::m_Color = m_Color;
}

const Vector3f DirectionalLight::GetDirection() const {
    Quaternion finalOrientation = Quaternion(Vector3f(-(m_Rotation.x+glm::radians(180.0f)), -m_Rotation.y, m_Rotation.z));


    Vector3f forwardDirection = finalOrientation * Vector3f(0,0,1);

    return glm::normalize(forwardDirection);
}


const Vector3f &DirectionalLight::GetRotation() const {
    return m_Rotation;
}

void DirectionalLight::SetRotation(const Vector3f &rotation) {
    m_Rotation = rotation;
}


float DirectionalLight::GetAmbientIntensity() const {
    return m_AmbientIntensity;
}

void DirectionalLight::SetAmbientIntensity(float m_AmbientIntensity) {
    DirectionalLight::m_AmbientIntensity = m_AmbientIntensity;
}

float DirectionalLight::GetDiffuseIntensity() const {
    return m_DiffuseIntensity;
}

void DirectionalLight::SetDiffuseIntensity(float m_DiffuseIntensity) {
    DirectionalLight::m_DiffuseIntensity = m_DiffuseIntensity;
}

Matrix4f DirectionalLight::GetLightMatrix() const {
    Matrix4f lightMatrix;
    lightMatrix = glm::rotate(lightMatrix, GetRotation().x, {1, 0, 0});
    lightMatrix = glm::rotate(lightMatrix, GetRotation().y, {0, 1, 0});
    lightMatrix = glm::rotate(lightMatrix, GetRotation().z, {0, 0, 1});

    return lightMatrix;
}

