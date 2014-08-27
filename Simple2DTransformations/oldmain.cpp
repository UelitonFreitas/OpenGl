#include "math.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>


using namespace std;


//Variáveis globais utilizadas para controle das tranformações.
//Usados para translação.
GLfloat	xAxisTranslade = 0.0;
GLfloat yAxisTranslade = 0.0;

GLfloat gfPosx = 0.0;
GLfloat	deltaX = .0001;

float	rotationAngle = 0.0f;

double objPosX;
double objPosY;
bool inOrigin = false;

class Vertice{
	
	private:
		double x;
		double y;

	public:
		Vertice(double x, double y){
			this->x = x;
			this->y = y;
		}
		
		void setX(double x){
			this->x = x;
		}
		
		void setY(double y){
			this->y = y;
		}
		
		double getX(){
			return this->x;
		}
		
		double getY(){
			return this->y;
		}

};

class Objeto{
	protected:
		vector<Vertice*>* vertices;

	public:
		Objeto(){
			vertices = new vector<Vertice*>();
		}
		
		void draw(){
			glBegin(GL_POLYGON);
				for(int i = 0; i < vertices->size(); i++){
					Vertice* v= this->vertices->at(i); 
					glVertex2f(v->getX(),v->getY());
				}
			glEnd();
		}
		
		
		Vertice& getCentroide(){
			double cx = 0.0;
			double cy = 0.0;
			for(int i = 0; i < vertices->size(); i++){
				cx += vertices->at(i)->getX();
				cy += vertices->at(i)->getY();
			}
			
			Vertice* v = new Vertice(cx/vertices->size(),cy/vertices->size());
			return *v;
		}
};

class Casa : public Objeto{
	
	public:
		
		Casa(){
			vertices->push_back(new Vertice(110, 50));
			vertices->push_back(new Vertice(110, 70));
			vertices->push_back(new Vertice(100, 80));
			vertices->push_back(new Vertice(90, 70));
			vertices->push_back(new Vertice(90, 50));
		}
	
};




//Função que recebe comandos do teclado.
void keyPressed(unsigned char key, int x, int y){
	
	cout << "Pressed: " << key << endl;
	
	
	if(key == 'w'){
		yAxisTranslade += 10;
	}
	else if(key == 's'){
		yAxisTranslade -= 10;
	}
	
	else if(key == 'a'){
		xAxisTranslade -= 10;
	}
	
	else if(key == 'd'){
		xAxisTranslade += 10;
	}
	
	/*
	else if(key == 'q'){
		glPushMatrix();
		rotationAngle -= 1.0f;
		if(rotationAngle >= 360.0f){
			rotationAngle = 0;
		}
		glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
		glPopMatrix();
		
	}

	else if(key == 'e'){
		
		glPushMatrix();
		rotationAngle += 1.0f;
		if(rotationAngle >= 360.0f){
			rotationAngle = 0;
		}
		glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
		glPopMatrix();
	}
	
	else if(key == 'o'){
		
		if(inOrigin){
			glTranslatef(objPosX,objPosX,0.0f);
			inOrigin = false;
		}
		else{
			
			Vertice v = casa->getCentroide();
			objPosX = v.getX();
			objPosY = v.getY();
			
			glTranslatef(-objPosX,-objPosX,0.0f);
			inOrigin = true;
		}
		
	}
	
	else if(key == 'z'){
		
		
	}
	
	else if(key == 'x'){
		
		Vertice v = casa->getCentroide();
	}
	glutPostRedisplay();
	*/
}

// Função callback chamada quando o tamanho da janela é alterado 
void resizeWindow(GLsizei w, GLsizei h)
{
                   // Evita a divisao por zero
                   if(h == 0) h = 1;
                           
                   // Especifica as dimensões da Viewport
                   glViewport(0, 0, w, h);

                   // Inicializa o sistema de coordenadas
                   glMatrixMode(GL_PROJECTION);
                   glLoadIdentity();

                   // Estabelece a janela de seleção (left, right, bottom, top)
                   if (w <= h) 
                           gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f*h/w);
                   else 
                           gluOrtho2D(0.0f, 250.0f*w/h, 0.0f, 250.0f);
}

Casa* casa = new Casa();
void draw() { 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	
	casa->draw();
	glTranslatef(xAxisTranslade,yAxisTranslade,0.0f);
	
	glFlush();
	
	glutPostRedisplay();
} 

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250.0f, 250.0f, -250.0f, 250.0f);
}

int main(int argc, char** argv) { 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(800,600); 
	glutInitWindowPosition(50,50);
	glutCreateWindow("OpenGL - MyWindow");
	
	Initialize();
	
	glutReshapeFunc(resizeWindow);
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyPressed);
	glutMainLoop(); 
	return 0; 
}
