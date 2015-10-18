
#include "FwdApp.h"

#include "Geometry.h"
#include "Light.h"
#include "Camera.h"

#include "RPass.h"

using namespace nsfw;

int main()
{
	ForwardApplication d;

	d.init();
	d.play();
	d.term();

	system("pause");
}


void ForwardApplication::onInit()
{
	auto &w = nsfw::Window::instance();
	auto &a = nsfw::Assets::instance();

	// Load Shaders
	a.loadShader("ForwardShader", "/resources/shaders/forward.vert", "/resources/shaders/forward.frag");

	// Load any other textures and geometry we want to use
	a.loadFBX("Soulspear", "/path/to/souuuulspppeeeeaaar");
	a.loadFBX("Cube", "/resources/models/cube.fbx");
}

void ForwardApplication::onPlay()
{
	TODO_D("Initialize our scene objects!");
	m_camera    = new Camera;
	m_cube		= new Geometry;
	m_soulspear	= new Geometry;

	m_camera->lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0,1,0));

	// provision geometry w/ asset names to use at render time
	m_cube->mesh			= "Cube";
	m_cube->tris			= "Cube";
	m_cube->diffuse			= "Cube/CubeDiffuse";	// loadFBX will need to name every handle it creates,
	m_cube->normal			= "Cube/CubeNormal";		// These handle names may not be what your loadFBX sets 
	m_cube->specular		= "Cube/CubeSpecular";	// them as! (Assets will report what the key names are though)
	m_cube->specPower		= 40.0f;
	m_cube->transform		= glm::mat4(1);

	m_soulspear->mesh		= "Soulspear";
	m_soulspear->tris		= "Soulspear";
	m_soulspear->diffuse	= "SoulspearDiffuse";	// loadFBX will need to name every handle it creates,
	m_soulspear->normal		= "SoulspearNormal";		// These handle names may not be what your loadFBX sets 
	m_soulspear->specular	= "SoulspearSpecular";	// them as! (Assets will report what the key names are though)
	m_soulspear->specPower	= 40.0f;
	m_soulspear->transform	= glm::mat4(1);

	m_renderPass			= new RPass ("ForwardShader"); // Screen is defined in nsfw::Assets::init()
}

void ForwardApplication::onStep()
{
	TODO_D("Update our game objects-- IF THEY EVEN DO ANYTHING");
	m_camera->update();
	m_soulspear->update();
	m_cube->update();
	
	TODO_D("Draw all of our renderpasses!");
	m_renderPass->prep();
	m_renderPass->draw(*m_camera, *m_cube);
	//m_renderPass->draw(*m_camera, *m_soulspear);
	m_renderPass->post();
}

void ForwardApplication::onTerm()
{
	delete m_camera;
	delete m_cube;
	delete m_soulspear;

	delete m_renderPass;
}
