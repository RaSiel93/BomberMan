#include "PROCESS.h"
#include <cmath>



PROCESS::PROCESS(){
	level = 0;
	type.push_back("BLOCK");	
	type.push_back("FIRE");	
	type.push_back("PLAYER");
	type.push_back("BOMB");
	type.push_back("MOOB");
	type.push_back("BRICK");
	type.push_back("BONUS");
}
PROCESS::~PROCESS(){
	block.clear();
	fire.clear();
	player.clear();
	bomb.clear();
	moob.clear();
	brick.clear();
	bonus.clear();
}
bool PROCESS::LevelGenerate( int level ){
	int area = area_h*area_w;
	if( !player.size() ) GetObject( "PLAYER", 0, 0 );
	GetObject( "BLOCK", (level - 1 )%6 + 1 );
	GetObject( "BRICK", area/4, "RANDOM", 1, 1 );
	GetObject( "BONUS_AB", area/60, "RANDOM", 0, 0 );
	GetObject( "BONUS_PwB", area/60, "RANDOM", 0, 0 );
	if( level > 2 ) GetObject( "BONUS_PhB", 1, "RANDOM", 0, 0 );
	if( level > 3 ) GetObject( "BONUS_TW", 1, "RANDOM", 0, 0 );
	if( level > 4 ) GetObject( "BONUS_FR", 1, "RANDOM", 0, 0 );
	if( level > 5 ) GetObject( "BONUS_UD", 1, "RANDOM", 0, 0 );
	GetObject( "MOOB_1", area/50  - level + 1, "RANDOM", 5, 5 );
	if ( level > 1 ) GetObject( "MOOB_2", area/60 - level + 2, "RANDOM", 5, 5 );
	if ( level > 2 ) GetObject( "MOOB_3", area/70 - level + 3, "RANDOM", 5, 5 );
	if ( level > 3 ) GetObject( "MOOB_4", area/70 - level + 4, "RANDOM", 5, 5 );
	if ( level > 4 ) GetObject( "MOOB_5", area/70 - level + 5, "RANDOM", 5, 5 );
	if ( level > 5 ) GetObject( "MOOB_6", area/70 - level + 6, "RANDOM", 5, 5 );
	if ( level > 6 ) GetObject( "MOOB_7", area/70 - level + 7, "RANDOM", 5, 5 );
	return true;
}
void PROCESS::GetObject( string temp, int y, int x ){
	if( temp == type[0] ){
		block.push_back( new BLOCK( y, x ) );
	}
	if( temp == type[1] ){
		fire.push_back( new FIRE( y, x ) );
	}
	if( temp == type[2] ){
		player.push_back( new PLAYER( y, x ) );
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
	if( temp == "MOOB_4" ){
		moob.push_back( new MOOB_4( y, x ) );
	}
	if( temp == "MOOB_5" ){
		moob.push_back( new MOOB_5( y, x ) );
	}
	if( temp == "MOOB_6" ){
		moob.push_back( new MOOB_6( y, x ) );
	}
	if( temp == "MOOB_7" ){
		moob.push_back( new MOOB_7( y, x ) );
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
	if( temp == "BONUS_UD" ){
		bonus.push_back( new BONUS_UD( y, x ) );
	}
}
void PROCESS::GetObject( string temp, int amount, string able, int border_y, int border_x ){
	for_each( i ){
		if( temp == type[i] || temp == "MOOB_1" || temp == "MOOB_2" || temp == "MOOB_3" || temp == "MOOB_4" || temp == "MOOB_5" || temp == "MOOB_6" || temp == "MOOB_7"){
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
		if( temp == "BONUS_AB" || temp == "BONUS_PwB" || temp == "BONUS_PhB" || temp == "BONUS_FR" || temp == "BONUS_TW" || temp == "BONUS_UD" ){
			if( (int)brick.size() - (int)bonus.size() > amount ){
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
	if( construction == 1 ){
		for( int y = 1; y < area_h; y += 2 ){
			for( int x = 1; x < area_w; x += 2 )
				GetObject( temp, y, x );
		}
	}
	if( construction == 2 ){
		for( int y = 1; y < area_h - 1; y++ ){
			for( int x = 1; x < area_w - 1; x += 3 ){
				if( ( y + 1 ) % 3 == 0 ) x++;
				GetObject( temp, y, x );
				if( ( y + 1 ) % 3 == 0 ) x--;
			}
			if( ( y + 1 ) % 3 == 0 ) y++;
		}
	}
	if( construction == 3 ){
		for( int y = 1; y < area_h - 1; y++ ){
			for( int x = 1; x < area_w - 1; x += 4 ){
				GetObject( temp, y, x );
			}
			if(  (y + 1 ) % 6 == 0 ) y++;
		}
	}
	if( construction == 4 ){
		for( int y = 1; y < area_h - 1; y++ ){
			for( int x = (y - 1)%4 + 1; x < area_w - 1; x += 4 ){
				GetObject( temp, y, x );
			}
		}
	}
	if( construction == 5 ){
		for( int y = 1; y < area_h - 1; y+=3 ){
			for( int x = 1; x < area_w - 1; x+=2 ){
				GetObject( temp, y, x );
			}
		}
	}
	if( construction == 6 ){
		for( int y = 1; y < area_h - 1; y++ ){
			for( int x = 1; x < area_w - 1; x++ ){
				if( ( x + y + 1 ) % 7 ) x++;
				else y++;
				GetObject( temp, y, x );
			}
		}
	}
	if( construction == 7 ){
		for( int y = 1; y < area_h - 1; y += 5 ){
			for( int x = 1; x < area_w - 1; x++ ){
				if( ( x * y ) % 2 ) x += 3;
				GetObject( temp, y, x );
			}
		}
	}
}
void PROCESS::Print(){
	glClear(GL_COLOR_BUFFER_BIT);
	for( int i = 6; i >= 0; i-- ){
		glColor3f(1.0, 1.0, 1.0);
		Draw( type[i] );
	}
	glutSwapBuffers();
}
void PROCESS::Draw( string temp ){
	if( temp == type[0] ){
		for( int j = 0; j < (int)block.size(); j++ ){
			block[j]->Draw();
		}
	}
	if( temp == type[1] ){
		for( int j = 0; j < (int)fire.size(); j++ ){
			fire[j]->Draw();
		}
	}
	if( temp == type[2] ){
		for( int j = 0; j < (int)player.size(); j++ ){
			player[j]->Draw();
		}
	}
	if( temp == type[3] ){
		for( int j = 0; j < (int)bomb.size(); j++ ){
			bomb[j]->Draw();
		}
	}
	if( temp == type[4] ){
		for( int j = 0; j < (int)moob.size(); j++ ){
			moob[j]->Draw();
		}
	}
	if( temp == type[5] ){
		for( int j = 0; j < (int)brick.size(); j++ ){
			brick[j]->Draw();
		}
	}
	if( temp == type[6] ){
		for( int j = 0; j < (int)bonus.size(); j++ ){
			bonus[j]->Draw();
		}
	}
}
void PROCESS::MovePlayer( string route ){
	for( int i = 0; i < (int)player.size(); i++ ){
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
				return;
			}
			if( b == -1 && c != -1 ){
				BYTE szBuf[256];
				mciSendString((LPSTR)"close snd", (LPSTR)szBuf, 256, NULL);
				mciSendString((LPSTR)"open sound/bag.wav type waveaudio alias snd wait", (LPSTR)szBuf, 256, NULL);
				mciSendString((LPSTR)"play snd", (LPSTR)szBuf, 256, NULL);

				string type = typeid(*bonus[c]).name();
				type.erase( type.begin(), type.begin() + 12 );
				if( type == "UD" ){
					player[i]->SetBonus( 300, type );
				} else {
					player[i]->SetBonus( 1, type );
					player[i]->SetBonus( true, type ); 
				}
				bonus.erase( bonus.begin() + c );
			}
			player[i]->SetPos( y, x );
		} else {
			BYTE szBuf[256];
			mciSendString((LPSTR)"close snd", (LPSTR)szBuf, 256, NULL);
			int sound = rand()%4;
			switch( sound ){
			case 0: mciSendString((LPSTR)"open sound/wall1.wav type waveaudio alias snd wait", (LPSTR)szBuf, 256, NULL); break;
			case 1: mciSendString((LPSTR)"open sound/wall2.wav type waveaudio alias snd wait", (LPSTR)szBuf, 256, NULL); break;
			case 2: mciSendString((LPSTR)"open sound/wall3.wav type waveaudio alias snd wait", (LPSTR)szBuf, 256, NULL); break;
			case 3: mciSendString((LPSTR)"open sound/wall4.wav type waveaudio alias snd wait", (LPSTR)szBuf, 256, NULL); break;
			}
			mciSendString((LPSTR)"play snd", (LPSTR)szBuf, 256, NULL);
		}
	}
}
void PROCESS::MoveBomb( int numb_p, int numb_b ){
	BYTE szBuf[256];
	mciSendString((LPSTR)"close snd", (LPSTR)szBuf, 256, NULL);
	mciSendString((LPSTR)"open sound/push.wav type waveaudio alias snd wait", (LPSTR)szBuf, 256, NULL);
	mciSendString((LPSTR)"play snd", (LPSTR)szBuf, 256, NULL);
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
		BYTE szBuf[256];
		mciSendString((LPSTR)"close snd", (LPSTR)szBuf, 256, NULL);
		mciSendString((LPSTR)"open sound/beep.wav type waveaudio alias snd wait", (LPSTR)szBuf, 256, NULL);
		mciSendString((LPSTR)"play snd", (LPSTR)szBuf, 256, NULL);
		
		bomb.push_back( new BOMB( y, x, player[0]->GetBonus( "PwB" ) ) );
		player[i]->SetBonus( -1, "AB" );
		return true;
	}
	return false;
}

void PROCESS::BombTime(){
	for( int i = 0; i < (int)bomb.size(); i++ ){
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
	int sound = rand()%3;
	switch( sound ){
		case 0: PlaySound("sound/BANG1.wav", NULL, SND_ASYNC); break;
		case 1: PlaySound("sound/BANG2.wav", NULL, SND_ASYNC); break;
		case 2: PlaySound("sound/BANG3.wav", NULL, SND_ASYNC); break;
	}
	player[0]->SetBonus( 1, "AB" );
	int y = bomb[ temp ]->GetPos().first;
	int x = bomb[ temp ]->GetPos().second;
	

	fire.push_back( new FIRE( y, x ) );
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
	fire.push_back( new FIRE( y, x ) );
	if( Find( y, x, "BRICK" ) != -1 || Find( y, x, "BOMB" ) != -1 ) 
		return false;
	return true;
}
void PROCESS::DestroyFire(){
	int size_moob = (int)moob.size();
	for( int i = 0; i < (int)fire.size(); ){
		int y = fire[i]->GetPos().first, x = fire[i]->GetPos().second;
		if( Find( y, x, "MOOB" ) != -1 ){
			string type = typeid(*moob[Find( y, x, "MOOB" )]).name();
			player[0]->score += atoi( &type[11] ) * 100;
			moob.erase( moob.begin() + Find( y, x, "MOOB" ) );
		}
		if( Find( y, x, "PLAYER" ) != -1 && player[0]->fire_resist == false )
			ResetPlayer( Find( y, x, "PLAYER" ) );
		if( Find( y, x, "BOMB" ) != -1 ){
			if( bomb[Find( y, x, "BOMB" )]->GetTimer() > 0 ){
				BangBomb( Find( y, x, "BOMB" ) );
			}
			bomb.erase( bomb.begin() + Find( y, x, "BOMB" ) );
		}
		if( fire[i]->GetTimer() == 0 ){
			if( Find( y, x, "BONUS" ) != -1 && Find( y, x, "BRICK" ) == -1 ){
				bonus.erase( bonus.begin() + Find( y, x, "BONUS" ) );
			}
			if( Find( y, x, "BRICK" ) != -1 ){
				brick.erase( brick.begin() + Find( y, x, "BRICK" ) );
			}
			fire.erase( fire.begin() + i );
		}
		else {
			fire[i]->SetTimer();
			i++;
		}
	}
	if( size_moob - (int)moob.size() ){
		BYTE szBuf[256];
		mciSendString((LPSTR)"close snd", (LPSTR)szBuf, 256, NULL);
		mciSendString((LPSTR)"open sound/moobd1.wav type waveaudio alias snd wait", (LPSTR)szBuf, 256, NULL);
		mciSendString((LPSTR)"play snd", (LPSTR)szBuf, 256, NULL);
	}
}
void PROCESS::MoveMoobs(){
	for( int i = 0; i < (int)moob.size(); i++ ){
		if( moob[i]->GetSpeed() == 0 ){
			bool way[4];
			int course = -1, count_way = 0, course_inverse = -1;

			if( moob[i]->course%2 ) course_inverse = moob[i]->course - 1;
			else course_inverse = moob[i]->course + 1;

			{
				int y = moob[i]->GetPos().first, x = moob[i]->GetPos().second;

				for( int k = 0; k < 4; k++ )
					way[k] = false;
				if( Passage( y - 1, x ) || ( Find( y - 1, x, "BRICK" ) != -1 && moob[i]->tw ) ){ 
					way[0] = true; count_way++; 
					if( Find( y - 1, x, "PLAYER" ) != -1 ){
						course = 0;
					}
				}
				if( Passage( y + 1, x ) || ( Find( y + 1, x, "BRICK" ) != -1 && moob[i]->tw ) ){ 
					way[1] = true; count_way++; 
					if( Find( y + 1, x, "PLAYER" ) != -1 ){
						course = 1;
					}
				}
				if( Passage( y, x - 1 ) || ( Find( y, x - 1, "BRICK" ) != -1 && moob[i]->tw ) ){ 
					way[2] = true; count_way++; 
					if( Find( y, x - 1, "PLAYER" ) != -1 ){
						course = 2;
					}
				}
				if( Passage( y, x + 1 ) || ( Find( y, x + 1, "BRICK" ) != -1 && moob[i]->tw ) ){ 
					way[3] = true; count_way++; 
					if( Find( y, x + 1, "PLAYER" ) != -1 ){
						course = 3;
					}
				}
			}
			if( !count_way ) continue;
			bool flag = way[course_inverse];
			if( moob[i]->smart_brain && course == -1 ){
				way[course_inverse] = false;
				for( int j = 0; j < (int)player.size(); j++ ){
					int yy = 0, xx = 2; 
					bool yx = true;
					if( player[j]->GetPos().first > moob[i]->GetPos().first ) yy = 1;
					if( player[j]->GetPos().second > moob[i]->GetPos().second ) xx = 3;
					if( player[j]->GetPos().first == moob[i]->GetPos().first || player[j]->GetPos().second == moob[i]->GetPos().second ) yx = false;
					if( yx ){
						if( abs( player[j]->GetPos().first - moob[i]->GetPos().first ) < abs( player[j]->GetPos().second - moob[i]->GetPos().second ) ){
							if( way[yy] ) course = yy;
							else if( way[xx] ) course = xx;
						}
						if( abs( player[j]->GetPos().first - moob[i]->GetPos().first ) > abs( player[j]->GetPos().second - moob[i]->GetPos().second ) ){
							if( way[xx] ) course = xx;
							else if( way[yy] ) course = yy;
						}
					}
				}
			}
			if( moob[i]->brain && course == -1 ){
				for( int j = 0; j < (int)player.size(); j++ ){
					if( player[j]->GetPos().first == moob[i]->GetPos().first ){
						if( player[j]->GetPos().second < moob[i]->GetPos().second ){ if( way[2] ) course = 2; 
						} else { if( way[3] ) course = 3; }
					}
					if( player[j]->GetPos().second == moob[i]->GetPos().second ){
						if( player[j]->GetPos().first < moob[i]->GetPos().first ){ if( way[0] ) course = 0;
						} else { if( way[1] ) course = 1; }
					}
				}
			}
			way[ course_inverse	] = flag;
			if( count_way == 1 ) 
				for( int k = 0; k < 4; k++ )
					if( way[k] == true ) course = k;
			if( course == -1 && way[moob[i]->course] && rand()%3 ) course = moob[i]->course;
			while( course == -1 ){
				int s = rand()%4;
				if( way[s] && ( s != course_inverse || rand()%4 ) ) course = s;
			}


			int x=0, y=0, v = -1;
			if( course%2 ) v = 1;
			if( course < 2 ) y += v;
			else x += v;
	
			y += moob[i]->GetPos().first;
			x += moob[i]->GetPos().second;

			if( ObjectIdentification( y, x ) == "PLAYER" )
				ResetPlayer( Find( y, x, "PLAYER" ) );
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
	if( Find( y, x, "PLAYER") != -1 )
		if( player[ Find( y, x, "PLAYER") ]->undead )
			return false;
	return true;
}
int PROCESS::Find( int y, int x, string temp ){
	if( temp == type[0] ){
		for( int i = 0; i < (int)block.size(); i++ )
			if( block[ i ]->GetPos().first == y && block[ i ]->GetPos().second == x )
				return i;
	}
	if( temp == type[1] ){
		for( int i = 0; i < (int)fire.size(); i++ )
			if( fire[ i ]->GetPos().first == y && fire[ i ]->GetPos().second == x )
				return i;
	}
	if( temp == type[2] ){
		for( int i = 0; i < (int)player.size(); i++ )
			if( player[ i ]->GetPos().first == y && player[ i ]->GetPos().second == x )
				return i;
	}
	if( temp == type[3] ){
		for( int i = 0; i < (int)bomb.size(); i++ )
			if( bomb[ i ]->GetPos().first == y && bomb[ i ]->GetPos().second == x )
				return i;
	}
	if( temp == type[4] ){
		for( int i = 0; i < (int)moob.size(); i++ )
			if( moob[ i ]->GetPos().first == y && moob[ i ]->GetPos().second == x )
				return i;
	}
	if( temp == type[5] ){
		for( int i = 0; i < (int)brick.size(); i++ )
			if( brick[ i ]->GetPos().first == y && brick[ i ]->GetPos().second == x )
				return i;
	}
	if( temp == type[6] ){
		for( int i = 0; i < (int)bonus.size(); i++ )
			if( bonus[ i ]->GetPos().first == y && bonus[ i ]->GetPos().second == x )
				return i;
	}
	return -1;
}
/*void PROCESS::PlayerBombMaster(){
	for( int i = 0; i < (int)player.size(); i++ ){
		if( player[i]->bomb_master ){
			if( player[i]->bomb_master%30 == 0 ){ 
				player[i]->undead = player[i]->bomb_master;
				PushBomb( i );
				for( int j = 0; j < (int)bomb.size(); j++ ){
					BangBomb( j );
				}
			}
			player[i]->bomb_master--;			
		}
	}
}*/
void PROCESS::GameStart(){
	if( IfEmpty() ){
		LevelGenerate( ++level );
	}
}
void PROCESS::GameProcess(){	
	GameStart();
	if( player[0]->undead ) player[0]->undead--;
	//PlayerBombMaster();
	BombTime();
	MoveMoobs();
	Print();
	LevelComplite();
}
void PROCESS::LevelComplite(){
	DestroyFire();
	if( !moob.size() ){
		PlaySound("sound/win.wav", NULL, SND_ASYNC);
		Sleep( 3000 );
		Clear();
	}
}
void PROCESS::ResetPlayer( int i ){
	if( player[0]->life && !player[0]->undead ){
		PlaySound("sound/dead.wav", NULL, SND_ASYNC);
		int sc = player[i]->score;
		int lf = player[i]->life - 1;
		delete player[i];
		player[i] = new PLAYER( 0, 0, lf, sc );
	}
}

bool PROCESS::GameOver(){
 	if( player[0]->life == 0 ) return true;
	return false;
}

bool PROCESS::IfEmpty(){
	if( moob.size() || brick.size() || block.size() || bonus.size() ) return false;
	return true;
}
void PROCESS::Clear(){
	player[0]->SetPos( 0, 0 );
	block.clear();
	fire.clear();
	bomb.clear();
	moob.clear();
	brick.clear();
	bonus.clear();
}