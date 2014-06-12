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

//Rotacion
int rotacion_grados_ficha_actual      = 0;

int CREDITOS = 0;

// Puntos
int PUNTOS                            = 0; // Iniciamos los puntos a 0
int PUNTOS_LINEA                      = 10;
int PUNTOS_TETRIS                     = 100;

struct Fecha{
    char dia[10];
    char mes[10];
    char anyo[10];
};

struct Lugar{
    char provincia[20];
    char pais[20];
};

struct Jugador{
    char usuario[20];
    char pass[20];
    char nombre[20];
    char apellido1[20];
    char apellido2[20];
    char email[40];
    int fichas;
    bool activo;
    Fecha fecha_nacimiento;
    Lugar lugar_nacimiento;
};

Jugador jugador;

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
int  getFicha();
void clearFichaSide(int posX, int posY, int side, int tipoFicha);
void checkLines();
void updatePoints();
void drawCredits();
void clearOnRotate(int posX, int posY, int tipoFicha);
bool testCollisionBottom(int posX, int posY, int tipoFicha);
bool testCollisionLeft(int posX, int posY, int tipoFicha);
bool testCollisionRight(int posX, int posY, int tipoFicha);
bool login();

void game_init(){
    seed();
    /* Para la correcta ejecución de este juego, debemos poner la consola en "fuente de mapa de bits" y 8x8 píxeles de tamaño */
    //Nuestra ventana molona bien grande
    ventanaConsola(anchoVentana/2, altoVentana/2, "iJosTris");
    //Establecemos los colores iniciales
    system("color 08");
    //Dibujamos los margenes
    //drawMargins();

    srand(time(NULL));
}


int getFicha(){
    checkLines(); // --> Dentro redibujamos
    int rand = aleatorio(6) + 1;
    rotacion_grados_ficha_actual = 0;
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

        if(kbhit()){
            fflush(stdin);
            tecla=getch();

            if(tecla == 80){ // Abajo
                if(testCollisionBottom(posX, posY, ficha)){
                    posY = starting_point_y;
                    posX = starting_point_x;
                    ficha = getFicha();
                    insertFicha(posX, posY, ficha); // ficha
                }else{
                    clearFichaSide(posX, posY, 1, ficha);
                    posY++;
                    insertFicha(posX, posY, ficha);
                }
            }else if(tecla == 72){ // Arriba
                rotacion_grados_ficha_actual += 90;
                if(rotacion_grados_ficha_actual == 360){
                    rotacion_grados_ficha_actual = 0;
                }
                clearOnRotate(posX, posY, ficha);
                insertFicha(posX, posY, ficha);
            }else if(tecla == 75){ // Izquierda
                if(!testCollisionLeft(posX, posY, ficha)){
                    posX--;
                    insertFicha(posX, posY, ficha);
                    clearFichaSide(posX, posY, 2, ficha);
                }
            }else if(tecla == 77){ // Derecha
                if(!testCollisionRight(posX, posY, ficha)){
                    clearFichaSide(posX, posY, 3, ficha);
                    posX++;
                    insertFicha(posX, posY, ficha);
                }
            }
        } // End kbhit

        // Gravedad
        t_ahora = time(NULL);		// Actualizamos el tiempo
        if ( t_ahora - t_ultimoTick > 0 ){ // Checkeamos si ha pasado 1 segundo desde la ultima caida de ficha (tick)
            //Comprobar que no caiga la ficha si hay cosas debajo
            if(testCollisionBottom(posX, posY, ficha)){
                posY = starting_point_y;
                posX = starting_point_x;
                ficha = getFicha();
                insertFicha(posX, posY, ficha); // ficha
            }else{
                clearFichaSide(posX, posY, 1, ficha);
                posY++;
                insertFicha(posX, posY, ficha);
            }
            t_ultimoTick = time(NULL);		// Actualizamos el tiempo otra vez

        }
     drawGameArea();
    }

}

