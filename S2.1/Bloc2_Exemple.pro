TEMPLATE    = app
QT         += opengl 

INCLUDEPATH +=  /usr/include/glm

FORMS += MyForm.ui

HEADERS += MyForm.h BL2GLWidget.h MyGLWidget.h

SOURCES += main.cpp MyForm.cpp \
        BL2GLWidget.cpp MyGLWidget.cpp

INCLUDEPATH += /dades/angel.andres.quinones/repos/IDI/IDI/S2.1/Model
SOURCES += /dades/angel.andres.quinones/repos/IDI/IDI/S2.1/Model/model.cpp