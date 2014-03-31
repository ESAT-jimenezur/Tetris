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
void setColors();





void setColors(int texto, int fondo){
    colorTexto(texto, fondo);
}

void menu(){

    printf("*** ------------ *** iJosTris Admin Backend *** ------------ ***\n\n\n");

}

int main(){
    /* Para la correcta ejecución de este juego, debemos poner la consola en "fuente de mapa de bits" y 8x8 píxeles de tamaño */
    //Nuestra ventana molona bien grande
    ventanaConsola(150, 100, "iJoStratego");

    //Establecemos los colores iniciales
    setColors(0, 14);


    menu();

    return 0;
}
