#include "RPass.h"

#include <glCore\gl_core_4_4.h>

void RPass::draw(const Camera &c, const Geometry &g)
{
	setUniform("Projection", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getProjection()));
	setUniform("View", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getView()));
	setUniform("Model", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(g.transform));

	TODO_D("Support advanced lighting and texturing.");

	glBindVertexArray(*g.mesh);
	glDrawElements(GL_TRIANGLES, *g.tris, GL_UNSIGNED_INT, 0);
}