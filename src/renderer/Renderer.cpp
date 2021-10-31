#include "Renderer.h"

#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include "utils.h"
#include "matrices.h"
#include "Model.h"
#include "QuadModel.h"
#include "Actor.h"
#include "Entity.h"

#define DOWNSCALE_FACTOR 1/4
//factor used in the game's pixelated effect

#define FOV 3.141592f/3.0f
#define NEARPLANE -0.1f
#define FARPLANE -100.0f

Renderer::Renderer(unsigned int screenWidth, unsigned int screenHeight)
    : downscaledBuffer(screenWidth * DOWNSCALE_FACTOR, screenHeight * DOWNSCALE_FACTOR), 
    playerEntity(Model("player")), groundEntity(Model("ground")), 
    screenQuad(new QuadModel("screenQuad", downscaledBuffer.getTextureId()))
{
    unsigned int firstVertexShaderId     = LoadVertexShader("firstPass/vertex");
    unsigned int firstFragmentShaderId   = LoadFragmentShader("firstPass/fragment");
    unsigned int secondVertexShaderId     = LoadVertexShader("secondPass/vertex");
    unsigned int secondFragmentShaderId   = LoadFragmentShader("secondPass/fragment");

    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    this->firstPassShaderId = CreateShaderProgram(firstVertexShaderId, firstFragmentShaderId);
    this->secondPassShaderId = CreateShaderProgram(secondVertexShaderId, secondFragmentShaderId);

    this->modelUniformId      = glGetUniformLocation(this->firstPassShaderId, "model"); 
    this->viewUniformId       = glGetUniformLocation(this->firstPassShaderId, "view"); 
    this->projectionUniformId = glGetUniformLocation(this->firstPassShaderId, "projection"); 
}

Renderer::~Renderer()
{
    glDeleteProgram(firstPassShaderId);
    glDeleteProgram(secondPassShaderId);
}

void Renderer::draw(Actor player)
{
    glViewport(0,0,downscaledBuffer.getWidth(),downscaledBuffer.getHeight());
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, downscaledBuffer.getId()));
    //uses downscaled screensize and binds framebuffer

    glClearColor(0.05f, 0.05f, 0.05f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST); 

    GLCall(glUseProgram(firstPassShaderId));

    float screenRatio = (float)screenWidth / (float)screenHeight;

    glm::mat4 projection = Matrix_Perspective(FOV, screenRatio, NEARPLANE, FARPLANE);
    glm::mat4 view = Matrix_Camera_View(player.getPosition(), player.getFacing(), glm::vec4(0,1,0,0));

    GLCall(glUniformMatrix4fv(projectionUniformId, 1 , GL_FALSE , glm::value_ptr(projection)));
    GLCall(glUniformMatrix4fv(viewUniformId, 1 , GL_FALSE , glm::value_ptr(view)));

    drawEntity(groundEntity);
    drawPlayer(playerEntity);

    glViewport(0,0, screenWidth, screenHeight);
    renderTextureToScreen();
    //sets normal screen size and render low resolution texture into screen
}

void Renderer::drawEntity(Entity entity)
{
    glm::mat4 model = entity.matrix;
    GLCall(glUniformMatrix4fv(this->modelUniformId, 1, GL_FALSE, glm::value_ptr(model)));
    drawModel(entity.model);
}

void Renderer::drawModel(Model model)
{
    GLCall(glBindTexture(GL_TEXTURE_2D, model.getTextureId()));         
    GLCall(glBindVertexArray(model.getId()));
    GLCall(glDrawElements(
            model.getRenderingMode(),
            model.getIndexCount(),
            GL_UNSIGNED_INT,
            (void*)0
    ));
    GLCall(glBindVertexArray(0));
}

void Renderer::drawPlayer(Entity playerEntity)
{
    glm::mat4 view = Matrix_Identity();
    GLCall(glUniformMatrix4fv(this->viewUniformId, 1 , GL_FALSE , glm::value_ptr(view)));
    glClear(GL_DEPTH_BUFFER_BIT);
    drawEntity(playerEntity);
}

void Renderer::renderTextureToScreen()
{
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    GLCall(glDisable(GL_DEPTH_TEST));
    GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
    GLCall(glUseProgram(this->secondPassShaderId));
    drawModel(*screenQuad);
}

unsigned int Renderer::LoadVertexShader(std::string name)
{
    std::string filename = "src/shaders/"+name+".glsl";
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

    LoadShader(filename.c_str(), vertex_shader_id);

    return vertex_shader_id;
}

unsigned int Renderer::LoadFragmentShader(std::string name)
{
    std::string filename = "src/shaders/"+name+".glsl";
    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    LoadShader(filename.c_str(), fragmentShaderId);

    return fragmentShaderId;
}

void Renderer::LoadShader(const char* filename, unsigned int shader_id)
{
    std::ifstream file;
    try {
        file.exceptions(std::ifstream::failbit);
        file.open(filename);
    } catch ( std::exception& e ) {
        fprintf(stderr, "ERROR: Cannot open file \"%s\".\n", filename);
        std::exit(EXIT_FAILURE);
    }
    std::stringstream shader;
    shader << file.rdbuf();
    std::string str = shader.str();
    const GLchar* shader_string = str.c_str();
    const GLint   shader_string_length = static_cast<GLint>( str.length() );

    GLCall(glShaderSource(shader_id, 1, &shader_string, &shader_string_length));

    GLCall(glCompileShader(shader_id));

    GLint compiled_ok;
    GLCall(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled_ok));

    GLint log_length = 0;
    GLCall(glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length));

    GLchar* log = new GLchar[log_length];
    GLCall(glGetShaderInfoLog(shader_id, log_length, &log_length, log));

    if ( log_length != 0 )
    {
        std::string  output;

        if ( !compiled_ok )
        {
            output += "ERROR: OpenGL compilation of \"";
            output += filename;
            output += "\" failed.\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }
        else
        {
            output += "WARNING: OpenGL compilation of \"";
            output += filename;
            output += "\".\n";
            output += "== Start of compilation log\n";
            output += log;
            output += "== End of compilation log\n";
        }

        fprintf(stderr, "%s", output.c_str());
    }

    delete [] log;
}

unsigned int Renderer::CreateShaderProgram(unsigned int vertexId, unsigned int fragmentId)
{
    GLuint program_id = glCreateProgram();

    glAttachShader(program_id, vertexId);
    glAttachShader(program_id, fragmentId);

    glLinkProgram(program_id);

    GLint linked_ok = GL_FALSE;
    glGetProgramiv(program_id, GL_LINK_STATUS, &linked_ok);

    if ( linked_ok == GL_FALSE )
    {
        GLint log_length = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);

        GLchar* log = new GLchar[log_length];

        glGetProgramInfoLog(program_id, log_length, &log_length, log);

        std::string output;

        output += "ERROR: OpenGL linking of program failed.\n";
        output += "== Start of link log\n";
        output += log;
        output += "\n== End of link log\n";

        delete [] log;

        fprintf(stderr, "%s", output.c_str());
    }

    return program_id;
}
