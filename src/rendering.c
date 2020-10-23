#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include "./game.h"
#include "./rendering.h"

const SDL_Color GRID_COLOR = { .r = 255, .g = 255, .b = 255 };
const SDL_Color PLAYER_X_COLOR = { .r = 16, .g = 146, .b = 152 };
const SDL_Color PLAYER_O_COLOR = { .r = 50, .g = 149, .b = 19 };
const SDL_Color TIE_COLOR = { .r = 100, .g = 100, .b = 100 };
////////////////////////////// Initialiser SDL et la fenaitre principale ///////////////////////////////////////////////////////////
SDL_Window *Initializer(SDL_Window *window)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
        fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    window = SDL_CreateWindow("Projet C Tic Tac Toe",
                                          100, 100,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_FULLSCREEN);
    if (window == NULL)
	{
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return window;
}
////////////////////////////// Creation du "renderer" /////////////////////////////////////////////////////////////////////////////
SDL_Renderer *InitRenderer(SDL_Renderer *renderer,SDL_Window *window)
{
     renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
	{
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        exit(1);
    }
    return renderer;
}
////////////////////////////// Initialisation de SDL_ttf ////////////////////////////////////////////////////////////////////////
void Init_Text()
{
	if(TTF_Init() == -1)
	{
		printf("failed to initialize SDL_TTF");
		exit(EXIT_FAILURE);
	}
}
////////////////////////////// La gestion des erreurs ///////////////////////////////////////////////////////////////////////////
void SDL_ERREUR_X(const char* x)
{
		SDL_Log("ERREUR : %s > %s\n",x,SDL_GetError());
		SDL_Quit();
		exit(EXIT_FAILURE);	
}
////////////////////////////// Dessin du rectangles /////////////////////////////////////////////////////////////////////////////
void Draw_carre(SDL_Renderer *renderer,int x,int y, int w, int h)
{
	SDL_Rect rectangle = {x,y,w,h};
	if(SDL_RenderFillRect(renderer, &rectangle) != 0)
		SDL_ERREUR_X("Impossible de dessiner le rectangle");
}
////////////////////////////// Importer les images /////////////////////////////////////////////////////////////////////////////
void LoadImage(SDL_Renderer *renderer,char *path,int x,int y, int w, int h)
{
	SDL_Surface *surface = IMG_Load(path);
	if(!surface)
	{
		printf("%s",IMG_GetError());
		exit(EXIT_FAILURE);
	}	
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!texture)
	{
		printf("%s",IMG_GetError());
		exit(EXIT_FAILURE);
	}
	SDL_Rect rect={x,y,w,h};
	SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
