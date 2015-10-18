#pragma once

#include "Render.h"

#include "nsfw.h"

#include "Camera.h"
#include "Geometry.h"

class RPass : public nsfw::RenderPass
{
public:
	RPass(const char *shaderName) : RenderPass(shaderName, "Screen") {}

	void prep() {}
	void post() {}

	void draw(const Camera &c, const Geometry &g);
};