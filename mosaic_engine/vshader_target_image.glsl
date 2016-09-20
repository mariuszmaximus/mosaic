#version 130
uniform float targetWidth = 1.0f;
uniform float targetHeight = 1.0f;
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
    float worldSize = sqrt(targetWidth * targetHeight);
    gl_Position = vec4(targetWidth * 2.0 * offset.x / worldSize,
                       targetHeight * 2.0 * offset.y / worldSize,
                       0.0f,
                       1.0f);
    texcoord = offset + vec2(0.5f, 0.5f);
}
