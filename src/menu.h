#ifndef MENU_H
#define MENU_H
#include "player.h" 
void Image_Init();//Initialiser SDL_Image
SDL_Surface *Load_Image(SDL_Surface *surface,char *Path);//creer une surface et inserer une image
SDL_Texture *Load_menu(SDL_Texture *Menu,SDL_Renderer *renderer,SDL_Surface *surface);//creer une texture qui va contenir l'image
void Draw_Menu(SDL_Renderer *renderer);
void Touch_Menu(SDL_Renderer *renderer,int x,int y);
int menu1(SDL_Event e);
void Draw_Menu2(SDL_Renderer *renderer);
int Menu2();
void Touch_Menu2(SDL_Renderer *renderer,int x,int y);
void Draw_Menu3(SDL_Renderer *renderer);
int Menu3();
void Touch_Menu3(SDL_Renderer *renderer,int x,int y);
void message(SDL_Renderer *renderer ,char *message,char *FontPath,int size, SDL_Color color,int x,int y);
void logo(SDL_Renderer *renderer,int *a);
char **Infos_Window(SDL_Renderer *renderer,char **info);
void Draw_Menu4(SDL_Renderer *renderer);
int Menu4();
int Highest(SDL_Renderer *renderer , FILE *f,player **p,int taille);
#endif // MENU_H