bool testCollisionLeft(int posX, int posY, int tipoFicha){
    switch (tipoFicha){
        case 1:
            if(rotacion_grados_ficha_actual == 0){
                if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX - 1] != 0 || game_area[posY + 2][posX - 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90){
                if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX - 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 180){
                if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX] != 0 || game_area[posY + 2][posX] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 270){
                if(game_area[posY + 1][posX - 1] != 0){
                    return true;
                }
            }
        break;
        case 2:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX - 1] != 0 || game_area[posY + 2][posX - 1] != 0 || game_area[posY + 3][posX - 1] != 0){
                    return true;
                }
            }else{
                if(game_area[posY][posX - 1]){
                    return true;
                }
            }
        break;
        case 3:
            if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX - 1] != 0){
                return true;
            }
        break;
        case 4:
            if(rotacion_grados_ficha_actual == 0){
                if(game_area[posY][posX] != 0 || game_area[posY + 1][posX] != 0 || game_area[posY + 2][posX - 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90){
                if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX - 1]){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 180){
                if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX - 1] != 0 || game_area[posY + 2][posX - 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 270){
                if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX + 1] != 0){
                    return true;
                }
            }
        break;
        case 5:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX - 1] != 0 || game_area[posY + 2][posX] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90 || rotacion_grados_ficha_actual == 270){
                if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX] != 0){
                    return true;
                }
            }
        break;
        case 6:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                if(game_area[posY][posX] != 0 || game_area[posY + 1][posX - 1] != 0 || game_area[posY + 2][posX - 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90 || rotacion_grados_ficha_actual == 270){
                if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX] != 0){
                    return true;
                }
            }
        break;
        case 7:
            if(rotacion_grados_ficha_actual == 0){
                if(game_area[posY][posX] != 0 || game_area[posY + 1][posX - 1] != 0 ){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90){
                if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX - 1] != 0 || game_area[posY + 1][posX - 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 180){
                if(game_area[posY][posX - 1] != 0 || game_area[posY + 1][posX] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 270){
                if(game_area[posY][posX] != 0 || game_area[posY + 1][posX - 1] != 0 || game_area[posY + 2][posX] != 0){
                    return true;
                }
            }
        break;
    }
}

