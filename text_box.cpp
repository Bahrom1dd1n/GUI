#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

#include <cstdlib>
#include <iostream>
#include <vector>

#include "GUI_Elements.h"
const int windowWidth = 400;
const int windowHeight = 600;
const int delay = 30;
int time_elapsed = 0;

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Cannot init SDL : " << SDL_GetError() << std::endl;
        exit(1);
    } else {
        std::cout << "SDL succesfully initailized" << std::endl;
    }

    if (TTF_Init() == -1) {
        std::cerr << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl;
        exit(1);
    } else {
        std::cout << "SDL2_ttf system ready to go!" << std::endl;
    }

    SDL_Window* win = SDL_CreateWindow("Chat_app", 0, 18, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    main_ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    bool running = true;
    SDL_Event event;

    Font main_font("Font2.ttf", 20, SDL_Color{0, 0, 0, 255});

    TextField field(5, (windowHeight - main_font.LetterHeight() - 20) >> 1, 25, &main_font);

    std::vector<LabelBox*> rial;

    auto keydown = [&](int key) {
        switch (key) {
            case 42:
                field.RemoveLast();
                break;
        }
    };

    while (running) {
        int start = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_TEXTINPUT:
                    field.AddLast(event.text.text[0]);
                    printf(" typed : %d\n", int(event.text.text[0]));
                    break;

                case SDL_KEYDOWN:
                    keydown(event.button.button);
                    break;
            }
        }
        SDL_SetRenderDrawColor(main_ren, 255, 255, 255, 255);
        SDL_RenderClear(main_ren);
        field.Render();

        for (auto& i : rial) {
            i->Render();
        }

        SDL_RenderPresent(main_ren);

        time_elapsed = SDL_GetTicks() - start;
        if (time_elapsed < ::delay) {
            SDL_Delay(::delay - time_elapsed);
            time_elapsed = ::delay;
        }
    }

    SDL_DestroyRenderer(main_ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
