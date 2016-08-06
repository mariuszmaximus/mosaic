#version 130
in vec4 qt_Vertex;
out vec4 qt_MultiTexCoord0;
uniform mat4 qt_ModelViewProjectionMatrix;
out vec4 qt_TexCoord0;

void main(void)
{
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    qt_TexCoord0 = qt_MultiTexCoord0;
}
