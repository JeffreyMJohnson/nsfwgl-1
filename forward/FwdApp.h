#pragma once

#include "Application.h"

struct Camera;
struct Geometry;
struct LightD;

class RPass;

class ForwardApplication : public nsfw::Application
{
	Camera   *m_camera;

	Geometry *m_cube;
	Geometry *m_soulspear;

	RPass	 *m_renderPass;

public:
	void onInit();
	void onStep();
	void onTerm();
	void onPlay();
};