#include "Window.h"

#include <glm\ext.hpp>
#include <glCore\gl_core_4_4.h>
#include <glfw\glfw3.h>

#include "nsfw.h"

void nsfw::Window::init(unsigned width, unsigned height)
{
	//TODO_D("Should create and set an active windowing context. ONLY GLFW! No GL!");
	assert(width > 0 && height > 0);	// validate window size

	int status = 0;
	status = glfwInit();
	assert(status == GL_TRUE);	// glfw initialization

	// @terrehbyte: consider the following... TODO_D("Expose a window title paramter.");
	window = glfwCreateWindow(width, height, "NSFWGL - Not Suited for Work - Open GL Edition", nullptr, nullptr);

	assert(window != nullptr);	// validate window created

	glfwMakeContextCurrent(window);
	
	status = ogl_LoadFunctions();
	assert(status == ogl_LOAD_SUCCEEDED);

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