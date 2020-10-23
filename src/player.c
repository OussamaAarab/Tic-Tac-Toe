#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "player.h"
#include "game.h"
#define Malloc(type,K) (type*)malloc(K*sizeof(type))
////////////////////////////// Chercher un joueur par son nom , retourner ses derniers informations s'il existe , NULL si non //////////////////////////////////////////
player *FindPlayer(char *Name,FILE *f)
{
    fseek(f,0,SEEK_SET);
    player *p;
    player temp;
    p=Malloc(player,1);
    strcpy(p->PlayerName,Name);
    int LastScore =0,MaxNbOfGames=-1,c=0;
    char password[40];
    while(!feof(f))
    {
        fread(&temp,sizeof(player),1,f);
        if(strcmp(Name,temp.PlayerName)==0 && temp.NbOfGames > MaxNbOfGames)
		{
			p->score = temp.score;
            c++;
            MaxNbOfGames = temp.NbOfGames;
            p->NbOfGames = temp.NbOfGames;
            strcpy(p->password,temp.password); 
        }
    }
    if(c==0) return NULL;
    return p;
}
////////////////////////////// Créer et enregistre un nouveaux joueur ///////////////////////////////////////////////////////////////
player *CreateNewPlayer(char *Name,char *password,FILE *f)
{   if(FindPlayer(Name,f) == NULL)
	{
		player *p;
        p=Malloc(player,1);
        strcpy(p->PlayerName,Name);
        strcpy(p->password,password);
        p->NbOfGames=0;
        p->score=0;
        fwrite(p,sizeof(player),1,f);
        return p;
    }
    return NULL;
}
////////////////////////////// Trier les joueurs selon leurs score /////////////////////////////////////////////////////////////////
player **TriABulle(player **p,int n)
{
    player temp;
    for(int i=0; i<n-1; i++)
    {
        for(int k=0; k < n-i-1; k++)
        {
            if(p[k]->score > p[k+1]->score)
            {
                strcpy(temp.PlayerName,p[k]->PlayerName);
                strcpy(temp.password,p[k]->password);
                temp.score = p[k]->score;
                strcpy(p[k]->PlayerName,p[k+1]->PlayerName);
                strcpy(p[k]->password,p[k+1]->password);
                p[k]->score = p[k+1]->score;
                strcpy(p[k+1]->PlayerName,temp.PlayerName);
                strcpy(p[k+1]->password,temp.password);
                p[k+1]->score=temp.score;
            }
        }
    }
    return p;
}
////////////////////////////// Sauvegarder un joueur ////////////////////////////////////////////////////////////////////
void save(player *p,FILE *f)
{
    fwrite(p,sizeof(player),1,f);
}
////////////////////////////// Verifier si le joueur deja existe ////////////////////////////////////////////////////////
int CheckIfExists(player **p,int n,char *Name)
{
    for(int i=0;i<n;i++)
    {
        if(strcmp(p[i]->PlayerName,Name)==0) return 1;
        
    }
    return 0;
}
////////////////////////////// Changer les donnée d'un joueur de la liste des joueur par ses derniers données /////////////
player **change(player **p,int n,player temp)
{
    for(int i=0;i<n;i++)
    {
        if(strcmp(p[i]->PlayerName,temp.PlayerName)==0) 
        {
            if(temp.NbOfGames >= p[i]->NbOfGames) 
            {
                p[i]->NbOfGames = temp.NbOfGames;
                p[i]->score = temp.score;
            } 
        }
    }
    return p;
}
////////////////////////////// créer une liste des dix meilleurs joueurs selon leurs score //////////////////////////////////
player **FirstTen(FILE *f,player **p,int *n)
{
    int file_lenght=0,firstTen=10,i;
    player temp;
    fseek(f,0,SEEK_SET);
    fseek(f,0,SEEK_SET);
    while (fread(&temp,sizeof(player),1,f))
    {
        file_lenght++;
    }
    if(file_lenght<10) firstTen=file_lenght;
    p=Malloc(player*,firstTen);
    for(i=0;i<firstTen;i++) {p[i]=Malloc(player,1);}
    for(i=0;i<firstTen;i++) {p[i]->PlayerName[0]='\0';}
    int min=0;
    int counter=0;
    fseek(f,0,SEEK_SET);
    fseek(f,0,SEEK_SET);
    for(int j=0;j<file_lenght;j++)
    {
        fread(&temp,sizeof(player),1,f);
        if(counter<firstTen)
		{
            if(CheckIfExists(p,counter,temp.PlayerName)==0)
            {
                strcpy(p[counter]->PlayerName,temp.PlayerName);
                strcpy(p[counter]->password,temp.password);
                p[counter]->score=temp.score;
                p[counter]->NbOfGames = temp.NbOfGames;
                for(i=0;i<=counter;i++)
                {
                    if(p[min]->score > p[i]->score ) min =i;
             
                }
                counter++;
            }
            else
			{
				p=change(p,counter,temp);
                for(i=0;i<firstTen;i++)
                {
                    if(p[min]->score > p[i]->score ) min =i;
                }
            }
        }
        
        else
		{
            if(CheckIfExists(p,firstTen,temp.PlayerName)==0)
			{
                if(temp.score > p[min]->score)
				{
					strcpy(p[min]->PlayerName,temp.PlayerName);
					strcpy(p[min]->password,temp.password);
					p[min]->score=temp.score;
					p[min]->NbOfGames = temp.NbOfGames;
					for(i=0;i<firstTen;i++)
					{
						if(p[min]->score > p[i]->score ) min =i;
					}
				}
			}
			else
			{
				p=change(p,firstTen,temp);
                for(i=0;i<firstTen;i++)
                {
                    if(p[min]->score > p[i]->score ) min =i;
                }
			}
		}
    }
    player name[firstTen];
    int taille = 0;
    for(int i=0;i<firstTen;i++)
    { 
        if((p[i]->PlayerName[0])!='\0')
        {
            strcpy(name[taille].PlayerName,p[i]->PlayerName);
            name[taille].score = p[i]->score;
            taille++;
        }
    }
    for(int i=0;i<taille;i++)
    {
		strcpy(p[i]->PlayerName,name[i].PlayerName);
        p[i]->score = name[i].score ;
    }
    p = TriABulle(p,taille);
    *n = taille;
    return p;
}