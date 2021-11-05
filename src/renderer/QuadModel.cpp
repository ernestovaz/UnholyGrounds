#include "QuadModel.h"

QuadModel::QuadModel(std::string name, unsigned int textureId)
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    float vertices[] = 
    {    
        -1.0f,  1.0f,  
        -1.0f, -1.0f,  
         1.0f,  1.0f,  
         1.0f, -1.0f,  

    };
    float texture[] = 
    {
         0.0f,  1.0f,  
         0.0f,  0.0f,  
         1.0f,  1.0f,  
         1.0f,  0.0f,  
    };
    unsigned int indices[] = {0, 1, 2, 3};
    VertexBuffer positions(vertices, 8*sizeof(float), 0, 2);
    VertexBuffer textures(texture,   8*sizeof(float), 1, 2);
    IndexBuffer ibo(indices, 6);

    this->name = name;
    this->indexCount        = 4; 
    this->renderingMode     = GL_TRIANGLE_STRIP;
    this->vaoID             = VAO;
    this->vertexPositions   = positions;
    this->vertexTextures    = textures;
    this->indices           = ibo;
    this->textureID         = textureId;

    glBindVertexArray(0);
}

QuadModel::QuadModel(std::string name) : QuadModel(name, loadTexture("data/ui/"+name+".png", true))
{
}
    
