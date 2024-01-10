#pragma once

// Warning disabled ---
#pragma warning( disable : 4577 ) // Warning that exceptions are disabled
#pragma warning( disable : 4530 )

#include <windows.h>
#include <stdio.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

#define CAP(n) ((n <= 0.0f) ? n=0.0f : (n >= 1.0f) ? n=1.0f : n=n)

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define HAVE_M_PI


typedef unsigned int uint;

enum RoadTypes
{
	FORWARD_RECT = 1,
	LEFT_RECT,
	RIGHT_RECT,
	TOP_RIGHT_CORNER,
	TOP_LEFT_CORNER,
	BOTTOM_RIGHT_CORNER,
	BOTTOM_LEFT_CORNER,
	RAMP,
	INVERSE_RAMP,
	TOP_RIGHT_RECT,
	FORWARD_WALL
};

enum CollisionObject
{
	NONE = 1,
	CAR,
	WALL,
	ENEMY,
	CHECKPOINT,
	WIN
};

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Configuration -----------
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 1024
#define SCREEN_SIZE 1
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE true
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false
#define VSYNC true
#define TITLE "3D Physics Playground"