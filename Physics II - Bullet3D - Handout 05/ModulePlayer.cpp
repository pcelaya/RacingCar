#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	fxPlayed = false;
	auxSeconds = 0;
	App->audio->LoadFx("SonidoRacing Car/CAIDA.wav");
	App->audio->LoadFx("SonidoRacing Car/CHECKPOINT.wav");
	App->audio->LoadFx("SonidoRacing Car/CHOQUE_PARED.wav");
	App->audio->LoadFx("SonidoRacing Car/MUERTE_POR_ENEMIGO.wav");
	App->audio->LoadFx("SonidoRacing Car/WIN.wav");
	App->audio->LoadFx("SonidoRacing Car/LOSE.wav");
	MaxSeconds = 300;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2.5, 1.3, 4);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	car.front_chassis_size.Set(3, 0.5, 1);
	car.front_chassis_offset.Set(0, 1, 2);
	car.rear_chassis_size.Set(3.5, 0.3, 1);
	car.rear_chassis_offset.Set(0,2.2, -2);
	car.cabine_radius = 1.0f;
	car.cabine_offset.Set(0, 2.1, 0.5);
	car.antenaSize.Set(0.1, 2, 0.1);
	car.antenaOffset.Set(0.8, 2.5, -1);
	car.sphereOffset.Set(0.8, 3.5, -1);
	car.sphereRadius = 0.2;
	car.rear_chassis_right_size.Set(0.3, 0.2, 1);
	car.rear_chassis_right_offset.Set(1.6, 2.4, -2);
	car.rear_chassis_left_size.Set(0.3, 0.2, 1);
	car.rear_chassis_left_offset.Set(-1.6, 2.4, -2);

	vehicleArea = car.chassis_size.x * car.chassis_size.y;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	decor = new Sphere(0.2f);
	//car.jointOffset = car.chassis_offset;
	//car.joint = App->physics->AddBody(Cube(0.1f,0.1f,0.1f),1.0f);
	decorBody = App->physics->AddBody(*decor);

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 10, 10);
	vehicle->collision_listeners.add(this);
	
	chekpoint1 = { 0, 6.2, 10 };
	chekpoint2 = { -200, 20.2, 435 };
	chekpoint3 = { -530, 0.2, 435 };

	constrain = App->physics->AddConstraintP2P(*decorBody->body, *vehicle->body, car.rear_chassis_offset, car.rear_chassis_offset);
	lastCheckpoint = App->scene_intro->cp1->checkpointX;
	startTime = SDL_GetTicks();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		if (acceleration > 0)
		{
			brake = BRAKE_POWER;
		}
		else
		{
			acceleration = -MAX_ACCELERATION;
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		App->scene_intro->cp1->GetTransform(&debugCheckpontTransform);
		vehicle->SetTransform(&debugCheckpontTransform);
		vehicle->SetPos(chekpoint1.x(), chekpoint1.y(), chekpoint1.z());
		turn = acceleration = brake = 0.0f;
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		accelerated = false;
		reduced = false;
		ChangeFriction(defaultFriction);
		actualFriction = defaultFriction;
	}

	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		App->scene_intro->cp2->GetTransform(&debugCheckpontTransform);
		vehicle->SetTransform(&debugCheckpontTransform);
		vehicle->SetPos(chekpoint2.x(), chekpoint2.y(), chekpoint2.z());
		turn = acceleration = brake = 0.0f;
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		accelerated = false;
		reduced = false;
		ChangeFriction(defaultFriction);
		actualFriction = defaultFriction;
	}

	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		App->scene_intro->cp3->GetTransform(&debugCheckpontTransform);
		vehicle->SetTransform(&debugCheckpontTransform);
		vehicle->SetPos(chekpoint3.x(), chekpoint3.y(), chekpoint3.z());
		turn = acceleration = brake = 0.0f;
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		accelerated = false;
		reduced = false;
		ChangeFriction(defaultFriction);
		actualFriction = defaultFriction;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		vehicle->SetTransform(&lastCheckpontTransform);
		RestartPlayer(lastCheckpoint.x + 3, lastCheckpoint.y + 1, lastCheckpoint.z + 3);
		turn = acceleration = brake = 0.0f;
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		ChangeFriction(defaultFriction);
		actualFriction = defaultFriction;
	}

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		vehicle->info.mass += 50.0f;
	}
	else if (App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
	{
		if (vehicle->info.mass > 0)
		{
			vehicle->info.mass -= 50.0f;
		}
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		if (decorRender) {
			decorRender = false;
			App->physics->world->removeConstraint(constrain);
			App->physics->world->removeRigidBody(decorBody->body);
		}
		else {
			decor = new Sphere(0.2f);
			decorBody = App->physics->AddBody(*decor);
			constrain = App->physics->AddConstraintP2P(*decorBody->body, *vehicle->body, car.rear_chassis_offset, car.rear_chassis_offset);
			decorRender = true;
		}
	}

	char title[255];
	sprintf_s(title, "|Ka-chow Car| Debug: %d Actual Vel: %.1f Km/h Gravity: %.1f m/s^2 Vehicle Mass: %.1f kg AirDrag X: %f, Y: %f, Z: %f Lift X: %f, Y: %f, Z: %f WheelFriction: %.1f Seconds to end: %d",
		App->physics->debug, vehicle->GetKmh(), App->physics->GetGravity(), vehicle->info.mass, Drag.x(), Drag.y(), Drag.z(), Lift.x(), Lift.y(), Lift.z(), actualFriction, MaxSeconds);
	App->window->SetTitle(title);

	

	if (decorRender) {
		mat4x4 decorMatrix;
		decorBody->GetTransform(&decorMatrix);
		decor->transform = decorMatrix;
		decor->Render();
	}

	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
	{
		vehicle->body->setLinearVelocity(vehicle->body->getLinearVelocity() * 2);
	}

	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
	{
		actualFriction += 50;
		ChangeFriction(actualFriction);
	}
	if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
	{
		actualFriction -= 50;
		ChangeFriction(actualFriction);
	}
	if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
	{
		actualFriction = 0;
		ChangeFriction(actualFriction);
	}
	if (App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN)
	{
		actualFriction = defaultFriction;
		ChangeFriction(actualFriction);
	}


	Uint32 currentTime = SDL_GetTicks();
	Uint32 elapsedTime = currentTime - startTime;

	//Seconds = (elapsedTime / 1000) % 60;
	//Seconds = elapsedTime / (1000 * 60);
	Seconds = (elapsedTime / 1000) % 60;
	//Seconds = elapsedTime % 1000;
	if (auxSeconds != Seconds) {
		MaxSeconds -= 1;
		auxSeconds = Seconds;
	}

	if (MaxSeconds <= 0) {
		App->audio->PlayFx(6, 0);
		App->scene_intro->cp1->GetTransform(&debugCheckpontTransform);
		vehicle->SetTransform(&debugCheckpontTransform);
		vehicle->SetPos(chekpoint1.x(), chekpoint1.y(), chekpoint1.z());
		turn = acceleration = brake = 0.0f;
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		accelerated = false;
		reduced = false;
		MaxSeconds = 300;
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body2->collType == ENEMY)
	{
		brake = BRAKE_POWER;
		vehicle->SetTransform(&lastCheckpontTransform);
		RestartPlayer(lastCheckpoint.x, lastCheckpoint.y, lastCheckpoint.z);
		turn = acceleration = brake = 0.0f;
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		if (!fxPlayed) { App->audio->PlayFx(4, 0); fxPlayed = true; }
		ChangeFriction(defaultFriction);
		actualFriction = defaultFriction;
	}

	if (body2->collType == WIN)
	{
		App->audio->PlayFx(5, 0);
		lastCheckpoint = App->scene_intro->cp1->checkpointX;
		App->scene_intro->cp1->GetTransform(&debugCheckpontTransform);
		vehicle->SetTransform(&debugCheckpontTransform);
		vehicle->SetPos(chekpoint1.x(), chekpoint1.y(), chekpoint1.z());
		turn = acceleration = brake = 0.0f;
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		accelerated = false;
		reduced = false;
		ChangeFriction(defaultFriction);
		actualFriction = defaultFriction;
		MaxSeconds = 300;
	}

	if (body2->collType == CHECKPOINT)
	{
		body2->GetTransform(&lastCheckpontTransform);
		if (lastCheckpoint.x != body2->checkpointX) { App->audio->PlayFx(2, 0);}
		lastCheckpoint.x = body2->checkpointX;
		lastCheckpoint.y = body2->checkpointY;
		lastCheckpoint.z = body2->checkpointZ;
	}

	if (body2->collType == WALL)
	{
		App->audio->PlayFx(3, 0);
	}

	if (body2->collType == FALL)
	{
		App->audio->PlayFx(1, 0);
		brake = BRAKE_POWER;
		vehicle->SetTransform(&lastCheckpontTransform);
		RestartPlayer(lastCheckpoint.x, lastCheckpoint.y, lastCheckpoint.z);
		turn = acceleration = brake = 0.0f;
		vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		ChangeFriction(defaultFriction);
		actualFriction = defaultFriction;
	}

	if (body2->collType == ACCELERATION)
	{
		if (!accelerated) {
			vehicle->body->setLinearVelocity(vehicle->body->getLinearVelocity() * 2);
		}
		accelerated = true;
	}

	if (body2->collType == REDUCCION)
	{
		if (!reduced) {
			vehicle->body->setLinearVelocity(btVector3(0, 0, 0));
		}
		reduced = true;
	}

	if (body2->collType == FRICTIONREDUC)
	{
		if (!Changeedfric) {
			actualFriction = 1;
			ChangeFriction(actualFriction);
		}
		Changeedfric = true;
	}
}

void ModulePlayer::RestartPlayer(int x, int y, int z)
{
	vehicle->SetPos(x, y, z);
	accelerated = false;
	reduced = false;
	fxPlayed = false;
}

void ModulePlayer::ChangeFriction(float friction)
{
	vehicle->vehicle->m_wheelInfo[0].m_frictionSlip = friction;
	vehicle->vehicle->m_wheelInfo[1].m_frictionSlip = friction;
	vehicle->vehicle->m_wheelInfo[2].m_frictionSlip = friction;
	vehicle->vehicle->m_wheelInfo[3].m_frictionSlip = friction;
}