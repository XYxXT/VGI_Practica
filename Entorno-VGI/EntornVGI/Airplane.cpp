#include "stdafx.h"
#include "Airplane.h"

Airplane::Airplane(int id, _D3DVECTOR position, _D3DVECTOR direction, std::vector<_D3DVECTOR> nextPositionList)
{
	this->id = id;
	this->position = position;
	this->direction = direction;
	this->nextPositionList = nextPositionList;
}

// GETTER SETTER

void Airplane::setDirection(_D3DVECTOR direction) {
	this->direction = direction;
}

void Airplane::setPosition(_D3DVECTOR position) {
	this->position = position;
}


void Airplane::setFinish(bool finish) {
	this->finish = finish;
}


_D3DVECTOR Airplane::getDirection() {
	return this->direction;
}

_D3DVECTOR Airplane::getPosition() {
	return this->position;
}

std::vector<_D3DVECTOR> Airplane::getNextPositionList() {
	return this->nextPositionList;
}

bool Airplane::isFinish() {
	return this->finish;
}