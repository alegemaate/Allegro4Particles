/*
 * Particle
 * Allan Legemaate
 * 07/01/2017
 * A better particle
 */
#ifndef PARTICLE_H
#define PARTICLE_H

#define CIRCLE 0
#define SQUARE 1
#define PIXEL 2
#define RANDOM 3
#define IMAGE 4

#include <allegro.h>
#include <alleggl.h>
#include "vec2.h"

class particle{
  public:
    // Constructor
    particle( int x, int y, vec2 velocity, vec2 acceleration, int size, int colorStart, int colorEnd, int life, char type, bool trans_life);

    // Destructor
    ~particle() {};

    // Is dead
    bool dead();

    // Set image
    void set_image( BITMAP *image);

    // Update
    void update( int dt);

    // Draw
    void draw(BITMAP *tempBitmap);

  private:
    // Make new color
    void mix_colors();

    // Position / size
    float x;
    float y;
    int size;

    // Looks
    int colorStart;
    int colorEnd;
    int color;
    char type;
    bool trans_life;

    BITMAP* image;

    // Behavior
    vec2 velocity;
    vec2 acceleration;
    int life;
    int life_start;
};

#endif

