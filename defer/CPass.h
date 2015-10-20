#pragma once

#include "nsfw.h"
#include "Render.h"

#include "Camera.h"

class CPass : public nsfw::RenderPass
{
	nsfw::Asset<nsfw::ASSET::TEXTURE> albedo, position, normal, depth, light;

public:
											
	CPass(const char *shaderName, const char *fboName) 
						  : RenderPass(shaderName, fboName), albedo("GPassAlbedo"), position("GPassPosition"), // NAMES ARE FROM ASSET LIBRARY!
											    normal("GPassNormal"),depth("GPassDepth"), light("LPassColor")
												 {}


	void prep();// { TODO_D("glUseProgram, glClear, glBindFrameBuffer, glViewPort, glEnable etc..."); }
	void post();// { TODO_D("Unset any gl settings"); }


	void draw();
};