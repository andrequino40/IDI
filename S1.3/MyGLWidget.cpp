
//#include <GL/glew.h>
#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();
}

void MyGLWidget::modelTranslate (float changex, float changey, float direction) {
  glm::mat4 TG (1.0); // Matriu de transformació, inicialment identitat
  TG = glm::translate (TG, glm::vec3 (movx + changex, movy + changey, 0.0));
  TG = glm::rotate (TG, (float)glm::radians(direction), glm::vec3 (0.0, 0.0, -1.0));
  TG = glm::scale (TG, glm::vec3 (scl, scl, 0));

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::keyPressEvent (QKeyEvent *e) {
  makeCurrent ();
  switch ( e->key() ) {
    // scale
    case Qt::Key_S :
      scl += 0.05;
      // glUniform1f (varLoc, scl);
      break;
    case Qt::Key_D :
      scl -= 0.05;
      // glUniform1f (varLoc, scl);
      break;
    // rotation
    case Qt::Key_Q :
      dir2 -= 2.0;
      dir1 -= 2.0;
      break;
    case Qt::Key_E :
      dir2 += 2.0;
      dir1 += 2.0;
      break;
    case Qt::Key_P :
      dir2 -= 2.0;
      dir1 += 2.0;
      break;
    // position
    case Qt::Key_Left :
      movx -= 0.5;
      direction += 45;
      break;
    case Qt::Key_Right :
      movx += 0.5;
      direction += 45;
      break;
    case Qt::Key_Down :
      movy -= 0.5;
      direction += 45;
      break;
    case Qt::Key_Up :
      movy += 0.5;
      direction += 45;
      break;
    default: e->ignore (); // propagar al pare
    }
  update ();
}

void MyGLWidget::paintGL ()
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  // funcion transformación
  modelTranslate(0.4, -0.2, dir1);
  
  // Activem l'Array a pintar 
  glBindVertexArray(VAO1);
 
  // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 3);

  modelTranslate(-0.4, -0.2, dir2);

    // Pintem l'escena
  glDrawArrays(GL_TRIANGLES, 0, 3);

  
  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
}

void MyGLWidget::creaBuffers ()
{
  glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z
  Vertices[0] = glm::vec3(-1.0, -1.0, 0.0);
  Vertices[1] = glm::vec3(1.0, -1.0, 0.0);
  Vertices[2] = glm::vec3(0.0, 1.0, 0.0);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  //VBO2 
  glm::vec3 Colors[3];
  Colors[0] = glm::vec3(1.0, 0.0, 0.0);
  Colors[1] = glm::vec3(0.0, 1.0, 0.0);
  Colors[2] = glm::vec3(0.0, 0.0, 1.0);
   // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO2;
  glGenBuffers(1  , &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  varLoc = glGetUniformLocation(program->programId(), "val");
  transLoc = glGetUniformLocation(program->programId(), "TS");
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  colorLoc = glGetAttribLocation (program->programId(), "color");
}
