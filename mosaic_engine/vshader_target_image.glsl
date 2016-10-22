#version 330
uniform float targetWidth = 1.0f;
uniform float targetHeight = 1.0f;
uniform float viewPortWidth = 1.0f;
uniform float viewPortHeight = 1.0f;
uniform float magnification = 1.0f;
out vec2 texcoord;

const vec2 pos[] = vec2[4](
  vec2(-0.5f,  0.5f),
  vec2(-0.5f, -0.5f),
  vec2( 0.5f,  0.5f),
  vec2( 0.5f, -0.5f)
);

void main(void)
{
    vec2 offset = pos[gl_VertexID];
    gl_Position = vec4(2.0 * targetWidth * magnification * offset.x / viewPortWidth,
                       2.0 * targetHeight * magnification * offset.y / viewPortHeight,
                       0.0f,
                       1.0f);
    texcoord = offset + vec2(0.5f, 0.5f);
}
