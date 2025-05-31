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
    virtual void modelTransofrmPatricio();
    void iniFocus();
    void setPosFocus(bool focus_set);
  private:
    GLuint posFocusSCOLoc, colorFocusLoc, llumAmbientLoc, posFocusSCOCamLoc, colorFocusCamLoc;

    glm::vec3 llumAmbient;
    glm::vec3 colorFocus;
    glm::vec3 colorFocusCam;
    glm::vec4 posFocusSCO;
    glm::vec4 posFocusSCOCam;
    bool focus_state;
    int printOglError(const char file[], int line, const char func[]);
};