bool testCollisionRight(int posX, int posY, int tipoFicha){
    switch (tipoFicha){

        case 1:
            if(rotacion_grados_ficha_actual == 0){
                if(game_area[posY][posX + 1] != 0 + game_area[posY + 1][posX + 1] != 0 || game_area[posY + 2][posX + 2] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90){
                if(game_area[posY][posX + 3] != 0 || game_area[posY + 1][posX + 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 180){
                if(game_area[posY][posX + 2] != 0 || game_area[posY + 1][posX + 2] != 0 || game_area[posY + 3][posX + 2] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 270){
                if(game_area[posY][posX + 3] != 0 || game_area[posY + 1][posX + 3] != 0){
                    return true;
                }
            }
        break;
        case 2:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                if(game_area[posY][posX + 1] != 0 || game_area[posY + 1][posX + 1] != 0 || game_area[posY + 2][posX + 1] != 0 || game_area[posY + 3][posX + 1] != 0){
                    return true;
                }
            }else{
                if(game_area[posY][posX + 4]){
                    return true;
                }
            }
        break;

        case 3:
            if(game_area[posY][posX + 2] != 0 || game_area[posY + 1][posX + 2] != 0){
                return true;
            }
        break;
        case 4:
            if(rotacion_grados_ficha_actual == 0){
                if(game_area[posY][posX + 2] != 0 || game_area[posY + 1][posX + 2] != 0 || game_area[posY + 2][posX + 2] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90){
                if(game_area[posY + 1][posX + 3] != 0 || game_area[posY][posX + 1]){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 180){
                if(game_area[posY][posX + 2] != 0 || game_area[posY + 1][posX + 1] != 0 || game_area[posY + 2][posX + 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 270){
                if(game_area[posY][posX + 3] != 0 || game_area[posY + 1][posX + 3] != 0){
                    return true;
                }
            }
        break;
        case 5:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                if(game_area[posY][posX + 1] != 0 || game_area[posY + 1][posX + 2] != 0 || game_area[posY + 2][posX + 2] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90 || rotacion_grados_ficha_actual == 270){
                if(game_area[posY][posX + 2] != 0 || game_area[posY + 1][posX + 3] != 0){
                    return true;
                }
            }
        break;
        case 6:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                if(game_area[posY][posX + 2] != 0 || game_area[posY + 1][posX + 2] != 0 || game_area[posY + 2][posX + 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90 || rotacion_grados_ficha_actual == 270){
                if(game_area[posY][posX + 2] != 0 || game_area[posY + 1][posX + 3] != 0){
                    return true;
                }
            }
        break;
        case 7:
            if(rotacion_grados_ficha_actual == 0){
                if(game_area[posY][posX + 2] != 0 || game_area[posY + 1][posX + 3] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90){
                if(game_area[posY + 1][posX + 2] != 0 || game_area[posY][posX + 1] != 0 || game_area[posY + 2][posX + 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 180){
                if(game_area[posY][posX + 3] != 0 || game_area[posY + 1][posX + 2] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 270){
                if(game_area[posY][posX + 2] != 0 || game_area[posY + 1][posX + 2] != 0 || game_area[posY + 2][posX + 2] != 0){
                    return true;
                }
            }
        break;
    }
}

bool testCollisionBottom(int posX, int posY, int tipoFicha){
    switch (tipoFicha){
        case 1:
            if(rotacion_grados_ficha_actual == 0){
                if(game_area[posY + 3][posX] != 0 || game_area[posY + 3][posX + 1] != 0 ){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90){
                if(game_area[posY + 2][posX] != 0 || game_area[posY + 1][posX + 1] != 0  || game_area[posY + 1][posX + 2] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 180){
                if(game_area[posY + 1][posX] != 0 || game_area[posY + 3][posX + 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 270){
                if(game_area[posY + 2][posX] != 0 || game_area[posY + 2][posX + 1] != 0 || game_area[posY + 2][posX + 2] != 0){
                    return true;
                }
            }
        break;
        case 2:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                if(game_area[posY + 4][posX] != 0){
                    return true;
                }
            }else{
                if(game_area[posY + 1][posX] || game_area[posY + 1][posX + 1] || game_area[posY + 1][posX + 2] || game_area[posY + 1][posX + 3]){
                    return true;
                }
            }
        break;
        case 3:
            if(game_area[posY + 2][posX] != 0 || game_area[posY + 2][posX + 1] != 0){
                return true;
            }
        break;
        case 4:
            if(rotacion_grados_ficha_actual == 0){
                if(game_area[posY + 3][posX] != 0 || game_area[posY + 3][posX + 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90){
                if(game_area[posY + 2][posX] != 0 || game_area[posY + 2][posX + 1] != 0 || game_area[posY + 2][posX + 2] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 180){
                if(game_area[posY + 3][posX] != 0 || game_area[posY + 1][posX + 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 270){
                if(game_area[posY + 1][posX] != 0 || game_area[posY + 1][posX + 1] != 0 || game_area[posY + 2][posX + 2]){
                    return true;
                }
            }
        break;
        case 5:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                if(game_area[posY + 2][posX] != 0 || game_area[posY + 3][posX + 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90 || rotacion_grados_ficha_actual == 270){
                if(game_area[posY + 1][posX] != 0 || game_area[posY + 2][posX + 1] != 0 || game_area[posY + 2][posX + 2]){
                    return true;
                }
            }
        break;
        case 6:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                if(game_area[posY + 3][posX] != 0 || game_area[posY + 2][posX + 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90 || rotacion_grados_ficha_actual == 270){
                if(game_area[posY + 1][posX] != 0 || game_area[posY + 2][posX + 1] != 0 || game_area[posY + 2][posX + 2]){
                    return true;
                }
            }
        break;
        case 7:
            if(rotacion_grados_ficha_actual == 0){
                if(game_area[posY + 2][posX] != 0 || game_area[posY + 2][posX + 1] != 0 || game_area[posY + 2][posX + 2] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 90){
                if(game_area[posY + 3][posX] != 0 || game_area[posY + 2][posX + 1] != 0){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 180){
                if(game_area[posY + 1][posX] != 0 || game_area[posY + 2][posX + 1] != 0 || game_area[posY + 1][posX + 2]){
                    return true;
                }
            }else if(rotacion_grados_ficha_actual == 270){
                if(game_area[posY + 2][posX] != 0 || game_area[posY + 3][posX + 1] != 0){
                    return true;
                }
            }
        break;
    }

}

void clearOnRotate(int posX, int posY, int tipoFicha){

    switch(tipoFicha){
        case 1:
            if(rotacion_grados_ficha_actual == 0){
                game_area[posY][posX + 2]           = 0;
                game_area[posY + 1][posX + 1]       = 0;
                game_area[posY + 1][posX + 2]       = 0;
            }else if(rotacion_grados_ficha_actual == 90){
                game_area[posY + 2][posX]           = 0;
                game_area[posY + 2][posX + 1]       = 0;
            }else if(rotacion_grados_ficha_actual == 180){
                game_area[posY + 1][posX]           = 0;
                game_area[posY][posX + 2]           = 0;
            }else if(rotacion_grados_ficha_actual == 270){
                game_area[posY][posX]               = 0;
                game_area[posY][posX + 1]           = 0;
                game_area[posY][posX + 2]           = 0;
                game_area[posY + 2][posX + 1]       = 0;
            }
        break;
        case 2:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                game_area[posY][posX]               = 0;
                game_area[posY][posX + 1]           = 0;
                game_area[posY][posX + 2]           = 0;
                game_area[posY][posX + 3]           = 0;
            }else{
                game_area[posY][posX]               = 0;
                game_area[posY + 1][posX]           = 0;
                game_area[posY + 2][posX]           = 0;
                game_area[posY + 3][posX]           = 0;
            }
        break;
        case 3:
           // Esta ficha no rota! :D
        break;
        case 4:
            if(rotacion_grados_ficha_actual == 0){
                game_area[posY][posX]               = 0;
                game_area[posY][posX + 2]           = 0;
                game_area[posY + 1][posX + 2]       = 0;
            }else if(rotacion_grados_ficha_actual == 90){
                game_area[posY][posX + 1]           = 0;
                game_area[posY + 2][posX]           = 0;
                game_area[posY + 2][posX + 1]       = 0;
            }else if(rotacion_grados_ficha_actual == 180){
                game_area[posY + 1][posX + 1]       = 0;
                game_area[posY + 1][posX + 2]       = 0;
            }else if (rotacion_grados_ficha_actual == 270){
                game_area[posY + 1][posX]           = 0;
                game_area[posY + 2][posX]           = 0;
            }
        break;
        case 5:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                game_area[posY][posX + 1]           = 0;
                game_area[posY][posX + 2]           = 0;
                game_area[posY + 1][posX + 2]       = 0;
            }else{
                game_area[posY + 2][posX + 1]       = 0;
                game_area[posY + 1][posX]           = 0;
            }
        break;
        case 6:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                game_area[posY][posX]               = 0;
                game_area[posY + 1][posX + 2]       = 0;
            }else{
                game_area[posY + 2][posX]           = 0;
                game_area[posY + 1][posX]           = 0;
            }
        break;
        case 7:
            if(rotacion_grados_ficha_actual == 0){
                game_area[posY + 2][posX + 1]       = 0;
            }else if(rotacion_grados_ficha_actual == 90){
                game_area[posY][posX + 1]           = 0;
                game_area[posY + 1][posX + 2]       = 0;
            }else if(rotacion_grados_ficha_actual == 180){
                game_area[posY + 1][posX]           = 0;
                game_area[posY + 2][posX]           = 0;
            }else if (rotacion_grados_ficha_actual == 270){
                game_area[posY][posX ]              = 0;
                game_area[posY][posX + 2]           = 0;
            }
        break;
    }

}

void drawGameArea(){
   int step = 0;
   for(int j = 0; j < gameInterface_size_height + (gameInterface_margin + 1); j++){
        cursorPos(starting_point_x - gameInterface_margin, starting_point_y + step);
        for(int i = 0; i < gameInterface_size_width + gameInterface_margin; i++){
            if(game_area[j][i] == 9 || game_area[j][i] == 8){
                //Margins (FC)
                setColors(3, 15);
                printf(" ", game_area[j][i]);
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
            }else if(game_area[j][i] == 7){
                setColors(12, 6);
                printf("%c", gameFicha_ascii_model);
            }else if(game_area[j][i] == 99){
                setColors(12, 14);
                printf("%d", game_area[j][i]);
            }else if(game_area[j][i] == 0){ // Vacio
                setColors(1, 15);
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
            if(rotacion_grados_ficha_actual == 0){
                if(side == 1){ // Top
                    game_area[posY][posX]           = 0;
                    game_area[posY + 2][posX + 1]   = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 1]       = 0;
                    game_area[posY + 1][posX + 1]   = 0;
                    game_area[posY + 2][posX + 2]   = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]           = 0;
                    game_area[posY + 1][posX]       = 0;
                    game_area[posY + 2][posX]       = 0;
                }
            }else if(rotacion_grados_ficha_actual == 90){
                if(side == 1){ // Top
                    game_area[posY][posX]           = 0;
                    game_area[posY][posX + 1]       = 0;
                    game_area[posY][posX + 2]       = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 3]       = 0;
                    game_area[posY + 1][posX + 1]   = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]           = 0;
                    game_area[posY + 1][posX]       = 0;
                }
            }else if(rotacion_grados_ficha_actual == 180){
                if(side == 1){ // Top
                    game_area[posY][posX]           = 0;
                    game_area[posY][posX + 1]       = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 2]       = 0;
                    game_area[posY + 1][posX + 2]   = 0;
                    game_area[posY + 2][posX + 2]   = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]           = 0;
                    game_area[posY + 1][posX + 1]   = 0;
                    game_area[posY + 2][posX + 1]   = 0;
                }
            }else if(rotacion_grados_ficha_actual == 270){
                if(side == 1){ // Top
                    game_area[posY + 1][posX]       = 0;
                    game_area[posY + 1][posX + 1]   = 0;
                    game_area[posY][posX + 2]       = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 3]       = 0;
                    game_area[posY + 1][posX + 3]   = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX + 2]       = 0;
                    game_area[posY + 1][posX]       = 0;
                }
            }
        break;
        case 2:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                if(side == 1){ // Top
                    game_area[posY][posX]           = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 1]       = 0;
                    game_area[posY + 1][posX + 1]   = 0;
                    game_area[posY + 2][posX + 1]   = 0;
                    game_area[posY + 3][posX + 1]   = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]           = 0;
                    game_area[posY + 1][posX]       = 0;
                    game_area[posY + 2][posX]       = 0;
                    game_area[posY + 3][posX]       = 0;
                }
            }else{
                if(side == 1){ // Top
                    game_area[posY][posX]           = 0;
                    game_area[posY][posX + 1]       = 0;
                    game_area[posY][posX + 2]       = 0;
                    game_area[posY][posX + 3]       = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 4]       = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]           = 0;
                }
            }
        break;
        case 3:
            if(side == 1){ // Top
                game_area[posY][posX]               = 0;
                game_area[posY][posX + 1]           = 0;
            }else if(side == 2){ // Right
                game_area[posY][posX + 2]           = 0;
                game_area[posY + 1][posX + 2]       = 0;
            }else if(side == 3){ //Left
                game_area[posY][posX]               = 0;
                game_area[posY + 1][posX]           = 0;
            }
        break;
        case 4:
            if(rotacion_grados_ficha_actual == 0){
                if(side == 1){ // Top
                    game_area[posY][posX + 1]           = 0;
                    game_area[posY + 2][posX]           = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 2]           = 0;
                    game_area[posY + 1][posX + 2]       = 0;
                    game_area[posY + 2][posX + 2]       = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX + 1]           = 0;
                    game_area[posY + 1][posX + 1]       = 0;
                    game_area[posY + 2][posX]           = 0;
                }
            }else if(rotacion_grados_ficha_actual == 90){
                if(side == 1){ // Top
                    game_area[posY][posX]              = 0;
                    game_area[posY + 1][posX + 1]      = 0;
                    game_area[posY + 1][posX + 2]      = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 1]          = 0;
                    game_area[posY + 1][posX + 3]      = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]              = 0;
                    game_area[posY + 1][posX]          = 0;
                }
            }else if(rotacion_grados_ficha_actual == 180){
                if(side == 1){ // Top
                    game_area[posY][posX]              = 0;
                    game_area[posY][posX + 1]          = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 2]          = 0;
                    game_area[posY + 1][posX + 1]      = 0;
                    game_area[posY + 2][posX + 1]      = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]              = 0;
                    game_area[posY + 1][posX]          = 0;
                    game_area[posY + 2][posX]          = 0;
                }
            }else if(rotacion_grados_ficha_actual == 270){
                if(side == 1){ // Top
                    game_area[posY][posX]             = 0;
                    game_area[posY][posX + 1]         = 0;
                    game_area[posY][posX + 2]         = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 3]         = 0;
                    game_area[posY + 1][posX + 3]     = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]             = 0;
                    game_area[posY + 1][posX + 2]     = 0;
                }
            }
        break;
        case 5:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                if(side == 1){ // Top
                    game_area[posY][posX]           = 0;
                    game_area[posY][posX + 1]       = 0;
                    game_area[posY + 1][posX + 1]   = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 1]       = 0;
                    game_area[posY + 1][posX + 2]   = 0;
                    game_area[posY + 2][posX + 2]   = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]           = 0;
                    game_area[posY + 1][posX]       = 0;
                    game_area[posY + 2][posX + 1]   = 0;
                }
            }else if(rotacion_grados_ficha_actual == 90 || rotacion_grados_ficha_actual == 270){
                if(side == 1){ // Top
                    game_area[posY][posX]           = 0;
                    game_area[posY][posX + 1]       = 0;
                    game_area[posY + 1][posX + 2]   = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 2]       = 0;
                    game_area[posY + 1][posX + 3]   = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]           = 0;
                    game_area[posY + 1][posX + 1]   = 0;
                }
            }
        break;
        case 6:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                if(side == 1){ // Top
                    game_area[posY + 1][posX]       = 0;
                    game_area[posY][posX + 1]       = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 2]       = 0;
                    game_area[posY + 1][posX + 2]   = 0;
                    game_area[posY + 2][posX + 1]   = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]           = 0;
                    game_area[posY][posX + 1]       = 0;
                    game_area[posY + 1][posX]       = 0;
                    game_area[posY + 2][posX]       = 0;
         game_area[posY][posX]           = 0;
                    game_area[posY + 1][posX + 1]   = 0;       }
            }else if(rotacion_grados_ficha_actual == 90 || rotacion_grados_ficha_actual == 270){
                if(side == 1){ // Top
                    game_area[posY][posX]           = 0;
                    game_area[posY][posX + 1]       = 0;
                    game_area[posY + 1][posX + 2]   = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 2]       = 0;
                    game_area[posY + 1][posX + 3]   = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]           = 0;
                    game_area[posY + 1][posX + 1]   = 0;
                }
            }
        break;
        case 7:
            if(rotacion_grados_ficha_actual == 0){
                if(side == 1){ // Top
                    game_area[posY][posX + 1]           = 0;
                    game_area[posY + 1][posX]           = 0;
                    game_area[posY + 1][posX + 2]       = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 2]           = 0;
                    game_area[posY + 1][posX + 3]       = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX + 1]           = 0;
                    game_area[posY + 1][posX]           = 0;
                }
            }else if(rotacion_grados_ficha_actual == 90){
                if(side == 1){ // Top
                    game_area[posY][posX]              = 0;
                    game_area[posY + 1][posX + 1]      = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 1]          = 0;
                    game_area[posY + 1][posX + 2]      = 0;
                    game_area[posY + 2][posX + 1]      = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]              = 0;
                    game_area[posY + 1][posX]          = 0;
                    game_area[posY + 2][posX]          = 0;
                }
            }else if(rotacion_grados_ficha_actual == 180){
                if(side == 1){ // Top
                    game_area[posY][posX]              = 0;
                    game_area[posY][posX + 1]          = 0;
                    game_area[posY][posX + 2]          = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 3]          = 0;
                    game_area[posY + 1][posX + 2]      = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX]              = 0;
                    game_area[posY + 1][posX + 1]      = 0;
                }
            }else if(rotacion_grados_ficha_actual == 270){
                if(side == 1){ // Top
                    game_area[posY + 1][posX]         = 0;
                    game_area[posY][posX + 1]         = 0;
                }else if(side == 2){ // Right
                    game_area[posY][posX + 2]         = 0;
                    game_area[posY + 1][posX + 2]     = 0;
                    game_area[posY + 2][posX + 2]     = 0;
                }else if(side == 3){ //Left
                    game_area[posY][posX + 1]         = 0;
                    game_area[posY + 1][posX]         = 0;
                    game_area[posY + 2][posX + 1]     = 0;
                }
            }
        break;
    }
}

