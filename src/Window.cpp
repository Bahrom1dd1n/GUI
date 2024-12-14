#include "Window.h"

#include <SDL2/SDL_events.h>

#include <cmath>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <iterator>

#include "Element.h"

Window::Window(uint32_t x, uint32_t y, const uint32_t window_width, const uint32_t window_height,
               const std::string& title, const SDL_Color& background_cl, uint32_t max_fps, int flags) {
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
    window = SDL_CreateWindow(title.c_str(), x, y, window_width, window_height, flags);

    main_ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (flags | SDL_WINDOW_FULLSCREEN) {
        SDL_GetRendererOutputSize(this->main_ren, &window_rect.w, &window_rect.h);
        this->window_rect.x = 0;
        this->window_rect.y = 0;
    } else
        window_rect = {0, 0, (int)window_width, (int)window_height};
    this->bg_cl = background_cl;
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
                    this->OnKeyDown(event);
                    break;

                case SDL_KEYDOWN:
                    this->OnKeyDown(event);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    this->OnMouseDown(event);
                    break;
                    // case SDL_MOUSEMOTION:this->OnMouseMove(event.button.x, event.button.y);
            }
        }
        SDL_SetRenderDrawColor(main_ren, bg_cl.r, bg_cl.g, bg_cl.b, 255);
        SDL_RenderClear(main_ren);
        if (bg_img) bg_img.DrawTo(NULL);

        for (auto i : children) {
            if (i->IsVisible()) i->Draw();
        }
        if (draw_frame_callback) draw_frame_callback();
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
void Window::OnMouseDown(const SDL_Event& event) {
    printf("Muse clicked\n");
    int x = event.button.x;
    int y = event.button.y;
    Element* elem = nullptr;
    for (auto it = children.rbegin(); it != children.rend(); it++) {
        auto i = *it;
        elem = i->ContainPoint(x, y);
        if (elem) {
            if (this->focused_element != elem) {
                if (focused_element) focused_element->Unfocuse();
                elem->Focuse();
            }
            elem->MouseDown(event);
            this->focused_element = elem;
            break;
        }
        if (mousedown_callback) mousedown_callback(event.button.x, event.button.y);
    }

    if (!elem && focused_element) {
        this->focused_element->Unfocuse();
        this->focused_element = nullptr;
    }
}

/*void Window::OnMouseMove(int x, int y) {
    static uint64_t last_moved = 0;
    if (current_time - last_moved < _MOUSE_MOVE_DELAY) return;

    printf("Muse << moved >>\n");
    last_moved = current_time;
    auto it = this->children.begin();
    while (it != this->children.end()) {
        if ((*it)->ContainPoint(x, y)) {
            if (hovered_element != *it) {
                if (this->hovered_element) this->hovered_element->UnHover();
                this->hovered_element = *it;
                (*it)->Hover();
            }
            if ((*it)->OnHovered) (*it)->OnHovered();
            break;
        }
        it++;
    }
    if (this->hovered_element && it == this->children.end()) {
        this->hovered_element->UnHover();
        this->hovered_element = nullptr;
    }
}*/

void Window::OnKeyDown(const Event& event) {
    if (this->focused_element) this->focused_element->KeyDown(event);
    if (keydown_callback) keydown_callback(event.key.keysym.sym);
}

void Window::Add(Element* elem) {
    this->children.push_back(elem);
}

Window::~Window() {
    printf("Window deleted\n");
    SDL_DestroyRenderer(this->main_ren);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
};
