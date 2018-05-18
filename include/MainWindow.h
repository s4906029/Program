#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "GLWindow.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:

    explicit MainWindow( QWidget * parent = 0 );
    ~MainWindow();
    void newFlock();
    void addBoid();
    void removeBoid();
    void addObstacle();
    void removeObstacle();

private:
    Ui::MainWindow * m_ui;
    GLWindow       * m_gl;

};

#endif
