#include "stdafx.h"
#include "Plane.h"


Plane::Plane(int landing_duration, int service_duration) {

	this->spawn_time = time(NULL);
	this->landing_duration = landing_duration;
	this->service_duration = service_duration;

	this->id = rand() % 10000;
	this->w = rand() % 2;
	this->cost = rand() % 2 + 1;
	this->cost_importance = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	this->priority = calculate_priority();

	this->airplane = new Airplane();

}

float Plane::calculate_priority() {

	float p = (this->w + this->cost * this->cost_importance);

	return p;
}