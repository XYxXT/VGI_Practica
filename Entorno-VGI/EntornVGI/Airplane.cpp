#include "stdafx.h"
#include "Airplane.h"

Airplane::Airplane(int id, _D3DVECTOR* position, _D3DVECTOR* direction, std::vector<_D3DVECTOR*> nextPositionList)
{
	this->fingerId = id;
	this->position = position;
	this->direction = direction;
	this->nextPositionList = nextPositionList;
	this->finish = false;
}

Airplane::Airplane(int id) {
	this->fingerId = id;
	this->finish = false;
}

// GETTER SETTER

void Airplane::setDirection(_D3DVECTOR* direction) {
	this->direction = direction;
}

void Airplane::setPosition(_D3DVECTOR* position) {
	this->position = position;
}

void Airplane::setNextPositionList(std::vector<_D3DVECTOR*> nextPositionList) {
	this->nextPositionList = nextPositionList;
}

void Airplane::addNextPosition(_D3DVECTOR* position) {
	this->nextPositionList.push_back(position);
}

void Airplane::setFinish(bool finish) {
	this->finish = finish;
}

int Airplane::getFingerID() {
	return fingerId;
}

void Airplane::setFingerID(int id) {
	MyVariable::getInstance()->getFingerList()[id] = true;
	this->fingerId = id;
}


_D3DVECTOR* Airplane::getDirection() {
	return this->direction;
}

_D3DVECTOR* Airplane::getPosition() {
	return this->position;
}

std::vector<_D3DVECTOR*> Airplane::getNextPositionList() {
	return this->nextPositionList;
}

bool Airplane::isFinish() {
	return this->finish;
}

void Airplane::removeNextPosition(int position) {
	this->nextPositionList.erase(this->nextPositionList.begin() + position);
}

