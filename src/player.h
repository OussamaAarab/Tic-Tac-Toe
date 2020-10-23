
#ifndef PLAYER_H
#define PLAYER_H
typedef struct _player
{
    char PlayerName[40];
    char password[40];
    int score;
    int NbOfGames;
}player;
player *CreateNewPlayer(char *Name,char *password,FILE *f);//une fonction qui cree un nouveau joueur
player *FindPlayer(char *Name,FILE *f);//une fonction qui cherche un joueur par son nom et return un pointeur null si ce joueur n'existe pas
player **FirstTen(FILE *f,player **p,int *n);//une fonction qui cree un tableau de type structures Player ou existent les dix premiers joueur
// faut creer des fonction qui libere l'espace allouee dans chacune des fcts precedentes
void save(player *p,FILE *f);
player **TriABulle(player **p,int n);
#endif // PLAYER_H
