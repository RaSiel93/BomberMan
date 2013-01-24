#ifndef PROCES_H
#define PROCES_H

#include "SERVICE.h"
#include "OBJECT.h"

class PROCESS{
public:
						PROCESS();
						~PROCESS();
	void				GetObject( string temp, int y, int x );
	void				GetObject( string temp, int pattern );
	void				GetObject( string temp, int pattern, string able, int border_y = area_h, int border_x = area_w );
	void				Print();
	bool				MovePlayer( string route );
	//void				GetBonus( string type, PLAYER *pl );
	void				MoveBomb( int numb_p, int numb_b );
	void				BombTime();
	bool				PushBomb( int i );
	void				DestroyFire();
	void				MoveMoobs();

	bool				EndGame();
	void				Restart();
private:
	void				BangBomb( int temp );
	void				Draw( string type );
	bool				BigBang( int y, int x );
	bool				Destroy( int y, int x );
	string				ObjectIdentification( int y, int x );
	bool				Passage( int y, int x );
	int					Find( int y, int x, string type );

	vector< string >	type;
	vector< PLAYER* >	player;
	vector< BLOCK* >	block;
	vector< BRICK* >	brick;
	vector< BOMB* >		bomb;
	vector< FIRE* >		fire;
	vector< MOOB* >		moob;
	vector< BONUS* >	bonus;
};
#endif //PROCES_H