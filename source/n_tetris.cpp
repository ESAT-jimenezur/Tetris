#include <stdio.h>
#include <iJos.h>
#include<conio.h>
#include <string.h>
#include <dictionary.h>
#include <tetrominoes.h>

/* Public Global Vars */
const int anchoVentana                = 150;
const int altoVentana                 = 100;

const int gameInterface_size_height   = 20;
const int gameInterface_size_width    = 10;
const int gameInterface_margin        = 2;

const int starting_point_x            = 5;
const int starting_point_y            = 5;


int game_area[23][12] = {
    9,8,8,8,8,8,8,8,8,8,8,9,
    9,8,8,8,8,8,8,8,8,8,8,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,0,0,0,0,0,0,0,0,0,0,9,
    9,9,9,9,9,9,9,9,9,9,9,9
};


/* Method declarations */
void setColors(int texto, int fondo);
void resetColors();
void drawMargins();
void drawGameArea();

void drawMargins(){
    bool rellenar = 0;
    int step = 0;

    //Top side
    cursorPos(starting_point_x, starting_point_y);
    for(int i = 0; i < gameInterface_size_width; i++){
            printf("9");
    }
    //Left side
    for(int i = 0; i < gameInterface_size_height; i++){
        cursorPos(starting_point_x, starting_point_y + step);
        printf("9\n");
        step++;
    }
    //Right side
    step = 0;
    for(int i = 0; i <= gameInterface_size_height; i++){
        cursorPos(starting_point_x + gameInterface_size_width, starting_point_y + step);
        printf("9\n");
        step++;
    }
    //Bottom side
    cursorPos(starting_point_x, starting_point_y + gameInterface_size_height);
    for(int i = 0; i < gameInterface_size_width; i++){
        printf("9");
    }

    //Si esta a 1, rellenamos el area de juego con espacios vacios
    if(rellenar){
        step = 0;
        for(int j = 0; j < (gameInterface_size_height - 5); j++){
            cursorPos(starting_point_x + 1, starting_point_y + 1 + step);
            for(int i = 0; i < gameInterface_size_width - 1; i++){
                printf(" ");
            }
           step++;
        }

    }

}

void drawGameArea(){
   int step = 0;
   for(int j = 0; j < gameInterface_size_height + (gameInterface_margin + 1); j++){
        cursorPos(starting_point_x - gameInterface_margin, starting_point_y + step);
        for(int i = 0; i < gameInterface_size_width + gameInterface_margin; i++){
            if(game_area[j][i] == 9){
                //Margins (FC)
                setColors(12, 15);
            }else{
                //Game content
                setColors(8, 15);
            }
            printf("%d", game_area[j][i]);
        }
       step++;
    }
    resetColors();
}

void setColors(int texto, int fondo){
    colorTexto(texto, fondo);
}

void resetColors(){
    setColors(8, 15);
}

int main(){
    /* Para la correcta ejecución de este juego, debemos poner la consola en "fuente de mapa de bits" y 8x8 píxeles de tamaño */
    //Nuestra ventana molona bien grande
    ventanaConsola(anchoVentana/2, altoVentana/2, "iJosTris");

    //Establecemos los colores iniciales
    system("color F8");
    //Dibujamos los margenes
    //drawMargins();
    drawGameArea();



    return 0;
}
