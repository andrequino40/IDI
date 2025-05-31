#version 330 core

in vec3 vertex;
in vec3 normal;

in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

 // PASAMOS AL FS
out vec4 vertexSCO; // VOLVER A NORMALIZAR
out vec3 normalSCO; // VOLVER A NORMALIZAR

 // PASAMOS AL FS
out vec3 matambFS;
out vec3 matdiffFS;
out vec3 matspecFS;
out float matshinFS;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

// Valors per als components que necessitem del focus de llum


//vec3 colorFocus = vec3(0.8, 0.8, 0.8);
//vec3 posFocus = vec3(1, 0, 1);  // en SCA


// AHORA ESTARAN EN FS
// Ara son uniform, els passem des de MyGLWidget
// uniform vec4 posFocusSCO;
// uniform vec3 colorFocus;
// uniform vec3 llumAmbient;



// AHORA ESTA ENFS
// out vec3 fcolor;



void main()
{	
  // PosVertex en SCO
    vertexSCO = view * TG * vec4(vertex, 1.0);

  // Normal en SCO
    mat3 normalMatrix = inverse(transpose(mat3(view*TG)));
    normalSCO = normalize(normalMatrix*normal);

  // Lo pasamos desde MyGlWidget omo uniform
  // vec4 posFocusSCO = view * vec4(posFocus, 1.0);

  // AHORA ESTARA EN FS
  // L en SCO
    // vec3 LSCO = normalize(posFocusSCO.xyz - vertexSCO.xyz);

  // AHORA ESTARA EN FS
  // Calcul llum model Phong
    // fcolor = Ambient() + 
    //          Difus(normalSCO, LSCO, colorFocus) +
    //          Especular(normalSCO, LSCO, vertexSCO, colorFocus);


  matambFS = matamb;
  matdiffFS = matdiff;
  matspecFS = matspec;
  matshinFS = matshin;
  gl_Position = proj * vertexSCO;
}