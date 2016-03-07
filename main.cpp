#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL.h>

#include "defs.h"
#include "CSDLManagerLite.h"
#include "CSDLInputManagerLite.h"

using namespace std;

float rf(float fmin, float fmax)
{
    float random = ((float) rand()) / (float) RAND_MAX;
    float range = fmax - fmin;
    return (random*range) + fmin;
}

void mutate(float &n, float step, float fmin, float fmax, bool &up) {
    n += up? step : -step;
    if (up){
        if (n > fmax){
            up = false;
        }
    } else{
        if (n < fmin) {
            up = true;
        }
    }
}

int main(int argc, char *argv[]) {
    srand (time(NULL));
    CSDLManagerLite::getInstance() -> initializeSDL(WIDTH, HEIGHT, TITLE);
    CSDLManagerLite::getInstance() -> setColor(255, 255, 255, 255);

    float vals[] = {rf(1, 2.5), rf(1, 2.5), rf(1, 20), rf(0.5, 10), rf(0.5, 10), rf(0.5, 10)};
    string names[] = {"a", "b", "m", "n1", "n2", "n3"};
    bool up[] = {rf(0,1) < 0.5, rf(0,1) < 0.5, rf(0,1) < 0.5, rf(0,1) < 0.5, rf(0,1) < 0.5, rf(0,1) < 0.5};

    while (!CSDLInputManagerLite::getInstance() -> isExit()) {

        CSDLManagerLite::getInstance() -> drawSuperformula(vals[0], vals[1], vals[2], vals[3], vals[4], vals[5]);

        mutate(vals[0], rf(0.001, 0.05), 0.01, 2.5, up[0]);
        mutate(vals[1], rf(0.001, 0.05), 0.01, 2.5, up[1]);
        mutate(vals[2], rf(0.001, 0.05), 1, 16, up[2]);
        mutate(vals[3], rf(0.001, 0.05), 0.5, 20, up[3]);
        mutate(vals[4], rf(0.001, 0.05), 0.5, 20, up[4]);
        mutate(vals[5], rf(0.001, 0.05), 0.5, 20, up[5]);

        //for (int k = 0; k < 6; k++)
            //cout << names[k] + ": " << vals[k] << endl;
        //cout << endl;


        CSDLManagerLite::getInstance() -> drawFrame();
        CSDLManagerLite::getInstance() -> delay(DELAY_TIME_MS);
        CSDLManagerLite::getInstance() -> background();
        CSDLInputManagerLite::getInstance() -> update();
    }

    CSDLManagerLite::getInstance() -> clean();
    return 0;
}
