#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stdlib.h>
#include <stdio.h>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

static void error_callback( int error, const char* description ) {
	fprintf( stderr, "Error: %s\n", description );
}

static void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods ) {
	if( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
		glfwSetWindowShouldClose( window, GLFW_TRUE );
}

int main( void ) {
	GLFWwindow* window;

	glfwSetErrorCallback( error_callback );

	if( !glfwInit() )
		exit( EXIT_FAILURE );

	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );

	window = glfwCreateWindow( 600, 900, "Tarea2", NULL, NULL );//640 480
	if( !window ) {
		glfwTerminate();
		exit( EXIT_FAILURE );
	}

	glfwSetKeyCallback( window, key_callback );

	glfwMakeContextCurrent( window );
	gladLoadGL();
	glfwSwapInterval( 1 );

	float vertices[] = {
		//ESTRUCTURA DE LAS COORDENADAS
		// xyz              //rgb transparencia  //textcord1 texcoord2   //texselector   //iscircle
		// textcord x,y 1 1  1 0  0 0   0 1
		
		//Colores que se van a emplear en notacion rgb normalizada:
		//cafe claro: (0.8117f, 0.7254f, 0.6117f)
		//cafe fuerte: (0.4117f,0.3215f,0.2313f)
		//cafe obscuro: (0.2705f, 0.1843f, 0.1137f)
		//cafe-amarillo: (0.8549f,0.6549f, 0.3176f)
		//cafe-miel: (0.7254f, 0.4431f,0.1607f)
		//crema: (0.8274f, 0.7647f,0.7254f)
		//rosa: (0.7058f,0.4784f,0.4549f)
		

		// CAPA 0
		// Rectangulos delgados(de izquierda a derecha)
		//R1
		-0.859f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,1.0f,  1.0f,   0.0f,  //0
		-0.803f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,0.0f,  1.0f,   0.0f,
		-0.859f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,0.0f,  1.0f,   0.0f,
		-0.803f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,1.0f,  1.0f,   0.0f,
		//R2
		-0.771f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,1.0f,  2.0f,   0.0f,  //4
		-0.715f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,0.0f,  2.0f,   0.0f,
		-0.771f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,0.0f,  2.0f,   0.0f,
		-0.715f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,1.0f,  2.0f,   0.0f,
		//R3
		-0.68f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,1.0f,  1.0f,   0.0f,  //8
		-0.625f, 0.828f, 0.0f,   0.0f, 0.20f,0.30f, 1.0f,   1.0f,0.0f,  1.0f,   0.0f,  
		-0.68f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,0.0f,  1.0f,   0.0f,  
		-0.625f, -0.25f, 0.0f,   0.0f, 0.20f,0.30f, 1.0f,   0.0f,1.0f,  1.0f,   0.0f,  
		//R4
		-0.60f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,1.0f,  2.0f,   0.0f,  //12
		-0.544f, 0.828f, 0.0f,   0.0f, 0.20f,0.30f, 1.0f,   1.0f,0.0f,  2.0f,   0.0f,  
		-0.60f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,0.0f,  2.0f,   0.0f,  
		-0.544f, -0.25f, 0.0f,   0.0f, 0.20f,0.30f, 1.0f,   0.0f,1.0f,  2.0f,   0.0f,  
		//R5
		-0.521f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,1.0f,  1.0f,   0.0f,  //16
		-0.465f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,0.0f,  1.0f,   0.0f, 
		-0.521f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,0.0f,  1.0f,   0.0f, 
		-0.465f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,1.0f,  1.0f,   0.0f, 
		//R6
		-0.437f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,1.0f,  2.0f,   0.0f,  //20
		-0.375f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,0.0f,  2.0f,   0.0f,  
		-0.437f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,0.0f,  2.0f,   0.0f,  
		-0.375f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,1.0f,  2.0f,   0.0f,  
		//R7
		-0.343f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,1.0f,  1.0f,   0.0f,  //24
		-0.284f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,0.0f,  1.0f,   0.0f,  
		-0.343f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,0.0f,  1.0f,   0.0f,  
		-0.284f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,1.0f,  1.0f,   0.0f,  
		//R8
		-0.256f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,1.0f,  2.0f,   0.0f,  
		-0.200f, 0.828f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   1.0f,0.0f,  2.0f,   0.0f,  
		-0.256f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,0.0f,  2.0f,   0.0f,  
		-0.200f, -0.25f, 0.0f,    0.0f, 0.20f,0.30f, 1.0f,   0.0f,1.0f,  2.0f,   0.0f,  

		//R (el mas grande)
		-0.5f, 0.625f, 0.0f,	  0.2705f, 0.1843f, 0.1137f, 1.0f,   1.0f,1.0f,  0.0f,   0.0f,  //32
		0.687f, 0.625f, 0.0f,     0.2705f, 0.1843f, 0.1137f, 1.0f,   1.0f,0.0f,  0.0f,   0.0f,
		-0.5f, -0.69f, 0.0f,      0.2705f, 0.1843f, 0.1137f, 1.0f,   0.0f,0.0f,  0.0f,   0.0f,
		0.687f, -0.69f, 0.0f,     0.2705f, 0.1843f, 0.1137f, 1.0f,   0.0f,1.0f,  0.0f,   0.0f,

		//CAPA 1
		//R inclinado (mas arriba)
		-0.093f, 0.9346f, 0.1f,   0.7254f, 0.4431f,0.1607f, 1.0f,   1.0f,1.0f,  0.0f,   0.0f,  //36
		0.471f, 0.640f, 0.1f,     0.7254f, 0.4431f,0.1607f, 1.0f,   1.0f,0.0f,  0.0f,   0.0f,
		-0.531f, 0.531f, 0.1f,    0.7254f, 0.4431f,0.1607f, 1.0f,   0.0f,0.0f,  0.0f,   0.0f,
		0.046f, 0.25f, 0.1f,      0.7254f, 0.4431f,0.1607f, 1.0f,   0.0f,1.0f,  0.0f,   0.0f,
		
		//CAPA 2
		//C negro
		-0.906f, 0.531f, 0.0f,    0.8117f, 0.7254f, 0.6117f, 0.9f,   0.0f,0.0f,  0.0f,   1.0f,  //40
		-0.031f, 0.531f, 0.0f,    0.8117f, 0.7254f, 0.6117f, 0.9f,   1.0f,0.0f,  0.0f,   1.0f,
		-0.906f, -0.031f, 0.0f,   0.8117f, 0.7254f, 0.6117f, 0.9f,   0.0f,1.0f,  0.0f,   1.0f,
		-0.031f, -0.031f, 0.0f,   0.8117f, 0.7254f, 0.6117f, 0.9f,   1.0f,1.0f,  0.0f,   1.0f,

		//CAPA 3
		//R inclinado (mas abajo)
		-0.171f, 0.387f, 0.3f,    0.8274f, 0.7647f,0.7254f, 1.0f,   1.0f,1.0f,  0.0f,   0.0f,  //44
		0.571f, 0.015f, 0.3f,     0.8274f, 0.7647f,0.7254f, 1.0f,   1.0f,0.0f,  0.0f,   0.0f,
		-0.968f, -0.35f, 0.3f,    0.8274f, 0.7647f,0.7254f, 1.0f,   0.0f,0.0f,  0.0f,   0.0f,
		-0.212f, -0.721f, 0.3f,   0.8274f, 0.7647f,0.7254f, 1.0f,   0.0f,1.0f,  0.0f,   0.0f,

		//CAPA 4
		//C gris
		-0.265f, 0.243f, 0.4f,    0.7058f,0.4784f,0.4549f, 0.9f,   0.0f,0.0f,  0.0f,   1.0f,  //48
		0.64f, 0.243f, 0.4f,      0.7058f,0.4784f,0.4549f, 0.9f,   1.0f,0.0f,  0.0f,   1.0f,
		-0.265f, -0.365f, 0.4f,   0.7058f,0.4784f,0.4549f, 0.9f,   0.0f,1.0f,  0.0f,   1.0f,
		0.64f, -0.365f, 0.4f,     0.7058f,0.4784f,0.4549f, 0.9f,   1.0f,1.0f,  0.0f,   1.0f,
		
		

		//CAPA 5
		//Cuadrado negro delante del circulo
		-0.375f, -0.031f, 0.5f,    0.7254f, 0.4431f,0.1607f, 0.5f,   1.0f,1.0f,  0.0f,   0.0f,  //52
		0.125f, -0.031f, 0.5f,     0.7254f, 0.4431f,0.1607f, 0.5f,   1.0f,0.0f,  0.0f,   0.0f,
		-0.375f, -0.415f, 0.5f,    0.7254f, 0.4431f,0.1607f, 0.5f,   0.0f,0.0f,  0.0f,   0.0f,
		0.125f, -0.415f, 0.5f,     0.7254f, 0.4431f,0.1607f, 0.5f,   0.0f,1.0f,  0.0f,   0.0f,

		//R amarillo esquina inferior derecha
		0.437f, 0.031f, 0.5f,	 0.4117f, 0.3215f, 0.2313f, 1.0f,  1.0f,1.0f,  0.0f,   0.0f,  //56
		1.0f, 0.031f, 0.5f,		 0.4117f, 0.3215f, 0.2313f, 1.0f,  1.0f,0.0f,  0.0f,   0.0f,  
		0.437f, -0.943f, 0.5f,	 0.4117f, 0.3215f, 0.2313f, 1.0f,  0.0f,0.0f,  0.0f,   0.0f,  
		1.0f, -0.943f, 0.5f,	 0.4117f, 0.3215f, 0.2313f, 1.0f,  0.0f,1.0f,  0.0f,   0.0f,  

		//CAPA 6
		//R negro(encima del amarillo esquina inferior derecha)
		0.381f, 0.034f, 0.6f,	0.8549f, 0.6549f, 0.3176f, 1.0f,   1.0f,1.0f,  1.0f,   0.0f,  //60
		0.656f, 0.034f, 0.6f,	0.8549f, 0.6549f, 0.3176f, 1.0f,   1.0f,0.0f,  1.0f,   0.0f,  
		0.381f, -0.431f, 0.6f,	0.8549f, 0.6549f, 0.3176f, 1.0f,   0.0f,0.0f,  1.0f,   0.0f,  
		0.656f, -0.431f, 0.6f,	0.8549f, 0.6549f, 0.3176f, 1.0f,   0.0f,1.0f,  1.0f,   0.0f,  

		//R amarillo esquina inferior izquierda
		-1.0f, -0.781f, 0.6f,	0.7058f, 0.4784f, 0.4549f, 1.0f,   1.0f,1.0f,  0.0f,   0.0f,  //64
		-0.45f, -0.781f, 0.6f,  0.7058f, 0.4784f, 0.4549f, 1.0f,   1.0f,0.0f,  0.0f,   0.0f,  
		-1.0f, -0.912f, 0.6f,	0.7058f, 0.4784f, 0.4549f, 1.0f,   0.0f,0.0f,  0.0f,   0.0f,  
		-0.45f, -0.912f, 0.6f,	0.7058f, 0.4784f, 0.4549f, 1.0f,   0.0f,1.0f,  0.0f,   0.0f,  
		 
	};

	unsigned int indices[] = {
		//R1
		0,1,2,
		2,3,1,
		//R2
		4,5,6,
		6,7,5,
		//R3
		8,9,10,
		10,11,9,		
		//R4
		12,13,14,
		14,15,13,		
		//R5
		16,17,18,
		18,19,17,		
		//R6
		20,21,22,
		22,23,21,		
		//R7
		24,25,26,
		26,27,25,		
		//R8
		28,29,30,
		30,31,29,		
		//R grande negro
		32,33,34,
		34,35,33,		
		//R inclinado (mas arriba)
		36,37,38,
		38,39,37,		
		//C negro
		40,41,42,
		41,42,43,		
		//R inclinado(el de mas abajo)
		44,45,46,
		46,47,45,		
		//C gris
		48,49,50,
		49,50,51,		
		//Cuadrado negro delante del circulo
		52,53,54,
		53,54,55,
		//R amarillo esquina inferior derecha
		56,57,58,
		58,59,57,
		//R negro(encima del amarillo esquina inferior derecha)
		60,61,62,
		62,63,61,
		//R amarillo esquina inferior izquierda
		64,65,66,
		66,67,65

		
	};

	// How OpenGL will work with the format of textures
	GLCall( glEnable( GL_BLEND ) );
	GLCall( glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ) );

	VertexArray va; //EBO
	VertexBuffer vb( vertices, sizeof( vertices ) ); //VBO
	VertexBufferLayout layout;

	//lo del VertexArray.cpp aqui se llama
	// aqui el numerito es la layer(lo puedes ver en el vs)
	//3 de posiciones de cordenadas //4 de colores  //2 de textura   //1 de textura o no textura  //1 si es circulo oo no
	layout.push<float>( 3 ); //3 posiciones de los colores
	layout.push<float>( 4 ); //4 posiciones de colores
	layout.push<float>( 2 );//2 posiciones de texturas
	layout.push<float>( 1 );//1 d etextura o no textura
	layout.push<float>( 1 );//1 de si es circulo o no
	va.addBuffer( vb, layout );
	va.bind();

	IndexBuffer ib( indices, sizeof( indices ) );

	Shader mainShader( "res/shaders/template.vs", "res/shaders/template.fs" );

	// Just write the direction of your Texture
	// puedo definir hasta 32
	Texture texture1("C:/Users/Djcho/OneDrive/Documentos/ITAM/Semestre_7/Gráficas por Computadora/Códigos/AdvancedProjectComputerGraphics/Fotos/roca3.jpg");
	Texture texture2("C:/Users/Djcho/OneDrive/Documentos/ITAM/Semestre_7/Gráficas por Computadora/Códigos/AdvancedProjectComputerGraphics/Fotos/madera.jpg");
	// If you add more than 1 texture, need to add + 1 in the param per each bind call
	texture1.bind( 0 );
	texture2.bind( 1);


	Renderer renderer;

	glPolygonMode( GL_FRONT, GL_FILL );

	while( !glfwWindowShouldClose( window ) ) {
		float ratio;
		int width, height;
		glm::mat4x4 projection, model, view;

		glfwGetFramebufferSize( window, &width, &height );
		ratio = width / ( float ) height;

		glViewport( 0, 0, width, height );

		renderer.clear();

		glm::mat4 m( 1.0f );
		model = m;
		//model = glm::rotate( m, ( float ) glfwGetTime(), glm::vec3( 1.f ) ); //si no quiero que rote pones:   model = m;
		projection = glm::ortho( -ratio, ratio, -1.f, 1.f, 1.f, -1.f );


		mainShader.bind();
		mainShader.SetuniformsMat4f( "model", model );
		mainShader.setUniform1i( "ourTexture", 0 );
		mainShader.setUniform1i("ourTexture2", 1);

		renderer.draw( va, ib, mainShader );


		glfwSwapBuffers( window );
		glfwPollEvents();
	}

	glfwDestroyWindow( window );

	glfwTerminate();
	exit( EXIT_SUCCESS );
}
