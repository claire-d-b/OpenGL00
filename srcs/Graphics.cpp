#include "../includes/Graphics.h"

Diamond::Diamond(void) : _vertices(NULL), _indices(NULL), _shaderProgram(0), _vertPos_loc(0), _vertColor_loc(1), _VAO(0), _VBO(0), _EBO(0), _vertexShader(0), _fragmentShader(0) {
}

Diamond::Diamond(Diamond const& rhs) : _vertices(rhs._vertices), _indices(rhs._indices), _shaderProgram(rhs._shaderProgram), _vertPos_loc(rhs._vertPos_loc), _vertColor_loc(rhs._vertColor_loc), _VAO(rhs._VAO), _VBO(rhs._VBO), _EBO(rhs._EBO), _vertexShader(rhs._vertexShader), _fragmentShader(rhs._fragmentShader) {
}

Diamond::Diamond(GLfloat **verts, GLuint **inds) : _vertices(verts), _indices(inds), _shaderProgram(0), _vertPos_loc(0), _vertColor_loc(1), _VAO(0), _VBO(0), _EBO(0), _vertexShader(0), _fragmentShader(0) {
}

Diamond& Diamond::operator=(Diamond const& rhs)
{
    new (this) Diamond(rhs);
    return *this;
}

Diamond::~Diamond(void)
{

}

const GLfloat* Diamond::getVertices()
{
    return *this->_vertices;
}

const GLuint* Diamond::getIndices()
{
    return *this->_indices;
}

const GLuint& Diamond::getVertPosLoc()
{
    return this->_vertPos_loc;
}

const GLuint& Diamond::getVertColorLoc()
{
    return this->_vertColor_loc;
}

const GLuint& Diamond::getVertexShader()
{
    return this->_vertexShader;
}

const GLuint& Diamond::getFragmentShader()
{
    return this->_fragmentShader;
}

const GLuint& Diamond::getShaderProgram()
{
    return this->_shaderProgram;
}

GLuint& Diamond::getVAO()
{
    return this->_VAO;
}

GLuint& Diamond::getVBO()
{
    return this->_VBO;
}

GLuint& Diamond::getEBO()
{
    return this->_EBO;
}

void Diamond::setVertices(GLfloat **vertices)
{
    this->_vertices = vertices;
}

void Diamond::setIndices(GLuint **indices)
{
    this->_indices = indices;
}

void Diamond::setVertPosLoc(GLuint vertPosLoc)
{
    this->_vertPos_loc = vertPosLoc;
}

void Diamond::setVertColorLoc(GLuint vertColorLoc)
{
    this->_vertPos_loc = vertColorLoc;
}

void Diamond::setVertexShader(GLuint vertexShader)
{
    this->_vertexShader = vertexShader;
}

void Diamond::setFragmentShader(GLuint fragmentShader)
{
    this->_fragmentShader = fragmentShader;
}

void Diamond::setShaderProgram(GLuint shaderProgram)
{
    this->_shaderProgram = shaderProgram;
}

void Diamond::setVAO(GLuint VAO)
{
    this->_VAO = VAO;
}

void Diamond::setVBO(GLuint VBO)
{
    this->_VBO = VBO;
}

void Diamond::setEBO(GLuint EBO)
{
    this->_EBO = EBO;
}