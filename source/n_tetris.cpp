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
const int starting_point_y            = 2;

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
void clearFichaSide(int posX, int posY, int side, int tipoFicha);

void game_init(){
    seed();
    /* Para la correcta ejecución de este juego, debemos poner la consola en "fuente de mapa de bits" y 8x8 píxeles de tamaño */
    //Nuestra ventana molona bien grande
    ventanaConsola(anchoVentana/2, altoVentana/2, "iJosTris");
    //Establecemos los colores iniciales
    system("color F8");
    //Dibujamos los margenes
    //drawMargins();

    srand( time(NULL) );
}

int getFicha(){
   int rand = aleatorio(5) + 1;
   //cursorPos(20, 20);
   //printf("%d", rand);
   return rand;
}


void gameLoop(){
    char tecla;
    int posY = starting_point_y;
    int posX = starting_point_x;

    int ficha = getFicha();

    insertFicha(posX, posY, ficha); // ficha

    //Variables para el tiempo
    time_t t_ultimoTick;		// Tiempo desde la ultima vez que una pieza bajo
    time_t t_ahora;				// Tiempo actual
    t_ultimoTick = time(NULL);

    while( t_ahora - t_ultimoTick == 0 ){
        t_ultimoTick = time(NULL);
    }

    while(true) {
        /** debug del tiempo
        cursorPos(25, 20);
        printf("Ultimo -> %d", t_ultimoTick);
        cursorPos(25, 22);
        printf("Ahora  -> %d", t_ahora);
        **/



        if(kbhit()){
            fflush(stdin);
            tecla=getch();




            //printf("%d", game_area[posY][posX]);
            //clearBlock(posFicha_X, posFicha_Y, ficha_size);
            if(tecla == 80){ // Abajo
                if(ficha == 1){
                    if(game_area[posY + 3][posX] >= 9 || game_area[posY + 3][posX] == 1 || game_area[posY + 3][posX] == 2 || game_area[posY + 3][posX] == 3 || game_area[posY + 3][posX] == 4 || game_area[posY + 3][posX] == 5 || game_area[posY + 3][posX] == 6          ||         game_area[posY + 3][posX + 1] == 1 || game_area[posY + 3][posX + 1] == 2 || game_area[posY + 3][posX + 1] == 3 || game_area[posY + 3][posX + 1] == 4 || game_area[posY + 3][posX + 1] == 5 || game_area[posY + 3][posX + 1] == 6){ // +4, porque 4 es el alto de la ficha
                        posY = starting_point_y;
                        posX = starting_point_x;
                        ficha = getFicha();
                        insertFicha(posX, posY, ficha); // ficha
                    }else{
                        clearFichaSide(posX, posY, 1, ficha);
                        posY++;
                        insertFicha(posX, posY, ficha);
                    }
                }else if(ficha == 2){
                    if(game_area[posY + 4][posX] >= 9 || game_area[posY + 4][posX] == 1 || game_area[posY + 4][posX] == 2 || game_area[posY + 4][posX] == 3 || game_area[posY + 4][posX] == 4 || game_area[posY + 4][posX] == 5 || game_area[posY + 4][posX] == 6){
                        posY = starting_point_y;
                        posX = starting_point_x;
                        ficha = getFicha();
                        insertFicha(posX, posY, ficha); // ficha
                    }else{
                        clearFichaSide(posX, posY, 1, ficha);
                        posY++;
                        insertFicha(posX, posY, ficha);
                    }
                }else if(ficha == 3){
                    if(game_area[posY + 2][posX] >= 9 || game_area[posY + 2][posX] == 1 || game_area[posY + 2][posX] == 2 || game_area[posY + 2][posX] == 3 || game_area[posY + 2][posX] == 4 || game_area[posY + 2][posX] == 5 || game_area[posY + 2][posX] == 6     ||     game_area[posY + 2][posX + 1] == 1 || game_area[posY + 2][posX + 1] == 2 || game_area[posY + 2][posX + 1] == 3 || game_area[posY + 2][posX + 1] == 4 || game_area[posY + 2][posX + 1] == 5 || game_area[posY + 2][posX + 1] == 6){
                        posY = starting_point_y;
                        posX = starting_point_x;
                        ficha = getFicha();
                        insertFicha(posX, posY, ficha); // ficha
                    }else{
                        clearFichaSide(posX, posY, 1, ficha);
                        posY++;
                        insertFicha(posX, posY, ficha);
                    }
                }else if(ficha == 4){
                   if(game_area[posY + 3][posX] >= 9 || game_area[posY + 3][posX] == 1 || game_area[posY + 3][posX] == 2 || game_area[posY + 3][posX] == 3 || game_area[posY + 3][posX] == 4 || game_area[posY + 3][posX] == 5 || game_area[posY + 3][posX] == 6         ||       game_area[posY + 3][posX + 1] == 1 || game_area[posY + 3][posX + 1] == 2 || game_area[posY + 3][posX + 1] == 3 || game_area[posY + 3][posX + 1] == 4 || game_area[posY + 3][posX + 1] == 5 || game_area[posY + 3][posX + 1] == 6){ // +4, porque 4 es el alto de la ficha
                        posY = starting_point_y;
                        posX = starting_point_x;
                        ficha = getFicha();
                        insertFicha(posX, posY, ficha); // ficha
                    }else{
                        clearFichaSide(posX, posY, 1, ficha);
                        posY++;
                        insertFicha(posX, posY, ficha);
                    }
                }else if(ficha == 5 || ficha == 6){
                    if(game_area[posY + 2][posX] >= 9 || game_area[posY + 2][posX] == 1 || game_area[posY + 2][posX] == 2 || game_area[posY + 2][posX] == 3 || game_area[posY + 2][posX] == 4 || game_area[posY + 2][posX] == 5 || game_area[posY + 2][posX] == 6){
                        posY = starting_point_y;
                        posX = starting_point_x;
                        ficha = getFicha();
                        insertFicha(posX, posY, ficha); // ficha
                    }else{
                        clearFichaSide(posX, posY, 1, ficha);
                        posY++;
                        insertFicha(posX, posY, ficha);
                    }
                }

            }else if(tecla == 72){ // Arriba
                //posY--;
                //insertFicha(posX, posY, 1);
            }else if(tecla == 75){ // Izquierda

                if(game_area[posY][posX - 1] >= 9){

                }else{
                    posX--;
                    insertFicha(posX, posY, ficha);
                    clearFichaSide(posX, posY, 2, ficha);
                }
            }else if(tecla == 77){ // Derecha
                if(ficha == 2){
                    if(game_area[posY][posX + 1] >= 9){

                    }else{
                        clearFichaSide(posX, posY, 3, ficha);
                        posX++;
                        insertFicha(posX, posY, ficha);

                    }
                }else{
                    if(game_area[posY][posX + 2] >= 9){

                    }else{
                        clearFichaSide(posX, posY, 3, ficha);
                        posX++;
                        insertFicha(posX, posY, ficha);

                    }
                }


            }



        } // End kbhit


        // Gravedad
        t_ahora = time(NULL);		// Actualizamos el tiempo
        if ( t_ahora - t_ultimoTick > 0 ){ // Checkeamos si ha pasado 1 segundo desde la ultima caida de ficha (tick)
            clearFichaSide(posX, posY, 1, ficha);
            posY++;
            insertFicha(posX, posY, ficha);
            t_ultimoTick = time(NULL);		// Actualizamos el tiempo otra vez
        }

        /* WTF?! --> Esta parte para que servia?! ahora creo que para nada... :D
        // Checkeamos lo que hay debajo de la ficha, si toca el suelo o otra ficha, generamos una nueva
        if(ficha == 1 || ficha == 4){
            if(game_area[posY + 3][posX] >= 9 || game_area[posY + 3][posX] == 1){ // Toca suelo, generamos una nueva ficha
                posY = starting_point_y;
                posX = starting_point_x;
                ficha = getFicha();
                insertFicha(posX, posY, ficha); // ficha
            }
        }else if(ficha == 2){
            if(game_area[posY + 4][posX] >= 9 || game_area[posY + 4][posX] == 1){ // Toca suelo, generamos una nueva ficha
                posY = starting_point_y;
                posX = starting_point_x;
                ficha = getFicha();
                insertFicha(posX, posY, ficha); // ficha
            }
        }else if(ficha == 3){
            if(game_area[posY + 2][posX] >= 9 || game_area[posY + 2][posX] == 1){ // Toca suelo, generamos una nueva ficha
                posY = starting_point_y;
                posX = starting_point_x;
                ficha = getFicha();
                insertFicha(posX, posY, ficha); // ficha
            }
        }else if(ficha == 5 || ficha == 6){
            if(game_area[posY + 2][posX] >= 9 || game_area[posY + 2][posX] == 1){ // Toca suelo, generamos una nueva ficha
                posY = starting_point_y;
                posX = starting_point_x;
                ficha = getFicha();
                insertFicha(posX, posY, ficha); // ficha
            }

        }
        */

        //Redibujamos el area de juego
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
            }else if(game_area[j][i] == 1){ // Ficha 1 -> L
                setColors(8, 13);
                printf("%c", gameFicha_ascii_model);
            }else if(game_area[j][i] == 2){ // Ficha 2 -> I
                setColors(8, 12);
                printf("%c", gameFicha_ascii_model);
            }else if(game_area[j][i] == 3){ // Ficha 3 -> Cuadrado
                setColors(8, 14);
                printf("%c", gameFicha_ascii_model);
            }else if(game_area[j][i] == 4){
                setColors(8, 11);
                printf("%c", gameFicha_ascii_model);
            }else if(game_area[j][i] == 5){
                setColors(8, 10);
                printf("%c", gameFicha_ascii_model);
            }else if(game_area[j][i] == 6){
                setColors(8, 9);
                printf("%c", gameFicha_ascii_model);
            }else if(game_area[j][i] == 0){ // Vacio
                setColors(8, 15);
                printf(" ", game_area[j][i]);
            }

        }
       step++;
    }
    resetColors();
}

