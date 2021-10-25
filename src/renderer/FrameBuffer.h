#pragma once

class FrameBuffer
{

public:
    FrameBuffer(unsigned int width, unsigned int height);
    ~FrameBuffer();
private:
    void configureRenderToTexture(unsigned int width, unsigned int height);

    unsigned int bufferID;
};
