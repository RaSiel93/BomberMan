#ifndef PROCES_H
#define PROCES_H

#define area_h 15
#define area_w 35
#define col_mobs 5
#define strength 2

#include <string>
#include <vector>
using namespace std;

#include "OBJECT.h"

class PROCESS{
public:
	PROCESS();
	~PROCESS();
	bool GetObject( string type, int pattern, string able  );
	void Print();
	void ClearObject( int y, int x );
	void FireDraw( int y, int x );
	bool PlayerMoveTo( int y, int x );
	bool PushBomb();
	bool BangBomb( int temp );
	int BigBang( int y, int x );
	bool Destroy( int y, int x );
	int FindFire( int y, int x );
	int FindBomb( int y, int x );
	int FindMonster( int y, int x );
	bool MoobsMoveTo();
	string Passage( int y, int x );

	OBJECT *map_object[ area_h ][ area_w ];
	vector< pair< int, int > > moobs_position;
	PLAYER *player;
	vector< BOMB* > bomb;
	vector< FIRE* > fire;
};
#endif //PROCES_H