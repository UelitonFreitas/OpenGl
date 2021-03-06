
#include <GL/glut.h>
#include <stdlib.h>


void init(void){
  	glClearColor(1.0, 1.0, 1.0, 1.0);    // cor de fundo

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

  	glOrtho(-5, 5, -5, 5, -5 ,5);     // modo de projecao ortogonal
} 

void display(void){

	//Ao gerar um novo quadro o Z-Buffer deve ser limpo.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);

	glColor3f(1.0, 0.0, 0.0);
 	glBegin(GL_TRIANGLES);
		glVertex3f(-2, -2, 0);
		glVertex3f(2, -2, 0);
		glVertex3f(0, 2, 0);
     	glEnd();
    
	glColor3f(0.0, 0.0, 1.0);
 	glBegin(GL_TRIANGLES);
		glVertex3f(-4, -3, -4);
		glVertex3f(-3.5, -1, -4);
		glVertex3f(-2, -1, -4);
     	glEnd();

    	glFlush();
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitWindowSize (400, 400); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
