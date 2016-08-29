#version 130
in float x;
in float y;
in float z;
out vec4 qt_MultiTexCoord0;
uniform mat4 qt_ModelViewProjectionMatrix;
out vec4 qt_TexCoord0;

void main(void)
{
    vec4 vertex = vec4(x, y, z, 0);
    gl_Position = qt_ModelViewProjectionMatrix * vertex;
    qt_TexCoord0 = qt_MultiTexCoord0;
}
