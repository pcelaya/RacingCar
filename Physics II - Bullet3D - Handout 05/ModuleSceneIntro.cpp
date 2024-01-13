#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	//------------------suelo------------------
	//principio
	App->physics->RectRoad(80, 20, 0.1, { 0, 6, 0 }, { 255,0,0,0 }, FORWARD_RECT);
	App->physics->RectRoad(80, 20, 0.1, { 0, 6, 80 }, { 255,0,0,0 }, FORWARD_RECT);
	//salto
	App->physics->RectRoad(80, 20, 0.1, { 0, 18, 155 }, { 255,0,0,0 }, INVERSE_RAMP);
	App->physics->RectRoad(80, 20, 0.1, { 0, 18, 255 }, { 255,0,0,0 }, RAMP);
	//despues del salto
	App->physics->RectRoad(80, 20, 0.1, { 0, 8, 305 }, { 255,0,0,0 }, FORWARD_RECT);
	App->physics->RectRoad(80, 20, 0.1, { 0, 6.5, 385 }, { 255,0,0,0 }, FORWARD_RECT);
	//carretera derecha
	App->physics->RectRoad(80, 20, 0.1, { -30, 6.5, 435 }, { 255,0,0,0 }, RIGHT_RECT);
	//escaleras
	App->physics->RectRoad(10, 20, 0.1, { -70, 7.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 0.1, { -80, 8.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 0.1, { -90, 9.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 0.1, { -100, 10.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 0.1, { -110, 11.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 0.1, { -120, 12.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 0.1, { -130, 13.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 0.1, { -140, 14.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 0.1, { -150, 15.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 0.1, { -160, 16.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 0.1, { -170, 17.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 0.1, { -180, 18.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(45, 20, 0.1, { -210, 19.5, 435 }, { 0,0,0,0 }, RIGHT_RECT);

	// Mega Rampa
	App->physics->RectRoad(20, 160, 0.1, { -300, 51, 435 }, { 0,0,0,0 }, RIGHT_INVERSE_RAMP);
	App->physics->RectRoad(45, 20, 0.1, { -395, 85, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -425, 80, 435 }, { 0,0,0,0 }, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -435, 70, 435 }, { 0,0,0,0 }, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -445, 60, 435 }, { 0,0,0,0 }, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -455, 50, 435 }, { 0,0,0,0 }, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -465, 40, 435 }, { 0,0,0,0 }, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -475, 30, 435 }, { 0,0,0,0 }, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -485, 20, 435 }, { 0,0,0,0 }, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -495, 10, 435 }, { 0,0,0,0 }, LEFT_RECT);
	
	// Final
	App->physics->RectRoad(45, 20, 0.1, { -530, 0, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(45, 0.1, 10, { -530, 5, 445 }, { 0,0,0,0 }, RIGHT_WALL);
	App->physics->RectRoad(45, 0.1, 10, { -530, 5, 425 }, { 0,0,0,0 }, RIGHT_WALL);
	App->physics->RectRoad(45, 20, 0.1, { -575, 0, 435 }, { 0,0,0,0 }, RIGHT_RECT);
	App->physics->RectRoad(45, 0.1, 10, { -575, 5, 445 }, { 0,0,0,0 }, RIGHT_WALL);
	App->physics->RectRoad(45, 0.1, 10, { -575, 5, 425 }, { 0,0,0,0 }, RIGHT_WALL);
	App->physics->RectRoad(20, 0.1, 10, { -595, 5, 435}, { 0,0,0,0 }, FORWARD_WALL);
	
	//------------------walls------------------
	App->physics->RectRoad(80, 0.1, 10, { -10, 8, 0 }, { 0,0,0,0 }, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { 10, 8, 0 }, { 0,0,0,0 }, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { -10, 8, 80 }, { 0,0,0,0 }, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { 10, 8, 80 }, { 0,0,0,0 }, FORWARD_WALL);

	App->physics->RectRoad(80, 0.1, 10, { -10, 8, 305 }, { 0,0,0,0 }, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { 10, 8, 305 }, { 0,0,0,0 }, FORWARD_WALL);

	App->physics->RectRoad(80, 0.1, 10, { -10, 8, 385 }, { 0,0,0,0 }, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { 10, 8, 385 }, { 0,0,0,0 }, FORWARD_WALL);

	App->physics->RectRoad(20, 0.1, 10, { 10, 8, 435 }, { 0,0,0,0 }, FORWARD_WALL);

	App->physics->RectRoad(80, 0.1, 10, { -30, 8, 445 }, { 0,0,0,0 }, RIGHT_WALL);
	App->physics->RectRoad(60, 0.1, 10, { -40, 8, 425 }, { 0,0,0,0 }, RIGHT_WALL);

	//App->physics->RectRoad(80, 20, 0.1, { -10, 7.9, 380 }, { 0,0,0,0 }, TOP_RIGHT_RECT);
	//Necesito poder modificar el angulo del suelp ara poder hacer giros
	

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	for (uint n = 0; n < PrimitiveObjects.Count(); n++)
	{
		//PrimitiveObjects[n]->body->GetTransform(&transMatrix);
		//PrimitiveObjects[n]->transform = transMatrix;
		PrimitiveObjects[n]->Render();
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

