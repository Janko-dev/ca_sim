#include "sim.h"
#include <stdio.h>
#include <stdlib.h>

State* init(const char* title, int width, int height){
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0){
        fprintf(stderr, "Unable to initialise subsystems: %s\n", SDL_GetError());
        exit(1);
    }

    State* s = malloc(sizeof(State));

    s->win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (s->win == NULL){
        fprintf(stderr, "Unable to initialise window: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    s->rend = SDL_CreateRenderer(s->win, -1, 0);
    if (s->rend == NULL){
        fprintf(stderr, "Unable to initialise renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(s->win);
        SDL_Quit();
        exit(1);
    }

    s->isRunning = 1;
    return s;
}

void update(State* state){

    Type **grid = (Type**)malloc(sizeof(Type*) * GRID_H);
    for (int i = 0; i < GRID_H; i++){
        grid[i] = (Type*)calloc(GRID_W, sizeof(Type));
    }

    for (int i = 0; i < GRID_W; i++){        
        for (int j = 0; j < GRID_H; j++){
            switch (state->grid[i][j]){

                case SAND: {
                    if (j+1 < GRID_H && state->grid[i][j+1] == EMPTY){
                        grid[i][j+1] = SAND;
                    } else if (j+1 < GRID_H && i+1 < GRID_W &&
                                state->grid[i][j+1] == SAND && 
                                state->grid[i+1][j+1] == EMPTY)
                    {
                        grid[i+1][j+1] = SAND;
                    } else if (j+1 < GRID_H && i-1 >= 0 &&
                                state->grid[i][j+1] == SAND && 
                                state->grid[i-1][j+1] == EMPTY)
                    {
                        grid[i-1][j+1] = SAND;
                    } else {
                        grid[i][j] = state->grid[i][j];
                    }
                } break;
                default: break;
            }
        }
    }

    for (int i = 0; i < GRID_H; i++){
        free(state->grid[i]);
    }
    free(state->grid);
    state->grid = grid;

    if (state->mousepressed){
        switch(state->mode){
            case SAND: {
                state->grid[state->mx][state->my] = SAND;
            } break;
        }
    }
    
}

void render(State* state){
    SDL_SetRenderDrawColor(state->rend, 0, 0, 0, 1);
    SDL_RenderClear(state->rend);

    for (int i = 0; i < GRID_H; i++){
        for (int j = 0; j < GRID_W; j++){
            if (state->grid[i][j] == SAND){
                SDL_SetRenderDrawColor(state->rend, 255, 255, 0, 1);
            } else {
                SDL_SetRenderDrawColor(state->rend, 0, 0, 0, 1);
            }
            SDL_RenderFillRect(state->rend, &(SDL_Rect){i*RES, j*RES, RES, RES});
        }
    }

    switch (state->mode){
        case SAND:{
            SDL_SetRenderDrawColor(state->rend, 255, 255, 0, 1);
            SDL_RenderFillRect(state->rend, &(SDL_Rect){state->mx*RES, state->my*RES, RES, RES});
        } break;
        default:break;
    }

    SDL_RenderPresent(state->rend);
}

void handleEvents(State* state){
    SDL_Event e;
    while(SDL_PollEvent(&e)){
        switch(e.type){
            case SDL_QUIT:{
                state->isRunning = 0;
            } break;
            case SDL_KEYDOWN: {
                if (e.key.keysym.sym == SDLK_s){
                    state->mode = SAND;
                }
            } break;
            case SDL_MOUSEBUTTONDOWN: {
                state->mousepressed = 1;
            } break;
            case SDL_MOUSEBUTTONUP: {
                state->mousepressed = 0;
            } break;
            case SDL_MOUSEMOTION:{
                state->mx = ((float)e.button.x/RES);
                state->my = ((float)e.button.y/RES);
            } break;
            default: break;
        }
    }
}

void quit(State* state){
    // for (int i = 0; i < GRID_H; i++) free(state->grid[i]);
    free(state->grid);
    SDL_DestroyRenderer(state->rend);
    SDL_DestroyWindow(state->win);
    SDL_Quit();
}