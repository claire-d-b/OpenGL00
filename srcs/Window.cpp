#include "../includes/Graphics.h"

GLfloat* verts;

    // float verts[] = {
    //     // positions         // colors
    //      0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    //     -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
    //      0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

    // };

GLuint* inds;

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    const unsigned int initWidth = 800;
    const unsigned int initHeight = 600;
    GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "Drawing", NULL, NULL);
    if (!(window)) {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // glViewport(0, 0, 800, 600);

    glewInit();
    std::cout << "GL renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version supported: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Supported GLSL version: " << (char *)glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    std::cout << "Glew version: " << glewGetString(GLEW_VERSION) << std::endl;

    verts = (GLfloat *)calloc(18, sizeof(GLfloat));
    verts[0] = 0.5f; // right
    verts[1] = -0.5f;
    verts[2] = 0.0f;
    verts[3] = 1.0f;
    verts[4] = 0.0f;
    verts[5] = 0.0f;
    verts[6] = -0.5f; // left
    verts[7] = -0.5f;
    verts[8] = 0.0f;
    verts[9] = 0.0f;
    verts[10] = 1.0f;
    verts[11] = 0.0f;
    verts[12] = 0.0f; //top
    verts[13] = 0.5f;
    verts[14] = 0.0f;
    verts[15] = 0.0f;
    verts[16] = 0.0f;
    verts[17] = 1.0f;

    inds = (GLuint *)calloc(3, sizeof(GLuint));
    inds[0] = 0;
    inds[1] = 1;
    inds[2] = 2;

    Diamond object = Diamond();

    // glViewport(0, 0, initWidth, initHeight); Draw into entire window

    // glEnable(GL_DEPTH_TEST);	// Enable depth buffering
	// glDepthFunc(GL_LEQUAL);	// Useful for multipass shaders

	// Set polygon drawing mode for front and back of each triangle
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	// Disable backface culling to render both sides of triangles
	// glDisable(GL_CULL_FACE);

    // be sure to activate the shader before any calls to glUniform
    handleShaders(object);
    object.setVertices(&verts);
    object.setIndices(&inds);
    handleBuffers(object);
    
    std::cout << sizeof(verts) << std::endl;
    std::cout << sizeof(object.getVertices()) << std::endl;
    std::cout << 18 * sizeof(GLfloat) << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        // glClearColor( 0.0, 0.0, 0.0, 1.0 ); // sets no transparency & black screen
        // Clear the rendering window
	    glClear(GL_COLOR_BUFFER_BIT); // | GL_DEPTH_BUFFER_BIT);
        renderScene(object);
        glfwSwapBuffers(window);
        glfwWaitEvents();
        if (check_for_opengl_errors()) {
            glfwTerminate();
            deleteShaderProgram(object);
            return 1;
        }
        // glfwWaitEventsTimeout(1.0/60.0f); Use this  animate at 60 frames/sec (time is NOT reliable)
        // glfwPollEvents(); Use this when animating as fast as possible
    }
    glfwTerminate();
    deleteShaderProgram(object);
    return 0;
}