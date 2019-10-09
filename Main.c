#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "drawline.h"
#include "triangle.h"
#include "teapot_data.h"


int main(void)
{
    const size_t bufsize = 100;
    
    /* Change the screen width and height to your own liking */
    const int screen_w = 1366;
    const int screen_h = 768;

    char errmsg[bufsize];
    int done;
    SDL_Surface *surface;
    SDL_Window *window;
    SDL_Event event;
    
    /* Initialize SDL */
    if (SDL_Init(SDL_INIT_VIDEO) < -1) {
        snprintf(errmsg, bufsize, "Unable to initialize SDL.");
        goto error;
    }
    
    /* Create a 1600x900 window */
    window = SDL_CreateWindow("The Amazing Teapot",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              screen_w, screen_h,
                              0);
    if(!window) {
        snprintf(errmsg, bufsize, "Unable to get video surface.");
        goto error;
    }

    /* Create the suface in RAM that we manipulate the pixels of */
    surface = SDL_GetWindowSurface(window);
    if(!surface) {
        snprintf(errmsg, bufsize, "Unable to create surface.");
        goto error;
    }

    /*
     * The teapot is represented as an array of triangle data structures.
     * To draw it on the screen you need to traverse the 'teapot_model' array
     * and call draw_triangle for each triangle (teapot_data.h contains the array).  
     * The definition TEAPOT_NUMTRIANGLES specifies the number of triangles in the array.
     * The teapot model is contained within a 1000x1000 box (coordinates
     * from -500 to 500 on the x and y axis).  Remember to translate the
     * model to the middle of the screen before drawing it (initialize 
     * triangle->tx and triangle->ty with the appropriate coordinates).
     */
    
    /*
     * Draw some example triangles on the screen. 
     * Use these examples in the beginning.
     *
     * Remove these and draw the triangles that represent he teapot
     */
    
    int i; 

    for(i = 0; i <= TEAPOT_NUMTRIANGLES; i++){
        draw_triangle(surface, &teapot_model[i]);
    }
	
    /* Wait for the user to exit the application */
    done = 0;
    while (!done) {
        
        /* Update the window surface */
        SDL_UpdateWindowSurface(window);
        
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    done = 1;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_SHOWN)
                        SDL_SetWindowPosition(window, 50, 50);
                    break;
            }          
        }
    }   
    
    SDL_Quit();

    return 0;

    /* Upon an error, print message and quit properly */
error:
    fprintf(stderr, "%s Error returned: %s\n", errmsg, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
