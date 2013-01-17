#include "PROCESS.h"

PROCESS::PROCESS(){
	for( int i = 0; i < area_h; i++ ){
		for( int j = 0; j < area_w; j++ ){
			map_object[ i ][ j ] = 0;
		}
	}
}
bool PROCESS::GetObject( string type, int pattern, string able  ){
	if( type == "PLAYER" ){
		player = new PLAYER( pattern, pattern );
	}
	if( type == "MONSTER_1" ){
		for( int i = 0; i < pattern; ){
			int y = rand()%area_h, x = rand()%area_h;
			if( map_object[ y ][ x ] == 0 && !( y < 5 && x < 5 ) ){
				map_object[ y ][ x ] = new MONSTER_1( y, x );
				pair< int, int > temp;
				temp.first = y;
				temp.second = x;
				moobs_position.push_back( temp );
				i++;
			}
		}
	}
	if( able == "NO_RANDOM" ){ 
		for( int i = 1; i < area_h; i += pattern ){
			for( int j = 1; j < area_w; j += pattern ){
				map_object[ i ][ j ] = new BLOCK( i, j );
			}
		}
	}
	if( able == "RANDOM" ){
		for( int i = 0; i < pattern; ){
			int y = rand()%area_h, x = rand()%area_w;
			if( map_object[ y ][ x ] == 0 && !( y < 2 && x < 2 ) ){
				map_object[ y ][ x ] = new BRICK( y, x );
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
			if( map_object[ i ][ j ] != 0 ){
				map_object[ i ][ j ]->Draw();
			}
		}
	}
}
void PROCESS::ClearObject( int y, int x ){
	//cursor_to_global( y*object_h, x*object_w );
	for( int i = 0; i < ob_size; i++ ){
		for( int j = 0; j < ob_size; j++ )
			cout << " ";
		//cursor_to( 1, -object_w );
	}
}
void PROCESS::FireDraw( int y, int x ){
	//cursor_to_global( y*object_h, x*object_w );
	//setColor( 12, 0 );
	for( int i = 0; i < ob_size; i++ ){
		for( int j = 0; j < ob_size; j++ )
			cout << rand()%10;
		//cursor_to( 1, -object_w );
	}
}
bool PROCESS::PlayerMoveTo( int y, int x ){
	string type = Passage( y = player->getPos().first + y, x = player->getPos().second + x );
	if( type == "" ){	
		//if( !map_object[player->getPos().first][player->getPos().second] ) {
			//ClearObject( player->getPos().first, player->getPos().second );	
		//}
		player->setPos( y, x );
		//player->Draw();
		//cursor_to_global( 0, 0 );
		return true;
	}
	return false;
}
bool PROCESS::PushBomb(){
	if( FindBomb( player->getPos().first, player->getPos().second ) == -1 ){
		bomb.push_back( new BOMB( player->getPos().first, player->getPos().second ) );
		map_object[ player->getPos().first ][ player->getPos().second ] = bomb.back();
		bomb.back()->Draw();
		return true;
	}
	return false;
}
bool PROCESS::BangBomb( int temp ){
	int y = bomb[ temp ]->getPos().first;
	int x = bomb[ temp ]->getPos().second;

	bomb.erase( bomb.begin() + temp );
		
	delete map_object[y][x];
	map_object[y][x] = 0;
		
	if( FindFire( y, x ) == -1 ) fire.push_back( new FIRE( y, x ) );
	for( int i=1, n1=1, n2=1, n3=1, n4=1; i < strength+1; i++ ){
		if( n1 ) n1=BigBang( y - i,  x );
		if( n2 ) n2=BigBang( y + i,  x );
		if( n3 ) n3=BigBang( y,  x - i );
		if( n4 ) n4=BigBang( y,  x + i );
	}
	for( int i = 0; i < fire.size(); i++ )
		fire[i]->Draw();
	for( int i = 0; i < fire.size(); )
		Destroy( fire[i]->getPos().first, fire[i]->getPos().second );
	return true;
}
int PROCESS::BigBang( int y, int x ){
	if( FindFire( y, x ) == -1 ){
		if( Passage( y, x ) == "-" || Passage( y, x ) == "class BLOCK" )
			return 0;
		if( Passage( y, x ) == "" ){
			fire.push_back( new FIRE( y, x ) );
			return 1;
		}
		if( Passage( y, x ) == "class BRICK" || Passage( y, x ) == "class BOMB" ){
			fire.push_back( new FIRE( y, x ) );
			return 0;
		}
		if( Passage( y, x ) == "class MONSTER_1" ){
			fire.push_back( new FIRE( y, x ) );
			return 1;
		}
	}
	return 1;
}
bool PROCESS::Destroy( int y, int x ){
	if( Passage( y, x ) == "class BOMB" ){
		BangBomb( FindBomb( y, x ) );
		return true;
	}
	if( Passage( y, x ) == "class MONSTER_1" ){
		moobs_position.erase( moobs_position.begin() + FindMonster( y, x ) );
	}
	if( Passage( y, x ) != "" ){
		delete map_object[y][x];
		map_object[y][x] = 0;
	}
	fire.erase( fire.begin() + FindFire( y, x ) );
	ClearObject( y, x );
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
	for( int i = 0; i < moobs_position.size(); i++ )
		if( moobs_position[ i ].first == y && moobs_position[ i ].second == x )
			return i;
	return 0;
}
bool PROCESS::MoobsMoveTo(){
	for( int i = 0; i < moobs_position.size(); i++ ){
		map_object[moobs_position[ i ].first][moobs_position[ i ].second] ->Draw();
		int x=0, y=0, xy=0;
		while( !(x + y) ) {
			x = rand()%3 - 1;
			y = rand()%3 - 1;
			xy = rand()%2;
			if( xy ) x = 0;
			else y = 0;
		}
		string type = Passage( y = moobs_position[i].first + y, x = moobs_position[i].second + x );
		if( type == "" ){
			//ClearObject( moobs_position[i].first, moobs_position[i].second );
			map_object[y][x] = map_object[moobs_position[i].first][moobs_position[i].second];
			map_object[moobs_position[i].first][moobs_position[i].second] = 0;
			map_object[y][x]->setPos(y,x);
			moobs_position[i].first = y;
			moobs_position[i].second = x;
			//map_object[y][x]->Draw();
			//cursor_to_global( 0, 0 );
		}
	}
	return true;
}
string PROCESS::Passage( int y, int x ){ 
	if( x < 0 || x >= area_w || y < 0 || y >= area_h )
		return "end";
	if( map_object[y][x] == 0 )
		return "";
	return typeid( *map_object[y][x] ).name();
}