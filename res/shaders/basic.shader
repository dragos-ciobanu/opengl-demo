#shader vertex
#version 120

void main() {
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
#shader fragment
#version 120

uniform vec4 u_Color;

void main(void) {

    gl_FragColor= u_Color;

}