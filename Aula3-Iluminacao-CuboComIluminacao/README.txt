Descrição do programa braco.c

static int shoulder = 0, elbow = 0;
As variáveis shoulder e elbow guardam o ângulo de rotação do ombro e o ângulo formado entre o braço e o antebraço do robô, respectivamente.

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT);
  glPushMatrix();
Uma vez que as transformações geométricas no espaço são representadas por matrizes, o uso de uma pilha de matrizes de transformação ajuda a lembrar a seqüência de transformações realizadas. No OpenGL, esta facilidade é provida pelas funções glPushMatrix(), que insere a matriz de transformação corrente na pilha, e glPopMatrix(), que retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente. Neste exemplo, a função glPushMatrix() serve para lembrar os parâmetros de translação, rotação e escalamento no início das operações de desenho.

  glTranslatef (-1.0, 0.0, 0.0);
  glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
  glTranslatef (1.0, 0.0, 0.0);
A origem do sistema de coordenadas é levado para o ponto (x,y,z)=(-1,0,0) através da função glTranslatef(), definindo a coordenada de origem (pivô) para o ombro do braço robótico. Em seguida, usando a função glRotatef(), o sistema de coordenadas é rotacionado de modo, definindo a orientação do braço.

A função glRotate() possui o seguinte protótipo:

void glRotate(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

Quando chamada, glRotate() efetua uma rotação de angle graus no sistema de coordenadas na direção contra o sentido do relógio em torno de um vetor que vai da origem ao ponto (x,y,z)

A função glTranslatef(), por sua vez, retorna a origem do sistema de coordenadas para o centro do braço. As etapas desta transformação são mostradas na Figura 4-2.

Figura 4-2. Transformação para desenho do braço



  glPushMatrix();
  glScalef (2.0, 0.4, 1.0);
  glutWireCube (1.0);
  glPopMatrix();
Mais uma vez, a matriz de transformação corrente é armazenada na pilha, agora para restringir o efeito da função glScale(). A função glScale() altera a escala dos eixos x, y e z. A função glutWireCube() desenha um cubo centrado na origem do sistema de coordenadas com aresta de tamanho unitário, conforme o argumento que lhe foi passado. Quando a função glPopMatrix() é chamada, a matriz de transformação do topo da pilha passa a vigorar, fazendo com que o cubo seja distorcido, assumindo a forma de um parelepípedo. A origem do sistema de coordenadas volta a ser o centro do braço.

  glTranslatef (1.0, 0.0, 0.0);
  glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
  glTranslatef (1.0, 0.0, 0.0);
A origem do sistema de coordenadas é levada agora para a ponta do braço com a função glTranslate(), demarcando o novo pivõ para rotação: o cotovelo do robô. A rotação é realizada com a função glRotate() e em seguida a origem do sistema de coordenadas é levada para o centro do antebraço, via glTranslate().

  glPushMatrix();
  glScalef (2.0, 0.4, 1.0);
  glutWireCube (1.0);
  glPopMatrix();
O antebraço é desenhado de forma semelhante ao braço: as escalas dos eixos coordenados são ajustadas e o cubo de aresta 1 é desenhado, sempre preservando as dimensões do sistema de coordenadas original.

  glPopMatrix();
  glutSwapBuffers();
A função glPopMatrix() remove a matriz de transformação do topo da pilha, fazendo-a corrente, retornando assim o sistema de coordenadas original. Quando glutSwapBuffers() é chamada, os buffers de desenho e de apresentação são alternados e a nova imagem do braço robótico é apresentada.

void reshape (int w, int h)
{
  glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
Define a área dentro da janela de desenho no sistema de coordenadas atual, origem (x,y), largura (w) e altura (h), que OpenGL pode utilizar para efetuar desenhos. Este trecho de código permite que toda a área da janela possa ser utilizada quando a janela sofrer redimensionamento.

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
A função glMatrixMode() especifica a pilha de matrizes que será o alvo das operações matriciais subseqüentes; neste caso, a pilha de matrizes de projeção. A função glLoadIdentity() inicia a matriz de projeção corrente como a matriz identidade. A função gluPerspective() define a transformação de perspectiva usada no exemplo. Projeções geométricas não são alvo desta lição e por enquanto não serão estudadas.

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef (0.0, 0.0, -5.0);
A função glMatrixMode() especifica agora que a pilha de matrizes de modelview, usadas para definir translação, rotação e escalamento, será o alvo das transformações subseqüentes. A função glLoadIdentity() inicia a matriz de modelview corrente como a matriz identidade. Finalmente, o objeto é deslocado -5 unidades para o fundo da tela, melhorando a sua visualização.

  glutReshapeFunc(reshape);
Especifica a função de retorno para redimensionamento de janela, possuindo o seguinte protótipo:

funcao(int width, int height);
