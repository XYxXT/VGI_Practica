#pragma once

class MyVariable
{
public:
	static MyVariable* getInstance();

	bool* getFingerList();
	bool isFinishAnimation();
	void setFinishAnimation(bool);
	void addAirplane(Airplane*);
	void clearAirplaneList();
	std::vector<Airplane*> getAirplaneList();
	void calcNextPositionAirplane(Airplane*);
	_D3DVECTOR calcNextPosition(_D3DVECTOR actualPosition, _D3DVECTOR vectorDirection, float distance);

	void setPosition(_D3DVECTOR);
	_D3DVECTOR getPosition();
	std::vector<_D3DVECTOR*> getGoFinger1List();
	std::vector<_D3DVECTOR*> getGoFinger2List();
	std::vector<_D3DVECTOR*> getGoFinger3List();
	std::vector<_D3DVECTOR*> getGoFinger4List();
	std::vector<_D3DVECTOR*> getOutFinger1List();
	std::vector<_D3DVECTOR*> getOutFinger2List();
	std::vector<_D3DVECTOR*> getOutFinger3List();
	std::vector<_D3DVECTOR*> getOutFinger4List();
	_D3DVECTOR* getPositionFinger1();
	_D3DVECTOR* getPositionFinger2();
	_D3DVECTOR* getPositionFinger3();
	_D3DVECTOR* getPositionFinger4();
	_D3DVECTOR* getPositionSky();
	int getTPPDirection();
	void setTPPDirection(int);

private:
	MyVariable();

	static MyVariable* myInstance;

	std::vector<Airplane*> airplaneList;
	bool fingerList[FINGER_SIZE];
	bool finishAnimation;
	int TPPDirection;

	_D3DVECTOR testPosition;
	_D3DVECTOR maxAngle;
};

