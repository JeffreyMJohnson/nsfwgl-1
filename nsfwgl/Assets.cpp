#include "Assets.h"

#include <iostream>
#include <fstream>

#include <sys/types.h>
#include <sys/stat.h>


#include <fbxLoader\FBXFile.h>
#include <stb\stb_image.h>
#include <glCore\gl_core_4_4.h>

#include "nsfw.h"
#include "Window.h"
#include "Vertex.h"

using namespace nsfw::ASSET;

const char *nsfw::TYPE_NAMES[eSIZE + 1] = { "NONE","vao","ibo","vbo","tri-size","fbo","rbo","texture","shader","SIZE" };

#ifdef _DEBUG
#define ASSET_LOG(type) do { std::cerr << "Trying to create key: <" << TYPE_NAMES[type] << ">" << name << std::endl; } while(0)
#else 
#define ASSET_LOG(type) do {} while (0)
#endif

// portable way to check if dir exists :: http://stackoverflow.com/questions/18100097/portable-way-to-check-if-directory-exists-windows-linux-c

// verifies if a file exists at the path provided
// - returns true if valid file
// - returns false if invalid file
// CONSIDER: should this make use of an enum instead?
// CONSIDER: should this tell us if we were denied access or if this is a dir?
bool validateFilePath(const char * path)
{
	struct stat info;	// we'll keep this for breakpoints for now...
	return stat(path, &info) == 0 ? true : false;
}


nsfw::GL_HANDLE nsfw::Assets::getVERIFIED(const AssetKey &key) const
{
#ifdef _DEBUG
			if (!handles.count(key))
			{
				std::cerr << "Asset Key not found: <" << TYPE_NAMES[key.first] << ">" << key.second << std::endl;
				return 0;
			}
#endif
			return handles.at(key);
}

bool nsfw::Assets::setINTERNAL(ASSET::GL_HANDLE_TYPE t, const char *name, GL_HANDLE handle)
{
	AssetKey key(t, name);
#ifdef _DEBUG
	if (handles.count(key))
	{
		std::cerr << "Asset Key already exists: <" << TYPE_NAMES[key.first] << ">" << key.second << " ignoring." << std::endl;
		return false;
	}
	else std::cerr << "Asset Key successfully created: <" << TYPE_NAMES[key.first] << ">" << key.second << std::endl;
#endif
	handles[key] = handle;
	return true;
}


bool nsfw::Assets::makeVAO(const char * name, const struct Vertex *verts, unsigned vsize,  const unsigned * tris, unsigned tsize)
{
	ASSET_LOG(GL_HANDLE_TYPE::VBO);
	ASSET_LOG(GL_HANDLE_TYPE::IBO);
	ASSET_LOG(GL_HANDLE_TYPE::VAO);
	ASSET_LOG(GL_HANDLE_TYPE::INDEXCOUNT);
	//TODO_D("Should generate VBO, IBO, VAO, and SIZE using the parameters, storing them in the 'handles' map.\nThis is where vertex attributes are set!");

	assert(name != nullptr);
	assert(verts != nullptr && vsize > 0);
	assert(tris != nullptr && tsize > 0);

	unsigned int vao, vbo, ibo;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	assert(vao > 0 && vbo > 0 && ibo > 0 && "Buffers must be non-zero to be valid!");

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vsize, verts, GL_STATIC_DRAW);

#ifdef _DEBUG
	assert(glGetError() == GL_NO_ERROR);
	GLint bufferedVBODataSize = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferedVBODataSize);
	assert(sizeof(Vertex) * vsize == bufferedVBODataSize && "Mismatch detected in vertex data size and buffer data size!");
#endif

	// NOTE! These need to correlate with the Vertex structure in Vertex.h!
	glEnableVertexAttribArray(0);	// Position
	glEnableVertexAttribArray(1);	// Normal
	glEnableVertexAttribArray(2);	// Tangent
	glEnableVertexAttribArray(3);	// TexCoord

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)POSITION_OFFSET);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE,	sizeof(Vertex), (GLvoid*)NORMAL_OFFSET);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)TANGENT_OFFSET);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)TEXCOORD_OFFSET);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * tsize, tris, GL_STATIC_DRAW);

