#version 330
uniform usampler2DArray texture0;
in vec2 texCoord;
in float layer;

void main(void)
{
    gl_FragColor = texture(texture0,
                           vec3(texCoord.x, texCoord.y, layer)) / 255.0;
    gl_FragColor = gl_FragColor.wzyx;
}
