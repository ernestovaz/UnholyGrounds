#include "FrameBuffer.h"

#include <iostream>
#include <glad/glad.h>

#include "utils.h"

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
{
    GLCall(glGenFramebuffers(1, &bufferID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
    //creates and binds framebuffer

    this->textureID = configureRenderToTexture(width, height);
    //allocates memory for screen texture and returns id, 
    //the id can then be used for rendering later
    
    this->width = width;
    this->height = height;

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer is not complete" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::FrameBuffer()
{
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &bufferID);
}

unsigned int FrameBuffer::configureRenderToTexture(unsigned int width, unsigned int height)
{
    unsigned int texture;
    GLCall(glGenTextures(1, &texture));
    GLCall(glBindTexture(GL_TEXTURE_2D, texture));
    GLCall(glTexImage2D(GL_TEXTURE_2D,0,GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,NULL));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    //creates texture and configures scaling algorithms
    //in here, GL_NEAREST is used in order to achieve clear pixel visiblity, without any blurryness

    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture,0));

    unsigned int renderbuffer;
    GLCall(glGenRenderbuffers(1, &renderbuffer));
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer));
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));  
    GLCall(glBindRenderbuffer(GL_RENDERBUFFER, 0));
    //creates render buffer, 
    //the object that the frame buffer holds in order to be able to be rendered onto

    GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
            GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer));
    return texture;
}

unsigned int FrameBuffer::getId()
{
    return this->bufferID;
}

unsigned int FrameBuffer::getTextureId()
{
    return this->textureID;
}

unsigned int FrameBuffer::getWidth()
{
    return this->width;
}

unsigned int FrameBuffer::getHeight()
{
    return this->height;
}
