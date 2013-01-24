#include "PROCESS.h"

PROCESS::PROCESS(){
	type.push_back("PLAYER");
	type.push_back("BLOCK");	
	type.push_back("FIRE");	
	type.push_back("BOMB");
	type.push_back("MOOB");
	type.push_back("BRICK");
	type.push_back("BONUS");
}
void PROCESS::GetObject( string temp, int y, int x ){
	if( temp == type[0] ){
		player.push_back( new PLAYER( y, x ) );
	}
	if( temp == type[1] ){
		block.push_back( new BLOCK( y, x ) );
	}
	if( temp == type[2] ){
		fire.push_back( new FIRE( y, x ) );
	}
	if( temp == type[3] ){
		bomb.push_back( new BOMB( y, x ) );
	}
	if( temp == "MOOB_1" ){
		moob.push_back( new MOOB_1( y, x ) );
	}
	if( temp == "MOOB_2" ){
		moob.push_back( new MOOB_2( y, x ) );
	}
	if( temp == "MOOB_3" ){
		moob.push_back( new MOOB_3( y, x ) );
	}
	if( temp == type[5] ){
		brick.push_back( new BRICK( y, x ) );
	}
	if( temp == "BONUS_AB" ){
		bonus.push_back( new BONUS_AB( y, x ) );
	}
	if( temp == "BONUS_PwB" ){
		bonus.push_back( new BONUS_PwB( y, x ) );
	}
	if( temp == "BONUS_PhB" ){
		bonus.push_back( new BONUS_PhB( y, x ) );
	}
	if( temp == "BONUS_FR" ){
		bonus.push_back( new BONUS_FR( y, x ) );
	}
	if( temp == "BONUS_TW" ){
		bonus.push_back( new BONUS_TW( y, x ) );
	}
}
void PROCESS::GetObject( string temp, int amount, string able, int border_y, int border_x ){
	for_each( i ){
		if( temp == type[i] || temp == "MOOB_1" || temp == "MOOB_2" || temp == "MOOB_3" ){
			for( int j = 0; j < amount; ){
				int y = rand()%area_h, x = rand()%area_w;
				if( border_y < y || border_x < x ){
					if( ObjectIdentification( y, x ) == "" ){
						GetObject( temp, y, x );
						j++;
					}
				}
			}
			return;
		}
		if( temp == "BONUS_AB" || temp == "BONUS_PwB" || temp == "BONUS_PhB" || temp == "BONUS_FR" || temp == "BONUS_TW" ){
			if( brick.size() - bonus.size() > amount ){
				for( int j = 0; j < amount; ){
					int y = rand()%area_h, x = rand()%area_w;
					if( border_y < y || border_x < x ){
						if( Find( y, x, "BRICK" ) != -1 && Find( y, x, "BONUS" ) == -1 ){
							GetObject( temp, y, x );
							j++;
						}
					}
				}
			}
			return;
		}
	}
}
void PROCESS::GetObject( string temp, int construction ){
	for( int y = 1; y < area_h; y += 2 ){
		for( int x = 1; x < area_w; x += 2 )
			GetObject( temp, y, x );
	}
}
void PROCESS::Print(){
	for( int i = 6; i >= 0; i-- ){
		Draw( type[i] );
	}
}
void PROCESS::Draw( string temp ){
	if( temp == type[0] ){
		for( int j = 0; j < player.size(); j++ ){
			player[j]->Draw();
		}
	}
	if( temp == type[1] ){
		for( int j = 0; j < block.size(); j++ ){
			block[j]->Draw();
		}
	}
	if( temp == type[2] ){
		for( int j = 0; j < fire.size(); j++ ){
			fire[j]->Draw();
		}
	}
	if( temp == type[3] ){
		for( int j = 0; j < bomb.size(); j++ ){
			bomb[j]->Draw();
		}
	}
	if( temp == type[4] ){
		for( int j = 0; j < moob.size(); j++ ){
			moob[j]->Draw();
		}
	}
	if( temp == type[5] ){
		for( int j = 0; j < brick.size(); j++ ){
			brick[j]->Draw();
		}
	}
	if( temp == type[6] ){
		for( int j = 0; j < bonus.size(); j++ ){
			bonus[j]->Draw();
		}
	}
}
bool PROCESS::MovePlayer( string route ){
	for( int i = 0; i < player.size(); i++ ){
		int y = 0, x = 0;
		if( route == "LEFT" ) x = -1; 
		if( route == "RIGHT" ) x = 1;
		if( route == "UP" ) y = -1;
		if( route == "DOWN" ) y = 1;

		y += player[i]->GetPos().first;
		x += player[i]->GetPos().second;
		
		int a = Find( y, x, "BOMB" );
		int b = Find( y, x, "BRICK" );
		int c = Find( y, x, "BONUS" );

		if( Passage( y, x ) || ( a != -1 && player[i]->push_bomb ) || ( b != -1 && player[i]->through_wall || Passage( y, x ) ) ){	
			if( a != -1 ){
				MoveBomb( i, a );
				return false;
			}
			if( b == -1 && c != -1 ){
				string type = typeid(*bonus[c]).name();
				type.erase( type.begin(), type.begin() + 12 );
				player[i]->SetBonus( 1, type );
				player[i]->SetBonus( true, type );
				bonus.erase( bonus.begin() + c );
			}
			player[i]->SetPos( y, x );
			return true;
		}
		return false;
	}
}
void PROCESS::MoveBomb( int numb_p, int numb_b ){
	bomb[numb_b]->push = true;
	if( bomb[numb_b]->GetPos().first == player[numb_p]->GetPos().first ){
		bomb[numb_b]->course = 1; 
		if( bomb[numb_b]->GetPos().second < player[numb_p]->GetPos().second ){
			bomb[numb_b]->course++; 
		}
	} else {
		bomb[numb_b]->course = 3; 
		if( bomb[numb_b]->GetPos().first < player[numb_p]->GetPos().first ){
			bomb[numb_b]->course++; 
		}
	}
}
bool PROCESS::PushBomb( int i ){
	int y = player[i]->GetPos().first, x = player[i]->GetPos().second;
	if( Find( y, x, "BOMB" ) == -1 && player[i]->GetBonus( "AB" ) && Find( y, x, "BRICK" ) == -1  ){
		bomb.push_back( new BOMB( y, x, player[0]->GetBonus( "PwB" ) ) );
		player[i]->SetBonus( -1, "AB" );
		return true;
	}
	return false;
}

