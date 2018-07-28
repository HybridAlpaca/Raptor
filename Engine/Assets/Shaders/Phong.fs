#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;  
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

void main ()
{
	vec3 normal = texture(texture_normal1, TexCoord).rgb;
	normal = normalize(normal * 2.0 - 1.0);
	
	vec3 color = texture(texture_diffuse1, TexCoord).rgb;
	
	// ambient
	vec3 ambient = 0.15 * lightColor * color;
  
  // diffuse 
	vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = lightColor * diff * color;  

	// specular
	vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
	vec3 halfwayDir = normalize(lightDir + viewDir);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
	vec3 specular = lightColor * spec * texture(texture_specular1, TexCoord).rgb;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
	float gamma = 2.2;
	FragColor.rgb = pow(FragColor.rgb, vec3(1.0 / gamma));
} 