void checkLines(){

    int lineaCompleta;

    int x_pos;
	int y_pos;
	int current_y_pos;
	int lineasEliminadas = 0;
	int must_update_points = 0;

    // Checkeamos todas las lineas, desde abajo hacia arriba, de izquierda a derecha
    // Si hay lineas completas, hacemos puntuacion
    for(int y_pos = gameInterface_size_height + 1; y_pos > 1; y_pos--){

        lineaCompleta = 1;
        for(int x_pos = 1; x_pos <= gameInterface_size_width; x_pos++){

            //Comprobamos si en esta linea hay algun "hueco"
            if(game_area[y_pos][x_pos] == 0){
                lineaCompleta = 0;
            }

        }

        if(lineaCompleta){

            // Eliminamos la linea
            for(int x_pos = 1; x_pos <= gameInterface_size_width; x_pos++){
                game_area[y_pos][x_pos] = 0;
            }

            // Tiramos lineas hacia abajo
            for(current_y_pos = y_pos; current_y_pos > 2; current_y_pos--){

                for(x_pos = 1; x_pos <= gameInterface_size_width; x_pos++){
                    game_area[current_y_pos][x_pos] = game_area[current_y_pos - 1][x_pos];
                }

            }

            must_update_points = 1;
            lineasEliminadas += 1;
            y_pos++;

        } // Linea completa


    }// Check lines bucle

    // Actualizamos los puntos
    if(lineasEliminadas < 4){
        PUNTOS += lineasEliminadas * PUNTOS_LINEA;

    }else{
        PUNTOS += PUNTOS_TETRIS;
    }

    if(must_update_points){
        updatePoints();
        must_update_points = 0;
    }





}

