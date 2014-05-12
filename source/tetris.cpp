#include <stdio.h>
#include <iJos.h>
#include<conio.h>
#include <string.h>
#include <dictionary.h>
#include <tetrominoes.h>





/* Public Vars */
const int anchoVentana      = 150;
const int altoVentana       = 100;

const int gameInterface_size_width    = 20;
const int gameInterface_size_height   = 10;
const int gameInterface_size_margin   = 2;
const int gameInterface_position_X    = 10;
const int gameInterface_position_Y    = 10;

const int gameFicha_ascii_model       = 178;

const int ficha_size                  = 4;
int currentFicha_X                    = 0;
int currentFicha_Y                    = 0;

int game_zone_table[gameInterface_size_width][gameInterface_size_height];



/* Definimos los métodos necesarios */

/**
    Este método se encarga de mostrar el menu por pantalla
**/
void menu();

/**
    Este método se encarga de establecer los colores necesarios para la ejecucion
**/
void setColors(int texto, int fondo);
void drawGameInterface(int posX, int posY, int size);
void insertFicha(int game_zone_table_X, int game_zone_table_Y);
void drawFicha(int posX, int posY, int tipoFicha);
void clearBlock(int posX, int opsY, int size);

void loader_game_zone_table(){
    for(int i = 0; i < gameInterface_size_width; i++){
        for(int j = 0; j < gameInterface_size_height; j++){
            game_zone_table[i][j] = 0;
        }
    }
}


void convierteTextoAASCII(int posX, int posY, char* titulo){

    cursorPos(posX, posY);

    // Tratar cadena para descomprimir por caracter
    // Convertir cada caracter a ASCII
    // Imprimir caracter en ascii

    for(int le = 0;  le < strlen(titulo); le++){
        printf("%c", titulo[le]);
        // Aqui convertimos
        /*
        for(int i = 0; i < 7; i++){
            for(int j = 0; j < 5; j++){
                //A[i][j]


                if(letra[i][j] == 1){
                    printf("%c", 219);
                }else{
                    printf(" ");
                }

            }

            posY++;
            printf("\n");
            cursorPos(posX, posY);
        }
        */

    }

}

void pantallaJuego(){
    // Este metodo se llama 1 vez y pinta toda la zona de juego
    // Establecemos el color de fondo
    system("color 80");

    char titulo[10] = "Tetris";


    //Cargamos el array de juego
    loader_game_zone_table();

    //convierteTextoAASCII(anchoVentana/2 - (strlen(titulo)/2), 2, titulo);

    //insertFicha(0, 0);
    drawGameInterface(gameInterface_position_X, gameInterface_position_Y, ficha_size);
    //YEAH --> drawFicha(0, 0, 1);
    drawFicha(10,10,1);

    // Tiempo Inicial
    struct tm *HoraFechaActual;
    time_t tiempo=time(NULL);
    int hh_ini,mm_ini,ss_ini;
    char tecla;
    time (&tiempo);
    HoraFechaActual = localtime(&tiempo);

    hh_ini=HoraFechaActual->tm_hour;
    mm_ini=HoraFechaActual->tm_min;
    ss_ini=HoraFechaActual->tm_sec;

    int drawPos_y = 0;
    int posFicha_X = 10;
    int posFicha_Y = 10;
    while(true) {

        //Calculamos la diferencia de tiempos
        time_t tiempo=time(NULL);
        time (&tiempo);
        struct tm *HoraSiguiente = localtime(&tiempo);

        //Esta es la estructura
        //hh=HoraFechaActual->tm_hour;
        //mm=HoraFechaActual->tm_min;
        //ss=HoraFechaActual->tm_sec;


        /*  Auto movimiento
        int t_diff = 0;
        if((HoraSiguiente->tm_sec - ss_ini) + t_diff == 1){
            drawFicha(0, drawPos_y, 1);
            drawPos_y ++;
            clearLine(0, ficha_size);
            t_diff++;
        }
        */


        /* TO-DO*/
        if(kbhit()){
            fflush(stdin);
            tecla=getch();

            clearBlock(posFicha_X, posFicha_Y, ficha_size);
            //printf("%d %d", posFicha_X, posFicha_Y);
            if(tecla == 80){ // Abajo
                posFicha_Y++;
                drawFicha(posFicha_X, posFicha_Y, 1);
            }else if(tecla == 72){ // Arriba
                posFicha_Y--;
                drawFicha(posFicha_X, posFicha_Y, 1);
            }else if(tecla == 75){ // Izquierda
                posFicha_X--;
                drawFicha(posFicha_X, posFicha_Y, 1);
            }else if(tecla == 77){ // Derecha
                posFicha_X++;
                drawFicha(posFicha_X, posFicha_Y, 1);
            }

        }

    }
}

