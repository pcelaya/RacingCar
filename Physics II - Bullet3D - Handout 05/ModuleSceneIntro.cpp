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

	//App->physics->Ground(500, 500, 0, 0, 0);
	// Mira te explico	  (length, width, {posicion}, {color}, TIPO DE CUADRADO)
	App->physics->RectRoad(80, 20, 0.1, { 0, 6, 0 }, { 0,0,0,0 }, FORWARD_RECT);
	App->physics->RectRoad(80, 20, 0.1, { 0, 6, 80 }, { 0,0,0,0 }, FORWARD_RECT);
	App->physics->RectRoad(80, 20, 0.1, { 0, 18, 155 }, { 0,0,0,0 }, INVERSE_RAMP);
	App->physics->RectRoad(80, 20, 0.1, { 0, 18, 255 }, { 0,0,0,0 }, RAMP);
	App->physics->RectRoad(80, 20, 0.1, { 0, 8, 305 }, { 0,0,0,0 }, FORWARD_RECT);
	//corners
	App->physics->RectRoad(80, 0.1, 10, { -3, 8, 380 }, { 0,0,0,0 }, TOP_RIGHT_CORNER);
	App->physics->RectRoad(80, 20, 0.1, { -10, 7.9, 380 }, { 0,0,0,0 }, TOP_RIGHT_RECT);
	//walls
	App->physics->RectRoad(80, 0.1, 10, { -10, 8, 0 }, { 0,0,0,0 }, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { 10, 8, 0 }, { 0,0,0,0 }, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { -10, 8, 80 }, { 0,0,0,0 }, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { 10, 8, 80 }, { 0,0,0,0 }, FORWARD_WALL);

	App->physics->RectRoad(80, 0.1, 10, { -10, 8, 305 }, { 0,0,0,0 }, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { 10, 8, 305 }, { 0,0,0,0 }, FORWARD_WALL);
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

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

