#include <stdio.h>
#include <stdlib.h>
#define NODOFINAL 9
#define NODOINICIAL 8
#define SIZE 20

struct Transformation {
    char input[10][10];
    char output[10][10];
};

int main(void)
{
//Variables
    FILE *automata;

    //caracter leido
    char c;

    //matriz de nodos
    char nodos[10][10];

    //Indicador de NuevoNodo
    int nuevoNodo = 1;

    //Indicador para terminar de leer un nodo y comenzar uno nuevo
    int terminarNuevoNodo = 0;

    //Indice de nombre nodo: 8=nodo inicial, 9=nodo final, resto nombre nodo
    int indiceNombreNodo = 0;

    //Indice nodo
    int indiceNodo = 0;

    //Comenzar lectura
    int leerNodo = 0;

    //Lectura nodo: 1 leer input, 0 leer output
    int input = 1;

    //Indice para el conteo de trasnformaciones posibles
    int indiceTransformacion = 0;

    int destino = 0;

    //Matriz del automata traductor
    int matrizAutomata[SIZE][SIZE];

    struct Transformation t[10];

    int i = 0;
    int j = 0;
    int k = 0;

//Inicializacion matrices
    while(i<10) {
        while(j<10) {
            nodos[i][j] = '0';
            j++;
        }
        i++;
        j = 0;
    }

    i=0;
    j=0;
    while(i<SIZE) {
        while(j<SIZE) {
            matrizAutomata[i][j] = 0;
            j++;
        }
        i++;
        j = 0;
    }
    i = 0;
    j = 0;
    k = 0;

    while(i<10){
        while(j<10){
            while(k<10){
                t[i].input[j][k] = '0';
                t[i].output[j][k] = '0';
                k++;
            }
            j++;
            k = 0;
        }
        i++;
        j = 0;
    }
//Abrir fichero para lectura
    automata = fopen("automata.txt", "r");

    if (automata == NULL) {
            printf("File not Found");
    }

    while ((c = fgetc(automata)) != EOF) {
//Preparacion para leer nuevo nodo
        if(nuevoNodo == 0){
            if(c == ';') {
                terminarNuevoNodo = 1;
                indiceNombreNodo = 0;
                indiceNodo++;
                leerNodo = 0;
            }
            else if (c == '\n'){
                destino = 0;
            }
            else if(c != '\n' && terminarNuevoNodo == 1) {
                nuevoNodo = 1;
                printf("nuevo nodo");
            }

        }

//Encontrar nodos del automata
        if(nuevoNodo == 1) {
            if(c == 'O') {
                nodos[indiceNodo][NODOFINAL] = '1';                          //Nodo final
            }
            else if(c == '>') {
                nodos[indiceNodo][NODOINICIAL] = '1';                        //Nodo inicial
            }
            else if(c != '\n') {
                nodos[indiceNodo][indiceNombreNodo] = c;                     //Nombre del nodo
                indiceNombreNodo++;
            }
            else {
                printf("leyendo nodo");
                nodos[indiceNodo][indiceNombreNodo] = ' ';                   //Final nombre del nodo
                nuevoNodo = 0;
                terminarNuevoNodo = 0;
                leerNodo = 1;
                indiceNombreNodo = 0;
            }
        }
//lectura nodo
        if(leerNodo == 1){
            if(c == '/'){
                input = 0;
                indiceNombreNodo = 0;
            }
            else if(c == '>'){
                input = 1;
                destino = 1;
            }
            else if(destino == 1){
                    //tratamiento de destino
            }
            else if(c != '\n'){
                if(input == 1){
                    printf("\ninsertando %c en input\n", c);
                    t[indiceNodo].input[indiceTransformacion][indiceNombreNodo] = c;
                }
                else {
                    printf("\ninsertando %c en output\n", c);
                    t[indiceNodo].output[indiceTransformacion][indiceNombreNodo] = c;
                }
                indiceNombreNodo++;
            }
            else {
                indiceTransformacion++;
            }


        }
//Debug
        printf("%c", c);

    }

    printf("\n\nNODOS: \n");
    i=0;
    j=0;
    while(i<10) {
        while(j<10) {
            printf("%c",nodos[i][j]);
            j++;
        }
        printf("\n");
        i++;
        j=0;
    }
    printf("\n\n");
    i=0;
    j=0;
    while(i<SIZE) {
        while(j<SIZE) {
            printf("%i", matrizAutomata[i][j]);
            j++;
        }
        printf("\n");
        i++;
        j = 0;
    }
    printf("transformaciones\n");
    i=0;
    j=0;
    k=0;
    while(i<10){
        printf("nodo %i\n", i);
        while(j<10){
            while(k<10){
                printf("%c ", t[i].input[j][k]);
                k++;
            }
            k = 0;
            printf("/");
            while(k<10){
                printf(" %c"), t[i].output[j][k];
                k++;
            }
            printf("\n");
            j++;
            k = 0;
        }
        printf("\n");
        i++;
        j = 0;
    }

    printf("\nI miss Python already");
//Cierre de fichero
    fclose(automata);
    return 0;
}
