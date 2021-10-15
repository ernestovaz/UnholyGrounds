#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <chrono>
#include <tuple>

#include <glad/glad.h>  
#include <GLFW/glfw3.h>  

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils.h"
#include "matrices.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Model.h"
#include "InputManager.h"
#include "Actor.h"
#include "Command.h"
#include "ForwardCommand.h"
#include "Window.h"

GLuint LoadShader_Vertex(const char* filename);   
GLuint LoadShader_Fragment(const char* filename);
void LoadShader(const char* filename, GLuint shader_id);
GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id); 

/*
void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
*/

float g_AngleX = 0.0f;
float g_AngleY = 0.0f;
float g_AngleZ = 0.0f;

bool g_LeftMouseButtonPressed = false;

float g_CameraTheta = 0.0f; 
float g_CameraPhi = 0.0f;  
float g_CameraDistance = 2.5f; 

float g_CameraX = 0.0f;
float g_CameraZ = 0.0f;

bool g_WPressed = false;
bool g_SPressed = false;
bool g_APressed = false;
bool g_DPressed = false;

int main()
{
    Command* forward = new ForwardCommand();
    std::tuple<int, Command*> commandLst[] = {std::make_tuple(GLFW_KEY_W,forward)};

    InputManager input(commandLst, 1);
    Window window(&input);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    GLuint vertex_shader_id = LoadShader_Vertex("src/shaders/vertex.glsl");
    GLuint fragment_shader_id = LoadShader_Fragment("src/shaders/fragment.glsl");
    GLuint program_id = CreateGpuProgram(vertex_shader_id, fragment_shader_id);

    //Vertex Array Object
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    Model tardis("data/tardis.obj");
    std::vector<float> vertex_pos = tardis.vertex_positions;
    std::vector<GLuint> indices = tardis.indices;

    VertexBuffer positions(vertex_pos.data(), vertex_pos.size()*sizeof(float));
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    IndexBuffer ib(indices.data(), indices.size());

    GLint model_uniform           = glGetUniformLocation(program_id, "model"); 
    GLint view_uniform            = glGetUniformLocation(program_id, "view"); 
    GLint projection_uniform      = glGetUniformLocation(program_id, "projection"); 
    glEnable(GL_DEPTH_TEST);

    float tardisrotation = 0;

    Actor player;
    while (!window.shouldClose())
    {
        glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GLCall(glUseProgram(program_id));
        GLCall(glBindVertexArray(vao));
        positions.Bind();
        ib.Bind();
        input.handleInput(player);

        glm::vec4 camera_position_c  = player.getPosition();
        glm::vec4 camera_view_vector = player.getFacing();
        glm::vec4 camera_up_vector   = glm::vec4(0.0f,1.0f,0.0f,0.0f); 

        glm::mat4 view = Matrix_Camera_View(camera_position_c, camera_view_vector, camera_up_vector);

        glm::mat4 projection;

        float nearplane = -0.1f; 
        float farplane  = -10.0f; 

        float field_of_view = 3.141592 / 3.0f;
        projection = Matrix_Perspective(field_of_view, window.getScreenRatio(), nearplane, farplane);

        GLCall(glUniformMatrix4fv(view_uniform       , 1 , GL_FALSE , glm::value_ptr(view)));
        GLCall(glUniformMatrix4fv(projection_uniform , 1 , GL_FALSE , glm::value_ptr(projection)));
        
        tardisrotation += 0.1;
        glm::mat4 model = Matrix_Scale(0.2f, 0.2f, 0.2f)*Matrix_Rotate_Y(tardisrotation);

        GLCall(glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model)));

        GLCall(glDrawElements(
                tardis.rendering_mode, 
                tardis.num_indices,
                GL_UNSIGNED_INT,
                (void*)tardis.first_index
        ));

        GLCall(glBindVertexArray(0));
        window.pollEvents();
        window.swapBuffers();
    }

    return 0;
}

GLuint LoadShader_Vertex(const char* filename)
{
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);

    LoadShader(filename, vertex_shader_id);

    return vertex_shader_id;
}

GLuint LoadShader_Fragment(const char* filename)
{
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    LoadShader(filename, fragment_shader_id);

    return fragment_shader_id;
}

void LoadShader(const char* filename, GLuint shader_id)
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

GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id)
{
    GLuint program_id = glCreateProgram();

    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

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

/*
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    g_ScreenRatio = (float)width / height;
}

double g_LastCursorPosX, g_LastCursorPosY;

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &g_LastCursorPosX, &g_LastCursorPosY);
        g_LeftMouseButtonPressed = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        g_LeftMouseButtonPressed = false;
    }
}

void CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{

    if (!g_LeftMouseButtonPressed)
        return;

    float dx = xpos - g_LastCursorPosX;
    float dy = ypos - g_LastCursorPosY;

    g_CameraTheta -= 0.01f*dx;
    g_CameraPhi   -= 0.01f*dy;

    float phimax = 3.141592f/2;
    float phimin = -phimax;

    if (g_CameraPhi > phimax)
        g_CameraPhi = phimax;

    if (g_CameraPhi < phimin)
        g_CameraPhi = phimin;

    g_LastCursorPosX = xpos;
    g_LastCursorPosY = ypos;
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    g_CameraDistance -= 0.1f*yoffset;

    const float verysmallnumber = std::numeric_limits<float>::epsilon();
    if (g_CameraDistance < verysmallnumber)
        g_CameraDistance = verysmallnumber;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    float delta = 3.141592 / 16; 

    if (key == GLFW_KEY_X && action == GLFW_PRESS)
    {
        g_AngleX += (mod & GLFW_MOD_SHIFT) ? -delta : delta;
    }

    if (key == GLFW_KEY_Y && action == GLFW_PRESS)
    {
        g_AngleY += (mod & GLFW_MOD_SHIFT) ? -delta : delta;
    }
    if (key == GLFW_KEY_Z && action == GLFW_PRESS)
    {
        g_AngleZ += (mod & GLFW_MOD_SHIFT) ? -delta : delta;
    }

    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        g_AngleX = 0.0f;
        g_AngleY = 0.0f;
        g_AngleZ = 0.0f;
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        g_CameraZ -= 1;
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        g_CameraX += 1;
    }

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        g_CameraX -= 1;
    }

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        g_WPressed = true;
    }
    if (key == GLFW_KEY_W && action == GLFW_RELEASE)
    {
        g_WPressed = false;
    }

    if (key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        g_SPressed = true;
    }
    if (key == GLFW_KEY_S && action == GLFW_RELEASE)
    {
        g_SPressed = false;
    }

    if (key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        g_APressed = true;
    }
    if (key == GLFW_KEY_A && action == GLFW_RELEASE)
    {
        g_APressed = false;
    }

    if (key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        g_DPressed = true;
    }
    if (key == GLFW_KEY_D && action == GLFW_RELEASE)
    {
        g_DPressed = false;
    }
}
*/

