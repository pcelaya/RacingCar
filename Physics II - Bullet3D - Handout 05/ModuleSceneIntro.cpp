#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"
#include "PhysVehicle3D.h"

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

	Color LightRed = { 0.976f, 0.152f, 0.152f, 0.8f };
	Color LightYellow = { 0.976f, 0.898f, 0.152f, 0.8f };
	Color LightBlue = { 0.152f, 0.819f, 0.976f, 0.8f };
	Color LightOrange = { 0.976f, 0.462f, 0.152f, 0.8f };
	
	//------------------checkpoints------------------
	Cube checkpoint_1(20, 2, 5);
	checkpoint_1.color = LightYellow;
	checkpoint_1.SetPos(0, 7, 10);
	App->physics->AddBody(checkpoint_1, 1, CHECKPOINT, -2.3, 5.5, 10);

	Cube checkpoint_2(20, 2, 5);
	checkpoint_2.color = LightYellow;
	checkpoint_2.SetPos(-200, 21, 435);
	vec3 rot = { 0,-1,0 };
	checkpoint_2.SetRotation(90, rot);
	App->physics->AddBody(checkpoint_2, 1, CHECKPOINT, -202.3, 19.5, 432.7);

	Cube checkpoint_3(20, 2, 5);
	checkpoint_3.color = LightYellow;
	checkpoint_3.SetPos(-530, 1, 435);
	rot = { 0,-1,0 };
	checkpoint_3.SetRotation(90, rot);
	App->physics->AddBody(checkpoint_3, 1, CHECKPOINT, -530, 0.5, 432.7);

	//-----------------Reduccion-----------------------

	Cube reduccion_1(20, 2, 5);
	reduccion_1.SetPos(-300, 51, 435);
	rot = { 0,-1,0 };
	checkpoint_3.SetRotation(90, rot);
	


	//------------------suelo------------------
	//principio
	App->physics->RectRoad(80, 20, 0.1, { 0, 6, 0 }, LightRed, FORWARD_RECT);
	App->physics->RectRoad(80, 20, 0.1, { 0, 6, 80 }, LightRed, FORWARD_RECT);
	//salto
	App->physics->RectRoad(80, 20, 0.1, { 0, 18, 155 }, LightRed, INVERSE_RAMP);
	App->physics->RectRoad(80, 20, 0.1, { 0, 18, 255 }, LightRed, RAMP);
	//despues del salto
	App->physics->RectRoad(160, 20, 0.1, { 0, 6.5, 365 }, LightRed, FORWARD_RECT);
	//carretera derecha
	App->physics->RectRoad(80, 20, 0.1, { -30, 6.5, 435 }, LightRed, RIGHT_RECT);
	//escaleras
	App->physics->RectRoad(10, 20, 1, { -70, 7.05, 435 }, LightRed, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 1, { -80, 8.05, 435 }, LightYellow, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 1, { -90, 9.05, 435 }, LightBlue, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 1, { -100, 10.05, 435 }, LightOrange, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 1, { -110, 11.05, 435 }, LightRed, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 1, { -120, 12.05, 435 }, LightYellow, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 1, { -130, 13.05, 435 }, LightBlue, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 1, { -140, 14.05, 435 }, LightOrange, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 1, { -150, 15.05, 435 }, LightRed, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 1, { -160, 16.05, 435 }, LightYellow, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 1, { -170, 17.05, 435 }, LightBlue, RIGHT_RECT);
	App->physics->RectRoad(10, 20, 1, { -180, 18.05, 435 }, LightOrange, RIGHT_RECT);
	App->physics->RectRoad(45, 20, 1, { -210, 19.05, 435 }, LightRed, RIGHT_RECT);

	// Mega Rampa
	App->physics->RectRoad(20, 160, 0.1, { -300, 51, 435 }, LightRed, RIGHT_INVERSE_RAMP);
	App->physics->RectRoad(45, 20, 0.1, { -395, 85, 435 }, LightRed, RIGHT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -425, 80, 435 }, LightYellow, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -435, 70, 435 }, LightBlue, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -445, 60, 435 }, LightOrange, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -455, 50, 435 }, LightRed, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -465, 40, 435 }, LightYellow, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -475, 30, 435 }, LightBlue, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -485, 20, 435 }, LightOrange, LEFT_RECT);
	App->physics->RectRoad(20, 10, 0.1, { -495, 10, 435 }, LightRed, LEFT_RECT);
	
	// Final
	App->physics->RectRoad(45, 20, 0.1, { -530, 0, 435 }, White, RIGHT_RECT);
	App->physics->RectRoad(45, 0.1, 10, { -530, 5, 445 }, White, RIGHT_WALL);
	App->physics->RectRoad(45, 0.1, 10, { -530, 5, 425 }, White, RIGHT_WALL);
	App->physics->RectRoad(45, 20, 0.1, { -575, 0, 435 }, White, RIGHT_RECT);
	App->physics->RectRoad(45, 0.1, 10, { -575, 5, 445 }, White, RIGHT_WALL);
	App->physics->RectRoad(45, 0.1, 10, { -575, 5, 425 }, White, RIGHT_WALL);
	App->physics->RectRoad(45, 20, 0.1, { -620, 0, 435 }, White, RIGHT_RECT);
	App->physics->RectRoad(45, 0.1, 10, { -620, 5, 445 }, White, RIGHT_WALL);
	App->physics->RectRoad(45, 0.1, 10, { -620, 5, 425 }, White, RIGHT_WALL);
	App->physics->RectRoad(45, 20, 0.1, { -652.5, 0, 422.5 }, LightRed, FORWARD_RECT);
	App->physics->RectRoad(20, 0.1, 10, { -652.5, 5, 445 }, White, RIGHT_WALL);
	App->physics->RectRoad(45, 0.1, 10, { -662.5, 5, 422.5 }, White, FORWARD_WALL);
	App->physics->RectRoad(25, 0.1, 10, { -642.5, 5, 412.5 }, White, FORWARD_WALL);
	App->physics->RectRoad(45, 20, 0.1, { -652.5, 0, 377.5 }, LightRed, FORWARD_RECT);
	App->physics->RectRoad(45, 0.1, 10, { -662.5, 5, 377.5 }, White, FORWARD_WALL);
	App->physics->RectRoad(45, 0.1, 10, { -642.5, 5, 377.5 }, White, FORWARD_WALL);
	App->physics->RectRoad(45, 20, 0.1, { -652.5, 0, 332.5 }, LightRed, FORWARD_RECT);
	App->physics->RectRoad(45, 0.1, 10, { -662.5, 5, 332.5 }, White, FORWARD_WALL);
	App->physics->RectRoad(45, 0.1, 10, { -642.5, 5, 332.5 }, White, FORWARD_WALL);
	App->physics->RectRoad(45, 20, 0.1, { -652.5, 0, 287.5 }, LightRed, FORWARD_RECT);
	App->physics->RectRoad(45, 0.1, 10, { -662.5, 5, 287.5 }, White, FORWARD_WALL);
	App->physics->RectRoad(45, 0.1, 10, { -642.5, 5, 287.5 }, White, FORWARD_WALL);
	App->physics->RectRoad(45, 20, 0.1, { -652.5, 0, 242.5 }, LightRed, FORWARD_RECT);
	App->physics->RectRoad(45, 0.1, 10, { -662.5, 5, 242.5 }, White, FORWARD_WALL);
	App->physics->RectRoad(45, 0.1, 10, { -642.5, 5, 242.5 }, White, FORWARD_WALL);
	App->physics->RectRoad(45, 20, 0.1, { -652.5, 0, 197.5 }, LightRed, FORWARD_RECT);
	App->physics->RectRoad(45, 0.1, 10, { -662.5, 5, 197.5 }, White, FORWARD_WALL);
	App->physics->RectRoad(45, 0.1, 10, { -642.5, 5, 197.5 }, White, FORWARD_WALL);
	App->physics->RectRoad(20, 0.1, 10, { -652.5, 5, 175 }, White, RIGHT_WALL);


	// Obstaculos Fnal
	App->physics->RectRoad(10, 0.1, 10, { -647.5, 5, 400 }, LightRed, RIGHT_WALL);
	App->physics->AddBall(3, (-652.5, 1, 430), LightOrange);
	App->physics->AddBall(3, (-652.5, 1, 425), LightOrange);
	
	Sphere s(3);
	s.SetPos(-652.5, 1, 430);
	App->physics->AddBody(s);
	s.SetPos(-652.5, 1, 425);
	App->physics->AddBody(s);

	App->physics->AddEnemy(10, 10, 10, { -652.5, 5, 287.5 }, LightOrange);

	App->physics->RectRoad(10, 0.1, 10, { -657.5, 5, 377.5 }, LightYellow, RIGHT_WALL);
	App->physics->RectRoad(10, 0.1, 10, { -647.5, 5, 355 }, LightBlue, RIGHT_WALL);
	App->physics->RectRoad(10, 0.1, 10, { -657.5, 5, 332.5 }, LightOrange, RIGHT_WALL);


	//------------------walls------------------
	App->physics->RectRoad(80, 0.1, 10, { -10, 8, 0 }, White, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { 10, 8, 0 }, White, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { -10, 8, 80 }, White, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { 10, 8, 80 }, White, FORWARD_WALL);

	App->physics->RectRoad(80, 0.1, 10, { -10, 8, 305 }, White, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { 10, 8, 305 }, White, FORWARD_WALL);

	App->physics->RectRoad(80, 0.1, 10, { -10, 8, 385 }, White, FORWARD_WALL);
	App->physics->RectRoad(80, 0.1, 10, { 10, 8, 385 }, White, FORWARD_WALL);

	App->physics->RectRoad(20, 0.1, 10, { 10, 8, 435 }, White, FORWARD_WALL);

	App->physics->RectRoad(80, 0.1, 10, { -30, 8, 445 }, White, RIGHT_WALL);
	App->physics->RectRoad(60, 0.1, 10, { -40, 8, 425 }, White, RIGHT_WALL);
	

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

	for (uint n = 0; n < PrimitiveObjects.Count(); n++)
	{
		//PrimitiveObjects[n]->body->GetTransform(&transMatrix);
		//PrimitiveObjects[n]->transform = transMatrix;
		PrimitiveObjects[n]->Render();
	}

	return UPDATE_CONTINUE;
}

