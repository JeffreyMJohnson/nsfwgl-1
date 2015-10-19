#include "RPass.h"

#include <glCore\gl_core_4_4.h>

void RPass::prep()
{
	// clear the frontbuffer
	glClearColor(0.5f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind shader program
	glUseProgram(*shader);
}

void RPass::post()
{

}

void RPass::draw(const Camera &c, const Geometry &g)
{
	setUniform("Projection", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getProjection()));
	setUniform("View", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(c.getView()));
	setUniform("Model", nsfw::UNIFORM::TYPE::MAT4, glm::value_ptr(g.transform));

	TODO_D("Support advanced lighting and texturing.");

	unsigned int vaoName = *g.mesh;
	unsigned int indexCount = *g.tris;

	glBindVertexArray(*g.mesh);
	glDrawElements(GL_TRIANGLES, *g.tris, GL_UNSIGNED_INT, 0);
}