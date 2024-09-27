#version 330

in vec3 vertexPosition;   // Vertex position
in vec2 vertexTexCoord;   // Vertex texture coordinates
in vec4 vertexColor;      // Vertex color

out vec2 fragTexCoord;
out vec4 fragColor;

uniform mat4 mvp;  // Model-view-projection matrix

void main()
{
    fragTexCoord = vertexTexCoord;  // Pass texture coordinates to fragment shader
    fragColor = vertexColor;        // Pass color to fragment shader

    gl_Position = mvp * vec4(vertexPosition, 1.0);  // Apply MVP matrix to vertex
}
