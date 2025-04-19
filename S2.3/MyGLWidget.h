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
  glm::vec3 centre_base;
  float factor_escala_model;
  float rota_model = 45.0;
  float escala_desitjada_model = 4.0f;
  int vertices_Suelo = 6;
  glm::vec3 centre_escena;
  float radi_escena;
  float fov_zoom = 0.0;
  float theta = 0;
  float psi = 0;
  float xmouse = 0;
  float ymouse = 0;
  void mouseMoveEvent (QMouseEvent *event);
  void calculaCapsaModel (Model &p, float &escala, float alcadaDesitjada, glm::vec3 &CentreBase);
  void updateCamera();
  void calcAtributsEscena(glm::vec3 punt_min, glm::vec3 punt_max);
  void modelTransformSuelo() ;
  void modelTransformModel() ;
  void creaBuffersSuelo();
  void creaBuffersModel();
  void viewTransform (glm::vec3 OBS, glm::vec3 VRP, glm::vec3 UP);
  void viewTransformEuler (glm::vec3 VRP, float d, float alçada);
  void projectTransform (float fov, float ra, float z_near, float z_far);
  int printOglError(const char file[], int line, const char func[]);
};
