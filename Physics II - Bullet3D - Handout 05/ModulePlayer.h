#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "PhysVehicle3D.h"

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
	void ChangeFriction(float friction);

public:
	VehicleInfo car;

	Sphere* decor;
	PhysBody3D* decorBody;
	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	bool fxPlayed;
	Uint32 startTime;
	int Seconds;
	int auxSeconds;
	int MaxSeconds;

	btVector3 chekpoint1;
	btVector3 chekpoint2;
	btVector3 chekpoint3;

	vec3 lastCheckpoint;
	mat4x4 lastCheckpontTransform;

	mat4x4 debugCheckpontTransform;

	bool decorRender = true;
	bool accelerated = false;
	bool reduced = false;
	bool Changeedfric = false;

	btTypedConstraint* constrain;

	float vehicleArea;

	btVector3 Drag;
	btVector3 Lift;

	float defaultFriction = 50.50f;
	float actualFriction = 50.50f;
};