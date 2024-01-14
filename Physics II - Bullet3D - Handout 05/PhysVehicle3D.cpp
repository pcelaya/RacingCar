#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render()
{
	Cylinder wheel;

	wheel.color = Blue;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);
	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	Cube FrontChassis(info.front_chassis_size.x, info.front_chassis_size.y, info.front_chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&FrontChassis.transform);
	q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offsetFront(info.front_chassis_offset.x, info.front_chassis_offset.y, info.front_chassis_offset.z);
	offsetFront = offsetFront.rotate(q.getAxis(), q.getAngle());

	Cube RearChassis(info.rear_chassis_size.x, info.rear_chassis_size.y, info.rear_chassis_size.z);
	RearChassis.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&RearChassis.transform);
	q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offsetRear(info.rear_chassis_offset.x, info.rear_chassis_offset.y, info.rear_chassis_offset.z);
	offsetRear = offsetRear.rotate(q.getAxis(), q.getAngle());

	Sphere cabine(info.cabine_radius);
	cabine.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&cabine.transform);
	q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offsetCabine(info.cabine_offset.x, info.cabine_offset.y, info.cabine_offset.z);
	offsetCabine = offsetCabine.rotate(q.getAxis(), q.getAngle());

	Cube RearChassisRight(info.rear_chassis_right_size.x, info.rear_chassis_right_size.y, info.rear_chassis_right_size.z);
	RearChassisRight.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&RearChassisRight.transform);
	q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offsetRearRight(info.rear_chassis_right_offset.x, info.rear_chassis_right_offset.y, info.rear_chassis_right_offset.z);
	offsetRearRight = offsetRearRight.rotate(q.getAxis(), q.getAngle());

	Cube RearChassisLeft(info.rear_chassis_left_size.x, info.rear_chassis_left_size.y, info.rear_chassis_left_size.z);
	RearChassisLeft.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&RearChassisLeft.transform);
	q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offsetRearLeft(info.rear_chassis_left_offset.x, info.rear_chassis_left_offset.y, info.rear_chassis_left_offset.z);
	offsetRearLeft = offsetRearLeft.rotate(q.getAxis(), q.getAngle());

	Cube antena(info.antenaSize.x, info.antenaSize.y, info.antenaSize.z);
	antena.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&antena.transform);
	q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offsetAntena(info.antenaOffset.x, info.antenaOffset.y, info.antenaOffset.z);
	offsetAntena = offsetAntena.rotate(q.getAxis(), q.getAngle());

	Sphere SphereAntena(info.sphereRadius);
	SphereAntena.color = Red;
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&SphereAntena.transform);
	q = vehicle->getChassisWorldTransform().getRotation();
	btVector3 offsetSphere(info.sphereOffset.x, info.sphereOffset.y, info.sphereOffset.z);
	offsetSphere = offsetSphere.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	FrontChassis.transform.M[12] += offsetFront.getX();
	FrontChassis.transform.M[13] += offsetFront.getY();
	FrontChassis.transform.M[14] += offsetFront.getZ();

	RearChassis.transform.M[12] += offsetRear.getX();
	RearChassis.transform.M[13] += offsetRear.getY();
	RearChassis.transform.M[14] += offsetRear.getZ();

	RearChassisRight.transform.M[12] += offsetRearRight.getX();
	RearChassisRight.transform.M[13] += offsetRearRight.getY();
	RearChassisRight.transform.M[14] += offsetRearRight.getZ();

	RearChassisLeft.transform.M[12] += offsetRearLeft.getX();
	RearChassisLeft.transform.M[13] += offsetRearLeft.getY();
	RearChassisLeft.transform.M[14] += offsetRearLeft.getZ();

	antena.transform.M[12] += offsetAntena.getX();
	antena.transform.M[13] += offsetAntena.getY();
	antena.transform.M[14] += offsetAntena.getZ();

	cabine.transform.M[12] += offsetCabine.getX();
	cabine.transform.M[13] += offsetCabine.getY();
	cabine.transform.M[14] += offsetCabine.getZ();

	SphereAntena.transform.M[12] += offsetSphere.getX();
	SphereAntena.transform.M[13] += offsetSphere.getY();
	SphereAntena.transform.M[14] += offsetSphere.getZ();

	chassis.Render();
	FrontChassis.Render();
	RearChassis.Render();
	RearChassisRight.Render();
	RearChassisLeft.Render();
	antena.Render();
	SphereAntena.Render();
	cabine.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}