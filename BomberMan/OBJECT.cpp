#include "OBJECT.h"

//OBJECT
OBJECT::OBJECT( int y, int x ){
	setPos( y, x );
}
void OBJECT::setPos( int y, int x ){
	position.first = y;
	position.second = x;
}
pair< int, int > OBJECT::getPos(){
	return position;
}

//BLOCK
BLOCK::BLOCK( int y, int x ){
	setPos( y, x );
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
	setPos( y, x );
}
void BRICK::Draw(){
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size , area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}

//PLAYER
PLAYER::PLAYER( int y, int x ){
	setPos( y, x );
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
BOMB::BOMB( int x, int y ){
	timer = 50;
	setPos( x, y );
}
int BOMB::getTimer(){
	return timer;
}
void BOMB::setTimer(){
	timer--;
}
void BOMB::Draw(){	
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}

//FIRE
FIRE::FIRE( int x, int y ){
	setPos( x, y );
	timer = 50;
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

//MONSTER
int MONSTER::GetSpeed(){
	return speed;
}
void MONSTER::SetSpeed(){
	speed--;
}

template <typename T, size_t Cols, size_t Rows>//<------------------------------------------------
bool MONSTER::MoveTo( OBJECT (&object)[area_h * area_w] ){
	if( speed != 0 )
		SetSpeed();
	else {
		int x=0, y=0, xy=0;
		while( !(x + y) ) {
			x = rand()%3 - 1;
			y = rand()%3 - 1;
			xy = rand()%2;
			if( xy ) x = 0;
			else y = 0;
		}
		if( object[y * area_w + x] == 0 ){
			object[y * area_w + x] = object[position.first * area_h + position.second];
			object[position.first * area_w + position.second] = 0;
			object[y * area_w + x]->setPos(y,x);
			speed = speed_const;
		}
		return true;
	}
	return false;
}
MONSTER_1::MONSTER_1( int y, int x ){
	setPos( y, x );
	speed_const = 30;
	speed = speed_const;
}
void MONSTER_1::Draw(){
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);	
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size - ob_size);
		glVertex2f(-area_w*ob_size/2 + position.second*ob_size + ob_size, area_h*ob_size/2 - position.first*ob_size);
	glEnd();
}