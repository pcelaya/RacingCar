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
	// Aqui
	//Para la posicion, el eje 0,0,0 del cuadrado esta en el centro de este o en una esquina
	// el 0 0 0 es el centro del coche pero hemos subido las rampas pa q esten a 6 de distancia del suelo
	// con esto puedes ir haciendo perfe
	// Mira te explico	  (length, width, {posicion}, {color}, TIPO DE CUADRADO)
	App->physics->RectRoad(80, 20, { 0, 6, 0 }, { 0,0,0,0 }, FORWARD_RECT);
	App->physics->RectRoad(80, 20, { 0, 46, 10 }, { 0,0,0,0 }, FORWARD_RECT);

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

