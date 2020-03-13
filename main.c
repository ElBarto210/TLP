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

char target[10][10][8];

//matriz de nodos para almacenar su nombra y si son iniciales o finales
char nodos[SIZE][10];

int indexTraduccion = -1;

int main(void){
    printf("AUTOMATA:\n");
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
    ficheroAutomata = fopen("automata_2.txt", "r");

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

//Cierre de fichero
    fclose(ficheroAutomata);

    //El tamanio máximo de la palabra a traducir es de 30 caracteres
    char palabra[30];
    printf("\nIntroduce la palabra a traducir:");
    scanf("%s", palabra);
    traducir(palabra);
    return 0;
}

int buscarTarget(char palabra[]){
    int i = 0;
    int j = 0;
    int encontrado = 0;
    while(i<SIZE && encontrado == 0){
        encontrado = 1;

        while(j<8 && encontrado == 1){
            if(nodos[i][j]!='#' && palabra[j] != '#'){
                if(nodos[i][j] != palabra[j]){
                    encontrado = 0;
                }
            }
            j++;
        }
        j=0;
        if(encontrado == 1){
            indexTraduccion = i;
        }
        i++;
    }
    return indexTraduccion;
}

void traducir(char palabra[]) {
    int index = 0;
    char c;
    int estadoActual = 0;
    int abortado = 0;
    printf("Traduccion: ");

    while(palabra[index] != '\0' && abortado == 0) {
        c = palabra[index];
        int encontrada = 0;

        for(int i=0; i<SIZE && encontrada == 0; i++){

            if(automata[estadoActual][i].input == c) {
                encontrada = 1;
                for(int j = 0; j<10 && automata[estadoActual][i].output[j] != '#'; j++)
                    if(automata[estadoActual][i].output[j] != '_')
                        printf("%c", automata[estadoActual][i].output[j]);

                estadoActual = buscarTarget(target[estadoActual][i]);

                if (estadoActual == -1){
                    printf("No pertenece la palabra al alfabeto");
                    abortado = 1;
                }
                index++;

                if(nodos[estadoActual][NODOFINAL] == '1' && palabra[index] == '\0')
                    printf("\nTraduccion finalizada.");
                else {
                    printf("\nLa palabra introducida no pertenece al alfabeto, proceso abortado");
                    abortado = 1;
                }
            }
        }

        if (encontrada == 0) {
                printf("\nProceso abortado");
                abortado = 1;
        }

    }
}
