uniform float aspectRatio;
uniform vec2 mousePosition;
uniform sampler2D texture;
uniform vec2 size;

void main( void ) {
    vec4 pixel = texture2D(texture, gl_TexCoord[0]);
    gl_FragColor = pixel;
}