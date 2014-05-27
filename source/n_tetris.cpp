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

const int gameFicha_ascii_model       = 178;


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
void game_init();
void setColors(int texto, int fondo);
void resetColors();
void drawGameArea();
void insertFicha(int posX, int posY, int tipoFicha);
void gameLoop();
int getFicha();

void game_init(){
    seed();
    /* Para la correcta ejecución de este juego, debemos poner la consola en "fuente de mapa de bits" y 8x8 píxeles de tamaño */
    //Nuestra ventana molona bien grande
    ventanaConsola(anchoVentana/2, altoVentana/2, "iJosTris");
    //Establecemos los colores iniciales
    system("color F8");
    //Dibujamos los margenes
    //drawMargins();
}

int getFicha(){
   return aleatorio(6);
}


void gameLoop(){
    char tecla;
    int posY = 2;
    int posX = 4;

    int ficha = getFicha();

    insertFicha(posX, posY, 1); // ficha

    while(true) {

        if(kbhit()){
            fflush(stdin);
            tecla=getch();

            //clearBlock(posFicha_X, posFicha_Y, ficha_size);
            if(tecla == 80){ // Abajo
                posY++;
                insertFicha(posX, posY, 1);
            }else if(tecla == 72){ // Arriba
                posY--;
                insertFicha(posX, posY, 1);
            }else if(tecla == 75){ // Izquierda
                posX--;
                insertFicha(posX, posY, 1);
            }else if(tecla == 77){ // Derecha
                posX++;
                insertFicha(posX, posY, 1);
            }

        }

        drawGameArea();
    }


}

void drawGameArea(){
   int step = 0;
   for(int j = 0; j < gameInterface_size_height + (gameInterface_margin + 1); j++){
        cursorPos(starting_point_x - gameInterface_margin, starting_point_y + step);
        for(int i = 0; i < gameInterface_size_width + gameInterface_margin; i++){
            if(game_area[j][i] == 9 || game_area[j][i] == 8){
                //Margins (FC)
                setColors(12, 15);
                printf("%d", game_area[j][i]);
            }else if(game_area[j][i] == 1){ // Ficha 1
                setColors(8, 13);
                printf("%c", gameFicha_ascii_model);
             }else if(game_area[j][i] == 2){ // Ficha 2
                setColors(8, 12);
                printf("%c", gameFicha_ascii_model);
            }else if(game_area[j][i] == 0){ // Vacio
                setColors(8, 15);
                printf("0", game_area[j][i]);
            }

        }
       step++;
    }
    resetColors();
}

void insertFicha(int posX, int posY, int tipoFicha){
    switch (tipoFicha){
        case 1:
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    if(tetrominoe_1[i][j] == 1){
                        //printf("%c", gameFicha_ascii_model);
                        game_area[i + posY][j + posX] = 1;
                    }else{
                        game_area[i + posY][j + posX] = 0;
                    }
                }

            }
        break;
        case 2:
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    if(tetrominoe_2[i][j] == 1){
                        //printf("%c", gameFicha_ascii_model);
                        game_area[i + posY][j + posX] = 2;
                    }else{
                        game_area[i + posY][j + posX] = 0;
                    }
                }

            }
        break;
    }



}

void setColors(int texto, int fondo){
    colorTexto(texto, fondo);
}

void resetColors(){
    setColors(8, 15);
}

int main(){

    game_init();

    drawGameArea();

    gameLoop();

    return 0;
}
