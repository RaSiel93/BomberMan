//#pragma comment (lib, "kernel32.lib")
#include <math.h>

#include <vector>
#include <time.h>
using namespace std;
#include <conio.h>

#include "PROCESS.h"
#include <GL\glut.h>

#define ob_size 40
#define area_h 15
#define area_w 31

PROCESS *game = new PROCESS;

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	
	for( int i = 0; i < game->bomb.size(); i++ ){
		game->bomb[i]->setTimer();
		if( game->bomb[i]->getTimer() == 0 ){
			game->BangBomb( i );
		}
	}
	for( int i = 0; i < game->moob.size(); i++ )
		//game->moob[i]->MoveTo( game->object );
	for( int i = 0; i < game->fire.size(); )
		if( game->fire[i]->getTimer() == 0 )
			game->Destroy( game->fire[i]->getPos().first, game->fire[i]->getPos().second );
		else game->fire[i]->setTimer();

	game->Print();
	glutSwapBuffers();
}

void Timer(int value){
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 0);
}

void Keyboard(unsigned char  key, int x, int y){
	switch(key){
	case 32: game->PushBomb();
		break;
	}
}
void SKeyboard(int key, int x, int y){
	switch(key){
	case GLUT_KEY_LEFT: game->PlayerMoveTo( 0, -1 ); break;
	case GLUT_KEY_RIGHT: game->PlayerMoveTo( 0, 1 ); break;
	case GLUT_KEY_UP: game->PlayerMoveTo( -1, 0 ); break;
	case GLUT_KEY_DOWN: game->PlayerMoveTo( 1, 0 ); break;
	}
}
void Initialize(){
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( -ob_size*area_w/2, ob_size*area_w/2,-ob_size*area_h/2, ob_size*area_h/2, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
	srand( time(0) );
	
	game->GetObject( "PLAYER", 0, "" );
	game->GetObject( "BLOCK", 2, "NO_RANDOM" );
	game->GetObject( "BRICK", area_h*area_w/2, "RANDOM" );
	game->GetObject( "MONSTER_1", 5, "RANDOM" );
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize( ob_size * area_w, ob_size * area_h );//ob_size*area_w, ob_size*area_h );
	glutInitWindowPosition( 50.0, 50.0 );
	glutCreateWindow("Bomberman with OpenGl");
	
	glutDisplayFunc(Draw);
	
	glutTimerFunc(500, Timer, 0);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SKeyboard);
	Initialize();
	glutMainLoop();

	return 0;
}