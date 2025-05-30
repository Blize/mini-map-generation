#include <raylib.h>
#include <stdlib.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BLOCK_SIZE 1.0f

#define MAP_X 50
#define MAP_Y 50
#define MAP_Z 25

typedef enum { GRASS, STONE, DIRT, WATER, AIR } BlockType;

typedef struct {
    BlockType type;
} Block;

Block map[MAP_X][MAP_Y][MAP_Z];


Color ColorBrightness(Color color, float factor) {
    return (Color){
        .r = (unsigned char)(color.r * factor),
        .g = (unsigned char)(color.g * factor),
        .b = (unsigned char)(color.b * factor),
        .a = color.a
    };
}

void generateHills() {
    int density = 40;
    int numHills = (MAP_X * MAP_Y) / density;  // Adjust density factor to taste

    for (int i = 0; i < numHills; i++) {
        int cx = rand() % (MAP_X - 4) + 2; // Avoid edge
        int cy = rand() % (MAP_Y - 4) + 2;
        int height = rand() % (MAP_Z - 3) + 3; // Min height 3
        int baseRadius = rand() % 3 + 2;       // Base width

        for (int h = 0; h < height; h++) {
            int radius = baseRadius - h; // Taper the hill
            if (radius < 0) break;

            for (int dx = -radius; dx <= radius; dx++) {
                for (int dy = -radius; dy <= radius; dy++) {
                    int x = cx + dx;
                    int y = cy + dy;
                    int z = MAP_Z - height + h;

                    
                    if (x >= 0 && x < MAP_X && y >= 0 && y < MAP_Y && z >= 0 && z < MAP_Z) {
                        if (map[x][y][2].type != WATER) {
                            for (int fillZ = 2; fillZ <= z; fillZ++) {
                                map[x][y][fillZ].type = STONE;
                            }
                        }
                    }
                }
            }
        }
    }
}



void placeWater(int x, int y) {
    if (rand() % 40 == 0) {
        map[x][y][2].type = WATER;

        int seaSize = rand() % 4 + ((MAP_X + MAP_Y) / 8);

        for (int i = 1; i <= seaSize; i++) {
            for (int dirX = -1; dirX <= 1; dirX++) {
                for (int dirY = -1; dirY <= 1; dirY++) {
                    int newX = x + i * dirX;
                    int newY = y + i * dirY;

                    if (newX >= 0 && newX < MAP_X && newY >= 0 && newY < MAP_Y) {
                        map[newX][newY][2].type = WATER;
                    }
                }
            }
        }
    }
}

void generateMap() {
    for (int x = 0; x < MAP_X; x++) {
        for (int y = 0; y < MAP_Y; y++) {
            for (int z = 0; z < MAP_Z; z++) {
                if (z < 2) {
                    map[x][y][z].type = DIRT; // Base layer set to have an minecraft junk look
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
                    case DIRT:
                        color = BROWN;
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

                float shadeFactor = 1.0f - (float)z / MAP_Z;
                color = ColorBrightness(color, shadeFactor);

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
        UpdateCamera(&camera, 1);

        if (IsKeyPressed(KEY_R) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                                       GetMouseX() > SCREEN_WIDTH - 50 &&
                                       GetMouseY() < 50)) {
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
