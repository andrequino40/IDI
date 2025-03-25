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
  void modelTransform () ;


  GLuint projLoc, viewLoc;
  Model m;
  GLuint VAO_HomerProves, VAO_Suelo;

  private:
  int vertices_Suelo = 6;
  void creaBuffersSuelo();
  void viewTransform ();
  void projectTransform ();
  int printOglError(const char file[], int line, const char func[]);
};
