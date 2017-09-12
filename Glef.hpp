#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <GL/glew.h>

#include <glfw3.h>

#include <glm/glm.hpp>
using namespace glm;

enum glef_status
{
	OK,ERROR,UNKNOWN
};


class Glef {
public:
	/** Initialize Glef API
	@param samples Define amount of fragments per shader (default 4)
	@param major_version Define version of OpenGL, that should be used
	@param minor_version Define versin of OpenGL, that should be used if major version was no found
	@returns Refference to Glef instance
	*/
	static Glef& getInstance(int samples = 4, float major_version = 3, float minor_version = 3)
	{
		static Glef instance;
		return instance;
	}
	Glef(Glef const&) = delete;
	void operator=(Glef const&) = delete;

	/** Create new window
	@param title Define window title. (New Window by default)
	@param width Window width (1024 by default)
	@param height Window height (768 by default)
	@returns Status of window creation (glef_status) OK-if window was successfully created or ERROR-if there was error uppon creation
	*/
	glef_status CreateWindow(std::string title="New Window",int width= 1024, int height=768)
	{
		GLFWwindow* window;
		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (window == NULL) {
			std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\
						 Try the 2.1 version of the tutorials." << std::endl;
			getchar();
			glfwTerminate();
			return ERROR;
		}
		windows.push_back(window);
		return OK;
	}

	/** Create new window and set is as active
	@param title Define window title. (New Window by default)
	@param width Window width (1024 by default)
	@param height Window height (768 by default)
	@returns Status of window creation (glef_status) OK-if window was successfully created or ERROR-if there was error uppon creation
	*/
	glef_status CreateAndMakeActive(std::string title = "New Window", int width = 1024, int height = 768)
	{
		GLFWwindow* window;
		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (window == NULL) {
			std::cerr << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\
						 Try the 2.1 version of the tutorials." << std::endl;
			getchar();
			glfwTerminate();
			return ERROR;
		}
		glfwMakeContextCurrent(window);
		windows.push_back(window);
		active_window = window;
		return OK;
	}
private:
	Glef(int samples=4, float major_version = 3, float minor_version = 3)
	{
		if (!glfwInit())
		{
			std::cerr << "Failed to initialize GLFW" << std::endl;
			getchar();
			status = ERROR;
		}

		glfwWindowHint(GLFW_SAMPLES, samples);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_version);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_version);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	}
	GLFWwindow* active_window;
	std::vector <GLFWwindow*> windows;
	glef_status status = UNKNOWN;
};