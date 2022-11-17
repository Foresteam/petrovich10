#include "Sun.h"

Sun::Sun() : Entity(ASSETS + "textures/sun.png") {
	kinematic = true;
	background = true;
	mass = 0;
}