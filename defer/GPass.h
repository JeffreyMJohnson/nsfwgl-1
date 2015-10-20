#pragma once
#include "Render.h"

#include "nsfw.h"

#include "Camera.h"
#include "Geometry.h"


class GPass : public nsfw::RenderPass
{


public:	
	void prep(); //{ TODO_D("glUseProgram, glClear, glBindFrameBuffer, glViewPort, glEnable etc..."); }
	void post(); //{ TODO_D("Unset any gl settings"); }

	GPass(const char *shaderName, const char *fboName) : RenderPass(shaderName, fboName) {}

	void draw(const Camera &c, const Geometry &g);
};