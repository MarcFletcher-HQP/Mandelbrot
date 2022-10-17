

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <Windows.h>
#include <math.h>
#include <string.h>


static int WIDTH = 800;
static int HEIGHT = 800;
static bool RENDERFRAMES = false;

static long double low = -2.84;
static long double high = 1.0;
static long double factor = 1;

static int MAXITER = 200;


long double map(long double value, 
                long double in_min, long double in_max, 
                long double out_min, long double out_max){


    return out_min + (value - in_min) * (out_max - out_min) / (in_max - in_min);

}



int main(int argc, char* argv[]){


    SDL_Init(SDL_INIT_EVERYTHING);


    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;


    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

    int count = 0;

    while (1){

        low += 0.15 * factor;
        high -= 0.1 * factor;
        factor *= 0.9349;
        MAXITER += 5;


        if (count > 30){
            MAXITER *= 1.02;
        }


        SDL_RenderPresent(renderer);

        for (int x = 0; x < WIDTH; x++){

            if (SDL_PollEvent(&event) && event.type == SDL_QUIT){
                return 0;
            }

            if (GetKeyState('Q') & 0x8000){
                return 0;
            }


            for(int y = 0; y < HEIGHT; y++){

                long double px = map(x, 0, WIDTH, low, high);
                long double py = map(y, 0, HEIGHT, low, high);

                long double pxi = px;
                long double pyi = py;

                int n = 0;

                for (int i = 0; i < MAXITER; i++) {

                    long double px1 = px * px - py * py;
                    long double py1 = 2 * px * py;

                    px = px1 + pxi;
                    py = py1 + pyi;

                    if ( (px + py) > 2){
                        break;
                    }

                    n++;

                }


                int bright = map(n, 0, MAXITER, 0, 255);


                if ((n == MAXITER || (bright < 20))){
                    bright = 0;
                }

                int red = map(bright * bright, 0, 255*255, 0, 255);
                int green = bright;
                int blue = map(sqrt(bright), 0, sqrt(255), 0, 255);

                SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
                SDL_RenderDrawPoint(renderer, x, y);

            }

        }

        if (RENDERFRAMES){

            SDL_Surface *sshot = SDL_GetWindowSurface(window);
            SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
            std::string file = std::to_string(count) + ".bmp";
            SDL_SaveBMP(sshot, file.c_str());
            SDL_FreeSurface(sshot);

        }

        ++count;

    }



    return 0;

}