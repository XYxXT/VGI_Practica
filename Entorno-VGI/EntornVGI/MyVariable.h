#pragma once

class MyVariable
{
public:
	static MyVariable* getInstance();

	bool* getFingerList();
	bool isFinishAnimation();
	void setFinishAnimation(bool);
	std::vector<Airplane> getAirplaneList();
	void calcNextPositionAirplane(Airplane);
	void moveAlongAirplane(Airplane, float);
	void calcNextRotateAirplane(Airplane);

	void incrementPosition();
	void setPosition(float);
	float getPosition();
private:
	MyVariable();

	static MyVariable* myInstance;

	std::vector<Airplane> airplaneList;
	bool fingerList[FINGER_SIZE];
	bool finishAnimation;

	float testPosition;
};

