#version 130
in float x;
in float y;
in float width;
in float height;
uniform float targetWidth = 1.0f;
uniform float targetHeight = 1.0f;

const vec2 pos[] = vec2[4](
  vec2(-0.5f,  0.5f),
  vec2(-0.5f, -0.5f),
  vec2( 0.5f,  0.5f),
  vec2( 0.5f, -0.5f)
);

in vec4 qt_MultiTexCoord0;
out vec4 qt_TexCoord0;

void main(void)
{
    vec2 offset = pos[gl_VertexID];
    gl_Position = vec4((x + width * offset.x) / targetWidth,
                       (y + height * offset.y) / targetHeight,
                       gl_InstanceID,
                       1.0f);
    qt_TexCoord0 = qt_MultiTexCoord0;
}
