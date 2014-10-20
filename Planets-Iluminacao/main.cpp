#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define PI 3.1415

GLint WIDTH =320;
GLint HEIGHT=240;

GLint fatias=30;
GLint pilhas=30;
GLint raioEsfera=1.5;

GLfloat obs[3]={0.0,7.0,0.0};
GLfloat olho[3]={0.0,3.0,0.0};

static int year = 0, day = 0;

/*Define os coeficientes de reflexão difusa (*_difusa) e especular (*_especular)
para os objetos da cena.

As componentes são do tipo R, G, B e A (alfa) que definem as cores do plano, esfera A
e esfera B.
A esfera B possui um valor alto de A para compor sua transparência (aparência translúcida).

O brilho do material pode assumir valores entre 1 e 128, que corresponde ao espoente que
modela a função de distribuição espacial da componente de luz refletida especularmente.
A medida em que o valor do brilho aumenta, diminui-se o espelhamento da luz refletida.
*/

GLfloat mat_a_difusa[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_a_especular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_a_brilho[]    = { 50.0 };
GLfloat cor_planeta[]     = { 0, 0, 1.0, 0.0};

/* Define a posição e as componentes de luz para reflexão difusa e especular (cor_luz0)
e a componente de luz para reflexão ambiente (cor_luz0_amb).
*/
GLfloat posicao_luz0[]    = { 0.0, 10.0, 0.0, 0.0};
GLfloat cor_luz0[]        = { 1, 1, 0.0, 1.0};

GLfloat sem_cor[]         = { 0.0, 0.0, 0.0, 1.0};
  
GLint gouraud=0;

GLfloat tetaxz=0;
GLfloat raioxz=6;


/* Redimensiona a janela */
void reshape(int width, int height){
  WIDTH=width;
  HEIGHT=height;
  /*ViewPort*/
  glViewport(0,0,(GLint)width,(GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  /*Visão perspectiva*/
  gluPerspective(70.0,width/(float)height,0.1,30.0);
  glMatrixMode(GL_MODELVIEW);
}



void display(void){
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_LIGHTING);
 
   glDepthMask(GL_TRUE);
   glClearColor(0.0,0.0,0.0,1.0);
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
   glShadeModel(GL_SMOOTH);
  
   
   glPushMatrix();
 
   /* calcula a posicao do observador */
   obs[0]=raioxz*cos(2*PI*tetaxz/360);
   obs[2]=raioxz*sin(2*PI*tetaxz/360);
   gluLookAt(obs[0],obs[1],obs[2],olho[0],olho[1],olho[2],0.0,1.0,0.0);
   
   
   glPushMatrix();
      glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz0);
      glutSolidSphere(1.0, fatias, pilhas);   /* draw sun */
      
      glMaterialfv(GL_FRONT, GL_EMISSION, cor_planeta);

      glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_a_difusa);
      glMaterialfv(GL_FRONT, GL_SPECULAR, mat_a_especular);
      glMaterialfv(GL_FRONT, GL_SHININESS, mat_a_brilho);
      
      glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
      glTranslatef (4.0, 0.0, 0.0);
      glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
      glutSolidSphere(0.5, 10, 8);    /* draw smaller planet */
   glPopMatrix();
 
   glPopMatrix();
   glutSwapBuffers();
}

void special(int key, int x, int y){
  switch (key) {
  case GLUT_KEY_UP:
    obs[1]=obs[1]+1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN:
    obs[1] =obs[1]-1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_LEFT:
    tetaxz=tetaxz+2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT:
    tetaxz=tetaxz-2;
    glutPostRedisplay();
    break;
  }
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
   case 27:
      exit(0);
      break;
   case 'g':
      gouraud = !gouraud;
      glutPostRedisplay();
      break;
   case 'r':
      raioxz=raioxz+1;
      glutPostRedisplay();
      break;
   case 'R':
      if(raioxz>1){
         raioxz=raioxz-1;
         glutPostRedisplay();
     }
   case 'd':
         day = (day + 10) % 360;
         glutPostRedisplay();
         break;
   case 'a':
      day = (day - 10) % 360;
      glutPostRedisplay();
      break;
   case 'e':
      year = (year + 5) % 360;
      glutPostRedisplay();
      break;
   case 'q':
      year = (year - 5) % 360;
      glutPostRedisplay();
      break;
   default:
      break;
  }
}


void init(){
  gouraud=1;
  glEnable(GL_DEPTH_TEST);
  /*Habilita a composição blending das imagens dos valores RGBA correntes com os do framebuffer. A função
  glBlendFunc() de os pesos para a imagem que está sendo processada e a presente no framebuffer. Neste caso,
  os pesos são o próprio valor do canal alfa (GL_SRC_ALPHA) e 1-alfa (GL_ONE_MINUS_SRC_ALPHA).*/
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  /*Define a posição dos componentes de cor da fonte de luz GL_LIGHT0*/
  glLightfv(GL_LIGHT0, GL_DIFFUSE, cor_luz0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, cor_luz0);
  glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz0);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  glEnable(GL_AUTO_NORMAL);
  glEnable(GL_NORMALIZE);
}

/*A função menu é ativada quando o botão direito do mouse é pressionado. De acordo com a variável volume, determinadas propriedades do material que compõe a esfera A são modificadas.*/
void menu(int value){
  switch (value) {
  case 0:
    mat_a_especular[0]=mat_a_especular[1]=mat_a_especular[2]=0.0;
    break;
  case 1: 
    mat_a_especular[0]=mat_a_especular[1]=mat_a_especular[2]=0.5;
    break;
  case 2:
    mat_a_especular[0]=mat_a_especular[1]=mat_a_especular[2]=1.0;
    break;
  case 3:
    mat_a_difusa[0]=mat_a_difusa[1]=mat_a_difusa[2]=0.0;
    break;
  case 4: 
    mat_a_difusa[0]=mat_a_difusa[1]=mat_a_difusa[2]=0.5;
    break;
  case 5:
    mat_a_difusa[0]=mat_a_difusa[1]=mat_a_difusa[2]=1.0;
    break;
  }
  glutPostRedisplay();
}




int main(int argc,char **argv){
  glutInitWindowPosition(0,0);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);

  if(!glutCreateWindow("Modelos de iluminacao")) {
    fprintf(stderr,"Error opening a window.\n");
    exit(-1);
  }

  init();
  
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  /*A função createMenu() em conjunto com a função glutAddMenuEntry habilitam um menu popup. A função glutAttachMenu() associa o aparecimento do menu com o código pressionado para executar uma determinada operação.*/
  glutCreateMenu(menu);
  glutAddMenuEntry("-sem spec", 0);
  glutAddMenuEntry("-spec media", 1);
  glutAddMenuEntry("-spec alta", 2);
  glutAddMenuEntry("-sem difusa", 3);
  glutAddMenuEntry("-difusa media", 4);
  glutAddMenuEntry("-difusa alta", 5);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop();
  return(0);
}
