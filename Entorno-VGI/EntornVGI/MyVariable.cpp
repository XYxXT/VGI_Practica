#include "stdafx.h"
#include "MyVariable.h"

MyVariable::MyVariable() {
	this->testPosition = 0;
	this->finishAnimation = true;
}

MyVariable* MyVariable::myInstance = NULL;

MyVariable* MyVariable::getInstance() {
	if (!myInstance)
		myInstance = new MyVariable;
	return myInstance;
}

bool* MyVariable::getFingerList() {
	return fingerList;
}

bool MyVariable::isFinishAnimation() {
	return finishAnimation;
}

void MyVariable::setFinishAnimation(bool isFinish) {
	this->finishAnimation = isFinish;
}

std::vector<Airplane> MyVariable::getAirplaneList() {
	return airplaneList;
}

void MyVariable::moveAlongAirplane(Airplane airplane, float distance) {
	if (airplane.getNextPositionList().size() > 0) {
		_D3DVECTOR nextPosition = airplane.getNextPositionList()[0];
		_D3DVECTOR actualPosition = airplane.getPosition();
		float actualDistance = sqrtf(pow(nextPosition.x - actualPosition.x, 2) + pow(nextPosition.y - actualPosition.y, 2)
			+ pow(nextPosition.z - actualPosition.z, 2));

		if (actualDistance < distance) {
			airplane.setPosition(nextPosition);
			
		}
		else {
			
		}
	}
}

void MyVariable::calcNextPositionAirplane(Airplane airplane) {

}

void MyVariable::calcNextRotateAirplane(Airplane airplane) {

}

void MyVariable::incrementPosition() {
	testPosition += 1;
}

void MyVariable::setPosition(float position) {
	this->testPosition = position;
}

float MyVariable::getPosition() {
	return this->testPosition;
}