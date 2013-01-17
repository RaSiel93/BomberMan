#ifndef OBJECT_H
#define OBJECT_H

#include <Windows.h>
#include <vector>
using namespace std;
#include <iostream>
#include <string>
#include <GL\glut.h>

#define ob_size 40
#define area_h 15
#define area_w 31

//#include "index.cpp"

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
	BOMB(){}
	BOMB( int x, int y );
	int getTimer();
	void setTimer();
	void Draw();
protected:
	int timer;
};

class FIRE: public BOMB {
public:
	FIRE( int x, int y );
	void Draw();
};

class MONSTER: public OBJECT{
public:
	virtual void Draw() = 0;
	int GetSpeed();
	void SetSpeed();
	bool MoveTo( OBJECT (&object)[area_h * area_w] );//<------------------------------------------------
protected:
	int speed;
	int speed_const;
};

class MONSTER_1: public MONSTER{
public:
	MONSTER_1( int y, int x );
	void Draw();
};

#endif // OBJECT_H