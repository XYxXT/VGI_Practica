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
		//system("PAUSE");
		//exit(1);
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
		this->buffer.push_back(plane);
		printf("Plane %d is ready for take-off\n", plane->id);
		this->fingers.erase(std::remove(this->fingers.begin(), this->fingers.end(), plane), this->fingers.end());
		MyVariable::getInstance()->prepareAirplane(plane->airplane, 1);
		MyVariable::getInstance()->setSimulationAirplane(plane->airplane);
		plane->airplane->setFinish(true);
	}
}



