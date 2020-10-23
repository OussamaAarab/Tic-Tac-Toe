#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./game.h"
#include "./menu.h"
#include "./logic.h"
#include "player.h"
#include "./rendering.h"

int main(int argc, char *argv[])
{
   const SDL_Color Font_Color = { .r = 255, .g = 0, .b = 0 };
	    FILE *f=NULL;
		FILE *GameFile=NULL;
	f = fopen("Players.dat","rb+");
	GameFile = fopen("GameFile.dat","rb+");
	if(f==NULL)
	{
		printf("ERROR");
		exit(EXIT_FAILURE);
	}
	GameToSave GTS;
    SDL_Window *window= NULL;
    window = Initializer(window);
    Image_Init();
    SDL_Renderer *renderer = NULL;
    renderer = InitRenderer(renderer,window);
	int a=0;
	logo(renderer,&a);
	if(a==1)
		Draw_Menu(renderer);
	Init_Text();
     game_t game = {
        .board = { EMPTY, EMPTY, EMPTY,
                   EMPTY, EMPTY, EMPTY,
                   EMPTY, EMPTY, EMPTY },
        .player = PLAYER_X,
        .state = RUNNING_STATE
    };
	char **PlayerInfo = NULL;
	player **p=NULL;
	int taille=0;
	player *joueur = NULL;
    int i=0,j,menu = 0,menu2=0,Continue,menu3,menu4,HighScoreMenu,x=0,y=0 ;
    menu = NONE;
	SDL_Event e;
    while(menu!=EXIT_GAME && game.state!=QUIT_STATE)
    {
        for(i=0;i<N;i++)
        {
            for(j=0;j<N;j++) game.board[i]=EMPTY;

        }
		Draw_Menu(renderer);
        game.player = PLAYER_X,
        game.state = RUNNING_STATE;
		SDL_GetMouseState(&x,&y);
		Touch_Menu(renderer,x,y);
		SDL_RenderPresent(renderer);
        menu = menu1(e);
		
        switch(menu)
        {
            case NEW_GAME:
			menu2 = NONE2;
				while(menu2 != RETURN_BACK)
				{
							for(i=0;i<N;i++)
							{
								for(j=0;j<N;j++) {game.board[i*N+j]=EMPTY;}

							}
						game.player = PLAYER_X,
						game.state = RUNNING_STATE;
						
						Draw_Menu2(renderer);
						SDL_GetMouseState(&x,&y);
						Touch_Menu2(renderer,x,y);
						SDL_RenderPresent(renderer);
						menu2 = Menu2();
						menu3 = NONE3;
						switch(menu2)
						{
							case PLAY1_VS_PLAY2:
								
								GameLoop(&game,renderer);
								
								break;
							case PLAY_VS_COM:
								menu4 = NONE3;
								while (menu4!=BACK4)
								{	
									Draw_Menu4(renderer);
									SDL_RenderPresent(renderer);
									menu4 = Menu4();
									switch (menu4)
									{
										case NEW:
											while(joueur == NULL && menu4 != BACK4)
											{
												PlayerInfo = Infos_Window(renderer,PlayerInfo);
												if(PlayerInfo == NULL)
												{
													menu4=BACK4;
													menu3=BACK;
												}
												else{
													joueur = CreateNewPlayer(PlayerInfo[0],PlayerInfo[1],f);
													
													if(joueur == NULL)
													{
														message(renderer,"Allready exists","ressources/crazy.ttf",60,Font_Color,100,580);
														SDL_RenderPresent(renderer);
														SDL_Delay(500);
													}
												}
											}
											menu4=BACK4;
									break;
									case EXIST:
											while(joueur == NULL && menu4 != BACK4)
											{
												PlayerInfo = Infos_Window(renderer,PlayerInfo);
												if(PlayerInfo == NULL)
												{
													menu4=BACK4;
													menu3=BACK;
												}
												else{
													joueur = FindPlayer(PlayerInfo[0],f);
													if(joueur == NULL)
													{
														message(renderer,"Doesn't exist","ressources/crazy.ttf",60,Font_Color,400,580);
														SDL_RenderPresent(renderer);
														SDL_Delay(10000);
													}
													else if(strcmp(joueur->password ,PlayerInfo[1])!=0)
													{
														joueur = NULL;
														message(renderer,"Password doesn't match","ressources/crazy.ttf",60,Font_Color,100,580);
														SDL_RenderPresent(renderer);
														SDL_Delay(10000);
													}
												}
												
											}
											if(joueur!=NULL) printf("Player score: %d", joueur->score);
											
											menu4=BACK4;									
									 break;
									case BACK4 : 
										menu3 = BACK;
										break;
								
								default:
									break;
								}
							}
							
								while(menu3 != BACK)
								{
									Draw_Menu3(renderer);
									SDL_GetMouseState(&x,&y);
									Touch_Menu3(renderer, x, y);
									SDL_RenderPresent(renderer);
									for(i=0;i<N;i++)
									{
										for(j=0;j<N;j++) {game.board[i*N+j]=EMPTY;}

									}
						
									game.player = PLAYER_X,
									game.state = RUNNING_STATE;
									menu3 = Menu3();
									switch(menu3)
									{
										case EASY:
											joueur=GameLoopVSCOM(&game,renderer,joueur,GameFile,GTS,0);
											save(joueur,f);
											break;
										case HARD:
											joueur=GameLoopVSCOM_MINIMAX(&game,renderer,joueur,GameFile,GTS,0);
											save(joueur,f);
											break;
										default:
											break;
									}
									if(game.state == QUIT_STATE)
									{
										menu3 = BACK;
									}
									if(game.state == HOME)
									{
										menu3 = BACK;
									}
	
								}
								if(joueur != NULL){free(joueur);joueur = NULL;}
								if(PlayerInfo != NULL)
									{
										free(PlayerInfo[0]);
										free(PlayerInfo[1]);
										free(PlayerInfo);
										PlayerInfo = NULL;
									}
								break;

						}
						
						if(game.state == QUIT_STATE)
						{
							menu2=RETURN_BACK;
							
						}
						if(game.state == HOME)
						{
							menu2=RETURN_BACK;
							
						}
						
						
                }
				break;
			case HIGH_SCORE:
				p=FirstTen(f,p,&taille);
				HighScoreMenu = NONE4;
				while(HighScoreMenu != BACK4)
				{
					HighScoreMenu = Highest(renderer ,f,p,taille);

				}
				for(i=0 ; i<taille ; i++) free(p[i]);
				free(p);
				break;
			case CONTINUE :
				Continue = NONE4;
				while(joueur == NULL && Continue != BACK4)
				{
					PlayerInfo = Infos_Window(renderer,PlayerInfo);
					if(PlayerInfo == NULL)
					{
						Continue=BACK4;
					}
					else{
						joueur = FindPlayer(PlayerInfo[0],f);
						if(joueur == NULL)
						{
								message(renderer,"Doesn't exist","ressources/crazy.ttf",60,Font_Color,400,580);
								SDL_RenderPresent(renderer);
								SDL_Delay(500);
						}
					else if(strcmp(joueur->password ,PlayerInfo[1])!=0)
						{
							joueur = NULL;
							message(renderer,"Password doesn't match","ressources/crazy.ttf",60,Font_Color,100,580);
							SDL_RenderPresent(renderer);
							SDL_Delay(500);
						}
					if(joueur != NULL){
						GTS=LoadGame(joueur,GameFile,GTS);
						if(GTS.GameType == -1) {message(renderer,"No Game exists","ressources/crazy.ttf",60,Font_Color,100,580);SDL_RenderPresent(renderer);SDL_Delay(500);}
						if(GTS.GameType == 0) {joueur=GameLoopVSCOM(&game, renderer ,joueur,GameFile,GTS,1);save(joueur,f);}
						if(GTS.GameType == 1)	{joueur=GameLoopVSCOM_MINIMAX(&game, renderer ,joueur,GameFile,GTS,1);save(joueur , f);}
					}						
				}
				}
				if(joueur !=NULL) free(joueur);
				joueur =NULL;
				break;
            default:
                    break;
        }
		SDL_RenderPresent(renderer);
		
    }
	fclose(f);
	fclose(GameFile);
   destroy(window,renderer);
    return EXIT_SUCCESS;
}