void PROCESS::BombTime(){
	for( int i = 0; i < bomb.size(); i++ ){
		if( bomb[i]->GetTimer() == 0 ){
			BangBomb( i );
		} else {
			if( bomb[i]->push ) {
				int y = bomb[i]->GetPos().first, x = bomb[i]->GetPos().second;
				switch ( bomb[i]->course ){
				case 1: if( Passage( y, x + 1 ) ){ bomb[i]->SetPos( y, x + 1 ); } else { bomb[i]->push = false; } break;
				case 2: if( Passage( y, x - 1 ) ){ bomb[i]->SetPos( y, x - 1 ); } else { bomb[i]->push = false; } break;
				case 3: if( Passage( y + 1, x ) ){ bomb[i]->SetPos( y + 1, x ); } else { bomb[i]->push = false; } break;
				case 4: if( Passage( y - 1, x ) ){ bomb[i]->SetPos( y - 1, x ); } else { bomb[i]->push = false; } break;
				}
			}
			bomb[i]->SetTimer();
		}
	}
}
void PROCESS::BangBomb( int temp ){	
	int i;
	player[0]->SetBonus( 1, "AB" );
	int y = bomb[ temp ]->GetPos().first;
	int x = bomb[ temp ]->GetPos().second;
		
	fire.push_back( new FIRE( y, x ) );
	if( ( i = Find( y, x, "PLAYER" )) != -1 && player[i]->fire_resist == false ) player.erase( player.begin() + i );
	int pow_bomb = bomb[ temp ]->GetPower();
	for( int k=1, n1=1, n2=1, n3=1, n4=1; k < pow_bomb + 1; k++ ){
		if( n1 ) n1 = BigBang( y - k,  x );
		if( n2 ) n2 = BigBang( y + k,  x );
		if( n3 ) n3 = BigBang( y,  x - k );
		if( n4 ) n4 = BigBang( y,  x + k );
	}
	bomb[ temp ]->SetTimer( -1 );
}
bool PROCESS::BigBang( int y, int x ){
	string temp = ObjectIdentification( y , x );
	int l;
	if( temp == "-" || temp == "BLOCK" )
		return false;
	if( ( l = Find( y, x, "BOMB" ) ) != -1 && Find( y, x, "FIRE" ) == -1 ){
		BangBomb( l );
		return false;
	}
	while( ( l = Find( y, x, "MOOB" ) ) != -1 ){
		moob.erase( moob.begin() + l );
	}
	if( ( l = Find( y, x, "PLAYER" ) ) != -1 ){
		if( player[l]->fire_resist == false ){ 
			player.erase( player.begin() + l );
		}
	}
	fire.push_back( new FIRE( y, x ) );
	if( Find( y, x, "BRICK" ) != -1 || Find( y, x, "BOMB" ) != -1 ) return false;
	return true;
}
void PROCESS::DestroyFire(){
	for( int i = 0; i < fire.size(); ){
		if( fire[i]->GetTimer() == 0 ){
			int y = fire[i]->GetPos().first, x = fire[i]->GetPos().second;
			while( Find( y, x, "MOOB" ) != -1 )
				moob.erase( moob.begin() + Find( y, x, "MOOB" ) );
			if( Find( y, x, "PLAYER" ) != -1 && player[0]->fire_resist == false )
				player.erase( player.begin() + Find( y, x, "PLAYER" ) );
			if( Find( y, x, "BOMB" ) != -1 )
				bomb.erase( bomb.begin() + Find( y, x, "BOMB" ) );
			if( Find( y, x, "BONUS" ) != -1 && Find( y, x, "BRICK" ) == -1 )
				bonus.erase( bonus.begin() + Find( y, x, "BONUS" ) );
			if( Find( y, x, "BRICK" ) != -1 )
				brick.erase( brick.begin() + Find( y, x, "BRICK" ) );
			fire.erase( fire.begin() + i );
		}
		else {
			fire[i]->SetTimer();
			i++;
		}
	}
}
void PROCESS::MoveMoobs(){
	for( int i = 0; i < moob.size(); i++ ){
		if( moob[i]->GetSpeed() == 0 ){
			bool way[4];
			int course = -1, count_way = 0, course_inverse = -1;

			if( moob[i]->course%2 ) course_inverse = moob[i]->course - 1;
			else course_inverse = moob[i]->course + 1;

			{
				int y = moob[i]->GetPos().first, x = moob[i]->GetPos().second;

				for( int k = 0; k < 4; k++ )
					way[k] = false;
				if( Passage( y - 1, x ) || ( Find( y - 1, x, "BRICK" ) != -1 && moob[i]->tw ) ){ way[0] = true; count_way++; }
				if( Passage( y + 1, x ) || ( Find( y + 1, x, "BRICK" ) != -1 && moob[i]->tw ) ){ way[1] = true; count_way++; }
				if( Passage( y, x - 1 ) || ( Find( y, x - 1, "BRICK" ) != -1 && moob[i]->tw ) ){ way[2] = true; count_way++; }
				if( Passage( y, x + 1 ) || ( Find( y, x + 1, "BRICK" ) != -1 && moob[i]->tw ) ){ way[3] = true; count_way++; }
			}
			if( !count_way ) continue;
			if( way[moob[i]->course] && rand()%3 ) course = moob[i]->course;
			if( count_way == 1 ) 
				for( int k = 0; k < 4; k++ )
					if( way[k] == true ) course = k;
			while( course == -1 ){
				int s = rand()%4;
				if( way[s] && ( s != course_inverse || rand()%3 ) ) course = s;
			}

			int x=0, y=0, v = -1;
			if( course%2 ) v = 1;
			if( course < 2 ) y += v;
			else x += v;
	
			y += moob[i]->GetPos().first;
			x += moob[i]->GetPos().second;

			if( ObjectIdentification( y, x ) == "PLAYER" )
				player.erase( player.begin() + Find( y, x, "PLAYER" ) );

			if( Find( y, x, "FIRE" ) == -1 ) moob[i]->SetPos( y, x );
			moob[i]->ResetSpeed();
			moob[i]->course = course;
		}
		else moob[i]->SetSpeed();
	}
}
string PROCESS::ObjectIdentification( int y, int x ){
	if( y > area_h - 1 || y < 0 || x > area_w - 1 || x < 0 )
		return "-";
	for( int i = 0; i < 7; i++ ){
		if( Find( y, x, type[i] ) != -1 ){
			return type[i];
		}
	}
	return "";
}
bool PROCESS::Passage( int y, int x ){
	if( y > area_h - 1 || y < 0 || x > area_w - 1 || x < 0 )
		return false;
	if( Find( y, x, "BOMB") != -1 || Find( y, x, "MOOB" ) != -1 || Find( y, x, "BRICK" ) != -1 || Find( y, x, "BLOCK") != -1 )
		return false;

	return true;
}
int PROCESS::Find( int y, int x, string temp ){
	if( temp == type[0] ){
		for( int i = 0; i < player.size(); i++ )
			if( player[ i ]->GetPos().first == y && player[ i ]->GetPos().second == x )
				return i;
	}
	if( temp == type[1] ){
		for( int i = 0; i < block.size(); i++ )
			if( block[ i ]->GetPos().first == y && block[ i ]->GetPos().second == x )
				return i;
	}
	if( temp == type[2] ){
		for( int i = 0; i < fire.size(); i++ )
			if( fire[ i ]->GetPos().first == y && fire[ i ]->GetPos().second == x )
				return i;
	}
	if( temp == type[3] ){
		for( int i = 0; i < bomb.size(); i++ )
			if( bomb[ i ]->GetPos().first == y && bomb[ i ]->GetPos().second == x )
				return i;
	}
	if( temp == type[4] ){
		for( int i = 0; i < moob.size(); i++ )
			if( moob[ i ]->GetPos().first == y && moob[ i ]->GetPos().second == x )
				return i;
	}
	if( temp == type[5] ){
		for( int i = 0; i < brick.size(); i++ )
			if( brick[ i ]->GetPos().first == y && brick[ i ]->GetPos().second == x )
				return i;
	}
	if( temp == type[6] ){
		for( int i = 0; i < bonus.size(); i++ )
			if( bonus[ i ]->GetPos().first == y && bonus[ i ]->GetPos().second == x )
				return i;
	}
	return -1;
}
bool PROCESS::EndGame(){
	if( !player.size() ){// || !moob.size() ||  ){
		return true;
	}
	return false;
}
void PROCESS::Restart(){
	player.push_back( new PLAYER( 0, 0 ) );
}