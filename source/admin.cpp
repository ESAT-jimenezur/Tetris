#include <stdio.h>
#include <iJos.h>
#include<conio.h>
#include <string.h>
#include <windows.h>

/* Public Global Vars */
const int anchoVentana                = 150;
const int altoVentana                 = 100;

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
    int high_score;
    bool activo;
    Fecha fecha_nacimiento;
    Lugar lugar_nacimiento;
};

Jugador jugador;
FILE *fichero_datos;
FILE *fichero_auxiliar;


/** Definimos los métodos necesarios **/

/**Este método se encarga de mostrar el menu por pantalla**/
void menu();

/**Este método se encarga de establecer los colores necesarios para la ejecucion**/
void setColors();

/**Este método se encarga de insertar nuevos jugadores**/
void alta_jugador();

/**Este método se encarga de pedir datos para hacer altas**/
void pedirDatos();

/**Este método se encarga mostrar la lista de jugadores**/
void alta_jugador();

/**Este método se encarga modificar jugadores**/
void modifica_jugador();

/**Este método se encarga eliminar jugadores**/
void elimina_jugador();


void setColors(int texto, int fondo){
    colorTexto(texto, fondo);
}


void pedirDatos(){

    system("cls");
    fflush(stdin);
    printf("*** Nuevo Jugador ***\n");
    printf("Introduce nombre de usuario: ");
        scanf("%s", &jugador.usuario);
        fflush(stdin);

    printf("Introduce una contrasena: ");
        scanf("%s", &jugador.pass);
        fflush(stdin);

    printf("Introduce el email: ");
        scanf("%s", &jugador.email);
        fflush(stdin);

    printf("Introduce un nombre: ");
        scanf("%s", &jugador.nombre);
        fflush(stdin);

    printf("Introduce el primer apellido: ");
        scanf("%s", &jugador.apellido1);
        fflush(stdin);

    printf("Introduce un segundo apellido: ");
        scanf("%s", &jugador.apellido2);
        fflush(stdin);

    printf("Introduce el DIA de nacimiento: ");
        scanf("%s", &jugador.fecha_nacimiento.dia);
        fflush(stdin);

    printf("Introduce el MES de nacimiento: ");
        scanf("%s", &jugador.fecha_nacimiento.mes);
        fflush(stdin);

     printf("Introduce el ANYO de nacimiento: ");
        scanf("%s", &jugador.fecha_nacimiento.anyo);
        fflush(stdin);


    printf("Introduce la provincia: ");
        scanf("%s", &jugador.lugar_nacimiento.provincia);
        fflush(stdin);

    printf("Introduce el pais: ");
        scanf("%s", &jugador.lugar_nacimiento.pais);
        fflush(stdin);

        //Activamos el jugador y establecemos sus fichas
        jugador.activo = true;
        jugador.fichas = 10;
        jugador.high_score = 0;
}


void alta_jugador(){

    char seguir;

    do{

        pedirDatos();
        fichero_datos = fopen("../database/players_database.dat", "ab");
        fwrite(&jugador, sizeof(jugador), 1, fichero_datos);
        fclose(fichero_datos);
        printf("\n Quieres insertar otro jugador?\n S/N \n");
        seguir = getch();

    }while(seguir == 's');

    //menu();
}


void lista_jugadores(){

    system("cls");

    fichero_datos = fopen("../database/players_database.dat", "rb");

    printf("\n *************** Lista de Jugadores *************** \n\n");
    printf("Usuario Nombre 1erApellido 2oApellido    Email        Fichas HighScore \n \n");

    while(!feof(fichero_datos)){
    fread(&jugador, sizeof(jugador), 1, fichero_datos);
    if(!feof(fichero_datos)){

        printf("  %s   %s   %s    %s    %s    %d     %d \n \n",
           jugador.usuario,
           jugador.nombre,
           jugador.apellido1,
           jugador.apellido2,
           jugador.email,
           jugador.fichas,
           jugador.high_score);
        }
    }


    fclose(fichero_datos);
    printf("\n *************** Pulsa cualquier tecla para salir *************** \n");
    getch();
    menu();
}


