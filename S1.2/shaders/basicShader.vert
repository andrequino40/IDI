#version 330 core

in vec3 vertex;
in vec3 color;
out vec3 freak;

void main()  {
    freak = color;
    gl_Position = vec4 (vertex * 0.5, 1.0);
}
