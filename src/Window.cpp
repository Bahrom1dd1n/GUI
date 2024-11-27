#include "Window.h"

#include <iostream>

Window::Window(uint32_t x, uint32_t y, uint32_t window_width, uint32_t window_height, const std::string& title,
               const SDL_Color& background_cl, uint32_t max_fps) {
    this->window_width = window_width;
    this->window_height = window_height;
    this->bg_cl = background_cl;

    // Default value
    if (max_fps)
        frame_delay = 1000 / max_fps;
    else
        frame_delay = 20;
    // Initialize the video subsystem.
    // iF it returns less than 1, then an
    // error code will be received.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Cannot init SDL : " << SDL_GetError() << std::endl;
        exit(1);
    } else {
        std::cout << "SDL succesfully initailized" << std::endl;
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow(title.c_str(), x, y, window_width, window_height, SDL_WINDOW_SHOWN);

    main_ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Window::Start() {
    SDL_Event event;
    this->running = true;

    while (running) {
        int start = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_TEXTINPUT:
                    OnTyped(event.text.text[0]);
                    break;

                case SDL_KEYDOWN:
                    OnKeyDown(event.button.button);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    this->OnMouseDown(event.button.x, event.button.y);
                    break;

                case SDL_MOUSEMOTION:
                    this->OnMouseMove(event.button.x, event.button.y);
            }
        }
        SDL_SetRenderDrawColor(main_ren, bg_cl.r, bg_cl.g, bg_cl.b, 255);
        SDL_RenderClear(main_ren);

        for (int i = 0; i < this->elements.size(); i++) {
            elements[i]->Draw();
        }

        SDL_RenderPresent(main_ren);
        this->current_time = SDL_GetTicks();
        uint32_t time_elapsed = this->current_time - start;
        if (time_elapsed < this->frame_delay) {
            SDL_Delay(this->frame_delay - time_elapsed);
            time_elapsed = frame_delay;
        }
    }
};

void Window::Stop() {
    this->running = false;
}
void Window::OnMouseDown(int x, int y) {
    printf("Muse clicked\n");
    auto it = this->elements.begin();
    while (it != this->elements.end()) {
        if ((*it)->ContainPoint(x, y)) {
            if (focused_element != *it) {
                if (this->focused_element) this->focused_element->Unfocuse();
                this->focused_element = *it;
                (*it)->Focuse();
            }
            (*it)->Click();
            (*it)->OnClick();
            break;
        }
        it++;
    }
    if (this->focused_element && it == this->elements.end()) {
        this->focused_element->Unfocuse();
        this->focused_element = nullptr;
    }
}

void Window::OnMouseMove(int x, int y) {
    static uint64_t last_moved = 0;
    if (current_time - last_moved < _MOUSE_MOVE_DELAY) return;

    printf("Muse << moved >>\n");
    last_moved = current_time;
    auto it = this->elements.begin();
    while (it != this->elements.end()) {
        if ((*it)->ContainPoint(x, y)) {
            if (hovered_element != *it) {
                if (this->hovered_element) this->hovered_element->UnHover();
                this->hovered_element = *it;
                (*it)->Hover();
            }
            (*it)->OnHovered();
            break;
        }
        it++;
    }
    if (this->hovered_element && it == this->elements.end()) {
        this->hovered_element->UnHover();
        this->hovered_element = nullptr;
    }
}

void Window::OnTyped(char letter) {
    if (!this->focused_element) return;
    this->focused_element->OnTyped(letter);
    this->focused_element->Type(letter);
}
void Window::OnKeyDown(uint32_t key) {
    if (!this->focused_element) return;
    this->focused_element->OnKeyPressed(key);
    this->focused_element->KeyPress(key);
}

void Window::Add(Element* elem) {
    this->elements.push_back(elem);
}

Window::~Window() {
    printf("Window deleted\n");
    SDL_DestroyRenderer(this->main_ren);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
};
