#include "LL2GLWidget.h"

#include <vector>

#include <QTimer>

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent);
    ~MyGLWidget();

  protected:
  
    virtual void keyPressEvent (QKeyEvent *event);

    // per al moviment automàtic
    QTimer timer;
    
  public slots:
    void updatePosition();

  private:
  
    int printOglError(const char file[], int line, const char func[]);
   
    // Aquí tots els atributs privats que necessitis

};
