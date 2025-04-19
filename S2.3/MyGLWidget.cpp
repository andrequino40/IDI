// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }   
    return retCode;
}

void MyGLWidget::modelTransformSuelo() 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::scale(transform, glm::vec3(escala));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::modelTransformModel () 
{
  // Matriu de transformació de model
  glm::mat4 transform (1.0f);
  transform = glm::rotate (transform, (float)glm::radians(rota_model), glm::vec3 (0.0, 1.0, 0.0));
  transform = glm::scale(transform, glm::vec3(factor_escala_model));
  transform = glm::translate(transform, -centre_base);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::mouseMoveEvent (QMouseEvent *e){
  makeCurrent();
  int xnew = e->x();
  int ynew = e->y();
  if ( e->buttons() == Qt::LeftButton && ! ( e->modifiers() &
  ( Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier ) ) )
  // controla que s’ha premut botó esquerre i cap modificador
  {
    int xdelta = xnew - xmouse;
    int ydelta = ynew - ymouse;
    xmouse = xnew;
    ymouse = ynew;
    theta += float(ydelta);
    psi -= float(xdelta);
    updateCamera();
    update();
    // std::cerr << "----------------" << std::endl;
    // std::cerr << "xdelta: " << xdelta << std::endl;
    // std::cerr << "ydelta: " << ydelta << std::endl;
    // std::cerr << "theta: " << theta << std::endl;
    // std::cerr << "psi: " << psi << std::endl;
  }
}


void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
      escala_desitjada_model+= 0.05;
      calculaCapsaModel(m, factor_escala_model, escala_desitjada_model, centre_base);
      break;
    }
    case Qt::Key_D: { // escalar a més petit
      escala_desitjada_model-= 0.05;
      calculaCapsaModel(m, factor_escala_model, escala_desitjada_model, centre_base);
      break;
    }
    case Qt::Key_Q: {
      rota_model += 45.0;
      break;
    }
    case Qt::Key_E: {
      rota_model -= 45.0;
      break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::resizeGL (int width, int height){
  rav = float (width) / float (height);
  updateCamera();
}

void MyGLWidget::paintGL () 
{
// En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)

  // glViewport (0, 0, ample, alt);
  // std::cerr << "ar: " <<  << std::endl; 
  // std::cerr << width() << " " << height() << std::endl; 
  // std::cerr << ">" << ample << " " << alt << std::endl; 
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Carreguem la transformació de model
  modelTransformModel();

  // Activem el VAO per a pintar la caseta 
  glBindVertexArray(VAO_HomerProves);

  // pintem
  glDrawArrays (GL_TRIANGLES, 0, m.faces ().size () * 3);

  // repeat
  modelTransformSuelo();

  glBindVertexArray(VAO_Suelo);

  glDrawArrays(GL_TRIANGLES, 0, vertices_Suelo);

  glBindVertexArray (0);
}


void MyGLWidget::creaBuffers(){
   creaBuffersModel();
   creaBuffersSuelo();
}

void MyGLWidget::creaBuffersModel(){
    // lodea modelo
    m.load("./Model/Patricio.obj");

    calculaCapsaModel(m, factor_escala_model, escala_desitjada_model, centre_base);

    // crea vao
    glGenVertexArrays(1, &VAO_HomerProves);
    glBindVertexArray(VAO_HomerProves);

    // crea vbos
    GLuint VBO_Homer[2];

    glGenBuffers(2, VBO_Homer);

    // carga vbo vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[0]);
    glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces ().size () * 3 * 3, m.VBO_vertices(), GL_STATIC_DRAW);

    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    // carga vbo colores
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[1]);
    glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces ().size () * 3 * 3, m.VBO_matdiff(), GL_STATIC_DRAW);

    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glBindVertexArray (0);
}



void MyGLWidget::creaBuffersSuelo() {
    glm::vec3 Vertices[vertices_Suelo];  // Tres vèrtexs amb X, Y i Z
    int i = 0;
// lado frente izquierda
  Vertices[i++] = glm::vec3(-2.5, 0.0, -2.5);
  Vertices[i++] = glm::vec3(-2.5, 0.0, 2.5);
  Vertices[i++] = glm::vec3(2.5, 0.0, 2.5);
  // lade fondo derecha
  Vertices[i++] = glm::vec3(2.5, 0.0, 2.5);
  Vertices[i++] = glm::vec3(2.5, 0.0, -2.5);
  Vertices[i++] = glm::vec3(-2.5, 0.0, -2.5);
  
  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO_Suelo);
  glBindVertexArray(VAO_Suelo);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  //VBO2 
  glm::vec3 Colors[vertices_Suelo];
  i = 0;
  Colors[i++] = glm::vec3(0.67, 0.85, 0.9);   // LBlue
  Colors[i++] = glm::vec3(1.0, 0.75, 0.8);  // Pink
