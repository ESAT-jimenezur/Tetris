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

    printf("*** ------------ *** iJosTris Admin Backend *** ------------ ***\n");

}

int main(){
    /* Para la correcta ejecución de este juego, debemos poner la consola en "Lucida Console" y 8 píxeles de tamaño */


    //Nuestra ventana molona bien grande
    ventanaConsola(155,73, "iJoStratego");

    //Establecemos los colores iniciales
    setColors(0, 14);


    menu();

    return 0;
}
