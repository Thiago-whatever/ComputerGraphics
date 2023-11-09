#version 410 core
//son las capas
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in float aTexSelector;
layout (location = 4) in float aIsCircle;
//

//variables de salida del shader
//s ele pasan al fragment shader
out vec4 ourColor;
out vec2 TexCoord;
out float TexSelector;
out float IsCircle;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
	//posicion de cada vertice
	//la parte del model es lo que permite hacer la transformacion
	gl_Position = model * vec4(aPos, 1.0);
	//variables que se le mandan al fragment shader
	ourColor = aColor;
	TexCoord = aTexCoord;
	TexSelector=aTexSelector;
	IsCircle=aIsCircle;
};