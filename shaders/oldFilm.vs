#version 330

layout(location = 0) in vec3 vertexPosition;  // Vertex position attribute
layout(location = 1) in vec2 vertexTexCoord;  // Vertex texture coordinate attribute

out vec2 fragTexCoord;  // Output to fragment shader

void main()
{
    fragTexCoord = vertexTexCoord;
    gl_Position = vec4(vertexPosition, 1.0);
}
