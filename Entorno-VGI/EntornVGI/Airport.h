#pragma once
class Airport
{
public:
	int n_fingers;
	int n_runways;
	std::list<Plane*> runways;
	std::list<Plane*> fingers;
	std::list<Plane*> buffer;
	float landing_duration;
	float take_off_duration;

	struct Priorities {
		bool operator() (Plane* a, Plane* b) { return (a->priority > b->priority); }
	} p_list;

	Airport(int, int, int, int);
	~Airport();

	void service_plane(Plane*);
	void departure(std::vector<Plane*>);
};

