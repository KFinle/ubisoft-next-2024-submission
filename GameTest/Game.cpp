#include "stdafx.h"
#include <windows.h> 
#include <math.h>  
#include "app\app.h"
#include "../src/scenes/SceneController.h"

// Declare Scene Controller
std::unique_ptr<SceneController> controller = std::make_unique<SceneController>();

// Load initial screen
void Init()
{
	controller->LoadScene(scene_type::menu);
}

// Called every frame 
void Update(float deltaTime)
{
	controller->Update(deltaTime);
}

// renders the game
void Render()
{	
	//glutReshapeWindow(APP_VIRTUAL_WIDTH, APP_VIRTUAL_HEIGHT); <--- very sad we aren't allow to write any openGL code 
	controller->RenderScene();
}

// cleanup
// Nothing to cleanup in this file 
void Shutdown()
{	
}