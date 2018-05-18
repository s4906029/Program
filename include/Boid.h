#ifndef BOID_H
#define BOID_H

#include <ngl/Vec3.h>
#include <vector>
#include <ostream>

class Boid

{

public:

    Boid( int _id );

    int getID();

    void Draw();

    ngl::Vec3 getVelocity();

    ngl::Vec3 getPosition();

    ngl::Vec3 getRotation();

    float getViewRadius();

    float getAvoidRadius();

    bool isLeader();

    bool isPredator();

    int getNeighbourSize();

    void setSpeed( float            _speed );

    void setAlignmentWeight( float  _aligmentWeight );

    void setCohesionWeight( float   _cohesionWeight );

    void setSeperationWeight( float _seperationWeight );

    void setAvoidWeight( float      _avoidWeight );

    void setPosition( ngl::Vec3     _position );

    void setVelocity( ngl::Vec3     _veloicty );

    void setLeader( Boid          * _leader );

    void setPredator( Boid        * _predator);

    void setNeighbours( Boid      * _boid);

    void setCentroid();

    void clearNeighbours();

    void clearLeader();

    void makeLeader();

    void makePredator();

    void setCohesion();

    void setAlignment();

    void setSeparation();

    void setSeek();

    void setPursuit( ngl::Vec3       _pursuePosition, ngl::Vec3 _persueVelocity );

    void setFlee( ngl::Vec3          _fleePosition );

    void evade( Boid               * _boid );

    void setWander();

    void setAvoid();

    void setFollow();

    void setTarget();

    void setSteering();

    void move();

    void rotate();

    void fleeWalls();

    void pathIntersectsSphere( ngl::Vec3 _obstaclePosition, float _obstacleSize );

    void setId( int _id );

private:

    int m_id;

    ngl::Vec3 m_position;

    ngl::Vec3 m_velocity;

    ngl::Vec3 m_centroid;

    ngl::Vec3 m_target;

    ngl::Vec3 m_separation;

    ngl::Vec3 m_alignment;

    ngl::Vec3 m_cohesion;

    ngl::Vec3 m_pursuit;

    ngl::Vec3 m_flee;

    ngl::Vec3 m_wander;

    ngl::Vec3 m_avoid;

    ngl::Vec3 m_follow;

    ngl::Vec3 m_threatPosition;

    ngl::Vec3 m_steering;

    float     m_slowingRadius;

    float     m_maxVelocity;

    float     m_wanderSphereDistance;

    float     m_wanderSphereRadius;

    float     m_wanderAngle;

    float     m_wanderAzimuth;

    float     m_wanderAngleChange;

    float     m_wanderAzimuthChange;

    float     m_avoidRadius;

    float     m_avoidWeight;

    float     m_cohesionWeight;

    float     m_alignmentWeight;

    float     m_separationWeight;

    float     m_speed;

    float     m_maxSeeAhead;

    float     m_leaderFollowDistance;

    float     m_viewRadius;

    float     m_separationRadius;

    float     m_roll;

    float     m_pitch;

    float     m_yaw;

    bool      m_isLeader;

    bool      m_hasLeader;

    bool      m_isPredator;

    bool      m_hasPredator;

    Boid    * m_leader;

    Boid    * m_predator;

    std::vector< Boid * > m_neighbours;

};

#endif
