#include "math.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glut.h>


using namespace std;


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
		
		void moveXAxis(){
			for(int i = 0; i < vertices->size(); i++){
				Vertice* v= this->vertices->at(i);
				
				if (v->getX() <= 0)
					v->setX(1);
				else if (v->getX() >= 1)
					v->setX(0);
					
				v->setX(v->getX()+deltaX);
				
			}	
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

Casa* casa = new Casa();
void draw() { 
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	
	casa->draw();
	
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



void keyPressed(unsigned char key, int x, int y){
	
	cout << "pressed: " << key << endl;
	glPushMatrix();
	
	if(key == 'w'){
		glTranslatef(0.000f, 10.0f, 0.0f);
		
		
	}
	else if(key == 's'){
		glTranslatef(0.000f, -10.0f, 0.0f);
	}
	
	else if(key == 'a'){
		glTranslatef(-10.0f, 0.00f, 0.0f);
	}
	
	else if(key == 'd'){
		glTranslatef(10.0f, 0.00f, 0.0f);
	}
	
	else if(key == 'q'){
		rotationAngle -= 1.0f;
		if(rotationAngle >= 360.0f){
			rotationAngle = 0;
		}
		glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
		
		
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
	glPophMatrix();
	glutPostRedisplay();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
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

void Timer(int iUnused)
{
    glutPostRedisplay();
    glutTimerFunc(30, Timer, 0);
}

int main(int argc, char** argv) { 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(800,600); 
	glutInitWindowPosition(50,50);
	glutCreateWindow("OpenGL - MyWindow");
	
	Initialize();
	
	glutReshapeFunc(AlteraTamanhoJanela);
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyPressed);
	Timer(0);
	glutMainLoop(); 
	return 0; 
}
