// COMP710 GP Framework 2022 
#ifndef __SCENE_H 
#define __SCENE_H 

#include <fmod.hpp>

// Forward declarations: 
class Renderer;
class InputSystem;
class SoundSystem;
// Class declaration: 
class Scene
{
	// Member methods: 
public:
	Scene();
	virtual ~Scene();
	virtual bool Initialise(Renderer& renderer, SoundSystem* soundSystem) = 0;
	virtual void Process(float deltaTime, InputSystem& inputSystem) = 0;
	virtual void Draw(Renderer& renderer) = 0;
	virtual void DebugDraw() = 0;
	virtual void SetupAudio(FMOD::System* audio) {}
protected:
private:
	Scene(const Scene& scene);
	Scene& operator=(const Scene& scene);
	// Member data: 
public:
protected:
private:
};
#endif // __SCENE_H 
