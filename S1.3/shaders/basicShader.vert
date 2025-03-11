#version 330 core

in vec3 vertex;
in vec3 color;
out vec3 freak;

uniform float val = 0.5;

void main()  {
    freak = color;
    gl_Position = vec4 (vertex * val, 1.0);
}
