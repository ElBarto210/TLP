#include <stdio.h>
#include <stdlib.h>
#define NODOFINAL 9
#define NODOINICIAL 8
#define SIZE 20

struct Transformation {
    char input;
    char output[10];

};

struct Transformation automata[10][10];
char target[10][10][10];

//matriz de nodos para almacenar su nombra y si son iniciales o finales
char nodos[SIZE][10];

int main(void){
//Variables
    FILE *ficheroAutomata;

    //caracter leido
    char c;

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

    int i=0;
    int j=0;
    int k=0;

//Inicializacion matrices
    for(i=0; i<SIZE; i++) {
        for(j=0; j<SIZE; j++) {
            nodos[i][j] = '#';
        }
    }

    for(i=0; i<SIZE; i++) {
        for(j=0; j<SIZE; j++) {
            automata[i][j].input = '#';
            for(k=0; k<10; k++) {
                automata[i][j].output[k] = '#';
                target[i][j][k] = '#';
            }
        }
    }

//Abrir fichero para lectura
    ficheroAutomata = fopen("automata.txt", "r");

    if (ficheroAutomata == NULL) {
            printf("File not Found");
    }

    while ((c = fgetc(ficheroAutomata)) != EOF) {
//Preparacion para leer nuevo nodo
        if(nuevoNodo == 0){
            if(c == ';') {
                terminarNuevoNodo = 1;
                indiceNombreNodo = 0;
                indiceNodo++;
                leerNodo = 0;
                indiceTransformacion = 0;
            }
            else if (c == '\n'){
                destino = 0;
            }
            else if(c != '\n' && terminarNuevoNodo == 1) {
                nuevoNodo = 1;
            }

        }

//Encontrar nodos del automata
        if(nuevoNodo == 1) {
            if(c == 'O') {
                nodos[indiceNodo][NODOFINAL] = '1';                          //Nodo
                if(nodos[indiceNodo][NODOINICIAL]!= '1')
                    nodos[indiceNodo][NODOINICIAL] = '0';
            }
            else if(c == '>') {
                nodos[indiceNodo][NODOINICIAL] = '1';                        //Nodo inicial
            }
            else if(c != '\n') {
                nodos[indiceNodo][indiceNombreNodo] = c;                     //Nombre del nodo
                indiceNombreNodo++;
            }
            else {
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
                indiceNombreNodo = 0;
            }
            else if(destino == 1){
                target[indiceNodo][indiceTransformacion][indiceNombreNodo] = c;
                indiceNombreNodo++;
            }
            else if(c != '\n'){
                if(input == 1){
                    automata[indiceNodo][indiceTransformacion].input = c;
                }
                else {
                    automata[indiceNodo][indiceTransformacion].output[indiceNombreNodo] = c;
                }
                indiceNombreNodo++;
            }
            else if (automata[indiceNodo][0].input != '#'){
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
            if(nodos[i][j] != '#')
                printf("%c",nodos[i][j]);
            j++;
        }
        if(nodos[i][j-1] != '#')
            printf("\n");
        i++;
        j=0;
    }
    printf("\n\n");
    printf("transformaciones\n");
    i=0;
    j=0;
    k=0;
    while(i<10){
        printf("nodo %i\n", i);
        while(j<10){
            if(automata[i][j].input != '#'){
                printf("%c ", automata[i][j].input);
                printf("/");
            }
            while(k<10){
                if(automata[i][j].output[k] != '#')
                    printf(" %c", automata[i][j].output[k]);
                k++;
            }
            k=0;
            if(automata[i][j].output[k] != '#')
                printf("; destino: ");
            while(k<10){
                if(target[i][j][k] != '#')
                    printf("%c ", target[i][j][k]);
                k++;
            }
            if(automata[i][j].output[k] != '#')
                printf("\n");
            j++;
            k = 0;
        }
        printf("\n");
        i++;
        j = 0;
    }

//Cierre de fichero
    fclose(ficheroAutomata);

    //El tamanio máximo de la palabra a traducir es de 30 caracteres
    //char palabra[30];
    //printf("Introduce la palabra a traducir:");
    //scanf("%s", palabra);

 //   traducir(palabra);
    return 0;
}


void traducir( char palabra[]) {
    int index = 0;
    char c;
    int estadoActual = 0;
    int abortado = 0;

    while(palabra[index] != '\0' && abortado == 0) {
        c = palabra[index];

        int encontrada = 0;

        for(int i=0; i<SIZE || encontrada == 0; i++){

            if(automata[estadoActual][i].input == c) {
                encontrada = 1;
                printf("%s", automata[estadoActual][i].output);

                estadoActual = i;
                index++;

                if(nodos[estadoActual][NODOFINAL] == '1' && c == '\0')
                    printf("\nTraduccion finalizada.");
            }

            else if (i==SIZE-1) {
                printf("Proceso abortado");
                abortado = 1;
            }
        }
    }
}