void clearFichaSide(int posX, int posY, int side, int tipoFicha){
    cursorPos(posX, posY-1);
    switch (tipoFicha){
        case 1:
            if(side == 1){ // Top
                for(int i = 0; i < 2; i++){
                    game_area[posY][posX] = 0;
                }
            }else if(side == 2){ // Right
                for(int i = 0; i < 3; i++){
                    game_area[posY + i][posX + 2] = 0;
                }
            }else if(side == 3){ //Left
                for(int i = 0; i < 3; i++){
                    game_area[posY + i][posX] = 0;
                }
            }
        break;
        case 2:
            if(side == 1){ // Top
                for(int i = 0; i < 1; i++){
                    game_area[posY][posX] = 0;
                }
            }else if(side == 2){ // Right
                for(int i = 0; i < 4; i++){
                    game_area[posY + i][posX + 1] = 0;
                }
            }else if(side == 3){ //Left
                for(int i = 0; i < 4; i++){
                    game_area[posY + i][posX] = 0;
                }
            }
        break;
        case 3:
            if(side == 1){ // Top
                for(int i = 0; i < 2; i++){
                    game_area[posY][posX+i] = 0;
                }
            }else if(side == 2){ // Right
                for(int i = 0; i < 2; i++){
                    game_area[posY + i][posX + 2] = 0;
                }
            }else if(side == 3){ //Left
                for(int i = 0; i < 2; i++){
                    game_area[posY + i][posX] = 0;
                }
            }
        break;
        case 4:
            if(side == 1){ // Top
                for(int i = 0; i < 2; i++){
                    game_area[posY][posX + i] = 0;
                }
            }else if(side == 2){ // Right
                for(int i = 0; i < 3; i++){
                    game_area[posY + i][posX + 2] = 0;
                }
            }else if(side == 3){ //Left
                for(int i = 0; i < 3; i++){
                    game_area[posY + i][posX] = 0;
                }
            }
        break;
        case 5:
            if(side == 1){ // Top
                for(int i = 0; i < 3; i++){
                    game_area[posY][posX + i] = 0;
                }
            }else if(side == 2){ // Right
                for(int i = 0; i < 3; i++){
                    game_area[posY + i][posX + 3] = 0;
                }
            }else if(side == 3){ //Left
                for(int i = 0; i < 3; i++){
                    game_area[posY + i][posX] = 0;
                }
            }
        break;
        case 6:
            if(side == 1){ // Top
                for(int i = 0; i < 3; i++){
                    game_area[posY][posX + i] = 0;
                }
            }else if(side == 2){ // Right
                for(int i = 0; i < 3; i++){
                    game_area[posY + i][posX + 3] = 0;
                }
            }else if(side == 3){ //Left
                for(int i = 0; i < 3; i++){
                    game_area[posY + i][posX] = 0;
                }
            }
        break;
    }
}

