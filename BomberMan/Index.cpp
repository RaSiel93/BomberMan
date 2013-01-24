#include <time.h>
#include "SERVICE.h"
#include "PROCESS.h"

PROCESS *game = new PROCESS;

void Draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	game->Print();
	game->BombTime();
	game->MoveMoobs();
	game->DestroyFire();
	glutSwapBuffers();
	if( game->EndGame() ) 
		game->Restart();
 }

void Timer(int value){
	glutPostRedisplay();
	glutTimerFunc(50, Timer, 0);
}

void Keyboard(unsigned char  key, int x, int y){
	switch(key){
	case 32: game->PushBomb( 0 );
		break;
	}
}
void SKeyboard(int key, int x, int y){
	switch(key){
	case GLUT_KEY_LEFT: game->MovePlayer( "LEFT" ); break;
	case GLUT_KEY_RIGHT: game->MovePlayer( "RIGHT" ); break;
	case GLUT_KEY_UP: game->MovePlayer( "UP" ); break;
	case GLUT_KEY_DOWN: game->MovePlayer( "DOWN" ); break;
	}
}
void Initialize(){
	glClearColor(0.1, 0.4, 0.1, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho( -ob_size*area_w/2, ob_size*area_w/2,-ob_size*area_h/2, ob_size*area_h/2, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv){
	srand( time(0) );

	start:

	game->GetObject( "PLAYER", 0, 0 );
	game->GetObject( "BLOCK", 2 );
	game->GetObject( "BRICK", area_h*area_w/3, "RANDOM", 1, 1 );
	game->GetObject( "BONUS_AB", 7, "RANDOM", 0, 0 );
	game->GetObject( "BONUS_PwB", 7, "RANDOM", 0, 0 );
	game->GetObject( "BONUS_PhB", 1, "RANDOM", 0, 0 );
	game->GetObject( "BONUS_FR", 1, "RANDOM", 0, 0 );
	game->GetObject( "BONUS_TW", 1, "RANDOM", 0, 0 );
	game->GetObject( "MOOB_1", area_h*area_w/30, "RANDOM", 5, 5 );
	game->GetObject( "MOOB_2", area_h*area_w/60, "RANDOM", 5, 5 );
	game->GetObject( "MOOB_3", area_h*area_w/90, "RANDOM", 5, 5 );
	
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