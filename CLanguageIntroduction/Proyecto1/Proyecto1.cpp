// Proyecto1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAXIMA_LONGITUD_TITULO 70
#define MAXIMA_LONGITUD_NOMBRE_APELLIDO 30


struct libro {
    int codigoDelLibro;
    char nombre[MAXIMA_LONGITUD_NOMBRE_APELLIDO];
    char apellido[MAXIMA_LONGITUD_NOMBRE_APELLIDO];
    char titulo[MAXIMA_LONGITUD_TITULO];
    int anoCompra;
    int cantUsuarioPrestado;
};

struct Nodo {
    struct libro* libro;
    struct Nodo* siguiente;
};

void los_libros(struct Nodo* lista) {
    struct Nodo* aux = lista;
    struct libro* l;

    if (lista == NULL) {
        printf("La lista está vacía");
        return;
    }

    printf("\n\nInformacion de los libros:\n");

    while (aux != NULL) {
        l = aux->libro;
        printf("\nCodigo del libro: %d\n", l->codigoDelLibro);
        printf("Titulo del libro: %s\n", l->titulo);
        printf("Nombre del autor: %s%s\n", l->nombre,l->apellido);
        printf("Ano de compra: %d\n", l->anoCompra);
        printf("Cantidad de usuarios que lo han pedido prestado: %d\n", l->cantUsuarioPrestado);

        aux = aux->siguiente;
    }
    return;
}

libro *crear_libro() {
    struct libro* l;

    l = (libro*)malloc(sizeof(libro));
    if (l == NULL) {
        printf("No hay memoria disponible");
        perror("No memoria:");
        exit(0);
    }

    //Se piden los datos para crear un libro
    //Se pide el nombre del libro primero:
    printf("\nAgregar datos para un libro\n");
    printf("Nombre del libro: ");
    fgets(l->titulo, MAXIMA_LONGITUD_TITULO, stdin);
    l->titulo[strlen(l->titulo) - 1] = '\0';

    //Se pide el nombre del autor:
    printf("Nombre del autor (sin el apellido): ");
    fgets(l->nombre, MAXIMA_LONGITUD_NOMBRE_APELLIDO, stdin);
    l->nombre[strlen(l->nombre) - 1] = '\0';

    //Se pide al apellido del autor
    printf("Apellido del autor: ");
    fgets(l->apellido, MAXIMA_LONGITUD_NOMBRE_APELLIDO, stdin);
    l->apellido[strlen(l->apellido) - 1] = '\0';

    //Se pide el año de compra
    printf("Ano de compra del libro: ");
    scanf_s("%d", & l->anoCompra);

    while (getchar() != '\n');

    //Se pide la cantidad de usuarios a los que se les ha prestado
    printf("Cantidad de veces prestado: ");
    scanf_s("%d", & l->cantUsuarioPrestado);

    while (getchar() != '\n');

    //El código del libro se toma de una valor generado aleatoriamente
    //srand(time(NULL));
    l->codigoDelLibro = rand();

    return l;
}

struct Nodo* insertar_libro(struct Nodo* lista) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    struct libro* nuevoLibro;
    // Manejar error de asignación de memoria
    if (nuevoNodo == NULL) {
        printf("No hay memoria");
        perror("No hay memoria");
        exit(0);
    }

    if(1)
        nuevoLibro = crear_libro();
    else {
        printf("No hay memoria");
        perror("No hay memoria");
        exit(0);
    }

    nuevoNodo->libro = nuevoLibro;
    nuevoNodo->siguiente = NULL;

    if (lista == NULL)
        return nuevoNodo;

    struct Nodo* aux1 = lista;
    struct Nodo* aux2 = lista->siguiente;

    if (aux1->libro->codigoDelLibro > nuevoLibro->codigoDelLibro) {
        nuevoNodo->siguiente = lista;
        return nuevoNodo;
    }

    bool band = true;

    while (band && aux2 != NULL) {
        if (/*aux1->libro->codigoDelLibro < nuevoLibro->codigoDelLibro &&*/ nuevoLibro->codigoDelLibro < aux2->libro->codigoDelLibro) {
            nuevoNodo->siguiente = aux2;
            aux1->siguiente = nuevoNodo;
            band = false;
        }
        aux1 = aux2;
        aux2 = aux2->siguiente;
    }

    if (band) 
        aux1->siguiente = nuevoNodo;
    
    return lista;
}

int num_libros(struct Nodo* lista) {
    struct Nodo* aux = lista;

    if (aux == NULL) {
        printf("La lista está vacía.");
        return 0;
    }

    int contador = 0;
    while (aux != NULL) {
        contador++;
        aux = aux->siguiente;
    }
    return contador;
}

int mostrar_libro(struct Nodo* lista, const char* titulo) {
    struct Nodo* aux = lista;
    struct libro* libro;

    if (aux == NULL) {
        printf("Error al buscar el libro: La lista está vacía");
        return -1;
    }

    bool band = true;

    while (aux != NULL && band) {
        libro = aux->libro;
        if (strcmp(libro->titulo,titulo)==0) {
            band = false;
            printf("\nCodigo del libro: %d\n", libro->codigoDelLibro);
            printf("Titulo del libro: %s\n", libro->titulo);
            printf("Nombre del autor: %s%s\n", libro->nombre, libro->apellido);
            printf("Ano de compra: %d\n", libro->anoCompra);
            printf("Cantidad de usuarios que lo han pedido prestado: %d\n", libro->cantUsuarioPrestado);
        }
        else
            aux = aux->siguiente;
    }

    if (band) {
        printf("No se encontro el libro");
        return -1;
    }
    else
        return 1;
}

struct Nodo* borrar_libro(struct Nodo* lista, const char* titulo) {
    struct Nodo* aux1 = lista;
    struct Nodo* aux2 = NULL;
    bool band = true;

    //Solo va a eliminar un libro, esto es, si hay dos libros con el mismo titulo
    // va a borrar unicamente el primero que encuentre. 
    while (aux1 != NULL && band) {
        if (strcmp(aux1->libro->titulo, titulo) == 0) {
            //Caso en que se encuentra al inicio de la lista
            if (aux2 == NULL)
                lista = aux1->siguiente;
            else //caso contrario
                aux2->siguiente = aux1->siguiente;

            //Libera el espacio en memoria
            free(aux1->libro);
            free(aux1);

            printf("\nEl libro con el titulo '%s' se ha eliminado. \n", titulo);
            
            band = false;            
        }
        else {
            aux2 = aux1;
            aux1 = aux1->siguiente;
        }
    }

    return lista;
}
    
int main()
{
    //Se hace la lista vacia
    struct Nodo* lista = NULL;

    //Se agregan cinco libros
    for(int i = 0; i <= 4; i++)
        lista = insertar_libro(lista);

    //printf("Lista3%p\n", (void*)lista);

    //Imprime todos los libros hasta el momento agregados
    //a a la lista. 
    los_libros(lista);

    //Imprime el numero de libros en la lista
    int res = num_libros(lista);
    printf("\nNumero de libros: %d\n", res);

    //Busca un libro con el titulo 
    const char *titulo = "Circe";
    mostrar_libro(lista, titulo);

    //Borra un libro con el titulo
    borrar_libro(lista, titulo);
    los_libros(lista);
}