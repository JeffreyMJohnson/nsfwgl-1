#include "GPass.h"

#include <glCore\gl_core_4_4.h>

void GPass::prep()
{
	// renders the albedo, position, and normal
	glEnable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_FRAMEBUFFER, *fbo);

	//TODO_D("HARD CODED VIEWPORT VALUES!!!");

	//glViewport(0, 0, 1280, 720);
	glClearColor(1, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(*shader);
}

void GPass::post()
{
	glDisable(GL_DEPTH_TEST);
}

void GPass::draw(const Camera &c, const Geometry &g)
{
	setUniform("Projection", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getProjection()));
	setUniform("View", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getView()));
	setUniform("Model", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(g.transform));

	setUniform("Diffuse", nsfw::UNIFORM::TEX2, g.diffuse, 0);
	setUniform("Normal", nsfw::UNIFORM::TEX2, g.normal, 1);
	//setUniform("Specular", nsfw::UNIFORM::TEX2, g.specular, 2);

	//setUniform("SpecularPower", nsfw::UNIFORM::FLO1, (void*)&g.specPower);

	glBindVertexArray(*g.mesh);
	glDrawElements(GL_TRIANGLES, *g.tris, GL_UNSIGNED_INT, 0);
}