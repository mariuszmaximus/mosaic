#version 130
in float x;
in float y;
in float z;
out vec4 qt_MultiTexCoord0;
out vec4 qt_TexCoord0;

void main(void)
{
    gl_Position = vec4(x, y, z, 1.0f);
    qt_TexCoord0 = qt_MultiTexCoord0;
}
