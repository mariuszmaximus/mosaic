#version 130
in float x;
in float y;
in float z;
uniform mat4 qt_ModelViewProjectionMatrix;

void main(void)
{
    gl_Position = vec4(x, y, z, 1.0f);
}
