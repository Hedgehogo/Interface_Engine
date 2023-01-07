/*
uniform float red;
uniform float blue;
*/
uniform vec2 vec;
uniform sampler2D texture;

void main( void ) {
    vec4 pixel = texture2D(texture, gl_TexCoord[0]);
/*
    pixel.r *= red;
    pixel.b *= blue;
*/
    pixel.r *= vec.r;
    pixel.g *= vec.g;
    gl_FragColor = pixel;
}