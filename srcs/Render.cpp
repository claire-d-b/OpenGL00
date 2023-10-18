#include "../includes/Graphics.h"

    // *** VERTEX SHADER *** RUNS ON EACH VERTEX
    // GLSL version gl shader language is a c++-like language used to write shaders.
    // We use the core features of 3.3
    // layouts: describe the input
    // vertPos: x,y,z z=0
    // color: r,g,b color
    // theColor = color;: the input colour value becomes the output colour
static const char* vertexShaderSource = "#version 410 core\n\
    layout (location = 0) in vec3 vertPos;\n\
    layout (location = 1) in vec3 color;\n\
    out vec3 theColor;\n\
    void main() {\n\
        gl_Position = vec4(vertPos.x,vertPos.y,vertPos.z,1.0);\n\
        theColor = color;\n\
    }\0";

    // *** FRAGMENT SHADER *** RUNED ONCE FOR EVERY PIXEL
    // out vec4 pixelColor;: outputs color of the pixel
    // pixelColor = vec4(theColor,1);: 1 is no transparency (alpha value)
static const char* fragmentShaderSource = "#version 410 core\n\
    in vec3 theColor;\n\
    out vec4 pixelColor;\n\
    void main()\n\
    {\n\
        pixelColor = vec4(theColor,1.0f);\n\
    }\n\0";


void handleShaders(Diamond& lhs)
{
    // Compile & link shaders
    // *** vertex shader ***
    lhs.setVertexShader(glCreateShader(GL_VERTEX_SHADER));
    glShaderSource(lhs.getVertexShader(), 1, &vertexShaderSource, NULL);
    glCompileShader(lhs.getVertexShader());
    // check for shader compile errors
    int success = 0;
    char infoLog[512];
    glGetShaderiv(lhs.getVertexShader(), GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(lhs.getVertexShader(), 512, NULL, infoLog);
        std::cout << "Error: vertex shader compilation failed [" << infoLog << "]" << std::endl;
    }
    // *** fragment shader ***
    lhs.setFragmentShader(glCreateShader(GL_FRAGMENT_SHADER));
    glShaderSource(lhs.getFragmentShader(), 1, &fragmentShaderSource, NULL);
    glCompileShader(lhs.getFragmentShader());
    // check for shader compile errors
    glGetShaderiv(lhs.getFragmentShader(), GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(lhs.getFragmentShader(), 512, NULL, infoLog);
        std::cout << "Error: fragment shader compilation failed [" << infoLog << "]" << std::endl;
    }
    // link shaders
    lhs.setShaderProgram(glCreateProgram());
    // _vertPos_loc: corresponds to "location = 0" in the verter shader definition
    // _vertColor_loc: corresponds to "location = 1" in the verter shader definition
    glAttachShader(lhs.getShaderProgram(), lhs.getVertexShader());
    glAttachShader(lhs.getShaderProgram(), lhs.getFragmentShader());
    glLinkProgram(lhs.getShaderProgram());
    // check for linking errors
    glGetProgramiv(lhs.getShaderProgram(), GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(lhs.getShaderProgram(), 512, NULL, infoLog);
        std::cout << "Error: program linking failed [" << infoLog << "]" << std::endl;
    }
    glDeleteShader(lhs.getVertexShader());
    glDeleteShader(lhs.getFragmentShader());
    if (!glIsProgram(lhs.getShaderProgram())) {
		std::cout << "ERROR: Not a shader program! Possibly an allocation error." << std::endl;
	}
}
void deleteShaderProgram(Diamond& lhs)
{
    glDeleteProgram(lhs.getShaderProgram());
}

void handleBuffers(Diamond& lhs)
{
    glGenVertexArrays(1, &lhs.getVAO());
    glGenBuffers(1, &lhs.getVBO()); // allocate a new Virtual Buffer Object
    // glGenBuffers(1, &lhs._EBO); // allocate a new Element Buffer Object
    glBindVertexArray(lhs.getVAO());

    // Both vertex positions AND vertex colors are loaded into the VBO.
	// Note that glVertexAttribPointer uses a non-zero "stride" parameter.
	// Also note that the second call to glVertexAttribPointer uses
    //     3*sizeof(float) to specify where the color information is.
    glBindBuffer(GL_ARRAY_BUFFER, lhs.getVBO()); // the current array is the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*18, lhs.getVertices(), GL_STATIC_DRAW); // load that array into OpenGL VBO array.
    // TO TELL THE VAO WHERE DATA IS STORED IN THE VBO
    glVertexAttribPointer(lhs.getVertPosLoc(),3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void *)0);
    // vertPos_loc: location as (x,y) coordinates
    // 3: number of data items i.e (x,y)
    // 6*sizeof(float): stride : how far apart from the data is the next
    // (void *)0: where the first (x,y) appears in the VBO measured in bytes
	glEnableVertexAttribArray(lhs.getVertPosLoc());
	glVertexAttribPointer(lhs.getVertColorLoc(),3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(lhs.getVertColorLoc());

	// This is optional, but allowed. The VAO already knows which buffer (VBO) is holding its
	//     vertex data, so it is OK to unbind the VBO here.
    // This can help with debugging: by unbinding here, a bug in later the code will not
    //     quietly affect the current GL_ARRAY_BUFFER (VBO) or the current Vertex Array Object (VAO)

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lhs._EBO); // the current arrayis the EBO
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3, lhs._indices, GL_STATIC_DRAW); // load that array into OpenGL EBO array.
    
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    // This step invokes the shader program to render the triangle.
    glUseProgram(lhs.getShaderProgram());
    check_for_opengl_errors();
}

void renderScene(Diamond& lhs)
{
    glBindVertexArray(lhs.getVAO());
    glDrawArrays(GL_TRIANGLES,0,3); // starts at the vertex nb 0 in the array of data that was uploaded and we use a total of 3 vertices.
    // glDrawElements(GL_POINTS,18*sizeof(GLfloat),GL_UNSIGNED_INT,this->_indices);
}
