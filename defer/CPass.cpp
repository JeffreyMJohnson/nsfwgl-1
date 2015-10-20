#include "CPass.h"

#include <glCore\gl_core_4_4.h>

#include "Window.h"

void CPass::prep()
{
	// renders a quad and combines albedo and light
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	

	// is this viewport okay?
	/*auto &window = nsfw::Window::instance();
	glViewport(0, 0, window.getWidth(), window.getHeight());*/

	glClearColor(0.33f, 0.f, 0.33f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glUseProgram(*shader);
}

void CPass::post()
{
	// todo huh
}

void CPass::draw()
{
	// Set uniforms for textures we're going to composite-> NAMES ARE FROM SHADER!
	//setUniform("Albedo", nsfw::UNIFORM::TEX2, albedo, 0);
	//setUniform("Position", nsfw::UNIFORM::TEX2, position, 1);
	//setUniform("Normal", nsfw::UNIFORM::TEX2, normal, 2);
	//setUniform("Depth", nsfw::UNIFORM::TEX2, depth, 3);
	//setUniform("Light", nsfw::UNIFORM::TEX2, light, 4);

	//setUniform("TexelScalar", nsfw::UNIFORM::MAT4, glm::value_ptr(nsfw::Window::instance().getTexelAdjustmentMatrix()));

	unsigned quadVAOHandle = nsfw::Assets::instance().get<nsfw::ASSET::VAO>("Quad");
	unsigned quadNumtris = nsfw::Assets::instance().get<nsfw::ASSET::INDEXCOUNT>("Quad");

	//TODO_D("GL BindVAO/DrawElements with quad size and vao");

	glBindVertexArray(quadVAOHandle);
	glDrawElements(GL_TRIANGLES, quadNumtris, GL_UNSIGNED_INT, 0);
}