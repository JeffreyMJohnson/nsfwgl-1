#include "LPassD.h"

#include <glCore\gl_core_4_4.h>

void LPassD::prep()
{
	glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
	glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glUseProgram(*shader);
}

void LPassD::post()
{

}

void LPassD::draw(const Camera &c, const LightD &l)
{
	setUniform("Projection", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getProjection()));
	setUniform("View", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getView()));

	setUniform("LightDirection", nsfw::UNIFORM::TYPE::FLO3, glm::value_ptr(l.direction));
	setUniform("LightColor", nsfw::UNIFORM::TYPE::FLO3, glm::value_ptr(l.color));

	setUniform("TexelScalar", nsfw::UNIFORM::MAT4, glm::value_ptr(nsfw::Window::instance().getTexelAdjustmentMatrix()));

	unsigned quadVAOHandle = nsfw::Assets::instance().get<nsfw::ASSET::VAO>("Quad");
	unsigned quadNumtris = nsfw::Assets::instance().get<nsfw::ASSET::INDEXCOUNT>("Quad");

	//TODO_D("GL BindVAO/DrawElements with quad size and vao");

	glBindVertexArray(quadVAOHandle);
	glDrawElements(GL_TRIANGLES, quadNumtris, GL_UNSIGNED_INT, 0);
}