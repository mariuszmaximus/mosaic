#version 130
uniform sampler2DArray qt_Texture0;
in vec2 texCoord;
in float layer;

void main(void)
{
    gl_FragColor = texture(qt_Texture0,
                           vec3(texCoord.x, texCoord.y, layer));
    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}
