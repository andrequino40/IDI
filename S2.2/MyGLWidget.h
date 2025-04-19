// MyGLWidget.h
#include "BL2GLWidget.h"
#include "./Model/model.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

  protected:
  void carregaShaders();
  void initializeGL();
  void creaBuffers ();
  void paintGL ();
  void keyPressEvent(QKeyEvent* event);
  void resizeGL (int width, int height);
  
  
  
  GLuint projLoc, viewLoc;
  Model m;
  GLuint VAO_HomerProves, VAO_Suelo;
  
  private:
  float rav = 1;
  float rota_Homer = 45.0;
  int vertices_Suelo = 6;
  glm::vec3 centre_escena;
  float radi_escena;
  void updateCamera();
  void calcAtributsEscena(glm::vec3 punt_min, glm::vec3 punt_max);
  void modelTransformSuelo() ;
  void modelTransformHomer() ;
  void creaBuffersSuelo();
  void creaBuffersHomer();
  void viewTransform (glm::vec3 OBS, glm::vec3 VRP, glm::vec3 UP);
  void projectTransform (float fov, float ra, float z_near, float z_far);
  int printOglError(const char file[], int line, const char func[]);
};
