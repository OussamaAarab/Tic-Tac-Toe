#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "./game.h"
#include "./logic.h"
#include "./player.h"
#include "rendering.h"
#include "menu.h"

const SDL_Color color = { .r = 255, .g = 255, .b = 255 };
////////////////////////////// Donner le role a l'autre joueur /////////////////////////////////////////////////////////
void switch_player(game_t *game)
{
    if (game->player == PLAYER_X){
        game->player = PLAYER_O;
    } else if (game->player == PLAYER_O) {
        game->player = PLAYER_X;
    }
}
////////////////////////////// Verifier s'il existe un vainqueur ///////////////////////////////////////////////////////
int check_player_won(game_t *game, int player)
{
    int row_count = 0;
    int column_count = 0;
    int diag1_count = 0;
    int diag2_count = 0;
    for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			if (game->board[i * N + j] == player)
			{
				row_count++;
            }
            if (game->board[j * N + i] == player)
			{
                column_count++;
            }
        }
        if (row_count >= N || column_count >= N)
		{
            return 1;
        }
        row_count = 0;
        column_count = 0;
        if (game->board[i * N + i] == player)
		{
            diag1_count++;
        }
        if (game->board[i * N + N - i - 1] == player)
		{
            diag2_count++;
        }
    }
    return diag1_count >= N || diag2_count >= N;
}
////////////////////////////// Compter les cellules de meme etat ///////////////////////////////////////////////////////
int count_cells(const int *board, int cell)
{
    int count = 0;
    for (int i = 0; i < N * N; ++i)
	{
		if (board[i] == cell)
		{
            count++;
        }
    }
    return count;
}
////////////////////////////// Verifier si le jeu est terminé /////////////////////////////////////////////////////////
void game_over_condition(game_t *game)
{
    if (check_player_won(game, PLAYER_X)) {
        game->state = PLAYER_X_WON_STATE;
    } else if (check_player_won(game, PLAYER_O)) {
        game->state = PLAYER_O_WON_STATE;
    } else if (count_cells(game->board, EMPTY) == 0) {
        game->state = TIE_STATE;
    }
}
////////////////////////////// Remplir la celule (si c'est possible) choisis par un joueur et verifie s'il existe un vainqueur /////////////
void player_turn(game_t *game, int row, int column)
{
    if (game->board[row * N + column] == EMPTY) {
        game->board[row * N + column] = game->player;
        switch_player(game);
        game_over_condition(game);
    }
}
////////////////////////////// Reinitialiser le jeu à zero /////////////////////////////////////////////////////////////
void reset_game(game_t *game)
{
    game->player = PLAYER_X;
    game->state = RUNNING_STATE;
    for (int i = 0; i < N * N; ++i) {
        game->board[i] = EMPTY;
    }
}
///////////////////////////// Executer 'player_turn' si le jeux n'est pas encore terminé et reinitialise le jeux si non ////////////////////
void click_on_cell(SDL_Renderer *renderer,game_t *game, int row, int column)
{
    if (game->state == RUNNING_STATE) {
        player_turn(game, row, column);
    }
	else {
        reset_game(game);
    }
}
////////////////////////////// Enregistrer les mouvements effectués par un joueur //////////////////////////////////////
int* PlayerMoves(int *moves,int row,int column,int *n)
{
    *n+=1;
    int i=*n;
    moves[i] = row*N + column + 1;
    return moves;
}
////////////////////////////// Afficher les mouvements effectués par un joueur /////////////////////////////////////////
void Show_Player_Moves(SDL_Renderer *renderer ,int *moves,int b,int n,int player)
{
    int a,line=0;
    if(player == PLAYER_O)
    {
        a = 83;
        b =+ 503;
    }
    if(player == PLAYER_X)
    {
        a = 1105;
        b += 503;
    }
    if(n<0) return;
    char Message[40] = "Choose cell ";
    char cell[5];
	for (size_t i = 0; i < n+1; i++)
	{
       if(moves[i]>=0)
       {
        itoa(moves[i],cell,10);
        strcat(Message,cell);       
        message(renderer ,Message,"ressources/crazy.ttf",20,color,a,b+20*line);
        line++;
        Message[12]='\0';
       }
   }  
}
////////////////////////////// Boucle du jeu 'player 1 vs player 2' ///////////////////////////////////////////////////
void GameLoop(game_t *game,SDL_Renderer *renderer )
{
    SDL_Event e;
    int *MovesX = NULL;
    int *MovesO=NULL;
    MovesX = (int*)malloc(5*sizeof(int));
    MovesO = (int*)malloc(5*sizeof(int));
	int X=0;
    int Y=0;
	int x,y,player,xwins=0,owins=0;
    char Xwins[5],Owins[5];
    int a=0,b=0,Player_X_nb_moves = -1,Player_O_nb_moves=-1;
    int State = game->state;
    while (game->state != QUIT_STATE && game->state != HOME && game->state != RETURN_TO_LAST_MENU)
	{
		itoa(xwins,Xwins,10);
        itoa(owins,Owins,10);
        State = game->state;
        SDL_GetMouseState(&x,&y);
        Touch_Icone(renderer,x,y);
		SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        render_game(renderer, game);
        if(game->state == RUNNING_STATE)
		{
			Show_Player_Moves(renderer,MovesO,0,Player_O_nb_moves,PLAYER_O);
            Show_Player_Moves(renderer,MovesX,0,Player_X_nb_moves,PLAYER_X);
        }
		message(renderer,"PLAYER 2","ressources/crazy.ttf",40,color,1100,300);
		message(renderer,"PLAYER 1","ressources/crazy.ttf",40,color,90,300);
        message(renderer,Xwins,"ressources/crazy.ttf",40,color,1170,400);
        message(renderer,Owins,"ressources/crazy.ttf",40,color,150,400);
		SDL_RenderPresent(renderer);           
        while (SDL_PollEvent(&e))
		{              
			switch (e.type)
			{
				case SDL_QUIT:
					game->state = QUIT_STATE;
					break;
				case SDL_MOUSEBUTTONDOWN:
					Y=e.button.y;
					X=e.button.x;
					if(X>355 && X<1011 && Y>109 && Y<764)
					{
						player = game->player;
                        click_on_cell(renderer,game,(Y-109)/ CELL_HEIGHT,(X-356)/ CELL_WIDTH);
                        SDL_RenderPresent(renderer);
					}
					if(x>869 && x<939 && y>15 && y<85)
					{
						game->state = HOME;
					}
					if(x>429 && x<499 && y>15 && y<85)
					{
						reset_game(game);
                        game->state = RESTART;
					}
					if(x>1146 && x<1226 && y>668 && y<748)
					{
						game->state = QUIT_STATE;
					}                
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							game->state = RETURN_TO_LAST_MENU;
							break;
					}
				default: {}
            }  
            if(e.type == SDL_MOUSEBUTTONDOWN && State == RUNNING_STATE)
            {
				if(player != game->player && X>355 && X<1011 && Y>109 && Y<764)
				{
					if(player == PLAYER_X)
					{
						MovesX = PlayerMoves(MovesX,(Y-109)/ CELL_HEIGHT,(X-356)/ CELL_WIDTH,&Player_X_nb_moves);
					}
                    if(player == PLAYER_O)
                    {
						MovesO = PlayerMoves(MovesO,(Y-109)/ CELL_HEIGHT,(X-356)/ CELL_WIDTH,&Player_O_nb_moves);
					}
                }
			}
			if(game->state != RUNNING_STATE)
			{
				for (size_t i = 0; i < 5; i++)
				{
					MovesX[i] = -1;
					MovesO[i] = -1;
				} 
				Player_O_nb_moves = -1;
				Player_X_nb_moves = -1;  
			}
			if(State != game->state  )
			{
				if(game->state == PLAYER_X_WON_STATE)
				{
					xwins++;
				}
				if(game->state == PLAYER_O_WON_STATE)
				{
					owins++;
				}
			}
		}
	}
    free(MovesO);
    free(MovesX);
}
////////////////////////////// Verifier s'il existe un vaiqueur ,return -1 si c'est PLAYER_X,1 si c'est  PLAYER_O, si aucun(adopté a l'algorithme minimax) //////////////////////
int Vainqueur(const int board[9])
{
    int cas[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i)
	{
		if(board[cas[i][0]] != 0 &&
        board[cas[i][0]] == board[cas[i][1]] &&
        board[cas[i][0]] == board[cas[i][2]])
        return board[cas[i][2]];
    }
    return 0;
}
////////////////////////////// L'algorithme minimax ////////////////////////////////////////////////////////////////////
int minimax(int board[9], int player) {
    int winner = Vainqueur(board);
    if(winner != 0) return winner*player;
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i)
	{
		if(board[i] == 0)
		{
			board[i] = player;
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score)
			{
                score = thisScore;
                move = i;
            }
            board[i] = 0;
        }
    }
    if(move == -1) return 0;
    return score;
}
////////////////////////////// L'algorithme qui choisis le mouvement suivant l'arbre minimax dans un noeud donné ////////////////
int computerMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i)
	{
        if(board[i] == 0)
		{
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score)
			{
                score = tempScore;
                move = i;
            }
        }
    }
    return move;
}
////////////////////////////// Mettre les informations à sauvegarder dans un objet de type structure GameToSave //////////////////////
GameToSave PutInGTS(GameToSave GTS,game_t *game,player *joueur,int *MovesX,int *MovesO,int Xwins,int Owins,int GameType)
{
    //GTS.game=game:
    GTS.game.state = game->state;
    for (size_t i = 0; i < 9; i++)
    {
        GTS.game.board[i] = game->board[i];
    }
    for (size_t i = 0; i < 5; i++)
    {
        GTS.movesX[i] = MovesX[i];
        GTS.movesO[i] = MovesO[i];
    } 
    GTS.game.player = game->player;
    //GTS.player = joueur
    strcpy(GTS.player.PlayerName,joueur->PlayerName);
    strcpy(GTS.player.password,joueur->password);
    GTS.player.NbOfGames = joueur->NbOfGames;
    GTS.player.score = joueur->score;
    //GTS.MOVESX = MOVESX
    GTS.Xwins = Xwins;
    GTS.Owins = Owins;
    GTS.GameType = GameType;
    return GTS;
    
}
////////////////////////////// Responsable de l'enregistrement des données du jeu ////////////////////////////////////////////
void SaveGame(FILE *GameFile,GameToSave GTS)
{
    GTS.player.NbOfGames++;
    fwrite(&GTS,sizeof(GameToSave),1,GameFile);
}
////////////////////////////// Responsable de l'importation des données d'un jeu sauvegardé auparavant //////////////////////////
GameToSave LoadGame(player *joueur,FILE *GameFile,GameToSave GTS)
{
    GameToSave temp;
    int nbofgames;
    GTS.GameType=-1;
    GTS.player.NbOfGames = -1;
    fseek(GameFile,0,SEEK_SET);
    while(!feof(GameFile))
    {
        fread(&temp,sizeof(GameToSave),1,GameFile);
        if(strcmp(joueur->PlayerName,temp.player.PlayerName)==0 && temp.player.NbOfGames > GTS.player.NbOfGames)
        {
            GTS.player.NbOfGames = temp.player.NbOfGames;
        }
    }
    fseek(GameFile,0,SEEK_SET);
    nbofgames = GTS.player.NbOfGames;
    while(!feof(GameFile))
    {
        fread(&GTS,sizeof(GameToSave),1,GameFile);
        if(strcmp(joueur->PlayerName,GTS.player.PlayerName)==0 && nbofgames == GTS.player.NbOfGames)
        {
            return GTS;
        }
    }
    fseek(GameFile,0,SEEK_SET);
    return GTS;
}
////////////////////////////// La boucle du jeux contre l'IA facile /////////////////////////////////////////////////////////////
player *GameLoopVSCOM(game_t *game,SDL_Renderer *renderer , player *joueur,FILE *GameFile,GameToSave GTS,int saved)
{
        int *MovesX = NULL;
        int *MovesO = NULL;
        MovesX = (int*)malloc(5*sizeof(int));
        MovesO = (int*)malloc(5*sizeof(int));
        for (size_t i = 0; i < 5; i++)
        {
            MovesX[i] = -1;
            MovesO[i] = -1;
        }
        
        char xwins[4];
        char owins[4];
	    int ComChoiceX=0;
	    int ComChoiceY=0;
        int cell=0;
        SDL_Event e;
        int X=0;
        int Y=0;
        int y=650,x=500;
        int player,Xwins=0,Owins=0,Player_X_nb_moves=-1,Player_O_nb_moves=-1;
		if(saved == 1)
		{
			for (size_t i = 0; i < 9; i++)
			{
				game->board[i]=GTS.game.board[i];
			}
			for (size_t i = 0; i < 5; i++)
			{
				if(GTS.movesX[i] > -1)
				{
					MovesX[i]=GTS.movesX[i];
					MovesO[i]=GTS.movesO[i];
					Player_X_nb_moves++;
					Player_O_nb_moves++;
				}
			}
			game->state = GTS.game.state;
			game->player = GTS.game.player;
			Xwins = GTS.Xwins;
			Owins = GTS.Owins;
		}
		int State=game->state;
		int State2=game->state;
		while (game->state != QUIT_STATE && game->state != HOME && game->state != RETURN_TO_LAST_MENU)
		{
			render_game_com(renderer, game);
			if(game->state == RUNNING_STATE)
            {
				Show_Player_Moves(renderer,MovesO,0,Player_O_nb_moves,PLAYER_O);
                Show_Player_Moves(renderer,MovesX,0,Player_X_nb_moves,PLAYER_X);
            }
            itoa(Xwins,xwins,10);
            itoa(Owins,owins,10);
			message(renderer,joueur->PlayerName,"ressources/crazy.ttf",40,color,1100,300);
			message(renderer,xwins,"ressources/crazy.ttf",40,color,1170,400);//1100,350
			message(renderer,"ROBOT","ressources/crazy.ttf",40,color,100,300);
			message(renderer,owins,"ressources/crazy.ttf",40,color,150,400);
			SDL_RenderPresent(renderer);
			SDL_GetMouseState(&x,&y);
			State2=game->state;
			Touch_Icone_com(renderer, x, y);
			SDL_RenderPresent(renderer);
			if (game->player == PLAYER_X)
			{ 
				while (SDL_PollEvent(&e))
				{
				switch (e.type)
				{
					case SDL_QUIT:
						game->state = QUIT_STATE;
						break;
					case SDL_MOUSEBUTTONDOWN:
						Y=e.button.y;
						X=e.button.x;
						if(X>355 && X<1011 && Y>109 && Y<764)
						{
							player = game->player;
							click_on_cell(renderer,game,(Y-109)/ CELL_HEIGHT,(X-356)/ CELL_WIDTH);
						}
						if(x>869 && x<939 && y>15 && y<85)
						{
							game->state = HOME;
						}
						if(x>429 && x<499 && y>15 && y<85)
						{
							reset_game(game);
							game->state = RESTART;
						}
						if(x>649 && x<719 && y>15 && y<85)
						{
							GTS =  PutInGTS(GTS,game,joueur,MovesX,MovesO,Xwins,Owins,0);
							SaveGame(GameFile,GTS);
							message(renderer,"Game Saved seccessfully !","ressources/crazy.ttf",60,color,380,400);
							SDL_RenderPresent(renderer);
							SDL_Delay(500);
						}
						if(x>1146 && x<1226 && y>668 && y<748)
						{
							game->state = QUIT_STATE;
						}
						break;
				case SDL_MOUSEMOTION:
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							game->state = RETURN_TO_LAST_MENU;
							break;
					}
				default: {}
			}
            if(e.type == SDL_MOUSEBUTTONDOWN && State == RUNNING_STATE)
            {
				if(player != game->player && X>355 && X<1011 && Y>109 && Y<764)
				{
					MovesX = PlayerMoves(MovesX,(Y-109)/ CELL_HEIGHT,(X-356)/ CELL_WIDTH,&Player_X_nb_moves);
                }
			}
		}
     }
	 else
	 {
		 SDL_Delay(250);
		 ComChoiceX = rand() % 3;
		 ComChoiceY = rand() % 3;
         player = game->player;
		 click_on_cell(renderer,game,ComChoiceX,ComChoiceY);
         if(player != game->player && State == RUNNING_STATE)
         {
			MovesO = PlayerMoves(MovesO,ComChoiceX,ComChoiceY,&Player_O_nb_moves);

		 }
	 }
	 SDL_SetRenderDrawColor(renderer,0,0,0,255);
     SDL_RenderClear(renderer);  
     render_game_com(renderer, game);
     if(game->state == RUNNING_STATE)
     {
		Show_Player_Moves(renderer,MovesO,0,Player_O_nb_moves,PLAYER_O);
        Show_Player_Moves(renderer,MovesX,0,Player_X_nb_moves,PLAYER_X);
     }
     itoa(Xwins,xwins,10);
     itoa(Owins,owins,10);
     message(renderer,joueur->PlayerName,"ressources/crazy.ttf",40,color,1100,300);
     message(renderer,xwins,"ressources/crazy.ttf",40,color,1170,400);
     message(renderer,"ROBOT","ressources/crazy.ttf",40,color,100,300);
     message(renderer,owins,"ressources/crazy.ttf",40,color,150,400);                     
     SDL_RenderPresent(renderer);
     State = game->state;
     if(game->state != RUNNING_STATE)
     {
		for (size_t i = 0; i < 5; i++)
		{
			MovesX[i] = -1;
            MovesO[i] = -1;
        } 
        Player_O_nb_moves = -1;
        Player_X_nb_moves = -1;  
	 }
     if(game -> state != State2)
     {
		if(game->state == PLAYER_X_WON_STATE )
        {
			joueur->score += 2;
            Xwins++;
        }
        if(game->state == PLAYER_O_WON_STATE)
        {
			joueur->score -= 1;
            Owins++;
        }
        if(game->state == TIE_STATE)
        {
			joueur->score += 0;
        }
        joueur->NbOfGames++;
     }
   }
   free(MovesX);
   free(MovesO);
   return joueur;
}
////////////////////////////// La boucle du jeux contre l'IA difficile /////////////////////////////////////////////////
player *GameLoopVSCOM_MINIMAX(game_t *game,SDL_Renderer *renderer ,player *joueur,FILE *GameFile,GameToSave GTS,int saved)
{
    int *MovesX = NULL;
    int *MovesO = NULL;
    MovesX = (int*)malloc(5*sizeof(int));
    MovesO = (int*)malloc(5*sizeof(int));
    for (size_t i = 0; i < 5; i++)
    {
		MovesX[i] = -1;
        MovesO[i] = -1;
    }       
    char xwins[4];
    char owins[4];
    int Xwins=0,Owins=0;
	int ComChoiceX=0;
	int ComChoiceY=0;
    int cell=0;
    SDL_Event e;
    int player,Player_X_nb_moves=-1,Player_O_nb_moves=-1;
    if(saved == 1)
    {
        for (size_t i = 0; i < 9; i++)
        {
           game->board[i]=GTS.game.board[i];
        }
         for (size_t i = 0; i < 5; i++)
        {
           MovesX[i]=GTS.movesX[i];
           MovesO[i]=GTS.movesO[i];
           if(MovesX[i]>=0) Player_X_nb_moves++;
           if(MovesO[i]>=0) Player_O_nb_moves++;
        }
        game->state = GTS.game.state;
        game->player = GTS.game.player;
        Xwins = GTS.Xwins;
        Owins = GTS.Owins;     
    }
    int X=0;
    int Y=0;
    int y=650,x=500;
    int State=game->state;
    int State2=game->state;
    while (game->state != QUIT_STATE && game->state != HOME && game->state != RETURN_TO_LAST_MENU)
	{
		State2=game->state;
        SDL_GetMouseState(&x,&y);
		Touch_Icone_com(renderer, x, y);
		SDL_RenderPresent(renderer);
	 if (game->player == PLAYER_X)
	 { 
		SDL_WaitEvent(&e);
        switch (e.type)
		{
			case SDL_QUIT:
				game->state = QUIT_STATE;
				break;
            case SDL_MOUSEBUTTONDOWN:
                Y=e.button.y;
                X=e.button.x;
                if(X>355 && X<1011 && Y>109 && Y<764)
				{
                    player = game->player;
					click_on_cell(renderer,game,(Y-109)/ CELL_HEIGHT,(X-356)/ CELL_WIDTH);
                }
                if(x>869 && x<939 && y>15 && y<85)
                {
                    game->state = HOME;
                }
				if(x>429 && x<499 && y>15 && y<85)
                {
						reset_game(game);
                        game->state = RESTART;
                }
				if(x>649 && x<719 && y>15 && y<85)
                {
                        GTS =  PutInGTS(GTS,game,joueur,MovesX,MovesO,Xwins,Owins,1);
                        SaveGame(GameFile,GTS);
                        message(renderer,"Game Saved seccessfully !","ressources/crazy.ttf",60,color,380,400);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(500);
                }
                if(x>1146 && x<1226 && y>668 && y<748)
                {
						game->state = QUIT_STATE;
                }
                break;
            case SDL_MOUSEMOTION:
                break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					game->state = RETURN_TO_LAST_MENU;
					break;
				}
            default: {}
		}
        if(e.type == SDL_MOUSEBUTTONDOWN && State == RUNNING_STATE)
        {
			if(player != game->player && X>355 && X<1011 && Y>109 && Y<764)
            {
				MovesX = PlayerMoves(MovesX,(Y-109)/ CELL_HEIGHT,(X-356)/ CELL_WIDTH,&Player_X_nb_moves);
			}
        }
	 
     }
	 else 
	 {
		SDL_Delay(250);
        cell = computerMove(game->board);
        ComChoiceX = cell/3;
        ComChoiceY = cell%3;
        player = game->player;
		click_on_cell(renderer,game,ComChoiceX,ComChoiceY);
        if(player != game->player && State == RUNNING_STATE)
        {
			MovesO = PlayerMoves(MovesO,ComChoiceX,ComChoiceY,&Player_O_nb_moves);
        }
	 }
	 SDL_SetRenderDrawColor(renderer,0,0,0,255);
     SDL_RenderClear(renderer);
	 render_game_com(renderer, game);
     if(game->state == RUNNING_STATE)
     {
		Show_Player_Moves(renderer,MovesO,0,Player_O_nb_moves,PLAYER_O);
        Show_Player_Moves(renderer,MovesX,0,Player_X_nb_moves,PLAYER_X);
     }
     itoa(Xwins,xwins,10);
     itoa(Owins,owins,10);
     message(renderer,joueur->PlayerName,"ressources/crazy.ttf",40,color,1100,300);
     message(renderer,xwins,"ressources/crazy.ttf",40,color,1170,400);
     message(renderer,"ROBOT","ressources/crazy.ttf",40,color,100,300);
     message(renderer,owins,"ressources/crazy.ttf",40,color,150,400);
     SDL_RenderPresent(renderer);
     State = game->state;
     if(game->state != RUNNING_STATE)
     {
		for (size_t i = 0; i < 5; i++)
        {
			MovesX[i] = -1;
            MovesO[i] = -1;
        } 
        Player_O_nb_moves = -1;
        Player_X_nb_moves = -1;  
	}
    if(game -> state != State2)
    {
		if(game->state == PLAYER_X_WON_STATE )
        {
			joueur->score += 5;
            Xwins++;
        }
        if(game->state == PLAYER_O_WON_STATE)
        {
			joueur->score -= 1;
            Owins++;
        }
        if(game->state == TIE_STATE)
        {
            joueur->score += 2;
        }
        joueur->NbOfGames++;
     }
  }
  free(MovesX);
  free(MovesO);
  return joueur;
}