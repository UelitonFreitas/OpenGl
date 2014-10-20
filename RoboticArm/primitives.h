#ifndef __primitives_h
#define __primitives_h

#include <GL/glut.h>


//[]-----------------------------------------------------------[]
//|		cubo - funcao e' chamada para inserir um cubo			|
void							 //| O - void					|
cubo( float r, float g, float b, //| I - valor das cores RGB	|
	  float x, float y, float z, //| I - posicao do objeto		|
	  float tam,				 //| I - tamanho do objeto		|
	  float transp )			 //| I - valor alpha			|
//[]-----------------------------------------------------------[]
{
	r = r/255; g=g/255; b=b/255;	// Como glColor4f só vai de 0 a 1 e não de 0 a 255

 	glBegin( GL_QUADS );

 		glColor4f( r,g,b , transp );
 		glTranslatef( x,y,z );
		
		// frente
		glVertex3f( tam		, tam		, tam );
	 	glVertex3f( tam	* -1, tam		, tam );
 		glVertex3f( tam * -1, tam * -1	, tam );
  		glVertex3f( tam		, tam * -1	, tam );
		
		// tras
		glVertex3f( tam		, tam * -1	, tam * -1 );
	 	glVertex3f( tam	* -1, tam * -1	, tam * -1 );
 		glVertex3f( tam * -1, tam		, tam * -1 );
  		glVertex3f( tam		, tam		, tam * -1 );
		
		// esq
		glVertex3f( tam	* -1, tam		, tam );
	 	glVertex3f( tam	* -1, tam		, tam * -1 );
 		glVertex3f( tam * -1, tam * -1	, tam * -1 );
  		glVertex3f( tam	* -1, tam * -1	, tam );

		// dir
		glVertex3f( tam		, tam		, tam * -1 );
	 	glVertex3f( tam		, tam		, tam );
 		glVertex3f( tam 	, tam * -1	, tam );
  		glVertex3f( tam 	, tam * -1	, tam * -1 );
		
		// baixo
		glVertex3f( tam		, tam * -1	, tam );
	 	glVertex3f( tam	* -1, tam * -1	, tam );
 		glVertex3f( tam * -1, tam * -1	, tam * -1 );
  		glVertex3f( tam		, tam * -1	, tam * -1 );
		
		// topo
		glVertex3f( tam 	, tam		, tam * -1 );
	 	glVertex3f( tam	* -1, tam		, tam * -1 );
 		glVertex3f( tam	* -1, tam		, tam );
  		glVertex3f( tam 	, tam		, tam );

	glEnd();
}

//[]---------------------------------------------------[]
//|		piramide - funcao  insere uma piramide			|
void					 //| O - void					|
piramide( float tam,	 //| I - tamanho do objeto		|
		  float transp ) //| I - valor alpha			|
//[]---------------------------------------------------[]
{
 	glBegin( GL_TRIANGLES );
		
		// frente
		glColor4f(  1.0f, 0.0f, 0.0f , transp );
		glVertex3f(  0.0f	, tam		,  0.0f	);
		glColor4f(  0.0f, 1.0f, 0.0f , transp );
		glVertex3f( tam *-1	, tam * -1	,  tam	);
		glColor4f(  0.0f, 0.0f, 1.0f , transp );
		glVertex3f( tam		, tam * -1	,  tam	);
		
		// dir
		glColor4f(  1.0f, 0.0f, 0.0f , transp );
		glVertex3f( 0.0f	, tam		,  0.0f );
		glColor4f(  0.0f, 0.0f, 1.0f , transp );
		glVertex3f( tam		, tam * -1	, tam	);
		glColor4f(  0.0f, 1.0f, 0.0f , transp );
		glVertex3f( tam		, tam * -1	, tam *-1 );
		
		// tras
		glColor4f(  1.0f, 0.0f, 0.0f , transp );
		glVertex3f(  0.0f	, tam		,  0.0f );
		glColor4f(  0.0f, 1.0f, 0.0f , transp );;
		glVertex3f(  tam	, tam *-1	, tam *-1 );
		glColor4f(  0.0f, 0.0f, 1.0f , transp );
		glVertex3f( tam *-1 , tam *-1	, tam *-1 );
		
		// esq
		glColor4f(		1.0f,		0.0f,	0.0f , transp );
		glVertex3f(		0.0f,		 tam,	0.0f );
		glColor4f(		0.0f,		0.0f,	1.0f , transp );
		glVertex3f(	tam * -1,	tam * -1,	tam *-1 );
		glColor4f(		0.0f,		1.0f,	0.0f , transp );
		glVertex3f( tam * -1,	tam * -1,	tam );
		
	glEnd();
}

void Grid( GLfloat size , GLint LinesX,GLint LinesZ )
{
	glBegin( GL_LINES );

	for( int xc=0 ; xc < LinesX ; xc++ )
	{ // horizontal
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size, 0.0, size /  2.0 );
		glVertex3f(	-size / 2.0 + xc / (GLfloat)(LinesX-1)*size, 0.0, size / -2.0 );
	}
	for( int zc=0 ; zc < LinesX ; zc++ )
	{ // vertical
		glVertex3f(	size /  2.0, 0.0, -size / 2.0 + zc / (GLfloat)(LinesZ-1)*size );
		glVertex3f(	size / -2.0, 0.0, -size / 2.0 + zc / (GLfloat)(LinesZ-1)*size );
	}

	glEnd();
}




void drawMirror()
{// espelho
	glPushMatrix();
		/*
		glNormal3f( 0,0,1 );
		glTranslatef( 0,0,-25 );
		glScalef( 3,1,0.05);
		cubo( 77,128,0 , 0,0,0 , 5,1 );
		*/
		glTranslatef( -10,0,-20 );
		glBegin( GL_QUADS );
			glNormal3f( 1,0,0 );
				glVertex3f( 0,0,0 );
				glVertex3f( 0,0,25 );
				glVertex3f( 0,5,25 );
				glVertex3f( 0,5,0 );
		glEnd();
	glPopMatrix();
}

void drawObjects()
{
	// piramide
	glPushMatrix();
		glTranslatef( -5 , 3.0f , -6.0f );
		glRotatef( 20.0 , 0.0f, 1.0f, 0.0f );
		piramide( 3,1 );
	glPopMatrix();

	// esfera
	glPushMatrix();
		glColor3f( 0,1,0 );
		glTranslatef( 0.75, 1.60, 0.0 ); 
		glRotatef( 30.0, 1.0, 0.0, 0.0 );
		glutSolidSphere(2.0, 16, 16);
	glPopMatrix();
		
	// Cubo
	glPushMatrix();
		glColor3f( 0,0,1 );
		glTranslatef( 10,2,0 );
		glutSolidCube( 5 );
	glPopMatrix();

	// vidro
	glPushMatrix();
		glTranslatef( 0, 2.5 , 5 );
		glScalef( 3 , 0.5 , 0.05 );
		cubo( 160,180,160 , 0,0,0 , 5,0.25 );
	glPopMatrix();
}



#endif
