#version 330 core
// Vertex color (interpolated/fragment)
in vec3 vColor;
in vec2 vTextCoord;
in vec3 vNormals;
in vec3 FragPos;
in mat3 TBN;
in vec3 TBNViewPos;
in vec3 TBNFragPos;
// Fragment Color
out vec4 color;

struct DirectionalLight {

    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

struct CookTorrenceReturn{

    vec3 diffuse;
    vec3 specular;
};

uniform sampler2D texture_diffuse;
uniform sampler2D texture_alpha;
uniform sampler2D texture_specularH;
uniform sampler2D texture_specular;
uniform sampler2D texture_normals;

uniform vec3 modelMaterial_a;
uniform vec3 modelMaterial_d;
uniform vec3 modelMaterial_s;
uniform float modelMaterial_ns;
uniform float modelMaterial_r;

uniform DirectionalLight dirLight;

#define PI 3.14159265
uniform vec3 viewPos;

CookTorrenceReturn CookTorrance(vec3 normal,vec3 lightDir,vec3 viewDir,vec3 lightColorD,vec3 lightColorS)
{
	float NdotL = clamp(dot(normal, lightDir),0.0,1.0);
	float Rs = 0.5;
    float k = 1.0;
    float roughness = modelMaterial_r;
    float reflectance = modelMaterial_ns;

	if (NdotL > 0.0) 
	{
		vec3 H = normalize(lightDir + viewDir);
		float NdotH = clamp(dot(normal, H),0.0,1.0);
		float NdotV = clamp(dot(normal, viewDir),0.0,1.0);
		float VdotH = clamp(dot(lightDir, H),0.0,1.0);

		// Fresnel reflectance
		float F = pow(1.0 - VdotH, 5.0);
		F *= (1.0 - reflectance);
		F += reflectance;

		// Microfacet distribution by Beckmann
		float m_squared = roughness * roughness;
		float r1 = 1.0 / (4.0 * m_squared * pow(NdotH, 4.0));
		float r2 = (NdotH * NdotH - 1.0) / (m_squared * NdotH * NdotH);
		float D = r1 * exp(r2);

		// Geometric shadowing
		float two_NdotH = 2.0 * NdotH;
		float g1 = (two_NdotH * NdotV) / VdotH;
		float g2 = (two_NdotH * NdotL) / VdotH;
		float G = min(1.0, min(g1, g2));

		Rs = (F * D * G) / (PI * NdotL * NdotV);
	}
    
    CookTorrenceReturn Re;

    Re.diffuse =  lightColorD * NdotL * texture(texture_diffuse, vTextCoord).rgb;
   	Re.specular = lightColorS * NdotL * (k + Rs * (1.0 - k))* texture(texture_specular, vTextCoord).rgb;


	return Re;
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-(TBN*light.direction));
    vec3 halfWayDir = normalize(lightDir*viewDir); //bling-phong

	vec3 reflectDir = reflect(-lightDir, normal);
	float diff = max(dot(lightDir, normal), 0.0);

    float spec = pow(max(dot(normal, halfWayDir), 0.0), modelMaterial_ns);

	CookTorrenceReturn Re;

	vec3 ambient = light.ambient * texture(texture_diffuse, vTextCoord).rgb*0;
	//Re.diffuse = light.diffuse * diff * texture(texture_diffuse, vTextCoord).rgb;
	//Re.specular = light.specular * spec * texture(texture_specular, vTextCoord).rgb;
    Re = CookTorrance(normal,lightDir,viewDir,light.diffuse,light.specular);
    return ( ambient+ Re.diffuse + Re.specular);

}

/*vec3 CalcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    CookTorrenceReturn Re;

	vec3 ambient = light.ambient * modelMaterial_a;
    Re = CookTorrance( normal, lightDir, viewDir, light.diffuse, light.specular);

    ambient *= attenuation;
    vec3 diffuse = Re.diffuse * attenuation;
    vec3 specular = Re.specular * attenuation;

    return (diffuse + specular);
}*/


void main()
{   
    vec3 vNormals =  texture(texture_normals, vTextCoord).rgb;
	vec3 norm = normalize(vNormals * 2.0 - 1.0);
	//norm = normalize(TBN * norm); 
	//vec3 viewDir = normalize(viewPos - FragPos);
    vec3 viewDir = normalize(TBNViewPos - TBNFragPos);
    
    vec3 lightResult = CalcDirLight(dirLight,norm,viewDir);
    float alpha = texture(texture_alpha, vTextCoord).a;
    color = vec4(lightResult,1.0);
}