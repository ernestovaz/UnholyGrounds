#pragma once

class FrameBuffer
{

public:
    FrameBuffer(unsigned int width, unsigned int height);
    FrameBuffer();
    ~FrameBuffer();

    unsigned int getId();
    unsigned int getTextureId();

private:
    unsigned int configureRenderToTexture(unsigned int width, unsigned int height);

    unsigned int bufferID;
    unsigned int textureID;
};
