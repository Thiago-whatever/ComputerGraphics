#pragma once

#include <vector>
#include <glad/glad.h>

#include "Renderer.h"
//esto es par aocupar el GL-FLOAT, lo puedes ocupar con cualquiera
struct VertexBufferElement {
	unsigned int type;
	unsigned int count;//cuenta cuantos elementos que tendria una capa
	unsigned char normalized; //GL_FALSE
	//aqui me sirve para regresarme sizeof(float) que va en el glVertexAttribPointer
	static unsigned int getSizeOfType( unsigned int type ) {
		switch( type ) {
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT( false );
		return 0;
	}
};

class VertexBufferLayout {
private:
	//vector - es para almacenar las cosas
	std::vector<VertexBufferElement> elements;
	unsigned int stride;//que tan ancho va a ser(cantidad de elementos por renglon aunque sena de diferentes capas(vertices,colores,texturas)).
public:
	//aqui no tenemos ni una sola capa
	VertexBufferLayout() : stride( 0 ) {};

	//push de cada capa
	template<typename T>
	void push( unsigned int count ) {
		static_assert( false );
	}

	//sus variantes
	template<>
	void push<float>( unsigned int count ) {
		elements.push_back( { GL_FLOAT, count, GL_FALSE } ); //tipo,contador,si esta normalizado
		stride += count * VertexBufferElement::getSizeOfType( GL_FLOAT ); // esto hace que el #*sizeof(float)
	}

	template<>
	void push<unsigned int>( unsigned int count ) {
		elements.push_back( { GL_UNSIGNED_INT, count, GL_FALSE } );
		stride += count * VertexBufferElement::getSizeOfType( GL_UNSIGNED_INT );
	}

	template<>
	void push<unsigned char>( unsigned int count ) {
		elements.push_back( { GL_UNSIGNED_BYTE, count, GL_TRUE } );
		stride += count * VertexBufferElement::getSizeOfType( GL_UNSIGNED_BYTE );
	}

	inline const std::vector<VertexBufferElement> getElements() const { return elements; }; //
	inline unsigned int getStrinde() const { return stride; }
};