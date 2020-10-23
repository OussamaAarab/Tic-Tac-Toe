#ifndef RENDERING_H_
#define RENDERING_H_

void render_game(SDL_Renderer *renderer,game_t *game);
void render_game_com(SDL_Renderer *renderer,game_t *game);
void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);
SDL_Renderer *InitRenderer(SDL_Renderer *renderer,SDL_Window *window);
SDL_Window *Initializer(SDL_Window *window);
void LoadImage(SDL_Renderer *renderer,char *path,int x,int y, int w, int h);
void SDL_ERREUR_X(const char* x);
void destroy(SDL_Window *window,SDL_Renderer *renderer);
void Touch_Icone(SDL_Renderer *renderer,int x,int y);
void Touch_Icone_com(SDL_Renderer *renderer,int x,int y);
void Init_Text();
void Draw_carre(SDL_Renderer *renderer,int x,int y, int w, int h);
#endif  // RENDERING_H_


