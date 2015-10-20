#include "Window.h"

#include <glm\ext.hpp>
#include <glCore\gl_core_4_4.h>
#include <glfw\glfw3.h>

#include "nsfw.h"

// TODO: look into why this is different: http://docs.gl/gl4/glDebugMessageCallback 
// from the specified typedef

void APIENTRY oglErrorDefaultCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar *message,
	const void *userParam)
{
	// if 'GL_DEBUG_OUTPUT_SYNCHRONOUS' is enabled, you can place a
	// breakpoint here and the callstack should reflect the problem location!

	std::cerr << message << std::endl;
}

void nsfw::Window::init(unsigned width, unsigned height)
{
	//TODO_D("Should create and set an active windowing context. ONLY GLFW! No GL!");
	assert(width > 0 && height > 0);	// validate window size
	this->width = width;
	this->height = height;

	int status = 0;
	status = glfwInit();
	assert(status == GL_TRUE);	// glfw initialization

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	// @terrehbyte: consider the following... TODO_D("Expose a window title paramter.");
	window = glfwCreateWindow(width, height, "NSFWGL - Not Suited for Work - Open GL Edition", nullptr, nullptr);

	assert(window != nullptr);	// validate window created

	glfwMakeContextCurrent(window);
	
	status = ogl_LoadFunctions();
	assert(status == ogl_LOAD_SUCCEEDED);

	// TODO: only do this on ogl4.3+
#ifdef _DEBUG
	if (glDebugMessageCallback)
	{
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(oglErrorDefaultCallback, nullptr);

		GLuint unusedIDs = 0;
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIDs, true);
	}
	else
	{
		std::cerr << "Failed to subscribe to glDebugMessageCallback." << std::endl;
	}
#endif

	return;
}

void nsfw::Window::step()
{
	//TODO_D("GLFW poll events and swap buffers is all that should really be here! No GL!");
	glfwPollEvents();
	glfwSwapBuffers(window);
}

void nsfw::Window::term()
{
	//TODO();
	glfwDestroyWindow(window);
	glfwTerminate();
}

float nsfw::Window::getTime() const
{
	//TODO();
	return glfwGetTime();
}

bool nsfw::Window::getKey(unsigned k) const
{
	//TODO();
	return glfwGetKey(window, k);
}

bool nsfw::Window::getShouldClose() const
{
	//TODO();
	return glfwWindowShouldClose(window);
}

unsigned nsfw::Window::getWidth() const
{
	//TODO();
	return width;
}

unsigned nsfw::Window::getHeight() const
{
	//TODO();
	return height;
}

glm::mat4 nsfw::Window::getTexelAdjustmentMatrix() const
{
	TODO_D("Implemented, not tested.");

	glm::vec3 texelSize = 1.0f/glm::vec3(width,height,0);
	glm::vec3 halfTexel = texelSize * 0.5f; // bottom left

	// scale up to the appropriate size, then shift it to line up w/center of texels
	return glm::translate(halfTexel) * glm::scale(glm::vec3(1, 1, 1) - texelSize);	
}