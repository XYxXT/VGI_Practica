#include "stdafx.h"
#include "Airport.h"


Airport::Airport(int n_fingers, int n_runways, int landing_duration, int take_off_duration) {

	this->n_fingers = n_fingers;
	this->n_runways = n_runways;
	this->landing_duration = landing_duration;
	this->take_off_duration = take_off_duration;

}

Airport::~Airport() {}

void Airport::service_plane(Plane* plane) {

	if (fingers.size() == n_fingers) {
		printf("Airport Collapsed: Fingers full\n");
		MyVariable::getInstance()->setFinishAnimation(true);
		MyVariable::getInstance()->clearAirplaneList();
		MyVariable::getInstance()->setSimulationAirplane(NULL);
		MyVariable::getInstance()->setSimulation(false);
		MyVariable::getInstance()->clearAirplaneList();
	}
	plane->service_time = time(NULL);
	this->fingers.push_front(plane);
	printf("Plane: %d is in service\n", plane->id);
	printf("Planes in service: %d\n", fingers.size());

}

void Airport::departure(std::vector<Plane*> departures) {

	std::sort(departures.begin(), departures.end(), p_list);

	std::list<Plane*> temp;

	for (Plane* plane : departures) {
		if (this->runways.size() < this->n_runways) {
			plane->take_off_time = time(NULL);
			this->runways.push_back(plane);
			this->fingers.erase(std::remove(this->fingers.begin(), this->fingers.end(), plane), this->fingers.end());
			//plane->airplane->setFinish(true);
			//MyVariable::getInstance()->prepareAirplane(plane->airplane, 1);
			printf("Plane %d ready for take-off\n", plane->id);
			printf("Plane: %d is taking off with Priority %.2f\n", plane->id, plane->priority);
			printf("Occupied Runways %d\n", runways.size());
		}

		temp = this->runways;

		for (Plane* plane : temp) {
			if (time(NULL) - plane->take_off_time >= this->take_off_duration) {
				this->runways.remove(plane);
			}
		}
	}

}
