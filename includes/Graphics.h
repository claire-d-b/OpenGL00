// These libraries are used to link the program (Visual Studio specific)
// #pragma comment(lib, opengl32.lib)
// #pragma comment(lib, glu32.lib)
// #pragma comment(lib, glwf3.lib)
// #pragma comment(lib, glew32s.lib)
// #pragma comment(glew32.lib)

#ifndef GRAPHICS_H

#define GRAPHICS_H

#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include "vendors/GLFW/glfw3.h"


class Diamond {
    private:
        GLfloat** _vertices;
        GLuint** _indices;
        GLuint _shaderProgram;
        GLuint _vertPos_loc;
        GLuint _vertColor_loc;
        GLuint _VAO;
        GLuint _VBO;
        GLuint _EBO;
        GLuint _vertexShader;
        GLuint _fragmentShader;

    public:
        Diamond(void);
        Diamond(Diamond const& rhs);
        Diamond(GLfloat** verts, GLuint** inds);
        Diamond& operator=(Diamond const& rhs);
        ~Diamond(void);
        const GLfloat* getVertices();
        const GLuint* getIndices();
        const GLuint& getVertPosLoc();
        const GLuint& getVertColorLoc();
        const GLuint& getShaderProgram();
        const GLuint& getVertexShader();
        const GLuint& getFragmentShader();
        GLuint& getVAO();
        GLuint& getVBO();
        GLuint& getEBO();
        void setVertices(GLfloat** vertices);
        void setIndices(GLuint **indices);
        void setVertPosLoc(GLuint vertPosLoc);
        void setVertColorLoc(GLuint vertColorLoc);
        void setVertexShader(GLuint vertexShader);
        void setFragmentShader(GLuint fragmentShader);
        void setShaderProgram(GLuint shaderProgram);
        void setVAO(GLuint VAO);
        void setVBO(GLuint VBO);
        void setEBO(GLuint EBO);
};

bool check_for_opengl_errors();
void handleShaders(Diamond& lhs);
void deleteShaderProgram(Diamond& lhs);
void handleBuffers(Diamond& lhs);
void processInput(GLFWwindow *window);
void renderScene(Diamond& lhs);

#endif