#ifdef _DEBUG
	assert(glGetError() == GL_NO_ERROR);
	GLint bufferedIBODataSize = 0;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferedIBODataSize);
	assert(sizeof(unsigned int) * tsize == bufferedIBODataSize && "Mismatch detected in index data size and buffer data size!");
#endif

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	setINTERNAL(ASSET::VAO, name, vao);
	setINTERNAL(ASSET::VBO, name, vbo);
	setINTERNAL(ASSET::IBO, name, ibo);
	setINTERNAL(ASSET::INDEXCOUNT, name, tsize);

	return false;
}

bool nsfw::Assets::makeFBO(const char * name, unsigned w, unsigned h, unsigned nTextures, const char * names[], const unsigned depths[])
{
	ASSET_LOG(GL_HANDLE_TYPE::FBO);
	//TODO_D("Create an FBO! Array parameters are for the render targets, which this function should also generate!\nuse makeTexture.\nNOTE THAT THERE IS NO FUNCTION SETUP FOR MAKING RENDER BUFFER OBJECTS.");

	assert(name != nullptr);
	assert(w > 0 && h > 0);

	assert(false && "Needs Implementation");

	return false;

	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);



	return false;
}

bool nsfw::Assets::makeTexture(const char * name, unsigned w, unsigned h, unsigned depth, const char *pixels)
{
	ASSET_LOG(GL_HANDLE_TYPE::TEXTURE);
	//TODO_D("Allocate a texture using the given space/dimensions. Should work if 'pixels' is null, so that you can use this same function with makeFBO\n note that Dept will use a GL value.");

	assert(name != nullptr);
	assert(w > 0 && h > 0);

	// generate the texture and load it in
	GLuint textureName;
	glGenTextures(1, &textureName);
	glBindTexture(GL_TEXTURE_2D, textureName);

	TODO_D("Do we need to set the active texture?");

	// if 'pixels' is NULL, this is intended to be used w/ a FBO
	if (nullptr == pixels && depth != GL_DEPTH_COMPONENT)
	{
		auto& windowInst = Window::instance();
		glTexStorage2D(GL_TEXTURE_2D, 1, depth, windowInst.getWidth(), windowInst.getHeight());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else   // otherwise, we're creating a normal texture for meshes to use
	{
		glTexImage2D(GL_TEXTURE_2D, 0, depth, w, h, 0, depth, GL_UNSIGNED_BYTE, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

#ifdef _DEBUG
	GLenum textureStatus = glGetError();
	if (textureStatus != GL_NO_ERROR)
	{
		std::cerr << "A problem occurred while attempting to making a texture." << std::endl;
		glBindTexture(GL_TEXTURE_2D, 0);
		return false;
	}
#endif

	// add it to the asset manager
	setINTERNAL(ASSET::TEXTURE, name, textureName);

	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

bool nsfw::Assets::loadTexture(const char * name, const char * path)
{
	//TODO_D("This should load a texture from a file, using makeTexture to perform the allocation.\nUse STBI, and make sure you switch the format STBI provides to match what openGL needs!");
	assert(name != nullptr && path != nullptr);

#ifdef _DEBUG
	if (!validateFilePath(path))
	{
		std::cerr << "A texture could not be found at " << path << std::endl;
		return false;
	}
#endif
	
	int imgWidth = 0, imgHeight = 0, imgFormat = 0;
	const char * pixelData = (const char *)stbi_load(path, &imgWidth, &imgHeight, &imgFormat, STBI_default);

	if (nullptr == pixelData)
	{
		std::cerr << "A problem occurred while loading a texture: " << stbi_failure_reason() << std::endl;
		return false;
	}

	// showing off - http://stackoverflow.com/a/160887
	imgFormat = (imgFormat == 1) ? GL_RED :
				(imgFormat == 2) ? GL_RG :
				(imgFormat == 3) ? GL_RGB : GL_RGBA;

	makeTexture(name, imgWidth, imgHeight, imgFormat, pixelData);
	stbi_image_free((void*)pixelData);

	return true;
}

int nsfw::Assets::loadSubShader(unsigned int shaderType, const char * path)
{
	assert(path != nullptr && "Path to shader source file must not be null!");

#ifdef _DEBUG
	if (!validateFilePath(path))
	{
		std::cerr << "The source for a sub-shader could not be found at " << path << std::endl;
		return false;
	}
#endif

	std::ifstream in(path);
	std::string contents((std::istreambuf_iterator<char>(in)),
						  std::istreambuf_iterator<char>());

	char * src = new char[contents.length() + 1];
	strncpy_s(src, contents.length() + 1, contents.c_str(), contents.length());

	unsigned int shaderName = glCreateShader(shaderType);
	assert(glGetError() != GL_INVALID_ENUM && "Invalid shader type provided when creating a sub-shader.");

	glShaderSource(shaderName, 1, &src, 0);
	delete[] src;	// safe to delete since glShaderSource is called, the char array is copied into the shader

	glCompileShader(shaderName);

#ifdef _DEBUG
	GLint shaderStatus = GL_FALSE;
	glGetShaderiv(shaderName, GL_COMPILE_STATUS, &shaderStatus);
	if (shaderStatus == GL_FALSE)
	{
		int logLen = 0;
		glGetShaderiv(shaderName, GL_INFO_LOG_LENGTH, &logLen);
		char *log = new char[logLen];
		glGetShaderInfoLog(shaderName, logLen, 0, log);
		std::cerr << "A problem occurred while attempting to compile a sub-shader." << std::endl << log << std::endl;
		delete[] log;

		// clean up any openGL resources allocated
		glDeleteShader(shaderName);

		return -1;
	}
#endif

	return shaderName;
}

bool nsfw::Assets::loadShader(const char * name, const char * vpath, const char * fpath)
{
	ASSET_LOG(GL_HANDLE_TYPE::SHADER);
	//TODO_D("Load shader from a file.");

	assert(name != nullptr && vpath != nullptr && fpath != nullptr);

#ifdef _DEBUG
	if (!validateFilePath(vpath) || !validateFilePath(vpath))
	{
		std::cerr << "A problem occurred while attempting to load a shader program." << std::endl;

		if (!validateFilePath(vpath))
		{
			std::cerr << "Could not locate the Vertex Shader at " << vpath << std::endl;
		}

		if (!validateFilePath(fpath))
		{
			std::cerr << "Could not locate the Fragment Shader at " << vpath << std::endl;
		}

		return false;
	}
#endif

	int vShader = loadSubShader(GL_VERTEX_SHADER, vpath);
	int fShader = loadSubShader(GL_FRAGMENT_SHADER, fpath);

	int shaderName = glCreateProgram();
	assert(shaderName != 0 && "A problem occurred while attempting to create a shader program.");
	glAttachShader(shaderName, vShader);
	glAttachShader(shaderName, fShader);
	glLinkProgram(shaderName);
	

#ifdef _DEBUG
	int shaderStatus = GL_FALSE;
	glGetProgramiv(shaderName, GL_LINK_STATUS, &shaderStatus);
	if (shaderStatus == GL_FALSE)
	{
		int logLen = 0;
		glGetProgramiv(shaderName, GL_INFO_LOG_LENGTH, &logLen);
		char *log = new char[logLen];
		glGetProgramInfoLog(shaderName, logLen, 0, log);
		std::cerr << "A problem occurred while attempting to link the shader program." << std::endl << log << std::endl;
		delete[] log;
	}
#endif

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	
	setINTERNAL(ASSET::GL_HANDLE_TYPE::SHADER, name, shaderName);
	return true;
}

bool nsfw::Assets::loadFBX(const char * name, const char * path)
{
	//name/meshName
	//name/textureName
	//TODO_D("FBX file-loading support needed.\nThis function should call loadTexture and makeVAO internally.\nFBX meshes each have their own name, you may use this to name the meshes as they come in.\nMAKE SURE YOU SUPPORT THE DIFFERENCE BETWEEN FBXVERTEX AND YOUR VERTEX STRUCT!\n");

	assert(name != nullptr && path != nullptr);	// validate name and path is not null

#ifdef _DEBUG
	if (!validateFilePath(path))
	{
		std::cerr << "Could not locate the FBX file located at " << path << std::endl;
		return false;
	}
#endif
	FBXFile file;
	if (!file.load(path, FBXFile::UNITS_METER, true, false, true))
	{
		std::cerr << "Failed to load " << path << name << "!";
		return false;
	}

	// load mesh vertex data
	for (int meshIndex = 0; meshIndex < file.getMeshCount(); meshIndex++)
	{
		FBXMeshNode * mesh = file.getMeshByIndex(meshIndex);

		int vertCount = mesh->m_vertices.size();
		Vertex * verts = new Vertex[vertCount];

		// copy all FBX data into our vertex structure...
		for (int vertIndex = 0; vertIndex < vertCount; ++vertIndex)
		{
			auto &fbxVert = mesh->m_vertices[vertIndex];	// FBX data
			auto &finalVert = verts[vertIndex];				// our data

			finalVert.position	= fbxVert.position;
			finalVert.normal    = fbxVert.normal;
			finalVert.tangent	= fbxVert.tangent;
			finalVert.texCoord	= fbxVert.texCoord1;
		}

		// and then make things from it!
		std::string assetName = name;
		assetName += '/';
		assetName += mesh->m_name;	// because I'm lazy (sorry esme, but fbx is already using it~)

		makeVAO(assetName.c_str(), verts, vertCount, &mesh->m_indices[0], mesh->m_indices.size());

		delete[] verts;
	}

	// load texture data
	// we'll load them via our methods so we can control their creation parameters
	//
	// actually, it doesn't seem like we can get the paths w/o getting them loaded in,
	// so we'll let FBX handle the pixel load, but load then into OGL ourselves
	for (int textureIndex = 0; textureIndex < file.getTextureCount(); ++textureIndex)
	{
		auto * tex = file.getTextureByIndex(textureIndex);

		// skip over it if the data wasn't loaded
		if (tex->data == nullptr)
		{
			continue;
		}

		std::string assetName = name;
		assetName += '/';
		assetName += tex->name;

		// convert from STB format to OpenGL
		int texFormat = (tex->format == 1) ? GL_RED :
						(tex->format == 2) ? GL_RG :
						(tex->format == 3) ? GL_RGB : GL_RGBA;

		makeTexture(assetName.c_str(), tex->width, tex->height, texFormat, (const char *)tex->data);
	}

	file.unload();

	return true;
}

bool nsfw::Assets::loadOBJ(const char * name, const char * path)
{
	TODO_D("OBJ file-loading support needed.\nThis function should call makeVAO and loadTexture (if necessary), MAKE SURE TO TAKE THE OBJ DATA AND PROPERLY LINE IT UP WITH YOUR VERTEX ATTRIBUTES (or interleave the data into your vertex struct).\n");

	assert(name != nullptr && path != nullptr);	// validate name and path is not null

	assert(false && "Needs Implementation");

	return false;
}

void nsfw::Assets::init()
{
	setINTERNAL(FBO,"Screen",0);
	
	makeVAO("Cube",CubeVerts,24,CubeTris,36);
	makeVAO("Quad",QuadVerts, 4, QuadTris,6);
	/*
	char w[] = { 255,255,255,255 };
	makeTexture("White", 1, 1, GL_RGB8, w);
	*/

}

void nsfw::Assets::term()
{
	//TODO();
	for each(std::pair<AssetKey,unsigned> k in handles)
	{
		switch (k.first.first)
		{
		case VBO:		glDeleteBuffers(1, &k.second);		break;
		case IBO:		glDeleteBuffers(1, &k.second);		break;
		case VAO:		glDeleteVertexArrays(1, &k.second);	break;
		case SHADER:	glDeleteProgram(k.second);			break;
		case TEXTURE:	glDeleteTextures(1, &k.second);		break;
		case RBO:		glDeleteRenderbuffers(1, &k.second);break;
		case FBO:		glDeleteFramebuffers(1, &k.second);	break;
		}
	}

	// nothing to track anymore, remove the handles
	handles.clear();
}


