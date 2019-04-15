#include <GLFW/glfw3.h>
#include <stdio.h>
#include <direct.h>
#include "MWCoreAPI.h"
#include "System\ISystem.h"
#include <string>
#include "Memory\MemoryDefine.h"
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;


class A
{
public:

	A()
	{
		a = 100;
		b = 100.0;
		c = false;
	}

private:

	int a;
	float b;
	bool c;
};


class B
{
public:

	B()
	{
		vx = 12345;
		y = 200.0f;
		str = "asdasdasd";
	}
public:

	int vx;
	A z;
	float y;
	std::string str;
	bool s;
};

class Test
{
public:

	template<class ClassType, class FieldType>
	static int GetOffset(FieldType ClassType::* member)
	{
		return reinterpret_cast<size_t>(&(reinterpret_cast<ClassType const volatile*>(0)->*member));
	}
};
int	main()
{
	// glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	B* pB = MW_New B();

	void* p = (void*)pB;

	int* pBx = (int*)p;
	

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Game", NULL, NULL);
    if (window == NULL)
    {
        //std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Core::MWCoreAPI::GetInstance()->Initialize();

	while (!glfwWindowShouldClose(window))
	{

	}


	return 0;
}


// process all input : query GLFW whether relevant keys are pressed / released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	//glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	
}
