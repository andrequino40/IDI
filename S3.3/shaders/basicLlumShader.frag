#version 330 core

in vec3 fcolor;
out vec4 FragColor;

in vec4 vertexSCO; // VOLVER A NORMALIZAR
in vec3 normalSCO; // VOLVER A NORMALIZAR

in vec3 matambFS;
in vec3 matdiffFS;
in vec3 matspecFS;
in float matshinFS;

uniform vec4 posFocusSCO;
uniform vec4 posFocusSCOCam;
uniform vec3 colorFocus;
uniform vec3 colorFocusCam;
uniform vec3 llumAmbient;

vec3 Ambient() {
    return llumAmbient * matambFS;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) 
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdiffFS * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (matshinFS == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), matshinFS);
    return (matspecFS * colFocus * shine); 
}

void main()
{	
    vec3 LSCO = normalize(posFocusSCO.xyz - vertexSCO.xyz);
    vec3 LSCOCam = normalize(posFocusSCOCam.xyz - vertexSCO.xyz);

	// VOLVEMOS A NORMALIZAR N
	vec3 normalSCOFS = normalize(normalSCO);     

	// Calcul llum model Phong
    vec3 fcolor = Ambient() + 
             Difus(normalSCOFS, LSCO, colorFocus) + 
             Difus(normalSCOFS, LSCOCam, colorFocusCam) +
             Especular(normalSCOFS, LSCO, vertexSCO, colorFocus) +
             Especular(normalSCOFS, LSCOCam, vertexSCO, colorFocusCam);

	FragColor = vec4(fcolor,1);	
}
