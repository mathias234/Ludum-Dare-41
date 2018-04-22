//
// Created by matha on 14/03/2018.
//

#pragma once

#include "Common.h"

struct FrameBufferCreateInfo {
public:
    int Width;
    int Height;
    bool UseDepthRenderBuffer;
    int MultiSampleCount;
    int RenderTargetCount;
    bool* Borders;
    GLenum* InternalFormats;
    GLenum* Formats;
    GLenum* Types;
    GLenum* Attachments;

    FrameBufferCreateInfo();
};

class FrameBuffer {
private:
    unsigned int* m_RendererId;
    unsigned int* m_IntermediateRendererId;

    unsigned int m_FrameBuffer;
    unsigned int m_IntermediateFrameBuffer;

    void Create();
    void Destroy();
public:
    FrameBufferCreateInfo FrameBufferSettings;


    explicit FrameBuffer(FrameBufferCreateInfo frameBufferCreateInfo);
    ~FrameBuffer();

    void BindAsFrameBuffer();
    void BindAsTexture(int frameBufferId, int slot);

    void Reload();
};




