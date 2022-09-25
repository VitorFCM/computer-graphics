#include <stdio.h>
#include "program.h"

Program program;

void key_event(GLFWwindow* window, int key, int scancode, int action, int mods);

void initializeProgram(const char* title_window, int width_window, int height_window) {

    initializeLinkedList(&program.entities);

    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    program.window = glfwCreateWindow(width_window, height_window, title_window, NULL, NULL);
    glfwMakeContextCurrent(program.window);

    GLint GlewInitResult = glewInit();
    printf("GlewStatus: %s", glewGetErrorString(GlewInitResult));

    const GLchar *vertex_code =
            "attribute vec2 position;\n"
            "uniform mat4 mat_transformation;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = mat_transformation*vec4(position, 0.0, 1.0);\n"
            "}\n";

    const GLchar *fragment_code =
            "uniform vec4 color;\n"
            "void main()\n"
            "{\n"
            "    gl_FragColor = color;\n"
            "}\n";

    program.program_code = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

    glCompileShader(vertex);
    GLint isCompiled = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE){

        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n", info);
    }

    glCompileShader(fragment);
    isCompiled = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE){

        int infoLength = 512;
        glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &infoLength);

        char info[infoLength];
        glGetShaderInfoLog(fragment, infoLength, NULL, info);

        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n", info);
    }

    glAttachShader(program.program_code, vertex);
    glAttachShader(program.program_code, fragment);

    glLinkProgram(program.program_code);
    glUseProgram(program.program_code);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    program.glPosition = glGetAttribLocation(program.program_code, "position");
    glEnableVertexAttribArray(program.glPosition);
    glVertexAttribPointer(program.glPosition, 2, GL_FLOAT, GL_FALSE, sizeof(coordinates), (void*) 0);

    program.glColor = glGetUniformLocation(program.program_code, "color");
    glfwSetKeyCallback(program.window, key_event);
    glfwShowWindow(program.window);

    program.glTransformation = glGetUniformLocation(program.program_code, "mat_transformation");
}

void startProgram() {

    while (!glfwWindowShouldClose(program.window)) {

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(1.0, 1.0, 1.0, 1.0);

        Node *node = program.entities.head;
        while (node != NULL) {
            Entity *e = (Entity*) node->data;
            e->render(e);
            node = node->next;
        }

        glfwSwapBuffers(program.window);
    }

    glfwDestroyWindow(program.window);
    glfwTerminate();
}

GLint getGLPosition() {
    return program.glPosition;
}

GLint getGLTransformation() {
    return program.glTransformation;
}

GLint getGLColor() {
    return program.glColor;
}

void addEntityToProgram(Entity *e) {
    program.entities.add(&program.entities, e);
}

void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){

    Node *node = program.entities.head;
    while (node != NULL) {

        Entity *e = (Entity*) node->data;
        if (e->controller != NULL) e->controller(e, key, action);

        node = node->next;
    }
}