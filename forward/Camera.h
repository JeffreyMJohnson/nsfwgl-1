#pragma once

#include <glm\glm.hpp>
#include <glm\ext.hpp>

#include "Window.h"

struct Camera
{
	glm::mat4 transform;
	float nearClip, farClip, aspect, fov;

	Camera() : nearClip(0), farClip(100), aspect(nsfw::Window::instance().getWidth() / (float)nsfw::Window::instance().getHeight()), fov(90) {}

	void update() {}
	void lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 up) { transform = glm::inverse(glm::lookAt(pos, target, up)); }
	glm::mat4 getView()		  const { return glm::inverse(transform); }
	glm::mat4 getProjection() const { return glm::perspective(fov, aspect, nearClip, farClip); }
};