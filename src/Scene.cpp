#include "Scene.h"
#include "Boid.h"

#include <ngl/Random.h>
#include <ngl/NGLStream.h>

Scene::Scene( ngl::Transformation * _t, ngl::Camera * _camera )

{

    m_transform = _t;
    m_camera    = _camera;

}

void Scene::addNewWall( ngl::Vec3 _point, float _size, ngl::Vec3 _normal, bool _draw )

{

    Wall * newWall = new Wall;
    _normal.normalize();
    newWall           -> centre    = _point;
    newWall           -> size      = _size;
    newWall           -> a         = _normal.m_x;
    newWall           -> b         = _normal.m_y;
    newWall           -> c         = _normal.m_z;
    newWall           -> d         = -(newWall->a * _point.m_x + newWall->b * _point.m_y + newWall->c * _point.m_z );
    newWall           -> draw_flag = _draw;

    m_walls.push_back( newWall );

}
