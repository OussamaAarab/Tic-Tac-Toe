#ifndef GAME_H_
#define GAME_H_

#define N 3
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768
#define GAME_WIDTH 660.0
#define GAME_HEIGHT 660.0
#define CELL_WIDTH (GAME_WIDTH / N )
#define CELL_HEIGHT (GAME_HEIGHT /N)
#include "player.h"
typedef enum {
    false,
    true
}bool;
typedef enum {
    PLAYER_X = -1,
    EMPTY = 0,
    PLAYER_O = 1
}Game_cells;//l'état de chaque cellule du jeux

typedef enum {
     RUNNING_STATE,
    PLAYER_X_WON_STATE,
    PLAYER_O_WON_STATE,
    TIE_STATE,
    HOME,
	SAVE,
	RESTART,
	RETURN_TO_LAST_MENU,
    QUIT_STATE
}Game_States;//L'état du jeux
typedef enum
{
	NONE2,
    PLAY1_VS_PLAY2,
    PLAY_VS_COM,
	RETURN_BACK
}MENU2;
typedef enum
{
	NONE3,
    EASY,
    HARD,
	BACK
}MENU3;
typedef enum
{
	NONE4,
    EXIST,
    NEW,
	BACK4
}MENU4;
typedef enum
{
    NONE,
    NEW_GAME,
    CONTINUE,
	HIGH_SCORE,
    EXIT_GAME
}MENU1;//les buttons du menu
typedef struct {
    int board[N * N];
    int player;
    int state;
} game_t;//structure qui va contenir tout les informations du jeux
typedef struct{
    game_t game;
    player player;
    int movesX[5] ;
    int movesO[5] ;
    int Xwins;
    int Owins;
    int GameType;
}GameToSave;
#endif  // GAME_H_

