#include "Bomberman.hpp"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "Key entry : " << key << " action : " << action << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    //if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    std::cout << "Mouse entry : " << button << " action : " << action << std::endl;
}

class HH : public IRenderLoop {
	void controllerLoop( void ) {
		std::cout << "HAHHAHA1" << std::endl;
	}

	void renderLoop( void ) {
		std::cout << "HAHHAHA2" << std::endl;
	}
};

int main(void)
{

	RenderLoop *loop = new RenderLoop(new HH());

	loop->start();

    // GLFWwindow* window;
    // glfwSetErrorCallback(error_callback);
    // if (!glfwInit())
    //     exit(EXIT_FAILURE);
    // window = glfwCreateWindow(640, 480, "Bomberman", NULL, NULL);
    // if (!window)
    // {
    //     glfwTerminate();
    //     exit(EXIT_FAILURE);
    // }
    // glfwMakeContextCurrent(window);
    // glfwSetKeyCallback(window, key_callback);
	// glfwSetCursorPosCallback(window, cursor_position_callback);
	// glfwSetMouseButtonCallback(window, mouse_button_callback);
    // while (!glfwWindowShouldClose(window))
    // {
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef((float) glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
        glBegin(GL_TRIANGLES);
	        glColor3f(1.f, 0.f, 0.f);
	        glVertex3f(-0.6f, -0.4f, 0.f);
	        glColor3f(0.f, 1.f, 0.f);
	        glVertex3f(0.6f, -0.4f, 0.f);
	        glColor3f(0.f, 0.f, 1.f);
	        glVertex3f(0.f, 0.6f, 0.f);
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    // }
    // glfwDestroyWindow(window);
    // glfwTerminate();
    // exit(EXIT_SUCCESS);
}
