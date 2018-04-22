//
// Created by matha on 16/03/2018.
//

#pragma once
#include "Common.h"
class Renderer {
private:
    static Matrix4f ProjMatrix3D;
    static Matrix4f ProjMatrix2D;
public:
    static void Start3D();
    static void Start2D();
};