void drawGameInterface(int posX, int posY, int size = 1){

    cursorPos(posX, posY);

    int controller_width = 0;
    for(int i = 0; i < (gameInterface_size_width + gameInterface_size_margin) * size; i++){

        int controller_height = 0;
        for(int j = 0; j < (gameInterface_size_height + gameInterface_size_margin) * size; j++){

            /*if(i == 0 || i == 21 || j == 0 || j == 11){
                //setColors(0, 12);
            }else{
                //setColors(0, 14);
            }*/
            setColors(0, 14);
            /*

            if(game_zone_table[controller_width][controller_height] == 1){
                setColors(0, 9);
            }else{
                setColors(0, 14);
            }

            printf("%d", game_zone_table[controller_width][controller_height]);
            controller_height++;
            */
            printf(" ");

        }

        printf("\n");

        posY++;
        controller_width++;
        cursorPos(posX, posY);
    }

}
/*
void insertFicha(int game_zone_table_X, int game_zone_table_Y){
    //La metemos en el array
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 5; j++){
            if(game_zone_table[i+game_zone_table_X][j+game_zone_table_Y] == 0){ // Este if puede servir para no chafar fichas
                game_zone_table[i+game_zone_table_X][j+game_zone_table_Y] = tetrominoe_1[i][j];
            }else{

            }

        }
    }

    currentFicha_X = game_zone_table_X;
    currentFicha_Y = game_zone_table_Y;
}
*/

void clearBlock(int posX, int posY, int size){

    int localX = posX + gameInterface_position_X + gameInterface_size_margin;
    int localY = posY + gameInterface_position_Y + gameInterface_size_margin;

    cursorPos(localX, localY);
    //printf("%d %d", posX, posY);
    for(int i = posY-1; i < posY+7; i++){
        for(int j = posX-1; j < posX+5; j++){
            printf(" ");
        }
        printf("\n");
        localY++;
        cursorPos(localX, localY);
    }


}

void drawFicha(int posX, int posY, int tipoFicha){
    // Pasamos coordenadas globales a locales
    int localX = posX + gameInterface_position_X + gameInterface_size_margin;
    int localY = posY + gameInterface_position_Y + gameInterface_size_margin;


    setColors(0, 14);
    cursorPos(localX, localY);

    switch (tipoFicha){
        case 1:
            // START L
            for(int i = 0; i < 7; i++){
                for(int j = 0; j < 5; j++){
                    if(tetrominoe_1[i][j] == 1){
                        printf("%c", gameFicha_ascii_model);
                    }
                }
                printf("\n");
                localY++;
                cursorPos(localX, localY);
            }
            // END L
        break;

    }



}

void setColors(int texto, int fondo){
    colorTexto(texto, fondo);
}

void menu(){
    //ventana(0, 0, 4, 3, 0);

}



int main(){
    /* Para la correcta ejecución de este juego, debemos poner la consola en "fuente de mapa de bits" y 8x8 píxeles de tamaño */
    //Nuestra ventana molona bien grande
    ventanaConsola(anchoVentana, altoVentana, "iJosTris");

    //Establecemos los colores iniciales
    setColors(0, 14);

    pantallaJuego();
    /*
    for(int i = 1; i < 255; i++){
        printf("%d -> %c \n", i, i);
    }
    */



    //menu();

    getch();
    return 0;
}



