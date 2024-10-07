#include "raylib.h"
#include "board.h"
#include "view.h"
#include "shape.h"
#include <math.h>
#include <stdio.h>

int main(void) {
    Board board;
    View view(board);

    bool gameCompleted = false;
    char currentScore[100];
    char message[100];
    int xyOffset = 50;

    const int screenWidth = 600;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Same Game");

    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int x = GetMouseX() - xyOffset;
            int y = GetMouseY() - xyOffset;
            int row = floor(y / 100);
            int col = floor(x / 100);
            ShapeColor toRM = board.getTile(row, col);
            if (toRM != S_EMPTY) {
                board.removeChunk(row, col);
                board.shiftTiles();
                gameCompleted = board.checkStatus();
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameCompleted) {
            sprintf(message, "Congratulations!\n\nGame completed in %d moves!", board.getNumMoves());
            DrawText(message, 150, 250, 20, BLACK);
        }
        else {
            view.draw();
            sprintf(currentScore, "Current score: %d", board.getNumMoves());
            DrawText(currentScore, screenWidth-200, 10, 20, RED);
        }
        
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}