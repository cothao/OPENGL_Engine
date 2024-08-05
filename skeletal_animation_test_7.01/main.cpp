#include "engine.h"
#include "gui.h"
#include <commdlg.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
unsigned int loadTexture(const char* path);
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1200;
bool editMode = true;
float DeltaTime = 0.0f;
float lastFrame = 0.0f; 
float offset = 0.5f;
float alphaValue = 0.2f;
float xf = 1.0f;
float lastX = 1600, lastY = 600;
float yaw = -90.0f;
float pitch = -45.0f;
int k = 0;
bool firstMouse = true;
Engine engine = Engine();
Gui gui = Gui();
// hello;
int main() {

    engine.initEngine();
    engine.initObjects();

    glfwSetFramebufferSizeCallback(engine.window, framebuffer_size_callback);

    glfwSetInputMode(engine.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(engine.window, mouse_callback);

    glfwSetScrollCallback(engine.window, scroll_callback);

    glfwSetKeyCallback(engine.window, key_callback);


    gui.initGui(engine);

    while (!glfwWindowShouldClose(engine.window))
    {


        float currentFrame = glfwGetTime();
        DeltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gui.newGuiFrame();

        engine.render(DeltaTime);
        engine.processInputs(DeltaTime, editMode);

        gui.displayGui(engine, editMode);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(engine.window);
        glfwPollEvents();

    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

	return 0;

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

    if (key >= 0 && key <= 1024)
    {
        if (action == GLFW_PRESS)
        {
            engine.pObject.Keys[key] = true;
            engine.Keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            engine.pObject.Keys[key] = false;
            engine.Keys[key] = false;

        }
    }
        
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);


    // Normalize mouse coordinates
    float xnorm = xpos / engine.SCR_WIDTH - 0.5f;
    float ynorm = (ypos / engine.SCR_HEIGHT - 0.5f) * -1.0f;

    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 xypos = glm::vec3(xnorm, ynorm, 0.0f);

    // Calculate angle using atan2 for full range
    float angle = atan2(ynorm, xnorm);
    if (angle < 0.0f) {
        angle += glm::two_pi<float>(); // Ensure angle is in the range [0, 2?]
    }

    engine.pObject.RotateY = angle;

    // Print or use the angle
    //std::cout << "Angle in radians: " << angle << std::endl;

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
    if (!editMode)
    {
    engine.camera.ProcessMouseMovement(xoffset, yoffset);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (!editMode)
    {
        engine.camera.ProcessMouseScroll(static_cast<float>(yoffset));
    }
}

void processMousInput()
{

}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
