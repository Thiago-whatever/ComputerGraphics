#version 410 core
in vec4 ourColor;
in vec2 TexCoord;
in float TexSelector;
in float IsCircle;
//te dice que color sale en la pantalla
out vec4 FragColor;

//textura igual es un uniform
uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

//transformas a enteros para manejarlos mejor
int texSel=int(TexSelector);
int circle=int(IsCircle);

void main(){
	if (texSel==1){
		vec4 texColor = texture(ourTexture, TexCoord);
		FragColor = texColor;
	} else if (texSel==2){
		vec4 texColor = texture(ourTexture2, TexCoord);
		FragColor = texColor;
	}else{
			FragColor=ourColor;
		}
	if(circle==1){
	//matriz de traslacion
		mat2 translate=mat2(1.0, 0.0, 0.0, 1.0);
		vec2 uv = TexCoord*translate*2 -1;//lo expande y lo regresa al centro para tener un circulo unitario
		float distance=1-length(uv);
		if (distance>0.0){
			distance=1.0;
		}
		vec4 texColor = ourColor * distance;
		FragColor=texColor;

	}
	
}