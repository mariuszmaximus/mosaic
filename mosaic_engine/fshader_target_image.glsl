#version 330

uniform sampler2D texture0;
in vec2 texcoord;

void main(void)
{
    vec4 dim = vec4(0.3f, 0.3f, 0.3f, 1.0f);
    //gl_FragColor = dim * texture(texture0, texcoord);
    gl_FragColor = dim * texture(texture0, texcoord);
}
