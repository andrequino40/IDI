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

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
    // case Qt::Key_K:
    //   posFocusSCO -= glm::vec4(0.1, 0.0, 0.0, 0.0);
    //   glUniform4fv(posFocusSCOLoc, 1, &posFocusSCO[0]);

    //   break;
    // case Qt::Key_L:
    //   posFocusSCO += glm::vec4(0.1, 0.0, 0.0, 0.0);
    //   glUniform4fv(posFocusSCOLoc, 1, &posFocusSCO[0]);
      case Qt::Key_F:
        // focus_state = !focus_state;
        // setPosFocus(focus_state);
      break;
   
    default: BL3GLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::iniMaterialTerra() {
    // Donem valors al material del terra
  amb = glm::vec3(0.0,0,0.2);
  diff = glm::vec3(0.0,0,0.8);
  spec = glm::vec3(1,1,1);
  shin = 90;
}

void MyGLWidget::setPosFocus(bool focus_set) {
  if (focus_set) {
    posFocusSCO = glm::vec4(0, 0, 0, 1); // en SCO
  } else {
    posFocusSCO = View * glm::vec4(1, 1, 1, 1); // de SCA a SCO
  }
  glUniform4fv(posFocusSCOLoc, 1, &posFocusSCO[0]);
}

void MyGLWidget::iniFocus() {
    focus_state = true;

    posFocusSCO = View * glm::vec4(1, 1, 1, 1); // de SCA a SCO
    posFocusSCOCam = glm::vec4(0, 0, 0, 1);  // en SCO
    glUniform4fv(posFocusSCOLoc, 1, &posFocusSCO[0]);
    glUniform4fv(posFocusSCOCamLoc, 1, &posFocusSCOCam[0]);

    colorFocus = glm::vec3(0.0, 0.0, 0.8);
    colorFocusCam = glm::vec3(0.8, 0.0, 0.0);
    glUniform3fv(colorFocusLoc, 1, &colorFocus[0]);
    glUniform3fv(colorFocusCamLoc, 1, &colorFocusCam[0]);

    llumAmbient = glm::vec3(1.0, 1.0, 1.0);
    glUniform3fv(llumAmbientLoc, 1, &llumAmbient[0]);
  }

  void MyGLWidget::initializeGL() {

    BL3GLWidget::initializeGL();
  
    posFocusSCOLoc = glGetUniformLocation (program->programId(), "posFocusSCO");
    colorFocusLoc = glGetUniformLocation (program->programId(), "colorFocus");
    posFocusSCOCamLoc = glGetUniformLocation (program->programId(), "posFocusSCOCam");
    colorFocusCamLoc = glGetUniformLocation (program->programId(), "colorFocusCam");
    llumAmbientLoc = glGetUniformLocation (program->programId(), "llumAmbient");
  
    iniFocus();
  }