////////////////////////////// Responssable du dessin du jeux contre l'IA /////////////////////////////////////////////////////
void render_grid_com(SDL_Renderer *renderer)
{
   	//Couleur du traçage 
	SDL_SetRenderDrawColor(renderer, 251, 251, 251, 255);
	LoadImage(renderer,"ressources/bois.jpg",0,0,1366,768);
	//Traçage des lignes
	int i=0;
	for(i=0;i<=3;i++)
	{
		if(SDL_RenderDrawLine(renderer, 572+i, 109, 572+i, 763) != 0)
			SDL_ERREUR_X("Impossible de dessiner une ligne");
	}
	for(i=0;i<=3;i++)
	{
		if(SDL_RenderDrawLine(renderer, 792+i, 109, 792+i, 763) != 0)
			SDL_ERREUR_X("Impossible de dessiner une ligne");
	}
	for(i=0;i<=3;i++)
	{
		if(SDL_RenderDrawLine(renderer, 356, 325+i, 1010, 325+i) != 0)
			SDL_ERREUR_X("Impossible de dessiner une ligne");
	}
	for(i=0;i<=3;i++)
	{
		if(SDL_RenderDrawLine(renderer, 356, 545+i, 1010, 545+i) != 0)
			SDL_ERREUR_X("Impossible de dessiner une ligne");
	}
	//Désigne du carré
	SDL_SetRenderDrawColor(renderer, 255, 174, 94, 255);
	Draw_carre(renderer,356,109,216,216); //carre 4
	Draw_carre(renderer,796,109,215,216); //carre 6
	Draw_carre(renderer,576,329,216,216); //carre8
	Draw_carre(renderer,356,549,216,215); //carre 10
	Draw_carre(renderer,796,549,215,215); //carre 12

	SDL_SetRenderDrawColor(renderer, 174, 87, 0, 255);
	Draw_carre(renderer,576,109,216,216); //carre 5
	Draw_carre(renderer,356,329,216,216); //carre 7
	Draw_carre(renderer,796,329,215,216); //carre 9
	Draw_carre(renderer,576,549,216,215); //carre 11

	//Désigne bouton
	LoadImage(renderer,"ressources/images.jpg",0,1,100,99);
	LoadImage(renderer,"ressources/images.jpg",1266,1,100,99);
	LoadImage(renderer,"ressources/save.jpg",649,15,70,70);	
	LoadImage(renderer,"ressources/restart.jpg",429,15,70,70);	
	LoadImage(renderer,"ressources/home.jpg",869,15,70,70);	
	LoadImage(renderer,"ressources/exit1.jpg",1146,668,80,80);	
	
	//Désigne joueur
	SDL_SetRenderDrawColor(renderer, 50, 149, 19, 255);
	Draw_carre(renderer,49,155,250,490);
	SDL_SetRenderDrawColor(renderer, 16, 146, 152, 255);
	Draw_carre(renderer,1070,155,250,490);
	
	//Zone d'affichage d'historique des mouvement
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	Draw_carre(renderer,68, 493, 212, 130);
	Draw_carre(renderer,1089, 493, 212, 130);	
	
	//Zone d'affichage de score
	Draw_carre(renderer,115, 385, 100, 60);
	Draw_carre(renderer,1135, 385, 100, 60);
	
	LoadImage(renderer,"ressources/robot.jpg",109,163,130,130);	
	LoadImage(renderer,"ressources/man.jpg",1130,163,130,130);	
}
////////////////////////////// Responsable du dessin du jeux contre les humains //////////////////////////////////////////////
void render_grid(SDL_Renderer *renderer)
{
   	//Couleur du traçage 
	SDL_SetRenderDrawColor(renderer, 251, 251, 251, 255);
	LoadImage(renderer,"ressources/bois.jpg",0,0,1366,768);

	//Traçage des lignes
	int i=0;
	for(i=0;i<=3;i++)
	{
		if(SDL_RenderDrawLine(renderer, 572+i, 109, 572+i, 763) != 0)
			SDL_ERREUR_X("Impossible de dessiner une ligne");
	}
	for(i=0;i<=3;i++)
	{
		if(SDL_RenderDrawLine(renderer, 792+i, 109, 792+i, 763) != 0)
			SDL_ERREUR_X("Impossible de dessiner une ligne");
	}
	for(i=0;i<=3;i++)
	{
		if(SDL_RenderDrawLine(renderer, 356, 325+i, 1010, 325+i) != 0)
			SDL_ERREUR_X("Impossible de dessiner une ligne");
	}
	for(i=0;i<=3;i++)
	{
		if(SDL_RenderDrawLine(renderer, 356, 545+i, 1010, 545+i) != 0)
			SDL_ERREUR_X("Impossible de dessiner une ligne");
	}
	//Désigne du carré
	SDL_SetRenderDrawColor(renderer, 255, 174, 94, 255);
	Draw_carre(renderer,356,109,216,216); //carre 4
	Draw_carre(renderer,796,109,215,216); //carre 6
	Draw_carre(renderer,576,329,216,216); //carre8
	Draw_carre(renderer,356,549,216,215); //carre 10
	Draw_carre(renderer,796,549,215,215); //carre 12

	SDL_SetRenderDrawColor(renderer, 174, 87, 0, 255);
	Draw_carre(renderer,576,109,216,216); //carre 5
	Draw_carre(renderer,356,329,216,216); //carre 7
	Draw_carre(renderer,796,329,215,216); //carre 9
	Draw_carre(renderer,576,549,216,215); //carre 11

	//Désigne bouton
	LoadImage(renderer,"ressources/images.jpg",0,1,100,99);
	LoadImage(renderer,"ressources/images.jpg",1266,1,100,99);
	LoadImage(renderer,"ressources/restart.jpg",429,15,70,70);	
	LoadImage(renderer,"ressources/home.jpg",869,15,70,70);	
	LoadImage(renderer,"ressources/exit1.jpg",1146,668,80,80);	
	
	//Désigne joueur
	SDL_SetRenderDrawColor(renderer, 50, 149, 19, 255);
	Draw_carre(renderer,49,155,250,490);
	SDL_SetRenderDrawColor(renderer, 16, 146, 152, 255);
	Draw_carre(renderer,1070,155,250,490);
	
	//Zone d'affichage d'historique des mouvement
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	Draw_carre(renderer,68, 493, 212, 130);
	Draw_carre(renderer,1089, 493, 212, 130);
	
	//Zone d'affichage de score
	Draw_carre(renderer,115, 385, 100, 60);
	Draw_carre(renderer,1135, 385, 100, 60);
	
	LoadImage(renderer,"ressources/man2.jpg",109,163,130,130);	
	LoadImage(renderer,"ressources/man.jpg",1130,163,130,130);	
}

