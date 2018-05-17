#version 330 core

//fragment normal and colour
in vec3  fragmentNormal;
out vec4 fragColour;

//create material properties
struct Materials

{

    vec4  ambient;
    vec4  diffuse;
    vec4  specular;
    float shininess;

};

//create light properties
struct Lights

{
    vec4 position;
    vec3 direction;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

};

//materials passed
uniform Materials material;

uniform Lights light;
in vec3 lightDir;
in vec3 halfVector;
in vec3 eyeDirection;
in vec3 vPosition;

uniform vec4 Colour;


//point light values
vec4 pointLight()
{
    vec3  N           = normalize( fragmentNormal );
    vec3  halfVector;
    float ndothv;
    vec3  E           = normalize( eyeDirection );
    vec3  L           = normalize( lightDir );
    float lambertTerm = dot( N, L );
    vec4  diffuse     = vec4( 0 );
    vec4  ambient     = vec4( 0 );
    vec4  specular    = vec4( 0 );
    if    ( lambertTerm > 0.0 )

    {

        //distance from surface to light position
        float d;
        vec3 VP;

        //vector from surface to light position
        VP = vec3 ( light.position ) - vPosition;

        //distance between surface and light
        d = length ( VP );

        diffuse   += Colour * light.diffuse*lambertTerm;
        ambient   += material.ambient * light.ambient;
        halfVector = normalize( halfVector );
        ndothv     = max( dot( N, halfVector ), 0.0 );
        specular  += material.specular * light.specular * pow( ndothv, material.shininess );

    }

    return ambient + diffuse + specular;

}

void main()

{

    gl_FragColor = pointLight();

}
