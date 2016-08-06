#version 130
in vec4 qt_Vertex;
uniform mat4 qt_ModelViewProjectionMatrix;
out vec4 gl_Position;

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
}
