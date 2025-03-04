#version 330 core

out vec4 FragColor;

void main() {
    FragColor = vec4(0, 0, 0, 1);
    int vecy = (int)gl_FragCoord.y;
    int num = 15;
    if (vecy % num > (num/2)) {
        discard;
         return;
    }
    if (gl_FragCoord.x < 354. && gl_FragCoord.y >354.)
        FragColor = vec4(1.,0.,0.,1);
    else if (gl_FragCoord.x > 354. && gl_FragCoord.y >354.)
        FragColor = vec4(0.,0.,1.,1);
    else if (gl_FragCoord.x > 354. && gl_FragCoord.y <354.)
        FragColor = vec4(0.,1.,0.,1);
    else
        FragColor = vec4(1.,1.,0.,1);
    
}

