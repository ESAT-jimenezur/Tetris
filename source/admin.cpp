#include <stdio.h>
#include <iJos.h>
#include<conio.h>
#include <string.h>



/* Definimos los m�todos necesarios */

/**
    Este m�todo se encarga de mostrar el menu por pantalla
**/
void menu();

/**
    Este m�todo se encarga de establecer los colores necesarios para la ejecucion
**/
void setColors();





void setColors(int texto, int fondo){
    colorTexto(texto, fondo);
}

void menu(){

    printf("*** ------------ *** iJosTris Admin Backend *** ------------ ***\n");

}

int main(){
    /* Para la correcta ejecuci�n de este juego, debemos poner la consola en "Lucida Console" y 8 p�xeles de tama�o */


    //Nuestra ventana molona bien grande
    ventanaConsola(155,73, "iJoStratego");

    //Establecemos los colores iniciales
    setColors(0, 14);


    menu();

    return 0;
}
