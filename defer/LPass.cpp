#include "LPassD.h"

#include <glCore\gl_core_4_4.h>

void LPassD::prep()
{
	glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glUseProgram(*shader);
}

void LPassD::post()
{
	glDisable(GL_BLEND);
}

void LPassD::draw(const Camera &c, const LightD &l)
{
	setUniform("Projection", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getProjection()));
	setUniform("View", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getView()));

	setUniform("LightDirection", nsfw::UNIFORM::TYPE::FLO3, glm::value_ptr(l.direction));
	setUniform("LightColor", nsfw::UNIFORM::TYPE::FLO3, glm::value_ptr(l.color));

	int hackPos = nsfw::Assets::instance().get<nsfw::ASSET::TEXTURE>("GPassPosition");
	int hackNorm = nsfw::Assets::instance().get<nsfw::ASSET::TEXTURE>("GPassNormal");
	setUniform("Position", nsfw::UNIFORM::TEX2, &hackPos);
	setUniform("Normal", nsfw::UNIFORM::TEX2, &hackNorm);

	//setUniform("TexelScalar", nsfw::UNIFORM::MAT4, glm::value_ptr(nsfw::Window::instance().getTexelAdjustmentMatrix()));

	unsigned quadVAOHandle = nsfw::Assets::instance().get<nsfw::ASSET::VAO>("Quad");
	unsigned quadNumtris = nsfw::Assets::instance().get<nsfw::ASSET::INDEXCOUNT>("Quad");

	//TODO_D("GL BindVAO/DrawElements with quad size and vao");

	glBindVertexArray(quadVAOHandle);
	glDrawElements(GL_TRIANGLES, quadNumtris, GL_UNSIGNED_INT, 0);
}