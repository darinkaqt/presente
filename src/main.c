
#include <raylib.h>
#include <math.h>
#include <stdio.h>

#include "level.h"
#include "draw.h"
#include "state.h"

int main(int argc, char const *argv[]){

    // Initialization
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width,screen_height,"Presente - the game");
    SetTargetFPS(60);

    // Initialize level and fill randomly
    level *lvl = level_new(50,40);
    level_fill_random(lvl,6);

    // Initialize state (and add enemies)
    state *sta = state_new();
    state_populate_random(lvl,sta,40);

    //the weapon is initialized
    int weapon = 0;

    // Main loop
    while(!WindowShouldClose()){

        // Update input depending if keys are pressed or not
        sta->button_state[0] = IsKeyDown(KEY_D);
        sta->button_state[1] = IsKeyDown(KEY_W);
        sta->button_state[2] = IsKeyDown(KEY_A);
        sta->button_state[3] = IsKeyDown(KEY_S);
        sta->button_state[4] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        sta->button_state[5] = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);  //change of weapon
        // Compute the angle the player is looking at from the mouse's position relative to the screen's center
        float mouse_y = GetMouseY()-GetScreenHeight()/2;
        float mouse_x = GetMouseX()-GetScreenWidth()/2;
        sta->aim_angle = atan2(-mouse_y,mouse_x);

        // Update the state
        state_update(lvl,sta,&weapon);                //weapon is added to STATE_UPDATE

        // Drawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_state(lvl, sta);

            DrawText("Cambia el arma con click derecho",90,80,20,LIGHTGRAY);
            DrawText("Presente profe!",90,100,20,LIGHTGRAY);
            if (weapon==0) DrawText("weapon: Default!",90,120,20,LIGHTGRAY);
            else if (weapon==1) DrawText("weapon: Three bullets!",90,120,20,LIGHTGRAY);
            else if (weapon==2) DrawText("weapon: Bomb!",90,120,20,LIGHTGRAY);
            else if (weapon==3) DrawText("weapon: Dynamite!",90,120,20,LIGHTGRAY);

        EndDrawing();

    }

    // Closer window
    CloseWindow();

    // Free memory
    state_free(sta);
    level_free(lvl);

    return 0;
}