Colors[i++] = glm::vec3(0.67, 0.85, 0.9);   // LBlue 
  Colors[i++] = glm::vec3(0.67, 0.85, 0.9);   // LBlue
  Colors[i++] = glm::vec3(1.0, 0.75, 0.8);  // Pink
  Colors[i++] = glm::vec3(0.67, 0.85, 0.9);   // LBlue
 
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
void MyGLWidget::initializeGL()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  BL2GLWidget::initializeGL();
  updateCamera();
  // MyGLWidget::projectTransform();
  // MyGLWidget::viewTransform();
  glEnable (GL_DEPTH_TEST);
}

void MyGLWidget::calculaCapsaModel (Model &p, float &escala, float alcadaDesitjada, glm::vec3 &centreBase)
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = p.vertices()[0];
  miny = maxy = p.vertices()[1];
  minz = maxz = p.vertices()[2];
  for (unsigned int i = 3; i < p.vertices().size(); i+=3)
  {
    if (p.vertices()[i+0] < minx)
      minx = p.vertices()[i+0];
    if (p.vertices()[i+0] > maxx)
      maxx = p.vertices()[i+0];
    if (p.vertices()[i+1] < miny)
      miny = p.vertices()[i+1];
    if (p.vertices()[i+1] > maxy)
      maxy = p.vertices()[i+1];
    if (p.vertices()[i+2] < minz)
      minz = p.vertices()[i+2];
    if (p.vertices()[i+2] > maxz)
      maxz = p.vertices()[i+2];
  }

  escala = alcadaDesitjada/(maxy-miny);
  centreBase[0] = (minx+maxx)/2.0; centreBase[1] = miny; centreBase[2] = (minz+maxz)/2.0;
}

void MyGLWidget::carregaShaders() { // declarem-lo també en MyGLWidget.h
    BL2GLWidget::carregaShaders(); // cridem primer al mètode de BL2GLWidget
    projLoc = glGetUniformLocation (program->programId(), "proj");
    viewLoc = glGetUniformLocation (program->programId(), "view");
}

void MyGLWidget::projectTransform (float fov, float ra, float z_near, float z_far) {
// glm::perspective (FOV en radians, ra window, znear, zfar)
// float)glm::radians()
    glm::mat4 Proj = glm::perspective (fov, ra, z_near, z_far);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform(glm::vec3 OBS, glm::vec3 VRP, glm::vec3 UP) {
  glm::mat4 View = glm::lookAt(OBS, VRP, UP);
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::viewTransformEuler(glm::vec3 VRP, float d, float alçada) {
  // glm::mat4 View = glm::lookAt(OBS, VRP, UP);
  glm::mat4 View(1.0f);
  View = glm::translate(View, glm::vec3(0.0f, 0.0f, -d));
  View = glm::rotate(View, (float)glm::radians(-theta), glm::vec3(1.0f, 0.0f, 0.0f));
  View = glm::rotate(View, (float)glm::radians(psi), glm::vec3(0.0f, 1.0f, 0.0f));
  View = glm::translate(View, -VRP);
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
  // std::cerr << "euler" << std::endl;
}

void MyGLWidget:: calcAtributsEscena(glm::vec3 min, glm::vec3 max) {
  centre_escena = (min+max)/2.0f;
  radi_escena = glm::distance(centre_escena, max);
}

void MyGLWidget::updateCamera() {
  // valores por defecto de la escena de homer y el suelo
   calcAtributsEscena(glm::vec3(-2.5f, 0.0f, -2.5f), glm::vec3(2.5f, 4.0f, 2.5f));

  float d = radi_escena * 2;
  float alçada = 1;
  glm::vec3 VRP = centre_escena;
  glm::vec3 OBS = VRP + glm::vec3(0,alçada,d);
  glm::vec3 UP = glm::vec3(0,1,0);

  // viewTransform(OBS, VRP, UP);
  viewTransformEuler(VRP, d, alçada);

  float z_near = d - radi_escena;
  float z_far = d + radi_escena;
  float fov;
  float av = glm::asin(radi_escena/d);
  if (rav >= 1)
    fov = 2 * av;
  else 
    fov = 2 * glm::atan((glm::tan(av)/rav));

  projectTransform(fov, rav, z_near, z_far);
}



MyGLWidget::~MyGLWidget() {
}


