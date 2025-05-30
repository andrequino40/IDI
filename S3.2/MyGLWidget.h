// MyGLWidget.h
#include "BL3GLWidget.h"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL3GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void iniMaterialTerra();
    virtual void initializeGL ( );
    void iniFocus();
    void setPosFocus(bool focus_set);
  private:
    GLuint posFocusSCOLoc, colorFocusLoc, llumAmbientLoc;
    glm::vec3 llumAmbient;
    glm::vec3 colorFocus;
    glm::vec4 posFocusSCO;
    bool focus_state;
    int printOglError(const char file[], int line, const char func[]);
};
