#include "player.h"
#include "game.h"
#ifndef LOGIC_H_
#define LOGIC_H_
#include <SDL2/SDL.h>

void GameLoop(game_t *game,SDL_Renderer *renderer );//la fonction qui contien le jeux
player *GameLoopVSCOM(game_t *game,SDL_Renderer *renderer , player *joueur,FILE *GameFile,GameToSave GTS,int saved);
player *GameLoopVSCOM_MINIMAX(game_t *game,SDL_Renderer *renderer ,player *joueur,FILE *GameFile,GameToSave GTS,int saved);
GameToSave LoadGame(player *joueur,FILE *GameFile,GameToSave GTS);

#endif  // LOGIC_H_