void updatePoints(){

    for(int y = 2; y < 8; y++){
        for(int x = 10; x <= 20; x++){
            cursorPos(gameInterface_size_width + x, y);
            printf(" ");
        }
    }
    cursorPos(gameInterface_size_width + 10, 2);
    printf("---SCORE---");

    cursorPos(gameInterface_size_width + 15, 3);
    printf("%d", PUNTOS);
}

void drawCredits(){

    for(int y = 10; y < 13; y++){
        for(int x = 10; x <= 20; x++){
            cursorPos(gameInterface_size_width + x, y);
            printf(" ");
        }
    }
    cursorPos(gameInterface_size_width + 10, 10);
    printf("---COINS---");

    cursorPos(gameInterface_size_width + 14, 12);
    printf("%d", CREDITOS);

}

void insertFicha(int posX, int posY, int tipoFicha){
    switch (tipoFicha){
        case 1:
            if(rotacion_grados_ficha_actual == 0){
                game_area[posY][posX]           = 1;
                game_area[posY + 1][posX]       = 1;
                game_area[posY + 2][posX]       = 1;
                game_area[posY + 2][posX + 1]   = 1;
            }else if(rotacion_grados_ficha_actual == 90){
                game_area[posY][posX]           = 1;
                game_area[posY][posX + 1]       = 1;
                game_area[posY][posX + 2]       = 1;
                game_area[posY + 1][posX]       = 1;
            }else if(rotacion_grados_ficha_actual == 180){
                game_area[posY][posX]           = 1;
                game_area[posY][posX + 1]       = 1;
                game_area[posY + 1][posX + 1]   = 1;
                game_area[posY + 2][posX + 1]   = 1;
            }else if(rotacion_grados_ficha_actual == 270){
                game_area[posY][posX + 2]       = 1;
                game_area[posY + 1][posX]       = 1;
                game_area[posY + 1][posX + 1]   = 1;
                game_area[posY + 1][posX + 2]   = 1;
            }
        break;
        case 2:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                game_area[posY][posX]       = 2;
                game_area[posY + 1][posX]   = 2;
                game_area[posY + 2][posX]   = 2;
                game_area[posY + 3][posX]   = 2;
            }else{
                game_area[posY][posX]       = 2;
                game_area[posY][posX + 1]   = 2;
                game_area[posY][posX + 2]   = 2;
                game_area[posY][posX + 3]   = 2;
            }
        break;
        case 3:
            game_area[posY][posX]               = 3;
            game_area[posY][posX + 1]           = 3;
            game_area[posY + 1][posX]           = 3;
            game_area[posY + 1][posX + 1]       = 3;
        break;
        case 4:
            if(rotacion_grados_ficha_actual == 0){
                game_area[posY][posX + 1]       = 4;
                game_area[posY + 1][posX + 1]   = 4;
                game_area[posY + 2][posX + 1]   = 4;
                game_area[posY + 2][posX]       = 4;
            }else if(rotacion_grados_ficha_actual == 90){
                game_area[posY][posX]           = 4;
                game_area[posY + 1][posX]       = 4;
                game_area[posY + 1][posX + 1]   = 4;
                game_area[posY + 1][posX + 2]   = 4;
            }else if(rotacion_grados_ficha_actual == 180){
                game_area[posY][posX]           = 4;
                game_area[posY][posX + 1]       = 4;
                game_area[posY + 1][posX]       = 4;
                game_area[posY + 2][posX]       = 4;
            }else if(rotacion_grados_ficha_actual == 270){
                game_area[posY][posX]           = 4;
                game_area[posY][posX + 1]       = 4;
                game_area[posY][posX + 2]       = 4;
                game_area[posY + 1][posX + 2]   = 4;
            }
        break;
        case 5:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                game_area[posY][posX]               = 5;
                game_area[posY + 1][posX]           = 5;
                game_area[posY + 1][posX + 1]       = 5;
                game_area[posY + 2][posX + 1]       = 5;
            }else if(rotacion_grados_ficha_actual == 90 || rotacion_grados_ficha_actual == 270){
                game_area[posY][posX]               = 5;
                game_area[posY][posX + 1]           = 5;
                game_area[posY + 1][posX + 1]       = 5;
                game_area[posY + 1][posX + 2]       = 5;
            }
        break;
        case 6:
            if(rotacion_grados_ficha_actual == 0 || rotacion_grados_ficha_actual == 180){
                game_area[posY][posX + 1]           = 6;
                game_area[posY + 1][posX + 1]       = 6;
                game_area[posY + 1][posX]           = 6;
                game_area[posY + 2][posX]           = 6;
            }else if(rotacion_grados_ficha_actual == 90 || rotacion_grados_ficha_actual == 270){

                game_area[posY][posX]               = 6;
                game_area[posY][posX + 1]           = 6;
                game_area[posY + 1][posX + 1]       = 6;
                game_area[posY + 1][posX + 2]       = 6;
            }
        break;
        case 7:
            if(rotacion_grados_ficha_actual == 0){
                game_area[posY][posX + 1]       = 7;
                game_area[posY + 1][posX]       = 7;
                game_area[posY + 1][posX + 1]   = 7;
                game_area[posY + 1][posX + 2]   = 7;
            }else if(rotacion_grados_ficha_actual == 90){
                game_area[posY][posX]           = 7;
                game_area[posY + 1][posX]       = 7;
                game_area[posY + 1][posX + 1]   = 7;
                game_area[posY + 2][posX]       = 7;
            }else if(rotacion_grados_ficha_actual == 180){
                game_area[posY][posX]           = 7;
                game_area[posY][posX + 1]       = 7;
                game_area[posY][posX + 2]       = 7;
                game_area[posY + 1][posX + 1]   = 7;
            }else if(rotacion_grados_ficha_actual == 270){
                game_area[posY][posX + 1]       = 7;
                game_area[posY + 1][posX]       = 7;
                game_area[posY + 1][posX + 1]   = 7;
                game_area[posY + 2][posX + 1]   = 7;
            }
        break;
    }

}

