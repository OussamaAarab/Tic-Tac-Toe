#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"
#include "rendering.h"
#include "player.h"
const SDL_Color Textcolor = { .r = 0, .g = 0, .b = 0 };
const SDL_Color Errorcolor = { .r = 0, .g = 0, .b = 0 };
//////////////////////////////////// Initialiser SDL_image /////////////////////////////////////////////////////////////
void Image_Init()
{
    if(IMG_Init(!(IMG_INIT_JPG | IMG_INIT_PNG)&(IMG_INIT_PNG | IMG_INIT_JPG)) )
    {
        printf("%s",IMG_GetError());
        exit(EXIT_FAILURE);
    }
}
int h1,w1;//des variables pour donner un effet dynamique aux buttons du menu
int a=0,b=0,c=0;
//////////////////////////////////// Dessiner le menu principale ///////////////////////////////////////////////////////
void Draw_Menu(SDL_Renderer *renderer)
{
	LoadImage(renderer,"ressources/bois.jpg",0,0,1366,768);
	LoadImage(renderer,"ressources/images.jpg",380,0,600,214);
	LoadImage(renderer,"ressources/new_game.jpg",520,335,300,100);
	LoadImage(renderer,"ressources/continue.jpg",520,445,300,100);
	LoadImage(renderer,"ressources/high_score.jpg",520,555,300,100);
}
//////////////////////////////////// Donner un effet dynamique aux buttons du menu principale //////////////////////////
void Touch_Menu(SDL_Renderer *renderer,int x,int y)
{
		if(x>520 && x<820 && y>555 && y<655)
		{
			h1=105;
			w1=305;
			LoadImage(renderer,"ressources/high_score.jpg",520,555,w1,h1);
			a=1;
		}
		else if(a==1)
		{
			a=0;			
			Draw_Menu(renderer);			
		}
			
		if(x>520 && x<820 && y>445 && y<545)
		{
			h1=105;
			w1=305;
			LoadImage(renderer,"ressources/continue.jpg",520,445,w1,h1);
			b=1;
		}
		else if(b==1)
		{
				b=0;			
				Draw_Menu(renderer);
		}

		if(x>520 && x<820 && y>335 && y<435)
		{
			h1=105;
			w1=305;
			LoadImage(renderer,"ressources/new_game.jpg",520,335,w1,h1);
			c=1;
		}
		else if(c==1)
		{			
			c=0;			
			Draw_Menu(renderer);
		}
}
////////////////////////////// Retourne le choix de l'utilisateur dans le menu principale //////////////////////////////
int menu1(SDL_Event e)
{
	int menu = NONE;
	int x=0,y=0;
    SDL_WaitEvent(&e);
	switch (e.type)
	{
		case SDL_QUIT:
			menu = EXIT_GAME;
            break;
        case SDL_MOUSEBUTTONDOWN:
			x=e.button.x;
            y=e.button.y;
            if(x>520 && x<820 && y>335 && y<435) {menu = NEW_GAME; break;}
            if(x>520 && x<820 && y>445 && y<545) {menu = CONTINUE; break;}
			if(x>520 && x<820 && y>555 && y<655) {menu = HIGH_SCORE; break;}
            break;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					menu = EXIT_GAME;
					break;
			}
		default: {}
	}
    return menu;
}
////////////////////////////// Dessiner le menu 2(NEW GAME) ////////////////////////////////////////////////////////////
void Draw_Menu2(SDL_Renderer *renderer)
{
	LoadImage(renderer,"ressources/bois.jpg", 0,0,1366,768);
	LoadImage(renderer,"ressources/images.jpg",380,0,600,214);
	LoadImage(renderer,"ressources/computer.jpg",480,335,380,100);
	LoadImage(renderer,"ressources/player.jpg",480,445,380,100);
}
////////////////////////////// Retourner le choix de l'utilisateur dans le menu 2 //////////////////////////////////////
int Menu2()
{
    int menu = NONE;
	int x=0,y=0;
	SDL_Event e;
    SDL_WaitEvent(&e);
	switch (e.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			x=e.button.x;
            y=e.button.y;
            if(x>480 && x<860 && y>335 && y<435) {menu=PLAY_VS_COM;break;}
            if(x>480 && x<860 && y>445 && y<545) {menu =PLAY1_VS_PLAY2 ;break;}
            break;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					menu = RETURN_BACK;
					break;
			}
		default: {}
	}    
    return menu;	
}
////////////////////////////// Donner un effet dynamique aux buttons du menu 2 /////////////////////////////////////////
void Touch_Menu2(SDL_Renderer *renderer,int x,int y)
{
	if(x>480 && x<860 && y>335 && y<435)
	{
		h1=105;
		w1=385;
		LoadImage(renderer,"ressources/computer.jpg",480,335,w1,h1);
		a=1;
	}
	else if(a==1)
	{		
		a=0;			
		Draw_Menu2(renderer);			
	}
				
	if(x>480 && x<860 && y>445 && y<545)
	{
		h1=105;
		w1=385;
		LoadImage(renderer,"ressources/player.jpg",480,445,w1,h1);
		b=1;
	}
	else if(b==1)
	{		
		b=0;			
		Draw_Menu2(renderer);
	}
}
////////////////////////////// Dessiner le menu 3 (Game Vs Computer) ///////////////////////////////////////////////////
void Draw_Menu3(SDL_Renderer *renderer)
{
	LoadImage(renderer,"ressources/bois.jpg", 0,0,1366,768);
	LoadImage(renderer,"ressources/images.jpg",380,0,600,214);
	LoadImage(renderer,"ressources/easy.jpg",520,335,300,100);
	LoadImage(renderer,"ressources/hard.jpg",520,445,300,100);
}
////////////////////////////// Retournee le choix de l'utilisateur dans le menu 3 //////////////////////////////////////
int Menu3()
{
    int menu = NONE;
	int x=0,y=0;
	SDL_Event e;
    SDL_WaitEvent(&e);
    switch (e.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			x=e.button.x;
            y=e.button.y;
            if(x>520 && x<820 && y>335 && y<435) {menu = EASY;break;}
            if(x>520 && x<820 && y>445 && y<545) {menu = HARD ;break;}
            break;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				menu = BACK;
				break;
			}
		default: {}
	}
	return menu;	
}
////////////////////////////// Donner un effet dynamique aux buttons du menu 3 /////////////////////////////////////////
void Touch_Menu3(SDL_Renderer *renderer,int x,int y)
{
	if(x>520 && x<820 && y>335 && y<435)
	{
		h1=105;
		w1=305;
		LoadImage(renderer,"ressources/easy.jpg",520,335,w1,h1);
		a=1;
	}
	else if(a==1)
	{
		a=0;			
		Draw_Menu3(renderer);			
	}
				
	if(x>520 && x<820 && y>445 && y<545)
	{
		h1=105;
		w1=305;
		LoadImage(renderer,"ressources/hard.jpg",520,445,w1,h1);
		b=1;
	}
	else if(b==1)
	{
		b=0;			
		Draw_Menu3(renderer);
	}
}
////////////////////////////// Afficher un message à l'utilisateur /////////////////////////////////////////////////////
void message(SDL_Renderer *renderer ,char *message,char *FontPath,int size, SDL_Color color,int x,int y)
{
	SDL_Texture *texte=NULL;
	TTF_Font *font = TTF_OpenFont(FontPath,size);
	SDL_Rect rect={
		.x=x,
		.y=y,
		.w=0,
		.h=0
	};
	if(!font)
	{
		printf("Failed to load font ");
		exit(EXIT_FAILURE);
	}
	SDL_Surface *MessageSurface= TTF_RenderText_Solid(font , message , color);
	if(!MessageSurface)
	{
		printf("Failed to create text surface : %s ",TTF_GetError());
		exit(EXIT_FAILURE);
	}
	texte = SDL_CreateTextureFromSurface(renderer,MessageSurface);
	SDL_FreeSurface(MessageSurface);
    SDL_QueryTexture(texte,NULL,NULL,&rect.w,&rect.h);
	SDL_RenderCopy(renderer, texte, NULL, &rect);
}
////////////////////////////// Dessiner la page du début du jeu ////////////////////////////////////////////////////////
void logo(SDL_Renderer *renderer,int *a)
{
	for(int i=0;i<=250;i+=5)
	{
		LoadImage(renderer,"ressources/logo.jpg",490,50,430,164);
		LoadImage(renderer,"ressources/tic.jpg",370,380,700,124);
		SDL_SetRenderDrawColor(renderer, 200, 173, 127, 255-i);
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
		SDL_RenderFillRect(renderer, NULL);
		SDL_RenderPresent(renderer);
		SDL_Delay(70);
		if(i==250)
			*a=1;
	}
}
////////////////////////////// Dessiner le menu 4 (NEW Player / SIGN IN) ///////////////////////////////////////////////
void Draw_Menu4(SDL_Renderer *renderer)
{
	LoadImage(renderer,"ressources/bois.jpg", 0,0,1366,768);
	LoadImage(renderer,"ressources/images.jpg",380,0,600,214);
	LoadImage(renderer,"ressources/new_player.jpg",520,335,300,100);
    LoadImage(renderer,"ressources/sign_in.jpg",520,445,300,100);
}
////////////////////////////// Retourner le choix du l'utilisateur dans ce menu ////////////////////////////////////////
int Menu4()
{
    int menu = NONE4;
	int x=0,y=0;
	SDL_Event e;
    SDL_WaitEvent(&e);
    switch (e.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			x=e.button.x;
            y=e.button.y;
            if(x>520 && x<820 && y>335 && y<435) {menu = NEW;break;}
            if(x>520 && x<820 && y>445 && y<535) {menu = EXIST ;break;}
            break;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					menu = BACK4;
					break;
			}
		default: {}
	}    
    return menu;	
}
////////////////////////////// Dessiner la page ou l'utilisateur entre ses données /////////////////////////////////////
void redraw(SDL_Renderer *renderer,char **info,int h,int w)
{
    char password[40];
    for(int i=0;i<strlen(info[1]);i++)
    {
        password[i]='*';
    }
    password[strlen(info[1])] = '\0';
	LoadImage(renderer,"ressources/bois.jpg",0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	LoadImage(renderer,"ressources/images.jpg",380,0,600,214);
	SDL_SetRenderDrawColor(renderer,255,128,64,255);
	Draw_carre(renderer,290,360,210, 50);
	Draw_carre(renderer,290,470,210, 50);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    message(renderer,"Name    :","ressources/crazy2.ttf",20,Textcolor,300,370);
    Draw_carre(renderer,500,360,500, 50);
    message(renderer,"Password :","ressources/crazy2.ttf",20,Textcolor,300,480);
    Draw_carre(renderer,500,470,500, 50);
	if(info[0][0]!='\0')
    {
		message(renderer,info[0],"ressources/crazy1.ttf",20,Textcolor,510,375);
	}
    if(info[1][0]!='\0')
    {
		message(renderer,password,"ressources/crazy1.ttf",20,Textcolor,510,485);
	}
    LoadImage(renderer,"ressources/enter.jpg",2*SCREEN_WIDTH/3,570,200+h,70+w);
    SDL_RenderPresent(renderer);
}
////////////////////////////// Retourner les informations de l'utilisateur /////////////////////////////////////////////
char **Infos_Window(SDL_Renderer *renderer,char **info)
{
    LoadImage(renderer,"ressources/bois.jpg",0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    LoadImage(renderer,"ressources/enter.jpg",2*SCREEN_WIDTH/3,570,200,70);
    SDL_Event e,ev;
    info = (char**)malloc(2*sizeof(char*));
   	info[1] = (char*)malloc(40*sizeof(char));
   	info[0] = (char*)malloc(40*sizeof(char));
    info[0][0]='\0';
    info[1][0]='\0';
    int quit=0,X,Y,x,y,w=0,h=0;
    SDL_StartTextInput();
    while(!quit)
    {
		SDL_GetMouseState(&x,&y);
		if(x>2*SCREEN_WIDTH/3 && (x<2*SCREEN_WIDTH/3+200) && y>570 && y<640 )
		{
			h=10;
			w=10;
		}
	else{
		h=0;
		w=0;
	}
	redraw(renderer , info,h,w);
		
        while(SDL_PollEvent(&e)!=0)
        {
            switch (e.type)
            {
            case SDL_QUIT :
                quit=1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                Y=e.button.y;
                X=e.button.x;
                if(X>2*SCREEN_WIDTH/3 && (X<2*SCREEN_WIDTH/3+200) && Y>570 && Y<640 )
                {
                    if(info[1][0] == '\0' || info[0][0] == '\0')
                    {
                        message(renderer,"Enter your informations","ressources/crazy.ttf",60,Errorcolor,100,580);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(500);
                    }
                    else quit=1; 
                    
                }
                while(X>500 && X<1000 && Y>360 && Y<410)
                {
							SDL_GetMouseState(&x,&y);
							if(x>2*SCREEN_WIDTH/3 && (x<2*SCREEN_WIDTH/3+200) && y>570 && y<640 )
							{
								h=10;
								w=10;
							}
						else{
							h=0;
							w=0;
	}
					SDL_WaitEvent(&ev);
					if(ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN)
                    {
						if(ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && strlen(info[0])>0)
                        {
							info[0][strlen(info[0])-1]='\0';
                        }
                        else if(ev.type == SDL_TEXTINPUT && strlen(info[0])<39)
                        {
							strcat(info[0],ev.text.text);
                        }
                        else if(ev.type == SDL_TEXTINPUT && strlen(info[0])>=39)
                        {
							printf("\a");
                        }
					}     
                    if(ev.type == SDL_MOUSEBUTTONDOWN)
                    {
						Y=ev.button.y;
                        X=ev.button.x;
                        if(X>2*SCREEN_WIDTH/3 && (X<2*SCREEN_WIDTH/3+200) && Y>570 && Y<640 )
                        {
							if(info[1][0] == '\0' || info[0][0] == '\0')
                            {
								message(renderer,"Enter your informations","ressources/crazy.ttf",60,Errorcolor,100,580);
                                SDL_RenderPresent(renderer);
                                SDL_Delay(500);
                            }
                            else quit=1; 
						}                            
					}
                    redraw(renderer , info,h,w);  
                    if(ev.key.keysym.sym == SDLK_ESCAPE)
                    {
						return NULL;
                    }              
                }
                while(X>500 && X<1000 && Y>470 && Y<520)
                {
							SDL_GetMouseState(&x,&y);
							if(x>2*SCREEN_WIDTH/3 && (x<2*SCREEN_WIDTH/3+200) && y>570 && y<640 )
							{
								h=10;
								w=10;
							}
						else{
							h=0;
							w=0;
						}
					SDL_WaitEvent(&ev);
                    if(ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN)
                    {
						if(ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && strlen(info[1])>0)
                        {
							info[1][strlen(info[1])-1]='\0';
                        }
                        else if(ev.type == SDL_TEXTINPUT && strlen(info[1])<39)
                        {
							strcat(info[1],ev.text.text);
                        }
                        else if(ev.type == SDL_TEXTINPUT && strlen(info[0])>=39)
                        {
							printf("\a");
                        }                            
					}     
                    if(ev.type == SDL_MOUSEBUTTONDOWN)
                    {
						Y=ev.button.y;
                        X=ev.button.x;
                        if(X>2*SCREEN_WIDTH/3 && (X<2*SCREEN_WIDTH/3+200) && Y>570 && Y<640 )
                        {
							if(info[1][0] == '\0' || info[0][0] == '\0')
                            {
								message(renderer,"Enter your informations","ressources/crazy.ttf",60,Errorcolor,100,580);
                                SDL_RenderPresent(renderer);
                                SDL_Delay(500);
                            }
                            else quit=1; 
                        }
					}
                    if(ev.key.keysym.scancode == SDL_SCANCODE_RETURN)
                    {
						Y=0;
                        X=0;
                        if(info[1][0] == '\0' || info[0][0] == '\0')
                        {
							message(renderer,"Enter your informations","ressources/crazy.ttf",60,Errorcolor,100,580);
                            SDL_RenderPresent(renderer);
                            SDL_Delay(500);
						}
                        else quit=1; 
					}
                    if(ev.key.keysym.sym == SDLK_ESCAPE)
                    {
						return NULL;
                    }
                    redraw(renderer , info,h,w);                
				}
                break;  
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						return NULL;
						break;
				}
            default: {}       
             }
            redraw(renderer , info,h,w);
        }
    }
    SDL_StopTextInput();
    if(info[0][0]=='\0' && info[1][0]=='\0') return NULL;
    return info;
}
////////////////////////////// Afficher les dix premiers joueurs selon leurs score /////////////////////////////////////
int Highest(SDL_Renderer *renderer , FILE *f,player **p,int taille)
{
    LoadImage(renderer,"ressources/bois.jpg",0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	LoadImage(renderer,"ressources/images.jpg",380,0,600,214);
    LoadImage(renderer,"ressources/continue.jpg",1090,680,200,70);
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
	Draw_carre(renderer,415,225,500, 525);
	LoadImage(renderer,"ressources/10.jpg",450,695,45,35);
	LoadImage(renderer,"ressources/9.jpg",450,645,45,35);
	LoadImage(renderer,"ressources/8.jpg",450,595,45,35);
	LoadImage(renderer,"ressources/7.jpg",450,545,45,35);
	LoadImage(renderer,"ressources/6.jpg",450,495,45,35);
	LoadImage(renderer,"ressources/5.jpg",450,445,45,35);
	LoadImage(renderer,"ressources/4.jpg",450,395,45,35);
	LoadImage(renderer,"ressources/3.jpg",450,345,45,35);
	LoadImage(renderer,"ressources/2.jpg",450,295,45,35);
	LoadImage(renderer,"ressources/1.jpg",450,245,45,35);
    char score[5];
    for(int i=0;i<taille;i++)
    {
            message(renderer,p[taille-i-1]->PlayerName,"ressources/crazy.ttf",30,Errorcolor,SCREEN_WIDTH/2.5,250+50*i);
            itoa(p[taille-i-1]->score,score,10);
            message(renderer,score,"ressources/crazy.ttf",30,Errorcolor,SCREEN_WIDTH/2.5+300,250+50*i);
    }
    SDL_RenderPresent(renderer);
    int menu = NONE4;
	int x=0,y=0;
	SDL_Event e;
    SDL_WaitEvent(&e);
    switch (e.type)
	{
		case SDL_MOUSEBUTTONDOWN:
			x=e.button.x;
            y=e.button.y;
            if(x>1090 && x<1290 && y>680 && y<750) {menu = BACK4;break;}
            break;
		case SDL_KEYDOWN:
			switch(e.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					menu = BACK4;
					break;
			}
		default: {}
	}  
    return menu;	
}