#include "PROCESS.h"

PROCESS::PROCESS(){
	for( int i = 0; i < area_h; i++ ){
		for( int j = 0; j < area_w; j++ ){
			object[ i * area_w + j ] = 0;
		}
	}
}
bool PROCESS::GetObject( string type, int pattern, string able  ){
	if( type == "PLAYER" ){
		player = new PLAYER( pattern, pattern );
	}
	if( type == "MONSTER_1" ){
		for( int i = 0; i < pattern; ){
			int y = rand()%area_h, x = rand()%area_w;
			if( object[ y * area_w + x ] == 0 && !( y < 5 && x < 5 ) ){
				moob.push_back( new MONSTER_1( y, x ) );
				object[ y * area_w + x ] = moob.front();
				i++;
			}
		}
	}
	if( type == "BLOCK" && able == "NO_RANDOM" ){ 
		for( int i = 1; i < area_h; i += pattern ){
			for( int j = 1; j < area_w; j += pattern ){
				object[ i * area_w + j ] = new BLOCK( i, j );
			}
		}
	}
	if( type == "BRICK" && able == "RANDOM"){
		for( int i = 0; i < pattern; ){
			int y = rand()%area_h, x = rand()%area_w;
			if( object[ y * area_w + x ] == 0 && !( y < 2 && x < 2 ) ){
				object[ y * area_w + x ] = new BRICK( y, x );
				i++;
			}
		}
	}
	return true;
}
void PROCESS::Print(){
	player->Draw();
	for( int i = 0; i < area_h; i++ ){
		for( int j = 0; j < area_w; j++ ){
			if( object[ i * area_w + j ] != 0 ){
				object[ i * area_w + j ]->Draw();
			}
		}
	}
}
bool PROCESS::PlayerMoveTo( int y, int x ){
	string type = Passage( y = player->getPos().first + y, x = player->getPos().second + x );
	if( type == "" ){
		player->setPos( y, x );
		return true;
	}
	return false;
}
bool PROCESS::PushBomb(){
	if( FindBomb( player->getPos().first, player->getPos().second ) == -1 ){
		bomb.push_back( new BOMB( player->getPos().first, player->getPos().second ) );
		object[ player->getPos().first * area_w + player->getPos().second ] = bomb.back();
		bomb.back()->Draw();
		return true;
	}
	return false;
}
void PROCESS::BangBomb( int temp ){
	int y = bomb[ temp ]->getPos().first;
	int x = bomb[ temp ]->getPos().second;

	bomb.erase( bomb.begin() + temp );
	delete object[ y * area_w + x ];
	object[ y * area_w + x ] = 0;
		
	if( FindFire( y, x ) == -1 ) fire.push_back( new FIRE( y, x ) );
	for( int i=1, n1=1, n2=1, n3=1, n4=1; i < strength+1; i++ ){
		if( n1 ) n1=BigBang( y - i,  x );
		if( n2 ) n2=BigBang( y + i,  x );
		if( n3 ) n3=BigBang( y,  x - i );
		if( n4 ) n4=BigBang( y,  x + i );
	}
	for( int i = 0; i < fire.size(); i++ )
		fire[i]->Draw();
}
bool PROCESS::BigBang( int y, int x ){
	if( FindFire( y, x ) == -1 ){
		if( Passage( y, x ) == "-" || Passage( y, x ) == "class BLOCK" )
			return false;
		if( Passage( y, x ) == "" ){
			fire.push_back( new FIRE( y, x ) );
			return true;
		}
		if( Passage( y, x ) == "class BRICK" || Passage( y, x ) == "class BOMB" ){
			fire.push_back( new FIRE( y, x ) );
			return false;
		}
		if( Passage( y, x ) == "class MONSTER_1" ){
			fire.push_back( new FIRE( y, x ) );
			return true;
		}
	}
	return true;
}
bool PROCESS::Destroy( int y, int x ){
	if( Passage( y, x ) == "class BOMB" ){
		BangBomb( FindBomb( y, x ) );
		return true;
	}
	if( Passage( y, x ) == "class MONSTER_1" ){
		moob.erase( moob.begin() + FindMonster( y, x ) );
	}
	if( Passage( y, x ) != "" ){
		delete object[ y * area_h + x ];
		object[ y * area_w + x ] = 0;
	}
	fire.erase( fire.begin() + FindFire( y, x ) );
	return true;
}
int PROCESS::FindFire( int y, int x ){
	for( int i = 0; i < fire.size(); i++ )
		if( fire[ i ]->getPos().first == y && fire[ i ]->getPos().second == x )
			return i;
	return -1;
}
int PROCESS::FindBomb( int y, int x ){
	for( int i = 0; i < bomb.size(); i++ )
		if( bomb[ i ]->getPos().first == y && bomb[ i ]->getPos().second == x )
			return i;
	return -1;
}
int PROCESS::FindMonster( int y, int x ){
	for( int i = 0; i < moob.size(); i++ )
		if( moob[i]->getPos().first == y && moob[i]->getPos().second == x )
			return i;
	return 0;
}
string PROCESS::Passage( int y, int x ){ 
	if( x < 0 || x >= area_w || y < 0 || y >= area_h )
		return "end";
	if( object[ y * area_w + x ] == 0 )
		return "";
	return typeid( *object[ y * area_w + x ] ).name();
}