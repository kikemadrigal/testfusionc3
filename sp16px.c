//stdio.h implementa el printf (o imprimir formateado), ver http://cplusplus.com/reference/cstdio/printf/
#include <stdio.h>
#include<math.h>
//Puedes ver las funciones que implementa msx_fusion.h abriendo el archivo
#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"

#include "player.h"
#include "enemy.h"
/*Es importante saber que c necesita que 1 se declaren las funciones*****/
/* Por norma general estas definiciones se ponen en un archivo.h y se incluyen como las de arriba*/

void procesar_entrada(void);
void inicializar_player(void);
void inicializar_enemigos(void);
void actualizar_personaje(void);
void actualizar_enemigos(void);
void comprobar_colisiones(void);
static void wait( int j );
//Personaje
//Ver Inicializar personaje
int px,py,pv,pm, pColisionX, pColisionY;
//Creamos 20 enemigos, 1 posicion x, 2 posicion y , 3 velocidad, 4 el byte que ocupa
int enemigos[20][4]={
    {10, 50, 5, 32},
    {20, 20, -5, 36},
    {30, 100, 10 , 40},
    {40, 10, 2, 44},
    {0, 5, 2, 48},
    {0, 2, 2, 52},
    {0, 12, -2, 56},
    {0, 14, 5, 60},
    {0, 16, -5, 64},
    {0, 18, 10, 68},
    {0, 21, -10, 72},
    {0, 23, 12, 76},
    {0, 45, -12, 80},
    {0, 46, 3, 84},
    {0, 40, 10, 88},
    {0, 48, -4, 92},
    {0, 40, -2, 96},
    {0, 55, 7, 100},
    {0, 57, -7, 104},
    {0, 60, 8, 108}
};
int colorBorde=0;
/********************Fin de las declaraciones**************************/


void main(void){
    //Hay que poner la pantalla en screen 1
    SpriteReset();
    Screen(5);
    Sprite16();
    inicializar_player();
    inicializar_enemigos();
    SetColors(255,0,110);
    PutText(10,10,"SCREEN 5",0);
    //Bucle render
    while(1){
        procesar_entrada();
        actualizar_personaje();
        actualizar_enemigos();
        //comprobar_colisiones();
    }
}

void inicializar_player(void){
    // px= player posición eje x, py= player posición eje y
    // pv player velocidad, pm= player movimiento (se obtiene del teclado)
    px=100; py=192-32; pv=5; pm=0;
    // lo metemos en la tabla de dEfinición de patrones
    // el 1 argumento es la posición en la poisión en la tabla de definición de sprites (sprite pattern)
    // el 2 argumentos son los datos del sprite
    // el 3 argumento es el numero del línea del patron

    SetSpritePattern( 0, player_derecha_1, 32);
    SetSpritePattern( 4, player_derecha_2, 32);
    SetSpritePattern( 8, player_izquierda_1, 32);
    SetSpritePattern( 12, player_izquierda_2, 32);
    SetSpritePattern( 16, player_abajo_1, 32);
    SetSpritePattern( 20, player_abajo_2, 32);
    SetSpritePattern( 24, player_arriba_1, 32);
    SetSpritePattern( 28, player_arriba_2, 32);
    
   


    SC5SpriteColors(0,player_color);
    

    //SC5SpriteColors(1,LineColorsPajaro1);
    // Mostramos nuestro esprite
    // 1. el plano o su definición en la tabla de atributos, ahí s e alamcenará la posición x e y
    // 2 la definición en sprite pattern qu eva de 4 en 4 bytes
    // 3 posición eje x, 4 posición eje y, 5 color
    //Ponemos el player
    PutSprite( 0, 0, px, py, 0 );
    
}
void actualizar_personaje(void){
    PutSprite( 0, 0, px, py,  1 );
}

void inicializar_enemigos(void){

    SetSpritePattern( 32, pajaro0, 32); //1
    SetSpritePattern( 36, pajaro1, 32); //2
    SetSpritePattern( 40, pajaro2, 32);
    SetSpritePattern( 44, pajaro3, 32);
    SetSpritePattern( 48, pajaro4, 32);
    SetSpritePattern( 52, pajaro5, 32);
    SetSpritePattern( 56, pajaro6, 32);
    SetSpritePattern( 60, pajaro7, 32);
    SetSpritePattern( 64, pajaro8, 32);
    SetSpritePattern( 68, pajaro9, 32);//10
    SetSpritePattern( 72, pajaro10, 32);
    SetSpritePattern( 76, pajaro11, 32);
    SetSpritePattern( 80, pajaro12, 32);
    SetSpritePattern( 84, pajaro13, 32);
    SetSpritePattern( 88, pajaro14, 32);
    SetSpritePattern( 92, pajaro15, 32);
    SetSpritePattern( 96, pajaro16, 32);
    SetSpritePattern( 100, pajaro17, 32);
    SetSpritePattern( 104, pajaro18, 32);
    SetSpritePattern( 108, pajaro19, 32);


    SC5SpriteColors(1,LineColorsPajaro0);
    SC5SpriteColors(2,LineColorsPajaro1);
    SC5SpriteColors(3,LineColorsPajaro2);
    SC5SpriteColors(4,LineColorsPajaro3);
    SC5SpriteColors(5,LineColorsPajaro4);
    SC5SpriteColors(6,LineColorsPajaro5);
    SC5SpriteColors(7,LineColorsPajaro6);
    SC5SpriteColors(8,LineColorsPajaro7);
    SC5SpriteColors(9,LineColorsPajaro8);
    SC5SpriteColors(10,LineColorsPajaro9);
    SC5SpriteColors(11,LineColorsPajaro10);

    PutSprite( 1, 32, enemigos[0][0], enemigos[0][0], 1  );
}
void actualizar_enemigos(void){
    wait(5);
    for (int i=2;i<20; i++){
        enemigos[i][0]+=enemigos[i][2];
        PutSprite(i,enemigos[i][3],enemigos[i][0],enemigos[i][1], 1);
    }
}
static void wait( int j ) {
  volatile int i;

  for( i = 0; i < j; i++ ) {
  }
}


//Sistema de input
void procesar_entrada(void){
	// 0 son cursores teclado
	pm = JoystickRead(0);
    switch (pm)
    {
    case 1:
        py-=pv;
        Locate (0,0);
        printf("Arriba: pc: %c py: %c:",px, py);
        break;
    case 3:
        px+=pv;
        Locate (0,0);
        printf("Derecha: pc: %d py: %d:",px, py);
        break;
    case 5:
        py+=pv;
        Locate (0,0);
        printf("Abajo: pc: %c py: %f:",px, py);
        break;
    case 7:
        px-=pv;
        Locate (0,0);
        printf("Iaquierda: pc: %d py: %d:",px, py);
        break;
    default:
        break;
    }
}


void comprobar_colisiones(void){
    if (SpriteCollision()) {
        if(colorBorde==3){
            colorBorde=1;
        }else{
            colorBorde=3;
        }
        SetBorderColor(colorBorde);
        Beep();
        pColisionX=SpriteCollisionX();
        pColisionY=SpriteCollisionY();
        Locate (0,1);
        printf("Colision en : pc: %d py: %d:",pColisionX, pColisionX);
    }
}
