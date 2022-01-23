#include "Sun.h"

Sun::Sun() : Object(ASSETS + "textures/sun.png") {
	kinematic = true;
	background = true;
	mass = 0;
}