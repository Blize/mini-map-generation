#include <raylib.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BLOCK_SIZE 1.0f

#define MAP_X 12
#define MAP_Y 10
#define MAP_Z 7

typedef enum { GRASS, STONE, WATER, AIR } BlockType;

typedef struct {
    BlockType type;
} Block;

Block map[MAP_X][MAP_Y][MAP_Z];


void generateHills() {
    for (int x = 1; x < MAP_X - 1; x++) {
        for (int y = 1; y < MAP_Y - 1; y++) {
            if (rand() % 20 == 0) {
                const int height = rand() % (MAP_Z - 2) + 2; // Generate height between 2 and MAP_Z
                const int width = rand() % 5 + 1; // Generate width of mountain
                int startZ = MAP_Z - height;

                for (int z = startZ; z < MAP_Z; z++) {
                    for (int w = -width / 2; w <= width / 2; w++) {
                        if (x + w >= 0 && x + w < MAP_X && y + w >= 0 && y + w < MAP_Y) {
                            map[x + w][y + w][z].type = STONE;
                        }
                    }
                }
            }
        }
    }
}

void placeWater(int x, int y) {
    if (rand() % 20 == 0) { // Chance of water spawning
        map[x][y][2].type = WATER;

        int seaSize = rand() % 10 + 5;

        int dirX = rand() % 3 - 1;
        int dirY = rand() % 3 - 1;

        for (int i = 1; i <= seaSize; i++) {
            // Update the adjacent water block
            if (x + i * dirX >= 0 && x + i * dirX < MAP_X && y + i * dirY >= 0 && y + i * dirY < MAP_Y) {
                map[x + i * dirX][y + i * dirY][2].type = WATER;
            } else {
                break;
            }
        }
    }
}





void generateMap() {
    for (int x = 0; x < MAP_X; x++) {
        for (int y = 0; y < MAP_Y; y++) {
            for (int z = 0; z < MAP_Z; z++) {
                if (z < 2) {
                    map[x][y][z].type = STONE; // Base layer set to have an minecraft junk look
                } else if (z == 2) {
                    map[x][y][z].type = GRASS;
                    placeWater(x, y);
                } else {
                    map[x][y][z].type = AIR;
                }
            }
        }
    }

    generateHills();
}


void drawMap() {
    for (int i = 0; i < MAP_X; i++) {
        for (int j = 0; j < MAP_Y; j++) {
            for (int z = 0; z < MAP_Z; z++) {
                Vector3 position = { i * BLOCK_SIZE, z * BLOCK_SIZE, j * BLOCK_SIZE };
                Color color;

                switch (map[i][j][z].type) {
                    case GRASS:
                        color = GREEN;
                        break;
                    case STONE:
                        color = GRAY;
                        break;
                    case WATER:
                        color = BLUE;
                        break;
                    case AIR:
                        continue; // Skip drawing for air blocks
                    default:
                        color = WHITE;
                        break;
                }

                DrawCube(position, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, color);
            }
        }
    }
}

int main(void) {
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Procedural Map Generation 3D");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 20.0f, 20.0f, 20.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;

    SetTargetFPS(80);

    generateMap();

    while (!WindowShouldClose()) {

        // Uncomment line below for camera control
        // UpdateCamera(&camera, 1);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && GetMouseX() > SCREEN_WIDTH - 50 && GetMouseY() < 50) {
            generateMap();
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        drawMap();

        EndMode3D();

        DrawFPS(10, 10);


        DrawRectangle(SCREEN_WIDTH - 60, 10, 60, 30, GRAY);
        DrawText("Generate", SCREEN_WIDTH - 55, 15, 10, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}