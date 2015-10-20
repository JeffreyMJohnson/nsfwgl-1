
#include "DefApp.h"

#include <glCore\gl_core_4_4.h>

#include "Geometry.h"
#include "Light.h"
#include "Camera.h"

#include "GPass.h"
#include "CPass.h"
#include "LPassD.h"


using namespace nsfw;

int main()
{
	DeferredApplication d;

	d.init();
	d.play();
	d.term();

	system("pause");
}

void DeferredApplication::onInit()
{
	auto &w = nsfw::Window::instance();
	auto &a = nsfw::Assets::instance();

	// Setup FBOs
	const char *gpassTextureNames[] = { "GPassAlbedo","GPassPosition","GPassNormal","GPassDepth" };
	const unsigned gpassDepths[] = { GL_RGB8, GL_RGB32F, GL_RGB32F, GL_DEPTH_COMPONENT }; // GL_RGB8, GL_RGB32, GL_RGB32, GL_DEPTH_COMPONENT
	a.makeFBO("GeometryPass", w.getWidth(), w.getHeight(), 4, gpassTextureNames, gpassDepths);

	const char *lpassTextureNames[] = { "LPassColor" };
	const unsigned lpassDepths[] = { GL_RGB8 }; // GL_RGB8
	a.makeFBO("LightPass", w.getWidth(), w.getHeight(), 1, lpassTextureNames, lpassDepths); 

	// Load Shaders
	a.loadShader("GeometryPassPhong", "resources/shaders/gpass.vert", "resources/shaders/gpass.frag");
	a.loadShader("LightPassDirectional", "resources/shaders/lpass.vert", "resources/shaders/lpass.frag");
	//a.loadShader("LightPassPoint", "/path/to/lpass/Point/vertex", "/path/to/lpass/Point/fragment");
	a.loadShader("CompPass", "resources/shaders/cpass.vert", "resources/shaders/cpass.frag");

	// Load any other textures and geometry we want to use
	a.loadFBX("Cube", "resources/models/cube.fbx");
	a.loadFBX("Soulspear", "resources/models/Soulspear/soulspear.fbx");
}

void DeferredApplication::onPlay()
{
	//TODO_D("Initialize our scene objects!");
	m_camera    = new Camera;
	m_light     = new LightD;
	m_cube		= new Geometry;
	m_soulspear = new Geometry;

	m_camera->lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0,1,0));

	m_light->color      = glm::vec3(1, 1, 1);
	m_light->direction = glm::normalize(glm::vec3(1, 1, 0));

	m_cube->mesh			= "Cube/cube";
	m_cube->tris			= "Cube/cube";
	m_cube->diffuse			= "Soulspear/soulspear_diffuse.tga";	// loadFBX will need to name every handle it creates,
	m_cube->normal			= "Soulspear/soulspear_normal.tga";		// These handle names may not be what your loadFBX sets 
	m_cube->specular		= "Soulspear/soulspear_specular.tga";	// them as! (Assets will report what the key names are though)
	m_cube->specPower		= 40.0f;
	m_cube->transform		= glm::mat4(1);

	m_soulspear->mesh		= "Soulspear/SoulSpear_Low:SoulSpear_Low1";
	m_soulspear->tris		= "Soulspear/SoulSpear_Low:SoulSpear_Low1";
	m_soulspear->diffuse	= "Soulspear/soulspear_diffuse.tga";	// loadFBX will need to name every handle it creates,
	m_soulspear->normal		= "Soulspear/soulspear_normal.tga";		// These handle names may not be what your loadFBX sets 
	m_soulspear->specular	= "Soulspear/soulspear_specular.tga";	// them as! (Assets will report what the key names are though)
	m_soulspear->specPower	= 40.0f;
	m_soulspear->transform	= glm::mat4(1);

	//TODO_D("Initialize our render passes!");

	m_geometryPass			= new GPass ("GeometryPassPhong", "GeometryPass");
	m_directionalLightPass  = new LPassD("LightPassDirectional", "LightPass");
	m_compositePass			= new CPass ("CompPass", "Screen"); // Screen is defined in nsfw::Assets::init()
}

void DeferredApplication::onStep()
{
	//TODO_D("Update our game objects-- IF THEY EVEN DO ANYTHING");
	m_light->update();
	m_camera->update();
	m_cube->update();
	m_soulspear->update();
	
	//TODO_D("Draw all of our renderpasses!");
	//m_geometryPass->prep();
	//m_geometryPass->draw(*m_camera, *m_cube);
	//m_geometryPass->post();

	//m_directionalLightPass->prep();
	//m_directionalLightPass->draw(*m_camera, *m_light);
	//m_directionalLightPass->post();

	m_compositePass->prep();
	m_compositePass->draw();
	m_compositePass->post();
}

void DeferredApplication::onTerm()
{
	delete m_camera;
	delete m_light;
	delete m_soulspear;

	delete m_compositePass;
	delete m_geometryPass;
	delete m_directionalLightPass;
}
