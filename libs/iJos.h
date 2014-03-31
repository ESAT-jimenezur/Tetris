/*--------------------------------*/
/*        iJos Public Lib         */
/*--------------------------------*/

#include <time.h>
#include <windows.h>
#include <locale.h>



/**       Funcion Sumar         **/
/**--------------------------------
    @Params float a;
            float b;
    @return float a + b
----------------------------------*/
float sumar(float a, float b){
    return a + b;
}


/**       Funcion Restar         **/
/**--------------------------------
    @Params float a;
            float b;
    @return float a - b
----------------------------------*/
float restar(float a, float b){
    return a - b;
}


/**       Funcion Factorial      **/
/**--------------------------------
    @Params float a;
    @return float a * factorial(a-1)
----------------------------------*/
float factorial(float a){
    if(a == 1){
        return 1;
    }else{
        return a * factorial(a - 1);
    }
}


/**       Funcion Potencia      **/
/**--------------------------------
    @Params float a;
            float b
    @return float c
----------------------------------*/
float potencia(float a, float b){
    if(b == 1){
        return a;
    }else{
        return a * potencia(a, b-1);
    }
}


/**    Llenar matriz aleatoria   */
/**--------------------------------
    @Params int matriz[x][y];
----------------------------------*/
/*
void llenarMatrizAleatoria(int matriz[x][y]){
    int nAle = 0;
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            nAle = aleatorio(100);
            matriz[i][j] = nAle;
        }
    }
}
*/

/**        Imprimir Matriz       */
/**--------------------------------
    @Params int matriz[x][y];
----------------------------------*/
/*
void imprimirMatriz(int matriz[x][y]){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            printf("%.3d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("---------------------------------------\n");
}
*/


/**        Sumar Matrices        */
/**--------------------------------
    @Params int matriz_A[x][y];
            int matriz_B[x][y];
            int suma[x][y];
----------------------------------*/
/*
void sumarMatrices(int matriz_A[x][y], int matriz_B[x][y], int suma[x][y]){
    for(int i = 0; i < x; i++){
        for(int j = 0; j < y; j++){
            suma[i][j] =  matriz_A[i][j] + matriz_B[i][j];
        }
    }
}
*/




/**--------------------------------
/**         U T I L S

    require:    <stdlib.h>
                <time.h>
                                **/
/**--------------------------------

/**       Create Seed            **/
/**------------------------------*/
void seed(){
    srand (time(NULL));
}


/**       Funcion aleatorio      **/
/**--------------------------------
    @return int a
----------------------------------*/

int aleatorio(int a){

    int b;
    b = (rand()% a);
    return b;

}





/**--------------------------------
/**         S C R E E N

    require:    <windows.h>
--------------------------------**/
void colorTexto(int texto, int fondo){
    int color;

    color = (texto * 16) + fondo;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void cursorPos(int x, int y){
    COORD coor = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
}

void ventana(int x, int y, int ancho, int alto, bool relieve){

    int i,j;
cursorPos(x,y);printf("%c",218);for(i=1;i<ancho-1;i++) printf("%c",196);printf("%c",191);
for(i=1;i<alto;i++)
{cursorPos(x,y+i);printf("%c",179);cursorPos(x+ancho-1,y+i);printf("%c",179);}
 cursorPos(x,y+alto);printf("%c",192);for(i=1;i<ancho-1;i++) printf("%c",196);printf("%c",217);

}

void parrilla(int x, int y, int filas, int columnas, int ancho, int alto, int espacioF, int espacioC){
    int i,j;

    for(i=0; i < filas; i++){
        for(j=0; j < columnas; j++){
            ventana(x+j*(ancho+espacioC), y+i*(alto+espacioF), ancho, alto, false);
        }
    }
}


void ventanaConsola(int columnas, int lineas, char *Titulo){
    char linea[250]="",temp[]="";
    strcpy(linea,"title ");strcat(linea,Titulo);system(linea);
    strcpy(linea,"MODE CON cols=");itoa(columnas,temp,10);strcat(linea,temp);itoa(lineas,temp,10);strcat(linea," lines=");strcat(linea,temp);
    system(linea);
}
