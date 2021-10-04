#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <map>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <chrono>

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

GLuint BuildTriangles(); 
GLuint LoadShader_Vertex(const char* filename);   
GLuint LoadShader_Fragment(const char* filename);
void LoadShader(const char* filename, GLuint shader_id);
GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id); 

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);


std::map<const char*, Model> g_VirtualScene;

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

float g_ScreenRatio;

int main()
{
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: glfwInit() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(ErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* screen = glfwGetVideoMode(monitor);
    g_ScreenRatio = screen->width/screen->height;
    GLFWwindow* window = glfwCreateWindow(screen->width, screen->height, "window", monitor, NULL);
    if (!window)
    {
        glfwTerminate();
        fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
        std::exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    {//creates scope, fix for now to force deconstruction of buffer objects before glfw is terminated
    GLuint vertex_shader_id = LoadShader_Vertex("src/shader_vertex.glsl");
    GLuint fragment_shader_id = LoadShader_Fragment("src/shader_fragment.glsl");
    GLuint program_id = CreateGpuProgram(vertex_shader_id, fragment_shader_id);
    GLfloat model_coefficients[] = {
        -0.5f,  0.5f,  0.5f, 1.0f, 
        -0.5f, -0.5f,  0.5f, 1.0f, 
         0.5f, -0.5f,  0.5f, 1.0f, 
         0.5f,  0.5f,  0.5f, 1.0f, 
        -0.5f,  0.5f, -0.5f, 1.0f, 
        -0.5f, -0.5f, -0.5f, 1.0f, 
         0.5f, -0.5f, -0.5f, 1.0f, 
         0.5f,  0.5f, -0.5f, 1.0f, 
    };

    //vao
    GLuint vertex_array_object_id;
    glGenVertexArrays(1, &vertex_array_object_id);
    glBindVertexArray(vertex_array_object_id);

    VertexBuffer vbo(model_coefficients, 32*sizeof(GLfloat));

    GLuint location = 0; 
    GLint  number_of_dimensions = 4; 
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLfloat color_coefficients[] = {
        1.0f, 0.5f, 0.0f, 1.0f, 
        1.0f, 0.5f, 0.0f, 1.0f,
        0.0f, 0.5f, 1.0f, 1.0f,
        0.0f, 0.5f, 1.0f, 1.0f, 
        1.0f, 0.5f, 0.0f, 1.0f, 
        1.0f, 0.5f, 0.0f, 1.0f, 
        0.0f, 0.5f, 1.0f, 1.0f, 
        0.0f, 0.5f, 1.0f, 1.0f, 
    };

    GLuint VBO_color_coefficients_id;
    glGenBuffers(1, &VBO_color_coefficients_id);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_color_coefficients_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_coefficients), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(color_coefficients), color_coefficients);

    //VertexBuffer vbcolor(color_coefficients,sizeof(color_coefficients));

    location = 1; 
    number_of_dimensions = 4; 
    glVertexAttribPointer(location, number_of_dimensions, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(location);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint indices[] = {
        0, 1, 2, 
        7, 6, 5, 
        3, 2, 6, 
        4, 0, 3, 
        4, 5, 1, 
        1, 5, 6, 
        0, 2, 3, 
        7, 5, 4, 
        3, 6, 7, 
        4, 3, 7, 
        4, 1, 0, 
        1, 6, 2, 
    };

    Model cube_faces("Cubo (faces coloridas)", 0, 36, GL_TRIANGLES);

    g_VirtualScene["cube_faces"] = cube_faces;

    GLuint indices_id;
    glGenBuffers(1, &indices_id);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);

    //IndexBuffer ibo(indices, 36);

    glBindVertexArray(0);

    GLint model_uniform           = glGetUniformLocation(program_id, "model"); 
    GLint view_uniform            = glGetUniformLocation(program_id, "view"); 
    GLint projection_uniform      = glGetUniformLocation(program_id, "projection"); 
    GLint render_as_black_uniform = glGetUniformLocation(program_id, "render_as_black"); 
    glEnable(GL_DEPTH_TEST);
    glm::mat4 the_projection;
    glm::mat4 the_model;
    glm::mat4 the_view;

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glm::vec4 d_W = glm::vec4(0.0f,0.0f, 0.0f, 0.0f);
    glm::vec4 d_S = glm::vec4(0.0f,0.0f, 0.0f, 0.0f);
    glm::vec4 d_A = glm::vec4(0.0f,0.0f, 0.0f, 0.0f);
    glm::vec4 d_D = glm::vec4(0.0f,0.0f, 0.0f, 0.0f);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(program_id);
        glBindVertexArray(vertex_array_object_id);

        glm::vec4 camera_position_c  = glm::vec4(0.0f,1.0f,-5.5f,1.0f)+d_W+d_S+d_A+d_D; 
        glm::vec4 camera_free_l      = glm::vec4(cos(g_CameraPhi)*sin(g_CameraTheta),
                                        sin(g_CameraPhi),
                                        cos(g_CameraTheta)*cos(g_CameraPhi),
                                        0.0f); 

        glm::vec4 camera_view_vector = camera_free_l;
        glm::vec4 camera_up_vector   = glm::vec4(0.0f,1.0f,0.0f,0.0f); 

        glm::vec4 w = -camera_view_vector;
        glm::vec4 u = crossproduct(camera_up_vector,w);
        w = w / norm(w);
        u = u / norm(u);

        if(g_WPressed) d_W -= w*0.01f;
        if(g_SPressed) d_S += w*0.01f;
        if(g_APressed) d_A -= u*0.01f;
        if(g_DPressed) d_D += u*0.01f;


        glm::mat4 view = Matrix_Camera_View(camera_position_c, camera_view_vector, camera_up_vector);

        glm::mat4 projection;

        float nearplane = -0.1f; 
        float farplane  = -10.0f; 

        float field_of_view = 3.141592 / 3.0f;
        projection = Matrix_Perspective(field_of_view, g_ScreenRatio, nearplane, farplane);

        glUniformMatrix4fv(view_uniform       , 1 , GL_FALSE , glm::value_ptr(view));
        glUniformMatrix4fv(projection_uniform , 1 , GL_FALSE , glm::value_ptr(projection));

        for (int i = 1; i <= 3; ++i)
        {
            glm::mat4 model;

            if (i == 1)
            {
                model = Matrix_Identity();
            }
            else if ( i == 2 )
            {
                model = Matrix_Translate(0.0f, 0.0f, -2.0f) 
                      * Matrix_Rotate(3.141592f / 8.0f, glm::vec4(1.0f,1.0f,1.0f,0.0f)) 
                      * Matrix_Scale(2.0f, 0.5f, 0.5f); 
            }
            else if ( i == 3 )
            {
                model = Matrix_Translate(-2.0f, 0.0f, 0.0f) 
                      * Matrix_Rotate_Z(g_AngleZ)  
                      * Matrix_Rotate_Y(g_AngleY) 
                      * Matrix_Rotate_X(g_AngleX);

                the_model = model;
                the_projection = projection;
                the_view = view;
            }

            glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));

            glUniform1i(render_as_black_uniform, false);

            glDrawElements(
                g_VirtualScene["cube_faces"].rendering_mode, 
                g_VirtualScene["cube_faces"].num_indices,
                GL_UNSIGNED_INT,
                (void*)g_VirtualScene["cube_faces"].first_index
            );
            if ( i == 3 )
            {
                glPointSize(15.0f);
                glDrawArrays(GL_POINTS, 3, 1);
            }
        }

        glm::mat4 model = Matrix_Identity();

        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));

        glLineWidth(10.0f);

        glUniform1i(render_as_black_uniform, false);

        glDrawElements(
            g_VirtualScene["axes"].rendering_mode,
            g_VirtualScene["axes"].num_indices,
            GL_UNSIGNED_INT,
            (void*)g_VirtualScene["axes"].first_index
        );

        glBindVertexArray(0);

        glm::vec4 p_model(0.5f, 0.5f, 0.5f, 1.0f);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    }//closing bracket for scope created for deconstruction fix
    glfwTerminate();

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

    glShaderSource(shader_id, 1, &shader_string, &shader_string_length);

    glCompileShader(shader_id);

    GLint compiled_ok;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled_ok);

    GLint log_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);

    GLchar* log = new GLchar[log_length];
    glGetShaderInfoLog(shader_id, log_length, &log_length, log);

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

void ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "ERROR: GLFW: %s\n", description);
}

