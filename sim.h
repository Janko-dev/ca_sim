#ifndef SIM_H
#define SIM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#define WIDTH 800
#define HEIGHT 800
#define RES 8
#define GRID_H (HEIGHT/RES)
#define GRID_W (WIDTH/RES)

enum Type {
    EMPTY,
    SAND
};

typedef enum Type Type;

typedef struct {
    SDL_Window* win;
    SDL_Renderer* rend;
    int isRunning;
    Type** grid;
    int mousepressed;
    Type mode;
    int mx;
    int my;
} State;

State* init(const char* title, int width, int height);
void update(State* state);
void render(State* state);
void handleEvents(State* state);
void quit(State* state);


#endif