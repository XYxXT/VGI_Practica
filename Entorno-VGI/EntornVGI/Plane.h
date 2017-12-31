#pragma once
class Plane
{
public:
	int id;
	int w;
	int cost;
	float cost_importance;
	float priority;


	time_t spawn_time;
	double landing_duration;

	time_t service_time;
	double service_duration;

	time_t landing_time;
	time_t take_off_time;

	bool landing;
	Airplane* airplane;

	Plane(int, int);
	float calculate_priority();


};

