#pragma once

#include "Render.h"

#include "../nsfwgl/nsfw.h"
#include "Light.h"
#include "Camera.h"

class LPassD : public nsfw::RenderPass
{
public:
	LPassD(const char *shaderName, const char *fboName) : RenderPass(shaderName, fboName) {}

	void prep();// { TODO_D("glUseProgram, glClear, glBindFrameBuffer, glViewPort, glEnable etc..."); }
	void post();// { TODO_D("Unset any gl settings"); }


	void draw(const Camera &c, const LightD &l);
};