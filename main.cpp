#if defined(NXDK)
#include <SDL.h>
#include <hal/video.h>
#include <hal/debug.h>
#else
#include <SDL2/SDL.h>
#endif

#define WIDTH 640
#define HEIGHT 480

static SDL_Window *window;
static SDL_Surface *windowSurface;
static SDL_Surface *ball;
static SDL_Surface *leftPaddle;
static SDL_Surface *rightPaddle;
static SDL_Rect leftPaddlePos;
static SDL_Rect rightPaddlePos;
static SDL_Rect ballPos;

void Init() {
#if defined(NXDK)
  XVideoSetMode(WIDTH, HEIGHT, 32, REFRESH_DEFAULT);
#endif
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  Uint32 Rmask = 0x000000FF;
  Uint32 Gmask = 0x0000FF00;
  Uint32 Bmask = 0x00FF0000;
  Uint32 Amask = 0xFF000000;
#else
  Uint32 Amask = 0x000000FF;
  Uint32 Rmask = 0x0000FF00;
  Uint32 Gmask = 0x00FF0000;
  Uint32 Bmask = 0xFF000000;
#endif
  SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMECONTROLLER|SDL_INIT_EVENTS);
  window = SDL_CreateWindow("PongX", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
  windowSurface = SDL_GetWindowSurface(window);
  leftPaddle = SDL_CreateRGBSurface(0, 20, 100, 32, Rmask, Gmask, Bmask, Amask);
  rightPaddle = SDL_CreateRGBSurface(0, 20, 100, 32, Rmask, Gmask, Bmask, Amask);
  ball = SDL_CreateRGBSurface(0, 20, 20, 32, Rmask, Gmask, Bmask, Amask);
  SDL_FillRect(windowSurface, NULL, SDL_MapRGBA(windowSurface->format, 0, 0, 0, 255));
}

void Quit(int8_t status) {
  SDL_DestroyWindow(window);
  SDL_FreeSurface(leftPaddle);
  SDL_FreeSurface(rightPaddle);
  SDL_FreeSurface(ball);
  SDL_Quit();
  exit(0);
}

int main() {
  bool quitting = false;
  SDL_Event event;
  Init();
  while (!quitting) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          quitting = true;
          break;
      }
    }
  }
  Quit(0);
  return 0;
}
