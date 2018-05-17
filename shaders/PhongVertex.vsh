#version 330 core

//flag for model unit normals
uniform bool Normalise;

//camera eye position
uniform vec3 viewerPos;

//colour position
uniform vec4 Colour;

//fragment normal of the vert processed
out vec3 fragmentNormal;
in vec3  inVert;
in vec3  inNormal;
in vec2  inUV;

struct Lights

{

    vec4 position;
    vec3 direction;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

};

//light array
uniform  Lights light;

//light direction
out vec3 lightDir;

//blinn half vector
out vec3 halfVector;
out vec3 eyeDirection;
out vec3 vPosition;

uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 normalMatrix;
uniform mat4 M;

void main()

{

    //calculate fragment surface normal
    fragmentNormal = ( normalMatrix*inNormal );

    if ( Normalise == true )

    {

        fragmentNormal = normalize( fragmentNormal );

    }

    //calculate vertex position
    gl_Position = MVP * vec4( inVert, 1.0 );

    vec4 worldPosition = M * vec4  ( inVert, 1.0 );
    eyeDirection =       normalize ( viewerPos - worldPosition.xyz );
    vec4 eyeCord =       MV * vec4 ( inVert, 1 );

    vPosition = eyeCord.xyz / eyeCord.w;;

    float dist;

    lightDir = vec3 (light.position.xyz-eyeCord.xyz );
    dist = length( lightDir );
    lightDir/= dist;
    halfVector = normalize( eyeDirection + lightDir );

}
