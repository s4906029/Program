#include "Boid.h"

#include <iostream>
#include <math.h>
#include <ngl/Random.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

//constructors
Boid::Boid( int _id )

{

    m_id = _id;
    m_flee.set( ngl::Vec3 (0.0f, 0.0f, 0.0f) );
    m_centroid.set (ngl::Vec3 (0.0f, 0.0f, 0.0f) );
    m_threatPosition.set (ngl::Vec3 (0.0f, 0.0f, 0.0f) );
    m_slowingRadius             =   5.0f;
    m_viewRadius                = 100.0f;
    m_separationRadius          =  20.0f;
    m_leaderFollowDistance      =  10.0f;
    m_maxSeeAhead               =  15.0f;
    m_avoidRadius               =  10.0f;
    m_wanderAzimuthChange       =   5.0f;
    m_wanderAngleChange         =   2.0f;
    m_wanderAzimuth = ngl::Random::instance() -> randomNumber() *  5;
    m_wanderAngle   = ngl::Random::instance() -> randomNumber() * 10;
    m_wanderSphereRadius        =   2.0f;
    m_wanderSphereDistance      =  20.0f;
    m_maxVelocity               =   7.5f;

    //greater the weight, greater the impact
    m_avoidWeight               =   7.5f; //avoidance weight
    m_cohesionWeight            =   4.0f; //cohesion weight
    m_alignmentWeight           =   3.0f; //alignment weight
    m_separationWeight          =   1.0f;

}

//making attributes
void Boid::setId(int _id)
{
    m_id = _id;

}

void Boid::setSpeed(float _speed) //set boid speed
{
        m_speed = _speed;
}

void Boid::setAlignmentWeight(float _alignmentWeight)
{
        m_alignmentWeight = _alignmentWeight;
}

void Boid::setCohesionWeight(float _cohesionWeight)
{
        m_cohesionWeight = _cohesionWeight;
}

void Boid::setSeperationWeight(float _seperationWeight)
{
        m_separationWeight = _seperationWeight;
}

void Boid::setAvoidWeight(float _avoidWeight)
{
        m_avoidWeight = _avoidWeight;
}

void Boid::setPosition(ngl::Vec3 _position)
{
        m_position.set(_position);
}

void Boid::setVelocity(ngl::Vec3 _velocity)
{
        m_velocity.set(_velocity);
}

void Boid::setNeighbours(Boid * _boid)
{
        if (_boid -> getID() > 0) m_neighbours.push_back(_boid);
}


void Boid::setCentroid()
    {
        if (m_neighbours.size() > 0)
        {
            for (size_t i = 0; i < m_neighbours.size(); ++i)

            {
                m_centroid += m_neighbours[i] -> getPosition();
            }

            m_centroid /= (m_neighbours.size());
        }
}

//movement behaviour
void Boid::move()
{
    if (m_id > 0)
    {
        setSteering();
        m_velocity += m_steering;
        m_velocity.normalize();
        m_position += m_velocity;
        rotate();
    }

    else

    {
        m_velocity -= ngl::Vec3(0.0f, 0.2f, 0.0f);
        if (m_position.m_y >= -100)
        {
            m_position += m_velocity;
        }

        else
        {
            m_id = -1;
        }
    }
}

//flocking behaviour

    //alignment
void Boid::setAlignment()
{
    if (m_neighbours.size() > 0)
    {
        for (size_t i = 0; i < m_neighbours.size(); ++i)
        {
            m_alignment += m_neighbours[i] -> getVelocity();

        }

        m_alignment /= m_neighbours.size();
            if (m_alignment.length()!=0)
        {
            m_alignment.normalize();

        }
    }
    else
        m_alignment.set(0.0f, 0.0f, 0.0f);
}

    //cohesion
void Boid::setCohesion()
{
    setCentroid();
    if (m_neighbours.size() > 0)
    {
        m_cohesion = m_centroid - m_position;
            if(m_cohesion.length()!=0)
        {
            m_cohesion.normalize();
        }
    }
    else
    {
        m_cohesion.set(0.0f, 0.0f, 0.0f);
    }
}
