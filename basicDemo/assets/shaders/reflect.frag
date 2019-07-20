#version 330 core
out vec4 FragColor;

in vec3 vNormals;
in vec3 FragPos;

uniform vec3 viewPos;
uniform samplerCube skybox;
uniform float refra;

void main()
{   
    if(refra > 0){

        vec3 I = normalize(FragPos - viewPos);
        vec3 R = reflect(I, normalize(vNormals));
        FragColor = vec4(texture(skybox, R).rgb, 1.0);
    }        
    else{

        float ratio = 1.00 / 1.52;
        vec3 I = normalize(FragPos - viewPos);
        vec3 R = refract(I, normalize(vNormals),ratio);
        FragColor = vec4(texture(skybox, R).rgb, 1.0);
    }  
}