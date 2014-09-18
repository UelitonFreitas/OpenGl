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
double	xAxisTranslade = 0.0;
double 	yAxisTranslade = 0.0;
double	transladeDeslocation = 0.2;

//Ângulo da Rotação.
int theta = 0.0;

//Proporção da escala.
int xyScale = 1;


//Definição de Um vértice.
class Vertice{
	
	private:
		//Coordenada da posição x.
		double x;
		//Coordenada da posição y.
		double y;

	public:
		//Construtor.
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

//A modelagem de um objeto qualquer.
// Todo objeto conhece seu conjunto de vértices, assim como se desenhar.
class Objeto{
	protected:
		//Lista de vértices.
		vector<Vertice*>* vertices;

	public:
		Objeto(){
			//Cria lista de vértices.
			vertices = new vector<Vertice*>();
		}
		
		//Desenha seus vértices como um polígono.
		void draw(){
			glBegin(GL_POLYGON);
				for(int i = 0; i < vertices->size(); i++){
					Vertice* v= this->vertices->at(i); 
					glVertex3f(v->getX(),v->getY(),0.0f);
				}
			glEnd();
		}
		
		//Calcula o centroide do objeto.
		//O centroid é utilizado para efeturar as operações de rotação e escalas de maneira correta, isto é, sem deslocar o objeto.
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

//Define o modelo de uma casa.
//A mesma é derivada de um objeto, ou seja, contém vértices e sabe "se desenhar".
class Casa : public Objeto{
	
	public:
		
		//Cria os vértices utilizados na modelagem da casa.
		Casa(){
			vertices->push_back(new Vertice(0, 0));
			vertices->push_back(new Vertice(1, 0));
			vertices->push_back(new Vertice(1, 1));
			vertices->push_back(new Vertice(0.5, 2));
			vertices->push_back(new Vertice(0, 1));
		}
	
};


//Função que recebe comandos do teclado.
void keyboard(unsigned char key, int x, int y){
	
	cout << "Pressed: " << key << endl;
	
	switch(key){
		//Translada objeto no eixo Y > 0.
		case 'w':
			yAxisTranslade += transladeDeslocation;
			glutPostRedisplay();
			break;
		//Translada objeto no eixo Y < 0.
		case 's':
			yAxisTranslade -= transladeDeslocation;
			glutPostRedisplay();
			break;
		
		//Translada objeto no eixo X < 0.
		case 'a':
			xAxisTranslade -= transladeDeslocation;
			glutPostRedisplay();
			break;
		
		//Translada objeto no eixo X > 0.
		case 'd':
			xAxisTranslade += transladeDeslocation;
			glutPostRedisplay();
			break;
		
		//Rotaciona objeto no sentido anti-horário.
		case 'q':
			theta = (theta + 5) % 360;
			glutPostRedisplay();
			break;
		
		//Rotaciona objeto no sentido horário.
		case 'e':
			theta = (theta - 5) % 360;
			glutPostRedisplay();
			break;
		
		//Dobra o tamanho do objeto.
		case 'f':
			xyScale = 2;
			glutPostRedisplay();
			break;
		
		//Quadriplica o tamanho do objeto.
		case 'g':
			xyScale = 4;
			glutPostRedisplay();
			break;
		
		//Retorna o objeto em sua escala original.
		case 'o':
			xyScale = 1;
			glutPostRedisplay();
			break;
		
		//Tecla ESC. Utilizada para sair do programa.
		case 27:
			exit(0);
			break;
		
		default:
			break;
	}
	
}

//Algumas funções de inicialização do OpenGL.
void init(void){
	//Cor de fundo da janela.
	glClearColor (0.0, 0.0, 0.0, 0.0);
}

//Instância um objeto Casa.
Casa* casa = new Casa();

//Função resposável pelas transformações das imagens.
//Lembrando que as operações de matrizes nesta função são efetuadas de tráz para frente.
void display(void){
	glClear (GL_COLOR_BUFFER_BIT);
	
	//Insere a matriz original na pilha. Isto é feito para garantir a integridade do sistema de coordenadas.
	glPushMatrix();
      
	 /* origem posicionada no centro do braço */ 
	
	
	//v é o centroid do objeto Casa.
	Vertice v = casa->getCentroide();
	//Salva matriz atual na pilha para manter a integridade do sistema de coordenadas.
	glPushMatrix();
		glTranslatef (xAxisTranslade, yAxisTranslade, 0.0);
		//Translada objeto de volata a posição original.
		glTranslatef (v.getX(), v.getY(), 0.0);
		//Rotaciona o objeto.
		glRotatef ((GLfloat) theta, 0.0, 0.0, 1.0);
		//Efetua a escala no objeto.
		glScalef(xyScale,xyScale,0.0f);
		//Translada o objeto para a origem do plano.
		glTranslatef (-v.getX(), -v.getY(), 0.0);
		//Executa o método responsável por desenhar o objeto.
		casa->draw();
	//Pega a matriz original do topo da pilha.
	glPopMatrix();
	casa->draw();
	/* origem volta para o sistema de coordenadas original */
	glPopMatrix();
	//Reinicia o desenho da imagem.
	glutSwapBuffers();
}

//Função responsável pela mudança no tamanho da janela de projeção.
void reshape (int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef (0.0, 0.0, -5.0);
}

//Main do programa.
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (500, 500); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}




















