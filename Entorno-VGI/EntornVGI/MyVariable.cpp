#include "stdafx.h"
#include "MyVariable.h"

MyVariable::MyVariable() {
	this->testPosition.x = 0;
	this->testPosition.y = 0;
	this->testPosition.z = 0;

	this->finishAnimation = true;
	this->maxAngle.x = 1;
	this->maxAngle.y = 5;
	this->maxAngle.z = 10;
	this->TPPDirection = 0;
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

std::vector<Airplane*> MyVariable::getAirplaneList() {
	return airplaneList;
}

void MyVariable::addAirplane(Airplane* air) {
	this->airplaneList.push_back(air);
}

void MyVariable::clearAirplaneList() {
	this->airplaneList.resize(0);
}

void MyVariable::setTPPDirection(int direction) {
	this->TPPDirection = direction;
}

int MyVariable::getTPPDirection() {
	return this->TPPDirection;
}

void MyVariable::setSimulation(bool isSimulation) {
	this->_isSimulation = isSimulation;
}

bool MyVariable::isSimulation() {
	return this->_isSimulation;
}

void MyVariable::setSimulationAirplane(Airplane* airplane) {
	this->simulationAirplane = airplane;
}

Airplane* MyVariable::getSimulationAirplane() {
	return this->simulationAirplane;
}

void MyVariable::setSimulationView(char view) {
	this->_simulationView = view;
}

char MyVariable::getSimulationView() {
	return this->_simulationView;
}

int MyVariable::getFreeFinger() {
	for (int i = 1; i <= FINGER_SIZE; i++) {
		if (this->fingerList[i] == false)
			return i;
	}
	return -1;
}

void MyVariable::removeAirplane(Airplane* airplane) {
	this->fingerList[airplane->getFingerID()] = false;
	this->airplaneList.erase(std::remove(this->airplaneList.begin(), this->airplaneList.end(), airplane), this->airplaneList.end());
}

void resetAngle(float &angle, float maxAngle, float originalAngle) {
	if (angle != originalAngle) {
		if (angle > originalAngle) {
			angle = angle - maxAngle > originalAngle ? angle - maxAngle : originalAngle;
		}
		else {
			angle = angle + maxAngle < originalAngle ? angle + maxAngle : originalAngle;
		}
	}
}

float calcAngle(float sourceAngle, float destAngle, float maxAngle) {
	float tmpAngle = fmod((360 + destAngle - sourceAngle), 360);
	if (tmpAngle <= 180) {
		if (maxAngle < tmpAngle)
			return fmod((sourceAngle + maxAngle), 360);
		return destAngle;
	}
	else {
		if (tmpAngle + maxAngle < 360)
			return fmod((360 + sourceAngle - maxAngle), 360);
		else
			return destAngle;
	}
}

_D3DVECTOR MyVariable::calcNextPosition(_D3DVECTOR actualPosition, _D3DVECTOR vectorDirection, float distance) {
	_D3DVECTOR nextPosition;
	nextPosition.z = actualPosition.z + sinf((vectorDirection.x) * PI / 180) * distance;
	nextPosition.x = actualPosition.x + -sinf((vectorDirection.z) * PI / 180) * distance;
	nextPosition.y = actualPosition.y + cosf((vectorDirection.z) * PI / 180) * distance;
	return nextPosition;
}

void MyVariable::calcNextPositionAirplane(Airplane *airplane) {
	_D3DVECTOR* direction = airplane->getDirection();
	float velocity = .2f;
	if (airplane->getNextPositionList().size() > 0) {
		_D3DVECTOR* nextPosition = airplane->getNextPositionList()[0];
		_D3DVECTOR* actualPosition = airplane->getPosition();
		_D3DVECTOR directionVector;
		directionVector.x = nextPosition->x - actualPosition->x;
		directionVector.y = nextPosition->y - actualPosition->y;
		directionVector.z = nextPosition->z - actualPosition->z;
		float distanciaXY = 0;

		if (directionVector.x == 0) {
			if (directionVector.y == 0) {
				//direction->y = calcAngle(direction->y, 0, maxAngle.y);
			}
			else {
				float nextAngleZ = calcAngle(direction->z, directionVector.y > 0 ? 0 : 180, maxAngle.z);
				/*float angleZDistance = nextAngleZ - direction->z;
				if (angleZDistance == 0) 
					direction->y = calcAngle(direction->y, 0, maxAngle.y);
				else {
					float tmpAngle = 360 - fmodf(360 + angleZDistance, 360);
					direction->y = calcAngle(direction->y, tmpAngle > maxAngle.z ? 300 : 60, maxAngle.y);
				}*/
				direction->z = nextAngleZ;
				distanciaXY = directionVector.y;
			}
		}
		else {
			if (directionVector.y == 0) {
				float nextAngleZ = calcAngle(direction->z, directionVector.x > 0 ? 270 : 90, maxAngle.z);
				/*float angleZDistance = nextAngleZ - direction->z;
				if (angleZDistance == 0)
					direction->y = calcAngle(direction->y, 0, maxAngle.y);
				else {
					float tmpAngle = 360 - fmodf(360 + angleZDistance, 360);
					direction->y = calcAngle(direction->y, tmpAngle > maxAngle.z ? 300 : 60, maxAngle.y);
				}*/
				direction->z = nextAngleZ;
				distanciaXY = directionVector.x;
			}
			else {
				float nextAngleZ = calcAngle(direction->z, fmod((atan2f(-directionVector.x, directionVector.y) * 180 / PI) + 360, 360), maxAngle.z);
				/*float angleZDistance = nextAngleZ - direction->z;
				if (angleZDistance == 0)
					direction->y = calcAngle(direction->y, 0, maxAngle.y);
				else {
					float tmpAngle = 360 - fmodf(360 + angleZDistance, 360);
					direction->y = calcAngle(direction->y, tmpAngle > maxAngle.z ? 300 : 60, maxAngle.y);
				}*/
				direction->z = nextAngleZ;
				distanciaXY = sqrt(pow(directionVector.y, 2) + pow(directionVector.x, 2));
			}
		}

		if (directionVector.z != 0) {
			direction->x = calcAngle(direction->x, fmod((atan2f(directionVector.z, distanciaXY) * 180 / PI) + 360, 360), maxAngle.x);
		}
		else{
			direction->x = calcAngle(direction->x, 0, maxAngle.x);
		}


		_D3DVECTOR nextPositionAir = calcNextPosition(*actualPosition, *direction, .5f);
		if (directionVector.z >= 0)
			actualPosition->z = nextPositionAir.z < nextPosition->z ? nextPositionAir.z : nextPosition->z;
		else
			actualPosition->z = nextPositionAir.z > nextPosition->z ? nextPositionAir.z : nextPosition->z;

		if (directionVector.x >= 0)
			actualPosition->x = nextPositionAir.x < nextPosition->x ? nextPositionAir.x : nextPosition->x;
		else
			actualPosition->x = nextPositionAir.x > nextPosition->x ? nextPositionAir.x : nextPosition->x;

		if (directionVector.y >= 0)
			actualPosition->y = nextPositionAir.y < nextPosition->y ? nextPositionAir.y : nextPosition->y;
		else
			actualPosition->y = nextPositionAir.y > nextPosition->y ? nextPositionAir.y : nextPosition->y;
		/*
		float tmpNext = actualPosition->z + sinf((direction->x) * PI / 180) * velocity;
		if (directionVector.z >= 0)
			actualPosition->z = tmpNext < nextPosition->z ? tmpNext : nextPosition->z;
		else
			actualPosition->z = tmpNext > nextPosition->z ? tmpNext : nextPosition->z;

		tmpNext = actualPosition->x + -sinf((direction->z) * PI / 180) * velocity;
		if (directionVector.x >= 0)
			actualPosition->x = tmpNext < nextPosition->x ? tmpNext : nextPosition->x;
		else
			actualPosition->x = tmpNext > nextPosition->x ? tmpNext : nextPosition->x;

		tmpNext = actualPosition->y + cosf((direction->z) * PI / 180) * velocity;
		if (directionVector.y >= 0)
			actualPosition->y = tmpNext < nextPosition->y ? tmpNext : nextPosition->y;
		else
			actualPosition->y = tmpNext > nextPosition->y ? tmpNext : nextPosition->y;
			*/
		directionVector.x = nextPosition->x - actualPosition->x;
		directionVector.y = nextPosition->y - actualPosition->y;
		directionVector.z = nextPosition->z - actualPosition->z;

		if (directionVector.x == 0 && directionVector.y == 0 && directionVector.z == 0)
			airplane->removeNextPosition(0);
	
	}
	else {
		if (airplane->isFinish())
			MyVariable::removeAirplane(airplane);
		else
			direction->x = calcAngle(direction->x, 0, maxAngle.x);
		//resetAngle(direction->x, maxAngle.x, 90);
		//resetAngle(direction->y, maxAngle.y);
		//resetAngle(direction->z, maxAngle.z, 0);
		//direction->y = calcAngle(direction->y, 0, maxAngle.y);
	}
}


void MyVariable::setPosition(_D3DVECTOR position) {
	this->testPosition = position;
}

_D3DVECTOR MyVariable::getPosition() {
	return this->testPosition;
}

_D3DVECTOR*  MyVariable::getPositionSky() {
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = -400;
	position->y = -5;
	position->z = 50;
	//position->x = -50;
	//position->y = -5;
	//position->z = 0;
	return position;
}

_D3DVECTOR*  MyVariable::getPositionFinger1() {
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = 38;
	position->y = -48;
	position->z = 0;
	return position;
}

_D3DVECTOR*  MyVariable::getPositionFinger2() {
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = 29;
	position->y = -48;
	position->z = 0;
	return position;
}

_D3DVECTOR*  MyVariable::getPositionFinger3() {
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = 6.f;
	position->y = -48;
	position->z = 0;
	return position;
}

_D3DVECTOR*  MyVariable::getPositionFinger4() {
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = -17;
	position->y = -47.f;
	position->z = 0;
	return position;
}


std::vector<_D3DVECTOR*> getGoFingerList() {
	std::vector<_D3DVECTOR*> positionList;
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = -300;
	position->y = -5;
	position->z = 30;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -200;
	position->y = -5;
	position->z = 10;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -150;
	position->y = -5;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -50;
	position->y = -5;
	position->z = 0;
	positionList.push_back(position);
	return positionList;
}

std::vector<_D3DVECTOR*> getGoSkyList(std::vector<_D3DVECTOR*> positionList) {
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = -50;
	position->y = -5;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -150;
	position->y = -5;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -200;
	position->y = -5;
	position->z = 10;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -300;
	position->y = -5;
	position->z = 30;
	positionList.push_back(position);
	return positionList;
}

std::vector<_D3DVECTOR*> MyVariable::getGoFinger1List() {
	std::vector<_D3DVECTOR*> positionList = getGoFingerList();
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = 20;
	position->y = -5;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 32;
	position->y = -10;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 45;
	position->y = -20;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 60;
	position->y = -40;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 45;
	position->y = -52;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 38;
	position->y = -48;
	position->z = 0;
	positionList.push_back(position);
	return positionList;
}

std::vector<_D3DVECTOR*> MyVariable::getGoFinger2List() {
	std::vector<_D3DVECTOR*> positionList = getGoFingerList();
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = -25;
	position->y = -5;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -5;
	position->y = -20;
	position->z = 0;
	positionList.push_back(position);

	position = new _D3DVECTOR();
	position->x = 20;
	position->y = -48;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 25;
	position->y = -52;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 29;
	position->y = -48;
	position->z = 0;
	positionList.push_back(position);

	return positionList;
}

std::vector<_D3DVECTOR*> MyVariable::getGoFinger3List() {
	std::vector<_D3DVECTOR*> positionList = getGoFingerList();
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = -25;
	position->y = -5;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -20;
	position->y = -20;
	position->z = 0;
	positionList.push_back(position);

	position = new _D3DVECTOR();
	position->x = -7;
	position->y = -48;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 2;
	position->y = -50;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 6.f;
	position->y = -48;
	position->z = 0;
	positionList.push_back(position);

	return positionList;
}

std::vector<_D3DVECTOR*> MyVariable::getGoFinger4List() {
	std::vector<_D3DVECTOR*> positionList = getGoFingerList();
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = -45;
	position->y = -5;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -40;
	position->y = -8;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -38;
	position->y = -20;
	position->z = 0;
	positionList.push_back(position);

	position = new _D3DVECTOR();
	position->x = -27;
	position->y = -48;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -22;
	position->y = -50;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -17;
	position->y = -47.f;
	position->z = 0;
	positionList.push_back(position);
	return positionList;
}

std::vector<_D3DVECTOR*> MyVariable::getOutFinger1List() {
	std::vector<_D3DVECTOR*> positionList;
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = 22;
	position->y = -20;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 17;
	position->y = -10;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 10;
	position->y = -5;
	position->z = 0;
	positionList.push_back(position);
	return getGoSkyList(positionList);
}

std::vector<_D3DVECTOR*> MyVariable::getOutFinger2List() {
	std::vector<_D3DVECTOR*> positionList;
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = 32;
	position->y = -42;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 28;
	position->y = -32;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 22;
	position->y = -20;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 17;
	position->y = -10;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 10;
	position->y = -5;
	position->z = 0;
	positionList.push_back(position);

	return getGoSkyList(positionList);
}

std::vector<_D3DVECTOR*> MyVariable::getOutFinger3List() {
	std::vector<_D3DVECTOR*> positionList;
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = 10.f;
	position->y = -42;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 11;
	position->y = -20;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 10;
	position->y = -15;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 10;
	position->y = -9;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 8;
	position->y = -7;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = 6;
	position->y = -6;
	position->z = 0;
	positionList.push_back(position);
	return getGoSkyList(positionList);
}

std::vector<_D3DVECTOR*> MyVariable::getOutFinger4List() {
	std::vector<_D3DVECTOR*> positionList;
	_D3DVECTOR* position = new _D3DVECTOR();
	position->x = -8;
	position->y = -20;
	position->z = 0;
	positionList.push_back(position);
	position = new _D3DVECTOR();
	position->x = -8;
	position->y = -18;
	position->z = 0;
	positionList.push_back(position);	
	position = new _D3DVECTOR();
	position->x = -25;
	position->y = -5;
	position->z = 0;
	positionList.push_back(position);
	return getGoSkyList(positionList);
}

void MyVariable::prepareAirplane(Airplane* air, int state) {
	_D3DVECTOR* ds = new _D3DVECTOR;
	if (state == 0) {
		switch (air->getFingerID())
		{
		case 0:
			ds->y = 0;
			ds->x = 0;
			ds->z = 270;
			air->setDirection(ds);
			air->setPosition(MyVariable::getInstance()->getPositionSky());
			air->setNextPositionList(MyVariable::getInstance()->getGoFinger1List());
			break;
		case 1:
			ds->y = 0;
			ds->x = 0;
			ds->z = 270;
			air->setDirection(ds);
			air->setPosition(MyVariable::getInstance()->getPositionSky());
			air->setNextPositionList(MyVariable::getInstance()->getGoFinger2List());
			break;
		case 2:
			ds->y = 0;
			ds->x = 0;
			ds->z = 270;
			air->setDirection(ds);
			air->setPosition(MyVariable::getInstance()->getPositionSky());
			air->setNextPositionList(MyVariable::getInstance()->getGoFinger3List());
			break;
		case 3:
			ds->y = 0;
			ds->x = 0;
			ds->z = 270;
			air->setDirection(ds);
			air->setPosition(MyVariable::getInstance()->getPositionSky());
			air->setNextPositionList(MyVariable::getInstance()->getGoFinger4List());
			break;
		default:
			break;
		}
	}
	else {
		switch (air->getFingerID())
		{
		case 0:
			ds->y = 0;
			ds->x = 0;
			ds->z = 45;
			air->setDirection(ds);
			air->setPosition(MyVariable::getInstance()->getPositionFinger1());
			air->setNextPositionList(MyVariable::getInstance()->getOutFinger1List());
			break;
		case 1:
			ds->y = 0;
			ds->x = 0;
			ds->z = 315;
			air->setDirection(ds);
			air->setPosition(MyVariable::getInstance()->getPositionFinger2());
			air->setNextPositionList(MyVariable::getInstance()->getOutFinger2List());
			break;
		case 2:
			ds->y = 0;
			ds->x = 0;
			ds->z = 315;
			air->setDirection(ds);
			air->setPosition(MyVariable::getInstance()->getPositionFinger3());
			air->setNextPositionList(MyVariable::getInstance()->getOutFinger3List());
			break;
		case 3:
			ds->y = 0;
			ds->x = 0;
			ds->z = 315;
			air->setDirection(ds);
			air->setPosition(MyVariable::getInstance()->getPositionFinger4());
			air->setNextPositionList(MyVariable::getInstance()->getOutFinger4List());
			break;
		default:
			break;
		}
	}
}