////////////////////////////// Dessiner  X à une cellule donnée //////////////////////////////////////////////////////////
void render_x(SDL_Renderer *renderer,int row, int column, const SDL_Color *color)
{
	for(int i=-3;i<=3;i++)
	{
		const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
		const float center_x = 356+CELL_WIDTH * 0.5 + column * CELL_WIDTH;
		const float center_y = 109 + CELL_HEIGHT * 0.5 + row * CELL_HEIGHT + i;
		SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
		SDL_RenderDrawLine(renderer,
					center_x - half_box_side,
					center_y - half_box_side,
					center_x + half_box_side,
					center_y + half_box_side
					);
		SDL_RenderDrawLine(renderer,
					center_x + half_box_side,
					center_y - half_box_side,
					center_x - half_box_side,
					center_y + half_box_side
					);
	}
}
////////////////////////////// Dessin des circles //////////////////////////////////////////////////////////////////////
void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);
   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);
   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);
      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}
////////////////////////////// Dessiner  O à une cellule donnée ///////////////////////////////////////////////////////////////////
void render_o(SDL_Renderer *renderer, int row, int column, const SDL_Color *color)
{
	SDL_SetRenderDrawColor(renderer, 50, 149, 19, 255);
	for(int i=-100;i<=100;i++)
	{
		const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
		const float center_x = 356 +CELL_WIDTH * 0.5 + column * CELL_WIDTH;
		const float center_y = 109+CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;
		DrawCircle(renderer,
                     center_x, center_y, half_box_side + 5 + i/50 );
	}
}
////////////////////////////// Dessiner le tableau aprés les modifications au sein du jeux ////////////////////////////////////////////
void render_board(SDL_Renderer *renderer, const int *board, const SDL_Color *player_x_color, const SDL_Color *player_o_color)
{
    for (int i = 0; i < N; ++i)
	{
        for (int j = 0; j < N; ++j)
		{
            switch (board[i * N + j])
			{
				case PLAYER_X:
					render_x(renderer, i, j, player_x_color);
					break;
				case PLAYER_O:
					render_o(renderer, i, j, player_o_color);
					break;
				default: {}
            }
        }
    }
}
////////////////////////////// Dessiner le jeux si l'etat est 'RUNNING_STATE' entre les Humains /////////////////////////////////////////////
void render_running_state(SDL_Renderer *renderer,game_t *game)
{
    render_grid(renderer);
    render_board(renderer,
                 game->board,
                 &PLAYER_X_COLOR,
                 &PLAYER_O_COLOR);
}
////////////////////////////// Dessiner le jeux si l'etat est 'RUNNING_STATE' contre l'IA ////////////////////////////////////////////////////
void render_running_state_com(SDL_Renderer *renderer,game_t *game)
{
    render_grid_com(renderer);
    render_board(renderer,
                 game->board,
                 &PLAYER_X_COLOR,
                 &PLAYER_O_COLOR);
}
////////////////////////////// Dessiner le jeux si il est terminé entre les humains ////////////////////////////////////////////////////////
void render_game_over_state(SDL_Renderer *renderer,
                            const game_t *game,
                            const SDL_Color *color)
{
    render_grid(renderer);
    render_board(renderer,
                 game->board,
                 color,
                 color);
}
////////////////////////////// Dessiner le jeux si il est terminé contre l'IA ///////////////////////////////////////////////////////////////
void render_game_over_state_com(SDL_Renderer *renderer,
                            const game_t *game,
                            const SDL_Color *color)
{
    render_grid_com(renderer);
    render_board(renderer,
                 game->board,
                 color,
                 color);
}
////////////////////////////// Dessiner le jeux dans chaque etat ///////////////////////////////////////////////////////////////////////////
void render_game(SDL_Renderer *renderer,game_t *game)
{
    switch (game->state)
	{
		case RUNNING_STATE:
			render_running_state(renderer, game);
			break;
		case RESTART:
			render_running_state(renderer, game);
			break;
		case PLAYER_X_WON_STATE:
			render_game_over_state(renderer, game, &PLAYER_X_COLOR);
			break;
		case PLAYER_O_WON_STATE:
			render_game_over_state(renderer, game, &PLAYER_O_COLOR);
			break;
		case TIE_STATE:
			render_game_over_state(renderer, game, &TIE_COLOR);
			break;
		default: {}
    }
}
////////////////////////////// Dessiner le jeux contre l'IA dans chaque etat ///////////////////////////////////////////////////////////////
void render_game_com(SDL_Renderer *renderer,game_t *game)
{
    switch (game->state)
	{
		case RUNNING_STATE:
			render_running_state_com(renderer, game);
			break;
		case RESTART:
			render_running_state_com(renderer, game);
			break;
		case PLAYER_X_WON_STATE:
			render_game_over_state_com(renderer, game, &PLAYER_X_COLOR);
			break;
		case PLAYER_O_WON_STATE:
			render_game_over_state_com(renderer, game, &PLAYER_O_COLOR);
			break;
		case TIE_STATE:
			render_game_over_state_com(renderer, game, &TIE_COLOR);
			break;
		default: {}
    }
}
////////////////////////////// Donner un effet dynamique aux buttons du jeu //////////////////////////////////////////////////////////////////
void Touch_Icone_com(SDL_Renderer *renderer,int x,int y)
{
	int h1=0,h2=0,h3=0,h4,w1=0,w2=0,w3=0,w4=0;
	if(x>649 && x<719 && y>15 && y<85)
	{
		h1=75;
		w1=75;			
	}
	else
	{
		h1=70,
		w1=70;
	}
	LoadImage(renderer, "ressources/save.jpg", 649,15,h1,w1);
		
	if(x>869 && x<939 && y>15 && y<85)
	{
		h2=75;
		w2=75;
	}
	else
	{
		h2=70;
		w2=70;
	}
		LoadImage(renderer,"ressources/home.jpg", 869,15,h2,w2);
		
	if(x>429 && x<499 && y>15 && y<85)
	{
		h3=75;
		w3=75;
	}
	else 
	{
		h3=70;
		w3=70;
	}
	LoadImage(renderer,"ressources/restart.jpg", 429,15,h3,w3);
		
	if(x>1146 && x<1226 && y>668 && y<748)
	{
		h4=85;
		w4=85;
			
	}
	else 
	{
		h4=80;
		w4=80;
	}
	LoadImage(renderer,"ressources/exit1.jpg", 1146,668,h4,w4);
}
////////////////////////////// Donner un effet dynamique aux buttons du jeu entres humains //////////////////////////////////////////////////////
void Touch_Icone(SDL_Renderer *renderer,int x,int y)
{
	int h1=0,h2=0,h3=0,h4,w1=0,w2=0,w3=0,w4=0;
	if(x>869 && x<939 && y>15 && y<85)
	{
		h2=75;
		w2=75;
	}
	else
	{
		h2=70;
		w2=70;
	}
		LoadImage(renderer,"ressources/home.jpg", 869,15,h2,w2);
		
	if(x>429 && x<499 && y>15 && y<85)
	{
		h3=75;
		w3=75;
	}
	else 
	{
		h3=70;
		w3=70;
	}
	LoadImage(renderer,"ressources/restart.jpg", 429,15,h3,w3);
		
	if(x>1146 && x<1226 && y>668 && y<748)
	{
		h4=85;
		w4=85;
			
	}
	else 
	{
		h4=80;
		w4=80;
	}
	LoadImage(renderer,"ressources/exit1.jpg", 1146,668,h4,w4);
}

void destroy(SDL_Window *window,SDL_Renderer *renderer)
{
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
