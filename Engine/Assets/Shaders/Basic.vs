#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aTangent;
layout (location = 3) in vec3 aBitangent;
layout (location = 4) in vec2 aTexCoord;

out vec3 ourColor;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	ourColor = vec3(1.0f, 0.0f, 1.0f);
}
