#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray() {
	GLCall( glGenVertexArrays( 1, &rendererId ) );
}

VertexArray::~VertexArray() {
	GLCall( glDeleteVertexArrays( 1, &rendererId ) );
}

void VertexArray::bind() const {
	GLCall( glBindVertexArray( rendererId ) );
}

void VertexArray::unBind() const {
	GLCall( glBindVertexArray( 0 ) );
}
//aqui le hara un bind de la clase vertex array y un bind de la de vertex buffer
void VertexArray::addBuffer( VertexBuffer& vb, const VertexBufferLayout& layout ) {
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	//itera sobre cada uno de los elementos de la capa. Para decirle las caracteristicas dek vertex array
	//esto sustituye al glVertexAttribPointer.........   (La parte que tiene
	for( unsigned int i = 0; i < elements.size(); i++ ) {
		const auto& element = elements[ i ];
		GLCall( glEnableVertexAttribArray( i ) );
		//indica como funciona cada una de las capas. getStrinde te dice tu stride
		GLCall( glVertexAttribPointer( i, element.count, element.type, element.normalized, layout.getStrinde(), ( const void* ) offset ) );
		offset += element.count * VertexBufferElement::getSizeOfType( element.type );
	}
}
