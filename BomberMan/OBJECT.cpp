#include "OBJECT.h"

//OBJECT
OBJECT::OBJECT( int y, int x ){
	SetPos( y, x );
}
void OBJECT::SetPos( int y, int x ){
	position.first = y;
	position.second = x;
}
pair< int, int > OBJECT::GetPos(){
	return position;
}

//BLOCK
BLOCK::BLOCK( int y, int x ){
	SetPos( y, x );
}
void BLOCK::Draw(){
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}

//BRICK
BRICK::BRICK( int y, int x ){
	SetPos( y, x );
}
void BRICK::Draw(){
	//glColor3f(0.0, 1.0, 0.0);
	//glBegin(GL_LINES);	
	//	glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
	//	glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
	//	glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
	//	glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size , area_h*ob_size/2 - position.first*ob_size);
	//glEnd();
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}

//PLAYER
PLAYER::PLAYER( int y, int x, int p, int ab, bool pb, bool fr, bool cb, bool tw ){
	SetPos( y, x );
	SetBonus( p, "PwB" );
	SetBonus( ab, "AB" );
	SetBonus( pb, "PhB" );
	SetBonus( fr, "FR" );
	SetBonus( cb, "CB" );
	SetBonus( tw, "TW" );
}
int PLAYER::GetBonus( string temp ){
	if( temp == "AB" ){
		return amount_bomb;
	}
	if( temp == "PwB" ){
		return power_bomb;
	}
	if( temp == "PhB" ){
		return push_bomb;
	}
	if( temp == "FR" ){
		return fire_resist;
	}
	if( temp == "CB" ){
		return control_bomb;
	}
	if( temp == "TW" ){
		return through_wall;
	}
}
void PLAYER::SetBonus( int volume, string temp ){
	if( temp == "AB" ){
		amount_bomb = volume;
	}
	if( temp == "PwB" ){
		power_bomb = volume;
	}
}
void PLAYER::SetBonus( bool volume, string temp ){
	if( temp == "PhB" ){
		push_bomb = volume;
	}
	if( temp == "FR" ){
		fire_resist = volume;
	}
	if( temp == "CB" ){
		control_bomb = volume;
	}
	if( temp == "TW" ){
		through_wall = volume;
	}
}
void PLAYER::Draw(){
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size/2, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size/2, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}

//BOMB
BOMB::BOMB( int x, int y, int p ){
	timer = 50;
	SetPos( x, y );
	SetPower( p );
	push = false;
	course = 0;
}
int BOMB::GetTimer(){
	return timer;
}
void BOMB::SetTimer(){
	timer--;
}
void BOMB::Draw(){	
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}
void BOMB::SetPower( int volume ){
	power = volume;
}
int BOMB::GetPower(){
	return power;
}

//FIRE
FIRE::FIRE( int x, int y ){
	SetPos( x, y );
	timer = 10;
}
void FIRE::Draw(){		
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}

//MOOB
int MOOB::GetSpeed(){
	return speed;
}
void MOOB::SetSpeed(){
	speed--;
}
void MOOB::ResetSpeed(){
	speed = speed_const;
}
MOOB_1::MOOB_1( int y, int x ){
	SetPos( y, x );
	speed_const = 20;
	course = rand()%4;
	speed = speed_const;
}
void MOOB_1::Draw(){
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}
MOOB_2::MOOB_2( int y, int x ){
	SetPos( y, x );
	speed_const = 15;
	course = rand()%4;
	speed = speed_const;
}
void MOOB_2::Draw(){
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}
MOOB_3::MOOB_3( int y, int x ){
	SetPos( y, x );
	speed_const = 10;
	course = rand()%4;
	speed = speed_const;
}
void MOOB_3::Draw(){
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}

//BONUS
BONUS_AB::BONUS_AB( int y, int x ){
	SetPos( y, x );
}
void BONUS_AB::Draw(){
	glColor3f(0.5, 0.5, 1.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}
BONUS_PwB::BONUS_PwB( int y, int x ){
	SetPos( y, x );
}
void BONUS_PwB::Draw(){
	glColor3f(1.0, 0.4, 0.4);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}
BONUS_PhB::BONUS_PhB( int y, int x ){
	SetPos( y, x );
}
void BONUS_PhB::Draw(){
	glColor3f(0.0, 0.5, 1.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}
BONUS_FR::BONUS_FR( int y, int x ){
	SetPos( y, x );
}
void BONUS_FR::Draw(){
	glColor3f(1.0, 0.7, 0.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}