void setColors(int texto, int fondo){
    colorTexto(texto, fondo);
}

void resetColors(){
    setColors(1, 15);
}

bool login_access(){

    FILE *fichero_datos;

    char usuario[20];
    char pass[20];
    bool keep_searching = true;
    bool lets_play = false;

    system("cls");
    printf("*** ------------ *** iJosTris *** ------------ ***\n\n\n");
    printf("Nombre de Usuario: ");
    scanf("%s", &usuario);
    fflush(stdin);

    printf("Password: ");
    scanf("%s", &pass);
    fflush(stdin);
    printf("\n");

    fichero_datos = fopen("../database/players_database.dat", "rb");

    while(!feof(fichero_datos)){

    fread(&jugador, sizeof(jugador), 1, fichero_datos);

        if(!feof(fichero_datos) || keep_searching){
            if(strcmp(strupr(jugador.usuario), strupr(usuario)) == 0 && strcmp(strupr(jugador.pass), strupr(pass)) == 0 ){
                printf("Login Correcto\n\n");
                printf("Pulsa cualquier tecla para iniciar partida");
                getch();

                CREDITOS = jugador.fichas;
                keep_searching = false;
                lets_play = true;
            }
        }
    }
    fclose(fichero_datos);
    if(lets_play){
        return true;
    }
}

bool login(){
    int elec;

    do{
        system("cls");
        printf("*** ------------ *** iJosTris *** ------------ ***\n\n\n");
        printf("1.- Jugar\n");
        printf("2.- Maximas puntuaciones\n\n\n");
        printf("5.- Salir \n\n");

        scanf("%d", &elec);


        switch(elec){
            case 1:
                while(login_access()){
                    return true;
                }
            break;
            case 2:

            break;

            case 5:
                return false;
        }

    }while(elec != 6);
}

int main(){

    if(login()){
        /*TODO*/
        game_init();
        drawGameArea();
        updatePoints();
        drawCredits();
        gameLoop();
    }


    return 0;
}
