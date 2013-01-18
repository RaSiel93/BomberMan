#ifndef PROCES_H
#define PROCES_H

#define col_mobs 5
#define strength 2

#include <string>
#include <vector>
using namespace std;

#define ob_size 40
#define area_h 15
#define area_w 31

//#include "Index.cpp"
#include "OBJECT.h"

class PROCESS{
public:
	PROCESS();
	~PROCESS();
	bool GetObject( string type, int pattern, string able  );
	void Print();
	bool PlayerMoveTo( int y, int x );
	bool PushBomb();
	void BangBomb( int temp );
	bool BigBang( int y, int x );
	bool Destroy( int y, int x );
	int FindFire( int y, int x );
	int FindBomb( int y, int x );
	int FindMonster( int y, int x );
	bool MoobMoveTo( int i );
	string Passage( int y, int x );

	OBJECT *object[ area_h * area_w ];
	PLAYER *player;
	vector< BOMB* > bomb;
	vector< FIRE* > fire;
	vector< MONSTER* > moob;
};
#endif //PROCES_H