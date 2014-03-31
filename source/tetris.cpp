#include <stdio.h>
#include <iJos.h>
#include<conio.h>
#include <string.h>



/* Definimos los métodos necesarios */

/**
    Este método se encarga de mostrar el menu por pantalla
**/
void menu();

/**
    Este método se encarga de establecer los colores necesarios para la ejecucion
**/
void setColors(int texto, int fondo);

void drawScreen(int posX, int posY){

    //cursorPos(posX, posY);

    for(int i = 0; i < 22; i++){
        for(int j = 0; j < 12; j++){
            if(i == 0 || i == 21 || j == 0 || j == 11){
                setColors(0, 12);
            }else{
                setColors(0, 14);
            }
            printf("0");
        }
        printf("\n");
    }
}



void setColors(int texto, int fondo){
    colorTexto(texto, fondo);
}

void menu(){

    //printf("*** ------------ *** iJosTris Admin Backend *** ------------ ***\n\n\n");

    //ventana(0, 0, 4, 3, 0);

}

void test(){

}

int main(){
    /* Para la correcta ejecución de este juego, debemos poner la consola en "fuente de mapa de bits" y 8x8 píxeles de tamaño */
    //Nuestra ventana molona bien grande
    ventanaConsola(150, 100, "iJoStratego");

    //Establecemos los colores iniciales
    setColors(0, 14);

    drawScreen(10, 10);

    //menu();

    return 0;
}



