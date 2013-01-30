#include <time.h>
#include "SERVICE.h"
#include "PROCESS.h"
#include <setjmp.h>
#include <conio.h>

static jmp_buf env;
#define NUM_TEXTURES 20

unsigned int TextureIDs[NUM_TEXTURES];

string win_title, title = "Bomberman v0.7";
char buf1[4];
char buf2[4];
char buf3[4];

bool pause = false;
time_t timer; /*time_game,*/; 
int timer_pause = 0;
int time_game;

PROCESS *game;

#include "stdlib.h"
#include <gl\glut.h>
#include <gl\glaux.h>

void LoadTextures(){
	AUX_RGBImageRec *texture1 = auxDIBImageLoadA("image/player.bmp"), *texture2 = auxDIBImageLoadA("image/block.bmp"), 
		*texture3 = auxDIBImageLoadA("image/brick.bmp"), *texture4 = auxDIBImageLoadA("image/bomb.bmp"), *texture5 = auxDIBImageLoadA("image/fire.bmp"),
		*texture6 = auxDIBImageLoadA("image/moob1.bmp"), *texture7 = auxDIBImageLoadA("image/moob2.bmp"), *texture8 = auxDIBImageLoadA("image/moob3.bmp"),
		*texture9 = auxDIBImageLoadA("image/moob4.bmp"), *texture10 = auxDIBImageLoadA("image/moob5.bmp"), *texture11 = auxDIBImageLoadA("image/moob6.bmp"),
		*texture12 = auxDIBImageLoadA("image/moob7.bmp"), *texture13 = auxDIBImageLoadA("image/bonus_ab.bmp"), *texture14 = auxDIBImageLoadA("image/bonus_pwb.bmp"),
		*texture15 = auxDIBImageLoadA("image/bonus_phb.bmp"), *texture16 = auxDIBImageLoadA("image/bonus_tw.bmp"), *texture17 = auxDIBImageLoadA("image/bonus_fr.bmp"),
		*texture18 = auxDIBImageLoadA("image/bonus_ud.bmp"), *texture19 = auxDIBImageLoadA("image/player_ud.bmp");
	glGenTextures(NUM_TEXTURES, &TextureIDs[0]);
	glBindTexture(GL_TEXTURE_2D, TextureIDs[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture1->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture2->sizeX, texture2->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture2->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture3->sizeX, texture3->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture3->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture4->sizeX, texture4->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture4->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture5->sizeX, texture5->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture5->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture6->sizeX, texture6->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture6->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture7->sizeX, texture7->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture7->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[7]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture8->sizeX, texture8->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture8->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[8]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture9->sizeX, texture9->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture9->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[9]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture10->sizeX, texture10->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture10->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[10]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture11->sizeX, texture11->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture11->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[11]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture12->sizeX, texture12->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture12->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[12]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture13->sizeX, texture13->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture13->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[13]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture14->sizeX, texture14->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture14->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[14]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture15->sizeX, texture15->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture15->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[15]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture16->sizeX, texture16->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture16->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[16]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture17->sizeX, texture17->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture17->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[17]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture18->sizeX, texture18->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture18->data );
	glBindTexture(GL_TEXTURE_2D, TextureIDs[18]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture19->sizeX, texture19->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture19->data );
}

void Draw(){
	time_t timer_now;
	timer_now = time(NULL);
	if( pause ){
		timer_pause = timer_now - timer - time_game;
	}
	if( !pause ){
		game->GameProcess();
		if( game->LevelComplite() ){
			pause = true;
			Sleep( 3000 );
			game->Clear();
		}

		time_game = timer_now - timer - timer_pause;
		win_title = title + ": Количество жизней - " + itoa(game->player[0]->life, buf1, 10) + "; Количество очков - " + itoa(game->player[0]->score, buf2, 10) + "; Время игры - " +
			itoa(time_game, buf3, 10);
		glutSetWindowTitle( win_title.c_str() );
		
		if( game->GameOver() ){
			glClear(GL_COLOR_BUFFER_BIT);
			Sleep( 1000 );
			glutSwapBuffers();
			Sleep( 1000 );	
			longjmp(env, 0);
		}
		pause = false;
	}
}
void Initialize(){
	LoadTextures();
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.3, 0.5, 0.2, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ob_size*area_w/2, ob_size*area_w/2,-ob_size*area_h/2, ob_size*area_h/2, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}
void Timer(int value){
	glutPostRedisplay();
	glutTimerFunc(40, Timer, 0);
}

void Keyboard(unsigned char  key, int x, int y){
	switch(key){
	
	case 32: 
		if( !pause ){
			game->PushBomb( 0 );
		}
		break;
	case 13:
		if( pause ){ 
			pause = false; 
		}
		break;
	case 27: 
		if( !pause ){ 
			pause = true; 
		} else { 
			pause = false;
		}
		break;
	}
}
void SKeyboard(int key, int x, int y){
	if( !pause ){
		switch(key){
		case GLUT_KEY_LEFT: game->MovePlayer( "LEFT" ); break;
		case GLUT_KEY_RIGHT: game->MovePlayer( "RIGHT" ); break;
		case GLUT_KEY_UP: game->MovePlayer( "UP" ); break;
		case GLUT_KEY_DOWN: game->MovePlayer( "DOWN" ); break;
		}
	}
}

/*int TimeGet( time_t t_past ){
	time_t t;
	t=time(NULL);
	//struct tm *t_now;
	//t_now=localtime(&t);
	return t_now - t_past;
*/

int main(int argc, char** argv){

	game = new PROCESS;

	timer = time(NULL);

	srand( time(0) );
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); 
	glutInitWindowSize( ob_size * area_w, ob_size * area_h );
	glutInitWindowPosition( 50.0, 50.0 );
	glutCreateWindow("Bomberman v0.7");
	glutDisplayFunc(Draw);
	glutTimerFunc(500, Timer, 0);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SKeyboard);	
	Initialize();
		
	if( !setjmp(env) ){
		glutMainLoop();
	}
	return 0;
}