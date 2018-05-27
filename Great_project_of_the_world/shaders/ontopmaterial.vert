#version 330 core

in vec3 vertexPosition;

uniform mat4 modelView;
uniform mat3 modelViewNormal;
uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4( vertexPosition*2, 1.0 );
    gl_Position.z = 0.0;
}
