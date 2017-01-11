/*
 * Particles
 * Allan Legemaate
 * 07/01/2017
 * A better particle system
 */

// Libraries
#include <allegro.h>
#include <alpng.h>
#include <ctime>
#include <vector>
#include <iostream>

#include "particle_emitter.h"
#include "vec2.h"

// FPS Tickers
volatile int ticks = 0;
int fps;
int frames_done;
int old_time;
const int updates_per_second = 60;
int frames_array[10];
int frame_index = 0;
volatile int game_time = 0;
volatile int delta_time = 0;

void ticker(){
	ticks++;
}
END_OF_FUNCTION(ticker)

void game_time_ticker(){
	game_time++;
}
END_OF_FUNCTION(game_time_ticker)

void delta_time_ticker(){
	delta_time++;
}
END_OF_FUNCTION(delta_time_ticker)


// Buffer
BITMAP *buffer;

// Emitters
std::vector<particle_emitter> my_emitters;

// Setup
void setup(){
  // Init allegro
  allegro_init();
  alpng_init();
  install_timer();
  install_keyboard();
  install_mouse();

  // Setup for FPS system
  LOCK_VARIABLE( ticks);
  LOCK_FUNCTION( ticker);
  install_int_ex( ticker, BPS_TO_TIMER( updates_per_second));

  LOCK_VARIABLE( game_time);
  LOCK_FUNCTION( game_time_ticker);
  install_int_ex( game_time_ticker, BPS_TO_TIMER(10));

  LOCK_VARIABLE( delta_time);
  LOCK_FUNCTION( delta_time_ticker);
  install_int_ex( delta_time_ticker, BPS_TO_TIMER(1000));

  for(int i = 0; i < 10; i++)
    frames_array[i] = 0;

  // Allegro video
  set_color_depth( 32);
  //set_gfx_mode( GFX_AUTODETECT_FULLSCREEN, 1920, 1080, 0, 0);
  set_gfx_mode( GFX_AUTODETECT_WINDOWED, 1280, 960, 0, 0);

  // Create buffer
  buffer = create_bitmap( SCREEN_W, SCREEN_H);

  for( int i = 0; i < 20; i ++){
    particle_emitter tempEmitter = particle_emitter( vec2( 0, 0), vec2( 0, 0));
    my_emitters.push_back(tempEmitter);
  }
}

// Update
void update( int dt){
  // Update and make particles
  for( unsigned int i = 0; i < my_emitters.size(); i ++){
    my_emitters.at(i).update( dt);
    my_emitters.at(i).move_to( vec2( mouse_x, mouse_y));

    if( key[KEY_Z]){
      my_emitters.at(i).set_size( vec2( 10, 10));
      my_emitters.at(i).create_particle( 0);
    }
    if( key[KEY_X]){
      my_emitters.at(i).set_size( vec2( 100, 5));
      my_emitters.at(i).create_particle( 1);
    }
    if( key[KEY_C]){
      my_emitters.at(i).set_size( vec2( 1));
      my_emitters.at(i).create_particle( 2);
    }
    if( key[KEY_V]){
      my_emitters.at(i).set_size( vec2( 0));
      my_emitters.at(i).create_particle( 3);
    }
    if( key[KEY_B]){
      my_emitters.at(i).set_size( vec2( 0));
      my_emitters.at(i).create_particle( 4);
    }
    if( key[KEY_N]){
      my_emitters.at(i).set_size( vec2( SCREEN_W/2, 0));
      my_emitters.at(i).create_particle( 5);
    }
    if( key[KEY_M]){
      my_emitters.at(i).set_size( vec2( 2));
      my_emitters.at(i).create_particle( 6);
    }
    if( key[KEY_A]){
      my_emitters.at(i).set_size( vec2( 100));
      my_emitters.at(i).create_particle( 7);
    }
  }
}

// Draw
void draw(){
  // Clear buffer
  clear_to_color( buffer, 0x000000);

  for( unsigned int i = 0; i < my_emitters.size(); i ++){
    my_emitters.at(i).draw( buffer);
  }

  // FPS
  textprintf_ex( buffer, font, 0, 0, 0xFFFFFF, -1, "%i", fps);

  // Show how many particles are on screen
  int number_particles = 0;
  for( unsigned int i = 0; i < my_emitters.size(); i ++)
    number_particles += my_emitters.at(i).get_size();
  textprintf_ex( buffer, font, 0, 30, 0xFFFFFF, -1, "# Particles:%i", number_particles);

  // Draw buffer
  draw_sprite( screen, buffer, 0, 0);
}

// Main
int main(){
  // Setup
  setup();

  // Loop
  // FPS Counter
  while( !key[KEY_ESC]){
    while( ticks == 0){
      rest( 1);
    }
    while( ticks > 0){
      int old_ticks = ticks;

      update( delta_time);
      delta_time = 0;

      ticks--;
      if( old_ticks <= ticks){
        break;
      }
    }
    if(game_time >= old_time + 1){// i.e. a 0.1 second has passed since we last counted the frames{
			fps -= frames_array[frame_index];// decrement the fps by the frames done a second ago
			frames_array[frame_index] = frames_done;// store the number of frames done this 0.1 second
			fps += frames_done;// increment the fps by the newly done frames
			frame_index = (frame_index + 1) % 10;// increment the frame index and snap it to 10
			frames_done = 0;
			old_time += 1;
		}
    draw();
    frames_done++;
  }

  // End program
  return 0;
}
END_OF_MAIN();
