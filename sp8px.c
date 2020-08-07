//stdio.h implementa el printf (o imprimir formateado), ver http://cplusplus.com/reference/cstdio/printf/
#include <stdio.h>
//Puedes ver las funciones que implementa msx_fusion.h abriendo el archivo
#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"

/*Es importante saber que c necesita que 1 se declaren las funciones*****/
/* Por norma general estas definiciones se ponen en un archivo.h y se incluyen como las de arriba*/
void inicializar_sprite_8px(void);
void procesar_entrada(void);
void inicializar_personaje(void);
void actualizar_personaje(void);
void comprobar_colisiones(void);
//Personaje
//Ver Inicializar personaje
int px,py,pv,pm, pColisionX, pColisionY;
int colorBorde=0;
/********************Fin de las declaraciones**************************/





// Lo 1 es definir nuestro sprite, creamos un array de chars
// recuerda que un char es un byte que puede contener un valor de -125 a 124
// o si es sin signo desde 0 a 255
static const unsigned char player8px[] = {
  0x3C, /* 00111100 */ /* 60 */
  0x7E, /* 01111110 */ /* 126 */
  0xFF, /* 11111111 */ /* 255 */
  0xFF, /* 11111111 */
  0xFF, /* 11111111 */
  0xFF, /* 11111111 */
  0x7E, /* 01111110 */
  0x3C  /* 00111100 */
};
static const unsigned char bloques8px[] = {
  0xFF, /* 11111111 */ /* 255 */
  0xFF, /* 11111111 */ 
  0xFF, /* 11111111 */ 
  0xFF, /* 11111111 */
  0xFF, /* 11111111 */
  0xFF, /* 11111111 */
  0xFF, /* 11111111 */
  0xFF  /* 11111111 */
};










void main(void){
    //Hay que poner la pantalla en screen 1
    Screen(1);
    inicializar_personaje();
    inicializar_sprite_8px();
    //Bucle render
    while(1){
        procesar_entrada();
        actualizar_personaje();
        comprobar_colisiones();
    }
}
void inicializar_personaje(void){
    // px= player posición eje x, py= player posición eje y
    // pv player velocidad, pm= player movimiento (se obtiene del teclado)
    px=100; py=100; pv=5; pm=0;
}
void inicializar_sprite_8px(void){
    // lo metemos en la tabla de dEfinición de patrones
    // el 1 argumento es la posición en la poisión en la tabla de definición de sprites (sprite pattern)
    // el 2 argumentos son los datos del sprite
    // el 3 argumento es el tamaño de bytes
    SetSpritePattern( 0, player8px,8 );
    SetSpritePattern( 1, player8px,8 );
    SetSpritePattern( 2, bloques8px,8 );
    
    // Mostramos nuestro esprite
    // 1. el plano o su definición en la tabla de atributos, ahí s e alamcenará la posición x e y
    // 2 la definición en sprite pattern
    // 3 posición eje x, 4 posición eje y, 5 color
    PutSprite( 0, 0, px, py,  6 );
    PutSprite( 1, 0, 10, 50,  3 );
    //creamos un monton de bloques
    int i;
    for( i = 2; i < 25; i++ ){
        PutSprite( i, 2, 150, i*8,  10 );
    }
    
}
void actualizar_personaje(void){
    PutSprite( 0, 0, px, py,  6 );
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
