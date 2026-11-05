#include <iostream>

//#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 800, HEIGHT = 600;
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rotX = 0.0f;
float rotY = 0.0f;
float rotZ = 0.0f;

// Función para transformar y dibujar cada parte de la mesa
void dibujarParte(glm::vec3 posicion, glm::vec3 escala, GLint modelLoc) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, posicion);
    model = glm::scale(model, escala);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Mesa 3D - Modelado Geometrico", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (nullptr == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, screenWidth, screenHeight);

    // Opciones de OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Cargar shaders
    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // Arreglo de vértices: cubo unitario con color por cara
    float vertices[] = {
        // Front
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

        // Back
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,

        // Right
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

         // Left
         -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

         // Bottom
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

         // Top
         -0.5f,  0.5f, -0.5f,  1.0f, 0.2f, 0.5f,
          0.5f,  0.5f, -0.5f,  1.0f, 0.2f, 0.5f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.2f, 0.5f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.2f, 0.5f,
         -0.5f,  0.5f,  0.5f,  1.0f, 0.2f, 0.5f,
         -0.5f,  0.5f, -0.5f,  1.0f, 0.2f, 0.5f,
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Posición (Location 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Color (Location 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);

    while (!glfwWindowShouldClose(window)) {
        Inputs(window);
        glfwPollEvents();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.Use();

        // Configuración de la matriz de Vista con 3 grados de libertad
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(movX, movY, movZ));
        view = glm::rotate(view, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::rotate(view, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::rotate(view, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));

        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);

        // Geometría de la mesa
        glm::vec3 escalaTabla = glm::vec3(3.0f, 0.1f, 2.0f);
        glm::vec3 escalaPata = glm::vec3(0.2f, 1.0f, 0.2f);
        glm::vec3 posicionMesa = glm::vec3(0.0f, 0.5f, 0.0f);

        glm::vec3 posicionesPatas[] = {
            glm::vec3(1.3f, 0.0f,  0.8f), // Delantera derecha
            glm::vec3(-1.3f, 0.0f,  0.8f), // Delantera izquierda
            glm::vec3(1.3f, 0.0f, -0.8f), // Trasera derecha
            glm::vec3(-1.3f, 0.0f, -0.8f)  // Trasera izquierda
        };

        // 1. Dibujar el tablero
        dibujarParte(posicionMesa, escalaTabla, modelLoc);

        // 2. Dibujar las 4 patas
        for (int i = 0; i < 4; ++i) {
            dibujarParte(posicionesPatas[i], escalaPata, modelLoc);
        }

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();

    return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Traslación de la cámara / escena
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movX += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movX -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
        movY += 0.08f;
    if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
        movY -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movZ -= 0.08f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movZ += 0.08f;

    // Rotación en X
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        rotX += 0.4f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        rotX -= 0.4f;

    // Rotación en Y
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rotY += 0.4f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rotY -= 0.4f;

    // Rotación en Z
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        rotZ += 0.4f;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        rotZ -= 0.4f;
}