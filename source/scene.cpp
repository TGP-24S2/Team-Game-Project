// COMP710 GP Framework 2022

// This include: 
#include "scene.h"

// Local includes: 
#include "renderer.h"
#include "soundsystem.h"

// Library includes: 
#include <cassert>
Scene::Scene()
{
}
Scene::~Scene()
{
}

bool
Scene::Initialise(Renderer& renderer, SoundSystem* soundSystem)
{
	return true;
}
