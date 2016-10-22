#version 330

in float x;
in float y;
in float width;
in float height;
in float rotation;
uniform float viewPortWidth = 1.0f;
uniform float viewPortHeight = 1.0f;
uniform float magnification = 1.0f;
uniform float numTiles = 10.0f;

const vec2 pos[] = vec2[4](
  vec2(-0.5f,  0.5f),
  vec2(-0.5f, -0.5f),
  vec2( 0.5f,  0.5f),
  vec2( 0.5f, -0.5f)
);

void main(void)
{
    vec2 offset = pos[gl_VertexID];
    float c = cos(rotation);
    float s = sin(rotation);
    float x_ = (x + width * offset.x);
    float y_ = (y + height * offset.y);
    gl_Position = vec4(2.0f * magnification * (c * x_ - s * y_) / viewPortWidth,
                       2.0f * magnification * (s * x_ + c * y_) / viewPortHeight,
                       (gl_InstanceID - numTiles) / numTiles,
                       1.0f);
}
