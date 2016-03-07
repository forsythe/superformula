#include <SDL.h>
#include <SDL_image.h>
#include <math.h>

#include "CSDLManagerLite.h"
#include "defs.h"


CSDLManagerLite* CSDLManagerLite::m_instance = NULL;

CSDLManagerLite::CSDLManagerLite() {
    this->m_pWindow = NULL;
    this->m_pRenderer = NULL;
}

CSDLManagerLite* CSDLManagerLite::getInstance() {
    if(m_instance  == NULL)
        m_instance = new CSDLManagerLite();
    return m_instance;
}

int CSDLManagerLite::initializeSDL(int width, int height, const std::string & title) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return -1;

    m_pWindow =      SDL_CreateWindow(
                         title.c_str(),                  // window title
                         SDL_WINDOWPOS_UNDEFINED,           // initial x position
                         SDL_WINDOWPOS_UNDEFINED,           // initial y position
                         width,                               // width, in pixels
                         height,                               // height, in pixels
                         SDL_WINDOW_OPENGL
                     );
    //

    if(m_pWindow == NULL) {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        return -2;
    }

    int imgFlags = IMG_INIT_PNG;

    if(!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize: ", IMG_GetError();
        return -4;
    }

    m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
    if(m_pWindow == NULL) {
        std::cerr << "Could not create renderer: " << SDL_GetError() << std::endl;
        return -2;
    }

    SDL_GetWindowSize(m_pWindow, &m_w, &m_h);

    return 0;
}

void CSDLManagerLite::drawFrame() {
    SDL_RenderPresent(m_pRenderer);
}


void CSDLManagerLite::delay(int ms) {
    SDL_Delay(ms);
}

void CSDLManagerLite::clean() {
    SDL_DestroyRenderer(m_pRenderer);
    SDL_DestroyWindow(m_pWindow);
    SDL_Quit();
}



void CSDLManagerLite::setColor(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(m_pRenderer, r, g, b, alpha);
}

void CSDLManagerLite::background() {
    setColor(0, 0, 0, 255);
    SDL_RenderClear(m_pRenderer);
    setColor(255, 255, 255, 255);

}

void CSDLManagerLite::drawSuperformula(float a, float b, float m, float n1, float n2, float n3) {

    int x1, y1, x2, y2;
    double theta = 0, r = 0;
    while (theta < 2*PI) {
        r = ZOOMFACTOR * pow(pow(fabs(cos(m*theta/4)/a), n2) + pow(fabs(sin(m*theta/4)/a), n3), (-1.0/n1));
        x1 = WIDTH/2 + r * cos(theta);
        y1 = HEIGHT/2 - r * sin(theta);

        theta += (PI/RESOLUTION);

        r = ZOOMFACTOR * pow(pow(fabs(cos(m*theta/4)/a), n2) + pow(fabs(sin(m*theta/4)/a), n3), (-1.0/n1));
        x2 = WIDTH/2 + r * cos(theta);
        y2 = HEIGHT/2 - r * sin(theta);
        drawLine(x1, y1, x2, y2);
    }
}

void CSDLManagerLite::drawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
}
