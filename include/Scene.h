#ifndef SCENE_H
#define SCENE_H

#include <Boid.h>

#include <ngl/Camera.h>
#include <ngl/Vec3.h>
#include <ngl/Transformation.h>
#include <list>

class Boid;

typedef struct WALL{
    ngl::Vec3   centre;
    float       size;
    float       a;
    float       b;
    float       c;
    float       d;
    bool        draw_flag;

} Wall;

class Scene

{

public:

    Scene( ngl::Transformation * _t, ngl::Camera * _camera );

    inline ngl::Camera * getCamera() {return m_camera;}

    void      clearBoids();

    void      addNewWall( ngl::Vec3 _point, float size, ngl::Vec3 _normal, bool _draw );

    void      deleteAllWalls();

    ngl::Vec3 getRotationFromY( ngl::Vec3 _vec ) const;

    void      collisionWithWalls();

    void      collisionWithBoids();

    void      update();

private:

    ngl::Transformation  * m_transform;

    ngl::Camera          * m_camera;

    std::vector < Wall * > m_walls;

};

#endif
