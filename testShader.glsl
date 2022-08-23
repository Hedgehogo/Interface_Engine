uniform float aspectRatio;
uniform vec2 mousePosition;
uniform sampler2D texture;
uniform vec2 size;

float cut(float a, float b){
    float k = pow((pow(abs(gl_TexCoord[0].x - (mousePosition.x / size.x)), 2) + pow(abs(gl_TexCoord[0].y - (mousePosition.y / size.y)) / aspectRatio, 2)) * a, b);
    if(k > 1)
    k = 1;
    return k;
}

float red(float x){
    float k = cut(50, 10);
    if (x > k){
        x = k;
    }
    return x;
}

void main( void ) {
    vec4 pixel = texture2D(texture, gl_TexCoord[0]);
    pixel.x = red(pixel.x);
    gl_FragColor = pixel;
    //gl_FragColor = texture2D(texture, gl_TexCoord[0]);
}