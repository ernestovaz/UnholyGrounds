#pragma once 

#include <glm/mat4x4.hpp>

glm::mat4 Matrix(
    float m00, float m01, float m02, float m03, 
    float m10, float m11, float m12, float m13, 
    float m20, float m21, float m22, float m23, 
    float m30, float m31, float m32, float m33  
);

glm::mat4 Matrix_Identity();

glm::mat4 Matrix_Translate(float tx, float ty, float tz);

glm::mat4 Matrix_Scale(float sx, float sy, float sz);

glm::mat4 Matrix_Rotate_X(float angle);

glm::mat4 Matrix_Rotate_Y(float angle);

glm::mat4 Matrix_Rotate_Z(float angle);

float norm(glm::vec4 v);

glm::mat4 Matrix_Rotate(float angle, glm::vec4 axis);

glm::vec4 crossproduct(glm::vec4 u, glm::vec4 v);

float dotproduct(glm::vec4 u, glm::vec4 v);

glm::mat4 Matrix_Camera_View(glm::vec4 position_c, glm::vec4 view_vector, glm::vec4 up_vector);

glm::mat4 Matrix_Orthographic(float l, float r, float b, float t, float n, float f);

glm::mat4 Matrix_Perspective(float field_of_view, float aspect, float n, float f);

void PrintMatrix(glm::mat4 M);

void PrintVector(glm::vec4 v);

void PrintMatrixVectorProduct(glm::mat4 M, glm::vec4 v);

void PrintMatrixVectorProductDivW(glm::mat4 M, glm::vec4 v);
