#ifndef OBJECT_H
#define OBJECT_H

#include "SERVICE.h"
#include <GL\glut.h>

class OBJECT{
public:
	OBJECT(){};
	OBJECT( int y, int x );
	~OBJECT(){};
	void SetPos( int y, int x );
	pair< int, int > GetPos();
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
	int GetPower();
	void SetPower( int volume );
private:
	int power;
};

class BOMB: public OBJECT{
public:
	BOMB(){}
	BOMB( int x, int y, int p = 1 );
	int GetTimer();
	void SetTimer();
	void Draw();
	int GetPower();
	void SetPower( int volume );
protected:
	int timer;
	int power;
};

class FIRE: public BOMB {
public:
	FIRE( int x, int y );
	void Draw();
};

class MOOB: public OBJECT{
public:
	virtual void Draw() = 0;
	int GetSpeed();
	void SetSpeed();
	void ResetSpeed();	
	int course;
protected:
	int speed;
	int speed_const;
};
class MOOB_1: public MOOB{
public:
	MOOB_1( int y, int x );
	void Draw();
};
class MOOB_2: public MOOB{
public:
	MOOB_2( int y, int x );
	void Draw();
};
class MOOB_3: public MOOB{
public:
	MOOB_3( int y, int x );
	void Draw();
};
#endif // OBJECT_H