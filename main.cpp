#include "SpaceBattle.h"

//#include <gl\GL.h>

int main(int argc, char** argv){
	/*
	const int XSize = 640, YSize = 480;
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0, XSize, YSize, 0, 0, 1);
	glMatrixMode (GL_MODELVIEW);
	*/
	SpaceBattle game(argc, argv);
	game.run();

	return 0;
}