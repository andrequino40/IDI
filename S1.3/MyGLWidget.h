#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <QKeyEvent>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    
  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
 
    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);  

    virtual void keyPressEvent ( QKeyEvent * e );

void modelTranslate (float changex, float changey, float direction);
  private:
    void creaBuffers ();
    void carregaShaders ();
    // attribute locations
    GLuint varLoc;
    GLuint vertexLoc;
    GLuint colorLoc;
    GLuint transLoc;

    
    // Program
    QOpenGLShaderProgram *program;

    float scl = 1;
    GLuint VAO1;
    GLint ample, alt;
    float dir1 = 0;
    float dir2 = 0;
    float movx = 0, movy = 0;
};
