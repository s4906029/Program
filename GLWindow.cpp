#include "GLWindow.h"
#include "Boid.h"
#include <QGuiApplication>
#include <QMouseEvent>

#include <iostream>
#include <ngl/Camera.h>
#include <ngl/Vec3.h>
#include <ngl/Light.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Transformation.h>
#include <ngl/VAOFactory.h>
#include <ngl/Material.h>
#include <ngl/Random.h>
#include <ngl/ShaderLib.h>
#include <ngl/NGLStream.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//the increment for mouse x/y translation
const static float INCREMENT = 0.01f;

GLWindow::GLWindow( QWidget * _parent ) :
    QOpenGLWidget( _parent )

{

    setFocus();

    this -> resize( _parent->size() );

}

void GLWindow::initializeGL()

{

    //grey background
    glClearColor( 0.4f, 0.4f, 0.4f, 1.0f );

        //depth testing
        glEnable( GL_DEPTH_TEST );

        //creates camera position
        ngl::Vec3 eye   ( 2, 2, 2 );
        ngl::Vec3 look  ( 0, 0, 0 );
        ngl::Vec3 up    ( 0, 1, 0 );

        //set up camera
        m_camera    =  new ngl::Camera      ( eye, look, up );
        m_camera    -> setShape(45, float   ( 1024 / 720 ), 0.1, 300 );

        //load shader
        ngl::ShaderLib *shader = ngl::ShaderLib::instance();

        constexpr auto shaderProgram    = "Phong";
        constexpr auto vertexShader     = "PhongVertex";
        constexpr auto fragShader       = "PhongFragment";

        //shader program
        shader -> createShaderProgram( shaderProgram );

        //empty shaders for Frag and Vert
        shader -> attachShader( vertexShader, ngl::ShaderType::VERTEX );
        shader -> attachShader( fragShader,   ngl::ShaderType::FRAGMENT );

        //attach to source
        shader -> loadShaderSource( vertexShader, "shaders/PhongVertex.glsl" );
        shader -> loadShaderSource( fragShader,   "shaders/PhongFragment.glsl" );

        //compile shaders
        shader -> compileShader( vertexShader );
        shader -> compileShader( fragShader );

        //adding shaders to program
        shader -> attachShaderToProgram( shaderProgram, vertexShader );
        shader -> attachShaderToProgram( shaderProgram, fragShader );

        //data link with shader
        shader -> linkProgramObject( shaderProgram );

        //make active
        ( *shader )[ shaderProgram ] -> use();

        //use current active material and light
        ngl::Material m( ngl::STDMAT::GOLD );

        //load material values to shader
        m.loadToShader( "material" );

        //set up light
        ngl::Mat4 iv = m_camera->getViewMatrix();
        iv.transpose();
        ngl::Light light(ngl::Vec3( -2, 5, 2 ), ngl::Colour( 1, 1, 1, 1 ), ngl::Colour( 1, 1, 1, 1 ), ngl::LightModes::POINTLIGHT );
        light.setTransform( iv );

        //load light values to shader
        light.loadToShader( "light" );

}

void GLWindow::loadMatricesToShader()

{

    ngl::ShaderLib * shader = ngl::ShaderLib::instance();

    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Mat4 M;
    M       = m_mouseGloballTX;
    MV      = m_camera -> getViewMatrix() * M;
    MVP     = m_camera -> getVPMatrix()   * M;

    normalMatrix = MV;
    normalMatrix.inverse().transpose();
    shader -> setUniform( "MV", MV );
    shader -> setUniform( "MVP", MVP );
    shader -> setUniform( "normalMatrix", normalMatrix );
    shader -> setUniform( "M", M );

}

void GLWindow::resizeGL( int _w, int _h )

{

    glViewport( 0, 0, _w, _h );

}

void GLWindow::paintGL()

{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ngl::NGLInit::instance();

    ngl::VAOPrimitives* prim = ngl::VAOPrimitives::instance();
    prim->createLineGrid("wall", 1, 1, 1);

    //creates initial wall positions
    m_scene -> addNewWall( ngl::Vec3   ( -10,   0,   0 ),   20, ngl::Vec3    (  1.0,  0.0,  0.0),   true);
    m_scene -> addNewWall( ngl::Vec3   (  10,   0,   0 ),   20, ngl::Vec3    ( -1.0,  0.0,  0.0),   true);
    m_scene -> addNewWall( ngl::Vec3   (   0,  10,   0 ),   20, ngl::Vec3    (  0.0, -1.0,  0.0),   true);
    m_scene -> addNewWall( ngl::Vec3   (   0, -10,   0 ),   20, ngl::Vec3    (  0.0,  1.0,  0.0),   true);
    m_scene -> addNewWall( ngl::Vec3   (   0,   0,  10 ),   20, ngl::Vec3    (  0.0,  0.0, -1.0),   true);
    m_scene -> addNewWall( ngl::Vec3   (   0,   0, -10 ),   20, ngl::Vec3    (  0.0,  0.0,  1.0),   true);

}

//create boid shape
void Boid::Draw()
{
    glPushMatrix();

        glTranslatef( 0, 0, 0 );

        glutSolidCone(0.1, 3.0, 3.0, 1.0);

    glPopMatrix();

}

//creates boids inside box
void GLWindow::addBoids()
{
    m_scene -> clearBoids();

    ngl::Vec3 dir (0.0f, 0.0f, 0.0f);

}

void GLWindow::mouseMoveEvent(
                             QMouseEvent * _event
                             )

{
    //left mouse button
    if( m_rotate && _event -> buttons() == Qt::LeftButton )

    {
        int diffx   =  _event -> x()  -m_origX;
        int diffy   =  _event -> y()  -m_origY;
        m_spinXFace += (float)   0.5f * diffy;
        m_spinYFace += (float)   0.5f * diffx;
        m_origX     =  _event -> x();
        m_origY     =  _event -> y();
        update();

    }

    //right mouse button
    else if( m_translate && _event -> buttons() == Qt::RightButton )

    {

        int diffX       =  (int)(_event    -> x() - m_origXPos );
        int diffY       =  (int)(_event    -> y() - m_origYPos );
        m_origXPos      =  _event          -> x();
        m_origYPos      =  _event          -> y();
        m_modelPos.m_x  += INCREMENT        * diffX;
        m_modelPos.m_y  += INCREMENT        * diffY;
        update();

    }

}

void GLWindow::mousePressEvent( QMouseEvent * _event )

{

    //left mouse button
    if( _event -> button() == Qt::LeftButton )

    {
        m_origX     = _event -> x();
        m_origY     = _event -> y();
        m_rotate    = true;

    }

    //right mouse button
    else if( _event -> button() == Qt::RightButton )

    {

        m_origXPos  = _event -> x();
        m_origYPos  = _event -> y();
        m_translate = true;

    }

}

void GLWindow::mouseReleaseEvent( QMouseEvent *_event )

{

    //left mouse button
    if ( _event->button() == Qt::LeftButton )

    {
        m_rotate = false;

    }

    //right mouse button
    if ( _event -> button() == Qt::RightButton )

    {

        m_translate = false;

    }

}

void GLWindow::keyPressEvent( QKeyEvent * _event )

{

    switch ( _event -> key() )

    {

    //press escape key to quit
    case Qt::Key_Escape: QGuiApplication::exit( EXIT_SUCCESS ); break;

    //press f for fullscreen
    case Qt::Key_F: showFullScreen(); break;

    default: break;

    }

    //update the GLWindow and re-draw
    update();

}
