#include "Render.h"

#include "nsfw.h"

#include <glCore\gl_core_4_4.h>

// Each Case should set up a uniform using the pass parameters
bool nsfw::RenderPass::setUniform(const char *name, nsfw::UNIFORM::TYPE type, const void *value, unsigned count, bool normalize) 
{
	GLint uniformLocation = glGetUniformLocation(*shader, name);
	assert(uniformLocation >= 0 && "Uniform must be 0 or greater to be valid!");

	switch (type)
	{
	case nsfw::UNIFORM::FLO1: glUniform1f(uniformLocation, *(GLfloat*)value);								break;
	case nsfw::UNIFORM::FLO3: glUniform3fv(uniformLocation, 1, (GLfloat*)value);							break;
	case nsfw::UNIFORM::FLO4: glUniform4fv(uniformLocation, 1, (GLfloat*)value);							break;
	case nsfw::UNIFORM::MAT4: glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, (const GLfloat*)value);		break;
	case nsfw::UNIFORM::INT1: glUniform1i(uniformLocation, *(GLint*)value);									break;
	case nsfw::UNIFORM::TEX2:
	{
		// THIS IS NOT SAFE
		// THIS IS NOT PORTABLE
		// THIS ONLY COMPILES ON MSVC
		// "Magic must defeat magic!" - Uncle
		void * danger = ((char*&)value)+8;
		AssetKey * key = (AssetKey*)danger;
		int textureName = Assets::instance().get(*key);

		glActiveTexture(GL_TEXTURE0 + count);
		glBindTexture(GL_TEXTURE_2D, textureName);
		glUniform1i(uniformLocation, count);
		break;
	}
	default:
		//TODO_D("INVALID Uniform type.");
		std::cerr << "An invalid uniform type was specified while attempting to set a uniform." << std::endl;
		return false;

		break;
	}

	return true;
}

// set GL state settings and globally accessible uniforms! Should be called before rendering occurs!
void nsfw::RenderPass::prep() { TODO_D("OVERRIDE: Setup the state of the card for this pass."); }

// reset the GL state- undo what we did just in case.
void nsfw::RenderPass::post() { TODO_D("OVERRIDE: Clean up the state of the card."); }