void modifica_jugador(){

    system("cls");

    char usuario[20];

    fichero_datos = fopen("../database/players_database.dat", "r+");

    printf("\n ***************        Modificar Jugador        *************** \n\n");
    printf("Usuario del jugador a modificar: ");
    scanf("%s", usuario);
    fflush(stdin);

    int apuntador = 0;

    while(!feof(fichero_datos)){
    fread(&jugador, sizeof(jugador), 1, fichero_datos);
        if(!feof(fichero_datos)){
            if(strcmp(strlwr(usuario), strlwr(jugador.usuario)) == 0){
                printf("Contacto encontrado, modificando...");
                getch();
                fseek(fichero_datos, sizeof(jugador) * apuntador, SEEK_SET);
                pedirDatos();
                fwrite(&jugador, sizeof(jugador), 1, fichero_datos);
                printf("Usuario modificado");
                fclose(fichero_datos);
                getch();
                menu();
            }else{
                printf("No se ha encontrado el jugador");
                fclose(fichero_datos);
                getch();
                menu();
            }
            apuntador++;
        }
    }

    fclose(fichero_datos);
    printf("\n *************** Pulsa cualquier tecla para salir *************** \n");
    getch();
    menu();

}


void elimina_jugador(){

    system("cls");

    char usuario[20];

    fichero_auxiliar = fopen("../database/AUX_players_database.dat", "wb");
    fichero_datos = fopen("../database/players_database.dat", "r+");

    printf("\n ***************        Eliminar Jugador        *************** \n\n");
    printf("Usuario del jugador a eliminar: ");
    scanf("%s", usuario);
    fflush(stdin);

    int apuntador = 0;

    while(!feof(fichero_datos)){
    fread(&jugador, sizeof(jugador), 1, fichero_datos);
        if(!feof(fichero_datos)){
            if(strcmp(strlwr(usuario), strlwr(jugador.usuario)) == 0){
                printf("Contacto encontrado, eliminando...\n");
                getch();
                fwrite(&jugador, sizeof(jugador), 1, fichero_auxiliar);
                printf("Usuario eliminado\n");
                fclose(fichero_datos);
                fclose(fichero_auxiliar);
                getch();
            }
            apuntador++;
        }
    }

    fclose(fichero_datos);
    fclose(fichero_auxiliar);

    remove("../database/AUX_players_database.dat");
    rename("../database/AUX_players_database.dat", "../database/players_database.dat");

    printf("\n *************** Pulsa cualquier tecla para salir *************** \n");
    getch();
    menu();


}


void menu(){


    int elec;

    do{
        system("cls");
        printf("*** ------------ *** iJosTris Admin Backend *** ------------ ***\n\n\n");
        printf("1.- Insertar nuevo jugador\n");
        printf("2.- Eliminar jugador\n");
        printf("3.- Modificar jugador\n");
        printf("4.- Ver lista de jugadores\n");
        printf("5.- Salir \n");

        scanf("%d", &elec);


        switch(elec){
            case 1:
                alta_jugador();
                break;
            case 2:
                elimina_jugador();
                break;
            case 3:
                modifica_jugador();
                break;
            case 4:
                lista_jugadores();
                break;
            case 5:
                return;
        }

    }while(elec != 6);

}


int main(){
    /* Para la correcta ejecución de este juego, debemos poner la consola en "fuente de mapa de bits" y 8x8 píxeles de tamaño */
    //Nuestra ventana molona bien grande
    ventanaConsola(anchoVentana/2, altoVentana/2, "iJosTris Admin Backend");

    //Establecemos los colores iniciales
    system("color 08");

    menu();

    return 0;
}
