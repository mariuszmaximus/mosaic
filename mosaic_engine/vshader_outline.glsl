#version 130
in float x;
in float y;
uniform mat4 qt_ModelViewProjectionMatrix;

void main(void)
{
    vec4 vertex = vec4(x, y, 0, 0);
    gl_Position = qt_ModelViewProjectionMatrix * vertex;
}
