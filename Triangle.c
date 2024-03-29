#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "triangle.h"
#include "drawline.h"

#define TRIANGLE_PENCOLOR   0xBBBB0000

/* 
 * Print triangle coordinates along with a message
 */
void print_triangle(triangle_t *triangle, char *msg)
{
    printf("%s: %d,%d - %d,%d - %d,%d\n",
        msg,
        triangle->x1, triangle->y1, 
        triangle->x2, triangle->y2, 
        triangle->x3, triangle->y3);
}

/*
 * Return 0 if triangle coordinates are outside the surface boundary. 1 otherwise.
 */
int sanity_check_triangle(SDL_Surface *surface, triangle_t *triangle)
{
    if (triangle->sx1 < 0 || triangle->sx1 >= surface->w ||
        triangle->sx2 < 0 || triangle->sx2 >= surface->w ||
        triangle->sx3 < 0 || triangle->sx3 >= surface->w ||
        triangle->sy1 < 0 || triangle->sy1 >= surface->h ||
        triangle->sy2 < 0 || triangle->sy2 >= surface->h ||
        triangle->sy3 < 0 || triangle->sy3 >= surface->h) {
        return 0;
    } else {
        return 1;
    }
}

/*
 * Scale triangle, altering the on-screen coordinates(e.g. triangle->sx1)
 */
void scale_triangle(triangle_t *triangle)
{
    // TODO: Replace the code below with code that scales each triangle coordinate. 
    // The scaling factor is specified in triangle->scale.
    // Remember that this function MUST write to the on-surface coordinates.
    // Do not alter the model coordinates.

    (float)triangle->sx1 * triangle->scale;
    (float)triangle->sy1 * triangle->scale;
    (float)triangle->sx2 * triangle->scale;
    (float)triangle->sy2 * triangle->scale;
    (float)triangle->sx3 * triangle->scale;
    (float)triangle->sy3 * triangle->scale; 
    
    
}

/*
 * Move the triangle to the center of the surface,
 * altering the on-screen coordinates(e.g. triangle->sx1)
 */
void translate_triangle(triangle_t *triangle)
{
    // TODO: Insert code that moves the triangle on the surface.
    // The translation coordinates are specified in triangle->tx and triangle->ty.
    // Remember to use the on-surface coordinates (triangle->sx1, etc.)

    triangle->tx = 783;
    triangle->ty = 384;

    triangle->sx1 = triangle->tx + triangle->x1;
    triangle->sy1 = triangle->ty + triangle->y1; 
    triangle->sx2 = triangle->tx + triangle->x2;
    triangle->sy2 = triangle->ty + triangle->y2;
    triangle->sx3 = triangle->tx + triangle->x3;
    triangle->sy3 = triangle->ty + triangle->y3;
}

/*
 * Calculate the triangle bounding box,
 * altering fields of the triangle's rect(e.g. triangle->rect.x)
 */
void calculate_triangle_bounding_box(triangle_t *triangle)
{
    // TODO: Insert code that calculates the bounding box of a triangle.
    // Remember to use the on-surface coordinates (triangle->sx1, etc.)
    // The bounding box coordinates should be written to 
    // triangle->rect.x, triangle->rect.y, triangle->rect.w, triangle->rect.h

    if(triangle->sx1 < triangle->sx2 && triangle->sx1 < triangle->sx3) 
   
    {
       triangle->rect.x = triangle->sx1;
    }
    
    if(triangle->sx2 < triangle->sx1 && triangle->sx2 < triangle->sx3)
   
    {
        triangle->rect.x = triangle->sx2;
    }
    
    else
   
    {
        triangle->rect.x = triangle->sx3;
    }
    
    if(triangle->sy1 < triangle->sy2 && triangle->sy1 < triangle->sy3)
   
    { 
        triangle->rect.y = triangle->sy1;
    }
    
    if(triangle->sy2 < triangle->sy1 && triangle->sy2 < triangle->sy3)
    
    {    
        triangle->rect.y = triangle->sy2;
    }
   
    else
    
    {
        triangle->rect.y = triangle->sy3; 
    }
    
    int lowest_x, lowest_y, highest_x, highest_y, width, hight; 

   
    //highest x

    if (triangle->sx1 > triangle->sx2 && triangle->sx1 > triangle->sx3)
    {
        highest_x = triangle->sx1; 
    }

    if (triangle->sx2 > triangle->sx1 && triangle->sx2 > triangle->sx3)
    {
        highest_x = triangle->sx2; 
    }

    else 
    {
        highest_x = triangle->sx3; 
    }
    
 
    
    if (triangle->sy1 > triangle->sy2 && triangle->sy1 > triangle->sy3)
    {
        highest_y = triangle->sy1;
    }

    if (triangle->sy2 > triangle->sy1 && triangle->sy2 > triangle->sy3)
    {
        highest_y = triangle->sy2;
    }

    else 
    {
        highest_y = triangle->sy3;
    }
    

    width = abs(highest_x - triangle->rect.x); 

    hight = abs(highest_y - triangle->rect.y); 

    triangle->rect.w = width; 

    triangle->rect.h = hight;  
}   

/*
 * Fill the triangle on the surface with the triangle's color
 */
void fill_triangle(SDL_Surface *surface, triangle_t *triangle)
{
    // TODO: Insert code that fills the triangle with the color specified in triangle->fillcolor.
    // Hint: Draw the triangle with color TRIANGLE_PENCOLOR (this color can not
    // occur in e.g. the teapot or the example triangles).  Thus, if your 
    // approach to filling the triangle relies on looking for the edges of
    // the triangle on the surface (via the GetPixel function), you will find those
    // edges even if the triangle overlaps with a triangle that has already
    // been drawn on the surface.
    int y, x;
   
    for (y=0; y <= triangle->rect.h; y++)
     {
         int start = -1; 
         int stop = -1;
        for(x = 0; x <= triangle->rect.w; x++)
        {
            if (get_pixel(surface, triangle->rect.x + x, triangle->rect.y + y) == TRIANGLE_PENCOLOR)
             {
             if(start==-1) 
             {
                 
                start=x; 
             }
             else
             {
                stop = x;
             } 
            
        }
        }
       
        while(start <= stop)
        {
            set_pixel(surface, triangle->rect.x + start, triangle->rect.y + y, triangle->fillcolor);
                start++; 
        }
     }   
}

/*
 * Draw a filled triangle on the given surface
 */
void draw_triangle(SDL_Surface *surface, triangle_t *triangle)
{
    int isOK;

    /* Scale. */
    scale_triangle(triangle);
    
    /* Translate. */
    translate_triangle(triangle);
    
    /* Determine bounding box */
    calculate_triangle_bounding_box(triangle);

    /* Sanity check that triangle is within surface boundaries. */
    isOK = sanity_check_triangle(surface, triangle);
    if (!isOK) {
        print_triangle(triangle, "Triangle outside surface boundaries");
        return;
    }

    /* 
     * TODO: Insert calls to draw_line to draw the triangle.
     * Remember to use the on-surface coordinates (triangle->sx1, etc.)
     */

     draw_line(surface, triangle -> sx1, triangle -> sy1, triangle -> sx2, triangle -> sy2, TRIANGLE_PENCOLOR); 
     draw_line(surface, triangle -> sx2, triangle -> sy2, triangle -> sx3, triangle -> sy3, TRIANGLE_PENCOLOR);
     draw_line(surface, triangle -> sx1, triangle -> sy1, triangle -> sx3, triangle -> sy3, TRIANGLE_PENCOLOR);

    /* Fill triangle */
    fill_triangle(surface, triangle);
}
