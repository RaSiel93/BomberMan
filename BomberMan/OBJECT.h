#ifndef OBJECT_H
#define OBJECT_H

#include <Windows.h>
#include <vector>
using namespace std;
#include <iostream>

//#include "index.cpp"

#define object_h 7
#define object_w 9

class OBJECT{
public:
	OBJECT(){};
	OBJECT( int y, int x );
	~OBJECT(){};
	void setPos( int y, int x );
	pair< int, int > getPos();
	virtual void Draw() = 0;
protected:
	pair< int, int > position;
};

class BLOCK: public OBJECT{
public:
	BLOCK(){}
	BLOCK( int y, int x );
	void Draw();
};

class BRICK: public OBJECT{
public:
	BRICK(){}
	BRICK( int y, int x );
	void Draw();
};

class PLAYER: public OBJECT{
public:
	PLAYER( int y, int x );
	void Draw();
};

class BOMB: public OBJECT{
public:
	BOMB( int x, int y );
	int getTimer();
	void setTimer();
	void Draw();
	int timer;
};

class FIRE: public OBJECT{
public:
	FIRE( int x, int y );
	void Draw();
};

class MONSTER_1: public OBJECT{
public:
	MONSTER_1( int y, int x );
	void Draw();
};

#endif // OBJECT_H