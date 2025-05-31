#version 330 core

in vec3 fcolor;
out vec4 FragColor;

in vec4 vertexSCO; // VOLVER A NORMALIZAR
in vec3 normalSCO; // VOLVER A NORMALIZAR

 // PASAMOS AL FS
in vec3 matambFS;
in vec3 matdiffFS;
in vec3 matspecFS;
in float matshinFS;


void main()
{	
	FragColor = vec4(fcolor,1);	
}
