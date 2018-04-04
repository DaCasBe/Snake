#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define V 21
#define H 75
#define N 100

//Serpiente
typedef struct{
	int x;
	int y;
	int modX;
	int modY;
	char imagen;
}serpiente;

//Fruta
typedef struct{
	int x;
	int y;
}fruta;

serpiente snake[N];
fruta fruit;

void inicio(int *tam,char campo[V][H]);
void borde(char campo[V][H]);
void leerDatos(char campo[V][H],int tam);
void leerCampo(char campo[V][H]);
void bucledeljuego(char campo[V][H],int tam);
void dibujarCampo(char campo[V][H]);
void datos(char campo[V][H],int *tam,int *muerto);
void intro_datos(char campo[V][H],int tam);
void actualizar(char campo[V][H],int tam);

int main(){
	int tam;
	char campo[V][H];
	
	inicio(&tam,campo);
	bucledeljuego(campo,tam);
	
	system("pause");
	return 0;
}

//Inicialización del juego
void inicio(int *tam,char campo[V][H]){
	int i;
	
//Declaración inicial de la cabeza de la serpiente
	snake[0].x=37;
	snake[0].y=10;
	
//Declaración inicial del tamaño de la serpiente
	*tam=4;

//Aparición aleatoria de la fruta
	srand(time(NULL));
	fruit.x=rand()%(H-1);
	fruit.y=rand()%(V-1);
	
	while(fruit.x==0){
		fruit.x=rand()%(H-1);
	}
	
	while(fruit.y==0){
		fruit.y=rand()%(V-1);
	}
	
//Declaración del movimiento de la serpiente
	for(i=0;i<*tam;i++){
		snake[i].modX=1;
		snake[i].modY=0;
	}
	
	borde(campo);
	leerDatos(campo,*tam);
}

void borde(char campo[V][H]){
	int i;
	int j;
	
//Delimitación del campo
	for(i=0;i<V;i++){
		for(j=0;j<H;j++){
			if(i==0 || i==V-1){
				campo[i][j]='-';
			}
			else if(j==0 || j==H-1){
				campo[i][j]='|';
			}
			else{
				campo[i][j]=' ';
			}
		}
	}
}

void leerDatos(char campo[V][H],int tam){
	int i;
	
//Apariencia del cuerpo de la serpiente
	for(i=1;i<tam;i++){
		snake[i].x=snake[i-1].x-1;
		snake[i].y=snake[i-1].y;
		snake[i].imagen='X';
	}
	
//Apariencia de la cabeza de la serpiente
	snake[0].imagen='O';

//Declaración de la posición de la serpiente
	for(i=0;i<tam;i++){
		campo[snake[i].y][snake[i].x]=snake[i].imagen;
	}

//Apariencia de la fruta
	campo[fruit.y][fruit.x]='%';
}

//Lectura del campo
void leerCampo(char campo[V][H]){
	int i;
	int j;
	
	for(i=0;i<V;i++){
		for(j=0;j<H;j++){
			printf("%c",campo[i][j]);
		}
		printf("\n");
	}
}

void bucledeljuego(char campo[V][H],int tam){
	int muerto=0;
	
	do{
		dibujarCampo(campo);
		datos(campo,&tam,&muerto);
		actualizar(campo,tam);
		Sleep(0.0001);
	}while(muerto==0);
}

void dibujarCampo(char campo[V][H]){
	leerCampo(campo);
	system("cls");
}

void datos(char campo[V][H],int *tam,int *muerto){
	int i;
	int tecla;

//Comprobación continua de muerte
	if(snake[0].x==0 || snake[0].x==H-1 || snake[0].y==0 || snake[0].y==V-1){
		*muerto=1;
	}
	
	for(i=1;i<*tam && *muerto==0;i++){
		if(snake[0].x==snake[i].x && snake[0].y==snake[i].y){
			*muerto=1;
		}
	}
	
//Comprobación continua de comida de fruta
	if(snake[0].x==fruit.x && snake[0].y==fruit.y){
		*tam+=1;
		snake[*tam-1].imagen='X';

//Aparición aleatoria de fruta
		fruit.x=rand()%(H-1);
		fruit.y=rand()%(V-1);
	
		while(fruit.x==0){
			fruit.x=rand()%(H-1);
		}
	
		while(fruit.y==0){
			fruit.y=rand()%(V-1);
		}
	}

//Declaración del movimiento de la serpiente
	if(*muerto==0){
		if(kbhit()==1){
			tecla=getch();
			
			if(tecla=='8' && snake[0].modY!=1){
				snake[0].modX=0;
				snake[0].modY=-1;
			}
			
			if(tecla=='2' && snake[0].modY!=-1){
				snake[0].modX=0;
				snake[0].modY=1;
			}
			
			if(tecla=='4' && snake[0].modX!=1){
				snake[0].modX=-1;
				snake[0].modY=0;
			}
			
			if(tecla=='6' && snake[0].modX!=-1){
				snake[0].modX=1;
				snake[0].modY=0;
			}
		}
	}
}

void intro_datos(char campo[V][H],int tam){
	int i;

//Crear movimiento de la serpiente
	for(i=tam-1;i>0;i--){
		snake[i].x=snake[i-1].x;
		snake[i].y=snake[i-1].y;
	}
	
	snake[0].x += snake[0].modX;
	snake[0].y += snake[0].modY;
	
	for(i=0;i<tam;i++){
		campo[snake[i].y][snake[i].x]=snake[i].imagen;
	}
	
	campo[fruit.y][fruit.x]='%';
}

void actualizar(char campo[V][H],int tam){
//Borrar los datos anteriores
	borde(campo);
	
//Introducir los nuevos datos
	intro_datos(campo,tam);
}
