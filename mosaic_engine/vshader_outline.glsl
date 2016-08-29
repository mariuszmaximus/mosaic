#version 130
in float x;
in float y;
in float z;
uniform mat4 qt_ModelViewProjectionMatrix;

void main(void)
{
    vec4 vertex = vec4(x, y, z, 1.0f);
    gl_Position = qt_ModelViewProjectionMatrix * vertex;
}
