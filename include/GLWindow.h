#ifndef GLWWINDOW_H
#define GLWWINDOW_H

#include <Scene.h>
#include <Boid.h>

#include <ngl/Camera.h>
#include <ngl/Vec3.h>
#include <ngl/Transformation.h>
#include <QEvent>
#include <QOpenGLWidget>
#include <QtOpenGL>
#include <memory>
#include <list>

class GLWindow : public QOpenGLWidget

{

    Q_OBJECT
    public:
        GLWindow( QWidget *_parent );

        GLWindow();

    private :

    protected :

        void initializeGL();

        void resizeGL(
                const int _w,
                const int _h
                );

        void paintGL();

        void addBoids();

        inline void clearBoids(){m_scene -> clearBoids();}

    private :

        int                    m_spinXFace;

        int                    m_spinYFace;

        bool                   m_rotate;

        bool                   m_translate;

        int                    m_origX;

        int                    m_origY;

        int                    m_origXPos;

        int                    m_origYPos;

        int                    m_width;

        int                    m_height;

        ngl::Mat4              m_mouseGloballTX;

        ngl::Camera          * m_camera;

        ngl::Transformation    m_transform;

        ngl::Vec3              m_modelPos;

        std::unique_ptr<Scene> m_scene;

        void loadMatricesToShader();

        void buildBoid();

        void mouseMoveEvent( QMouseEvent    * _event );

        void mousePressEvent( QMouseEvent   * _event );

        void mouseReleaseEvent( QMouseEvent * _event );

        void keyPressEvent( QKeyEvent       * _event );

};

#endif
