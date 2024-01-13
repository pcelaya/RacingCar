#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1000.0f
#define TURN_DEGREES 10.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	void RestartPlayer(int x, int y, int z);

public:
	Sphere* decor;
	PhysBody3D* decorBody;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;

	btVector3 chekpoint1;
	btVector3 chekpoint2;
	btVector3 chekpoint3;

	vec3 lastCheckpoint;
	mat4x4 lastCheckpontTransform;
};