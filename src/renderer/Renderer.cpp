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
#include "Actor.h"

#define FOV 3.141592f/3.0f
#define NEARPLANE -0.1f
#define FARPLANE -10.0f

Renderer::Renderer(std::string vertexShader, std::string fragmentShader, float screenRatio)
{
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glEnable(GL_DEPTH_TEST); 

    Model tardis("tardis");

    this->testObject = tardis;
    this->testObjectRotation = 0;

    this->screenRatio = screenRatio;

    this->vertexShaderId     = LoadVertexShader(vertexShader);
    this->fragmentShaderId   = LoadFragmentShader(fragmentShader);
    this->shaderProgramId    = CreateShaderProgram(this->vertexShaderId, this->fragmentShaderId);

    this->modelUniformId      = glGetUniformLocation(this->shaderProgramId, "model"); 
    this->viewUniformId       = glGetUniformLocation(this->shaderProgramId, "view"); 
    this->projectionUniformId = glGetUniformLocation(this->shaderProgramId, "projection"); 
}

Renderer::~Renderer()
{
    glDeleteProgram(shaderProgramId);
}

void Renderer::draw(Actor player)
{
    this->testObjectRotation += 0.1;

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLCall(glUseProgram(this->shaderProgramId));

    glm::vec4 camera_position_c  = player.getPosition();
    glm::vec4 camera_view_vector = player.getFacing();
    glm::vec4 camera_up_vector   = glm::vec4(0.0f,1.0f,0.0f,0.0f); 

    glm::mat4 view = Matrix_Camera_View(camera_position_c, camera_view_vector, camera_up_vector);
    glm::mat4 projection = Matrix_Perspective(FOV, this->screenRatio, NEARPLANE, FARPLANE);
    glm::mat4 model = Matrix_Scale(0.2f, 0.2f, 0.2f)*Matrix_Rotate_Y(this->testObjectRotation);

    GLCall(glUniformMatrix4fv(this->viewUniformId, 1 , GL_FALSE , glm::value_ptr(view)));
    GLCall(glUniformMatrix4fv(this->projectionUniformId, 1 , GL_FALSE , glm::value_ptr(projection)));
    GLCall(glUniformMatrix4fv(this->modelUniformId, 1, GL_FALSE, glm::value_ptr(model)));
    
    GLCall(glBindVertexArray(this->testObject.getId()));
    GLCall(glDrawElements(
            GL_TRIANGLES,
            this->testObject.getIndexCount(),
            GL_UNSIGNED_INT,
            (void*)0
    ));
    GLCall(glBindVertexArray(0));
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