void insertFicha(int posX, int posY, int tipoFicha){
    switch (tipoFicha){
        case 1:
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 2; j++){
                    if(tetrominoe_1[i][j] == 1){
                        game_area[i + posY][j + posX] = 1;
                    }else{
                        game_area[i + posY][j + posX] = 0;
                    }
                }

            }
        break;
        case 2:
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 1; j++){
                    if(tetrominoe_2[i][j] == 1){
                        game_area[i + posY][j + posX] = 2;
                    }else{
                        game_area[i + posY][j + posX] = 0;
                    }
                }

            }
        break;
        case 3:
            for(int i = 0; i < 2; i++){
                for(int j = 0; j < 2; j++){
                    if(tetrominoe_3[i][j] == 1){
                        game_area[i + posY][j + posX] = 3;
                    }else{
                        game_area[i + posY][j + posX] = 0;
                    }
                }

            }
        break;
        case 4:
            for(int i = 0; i < 3; i++){
                for(int j = 0; j < 2; j++){
                    if(tetrominoe_4[i][j] == 1){
                        game_area[i + posY][j + posX] = 4;
                    }else{
                        game_area[i + posY][j + posX] = 0;
                    }
                }

            }
        break;
        case 5:
            for(int i = 0; i < 2; i++){
                for(int j = 0; j < 3; j++){
                    if(tetrominoe_5[i][j] == 1){
                        game_area[i + posY][j + posX] = 5;
                    }else{
                        game_area[i + posY][j + posX] = 0;
                    }
                }

            }
        break;
        case 6:
            for(int i = 0; i < 2; i++){
                for(int j = 0; j < 3; j++){
                    if(tetrominoe_6[i][j] == 1){
                        game_area[i + posY][j + posX] = 6;
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
