#pragma once

class Airplane
{
public:
	Airplane() {};
	~Airplane() {};

	Airplane(int, _D3DVECTOR*, _D3DVECTOR*, std::vector<_D3DVECTOR*>);

	void setDirection(_D3DVECTOR*);
	void setPosition(_D3DVECTOR*);
	void setNextPositionList(std::vector<_D3DVECTOR*>);
	void setFinish(bool);
	void addNextPosition(_D3DVECTOR*);
	void removeNextPosition(int);

	_D3DVECTOR* getDirection();
	_D3DVECTOR* getPosition();
	std::vector<_D3DVECTOR*> getNextPositionList();
	bool isFinish();

private:
	int id;
	_D3DVECTOR* direction;
	_D3DVECTOR* position;
	std::vector<_D3DVECTOR*> nextPositionList;
	bool finish;
	

};

