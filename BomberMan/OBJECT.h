#ifndef OBJECT_H
#define OBJECT_H

#include "SERVICE.h"

class OBJECT{
public:
						OBJECT(){};
						OBJECT( int y, int x );
						~OBJECT(){};	
	void				SetPos( int y, int x );
	pair< int, int >	GetPos();
	virtual void		Draw() = 0;
protected:
	pair< int, int >	position;
};

class BLOCK: public OBJECT{
public:
						BLOCK(){}
						BLOCK( int y, int x );
	void				Draw();
};

class BRICK: public OBJECT{
public:
						BRICK(){}
						BRICK( int y, int x );
	void				Draw();
};

class PLAYER: public OBJECT{
public:
						PLAYER( int y, int x, int p = 1, int ab = 1, bool pb = false, bool fr = false, bool tw = false );
	void				Draw();
	int					GetBonus( string temp );
	void				SetBonus( int volume, string temp );
	void				SetBonus( bool volume, string temp );
//private:
	int					power_bomb;
	int					amount_bomb;
	bool				push_bomb;
	bool				fire_resist;
	//bool				control_bomb;
	bool				through_wall;
};

class BOMB: public OBJECT{
public:
						BOMB(){}
						BOMB( int x, int y, int p = 1 );
	int					GetTimer();
	void				SetTimer();
	void				SetTimer( int volume );
	void				Draw();
	int					GetPower();
	void				SetPower( int volume );
	bool				push;
	int					course;
protected:
	int					timer;
	int					power;
};

class FIRE: public BOMB {
public:
						FIRE( int x, int y );
	void				Draw();
};

class MOOB: public OBJECT{
public:
						MOOB( bool temp = false ) : tw( temp ){}
	virtual void		Draw() = 0;
	int					GetSpeed();
	void				SetSpeed();
	void				ResetSpeed();	
	int					course;
	bool				tw;
protected:
	int					speed;
	int					speed_const;
};
class MOOB_1: public MOOB{
public:
						MOOB_1( int y, int x );
	void				Draw();
};
class MOOB_2: public MOOB{
public:
						MOOB_2( int y, int x );
	void				Draw();
};
class MOOB_3: public MOOB{
public:
						MOOB_3( int y, int x );
	void				Draw();
};

class BONUS: public OBJECT{
public:
	virtual void		Draw() = 0;
};
class BONUS_AB: public BONUS{
public:
						BONUS_AB( int y, int x );
	void				Draw();
};
class BONUS_PwB: public BONUS{
public:
						BONUS_PwB( int y, int x );
	void				Draw();
};
class BONUS_PhB: public BONUS{
public:
						BONUS_PhB( int y, int x );
	void				Draw();
};
class BONUS_FR: public BONUS{
public:
						BONUS_FR( int y, int x );
	void				Draw();
};
class BONUS_TW: public BONUS{
public:
						BONUS_TW( int y, int x );
	void				Draw();
};
#endif // OBJECT_H