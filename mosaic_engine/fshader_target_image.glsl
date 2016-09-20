uniform sampler2D texture0;
in vec2 texcoord;

void main(void)
{
    gl_FragColor = texture2D(texture0, texcoord);
}
