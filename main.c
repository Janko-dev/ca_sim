#include "sim.h"

int main(void){
    
    State* sim = init("Simulator", WIDTH, HEIGHT);

    sim->grid = (Type**)malloc(sizeof(Type*) * GRID_H);
    for (int i = 0; i < GRID_H; i++){
        sim->grid[i] = (Type*)calloc(GRID_W, sizeof(Type));
    }

    // for (int i = 0; i < GRID_H; i++){
    //     for (int j = 0; j < GRID_W; j++){
    //         sim->grid[i][j] = rand()%2 == 0 ? SAND : EMPTY;
    //         //sim->grid[i][i] = SAND;
    //     }
    // }


    while(sim->isRunning){
        update(sim);
        render(sim);
        handleEvents(sim);
        SDL_Delay(1000/30);
    }

    quit(sim);
    return 0;
}