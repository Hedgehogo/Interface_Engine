uniform sampler2D texture;

void main(void) {
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    gl_FragColor = gl_Color * pixel;
}