#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define FONT_SIZE 24
#define CHAR_SET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()_+-=[]{}|;':,.<>?/~`\"\\"

// Function to generate random characters
char random_char() {
    return CHAR_SET[rand() % (sizeof(CHAR_SET) - 1)];
}

int main(int argc, char* args[]) {
    // Initialize SDL2
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL2_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Character Rain",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load font
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", FONT_SIZE);
    if (font == NULL) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return 1;
    }

    // Set text color
    SDL_Color text_color = {255, 255, 255}; // White

    // Create surface for text
    SDL_Surface* text_surface;

    // Create texture
    SDL_Texture* text_texture;

    // Main loop flag
    int quit = 0;

    // Event handler
    SDL_Event e;

    // Seed random number generator
    srand(time(NULL));

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
        SDL_RenderClear(renderer);

        // Render characters
        for (int x = 0; x < SCREEN_WIDTH; x += FONT_SIZE) {
            char c = random_char();

            // Create surface from character
            text_surface = TTF_RenderText_Solid(font, &c, text_color);

            // Create texture from surface
            text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);

            // Calculate position
            SDL_Rect render_rect = {x, rand() % SCREEN_HEIGHT, FONT_SIZE, FONT_SIZE};

            // Render texture
            SDL_RenderCopy(renderer, text_texture, NULL, &render_rect);

            // Free surface and texture
            SDL_FreeSurface(text_surface);
            SDL_DestroyTexture(text_texture);
        }

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(1000 / 40); // 30 fps
    }

    // Clean up
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
