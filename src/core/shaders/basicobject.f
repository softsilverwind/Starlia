#version 120

varying vec2 f_texcoord;
uniform sampler2D tex;

void main(void)
{
    vec2 flipped_texcoord = vec2(f_texcoord.x, f_texcoord.y);
    gl_FragColor = texture2D(tex, flipped_texcoord);
}
