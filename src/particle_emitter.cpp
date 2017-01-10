#include "particle_emitter.h"

// Constructor basic
particle_emitter::particle_emitter(){
  // Position
  this -> min_pos = vec2( 0, 0);
  this -> max_pos = vec2( 0, 0);
  type = 0;
}

// Constructor with parameters
particle_emitter::particle_emitter( vec2 min_pos, vec2 max_pos){
  // Position
  this -> min_pos = min_pos;
  this -> max_pos = max_pos;

  launch_velocity = vec2( -10, 10);

  // Load image
  image = load_bitmap( "images/fuzzball.png", NULL);
}

// Destructor
particle_emitter::~particle_emitter(){

}

// Create particles
void particle_emitter::create_particle( int type){
  if( type == 0){
    // Smoke
    particle newPart1( random( min_pos.x, max_pos.x), random( min_pos.y - 40, max_pos.y - 40),
                      vec2( randomf( -0.1, 0.2), randomf( -0.1, -0.5)),
                      vec2( 0.003, -0.003),
                      random( 5, 8), 0xFFFFFF, 0x000000, random( 500, 1000), IMAGE, true);
    newPart1.set_image( image);
    particles.push_back( newPart1);
    this -> type = type;
  }

  if( type == 1){
    // Fire
    particle newPart4( random( min_pos.x, max_pos.x), random( min_pos.y, max_pos.y),
                      vec2( randomf( -0.5, 0.5), randomf( -1, -2)),
                      vec2( 0, randomf( 0.01, 0.03)),
                      random( 4, 8), 0xFFAA00, 0xFF0000, random( 20, 80), SQUARE, false);
    particles.push_back( newPart4);
    this -> type = type;
  }

  if( type == 2){
    // Water
    particle newPart2( random( min_pos.x, max_pos.x), random( min_pos.y, max_pos.y),
                      vec2( randomf( -1, 1), randomf( -10, -5)),
                      vec2( 0, 0.1),
                      random( 4, 6), 0x0000FF, 0x000000, random( 200, 400), CIRCLE, true);
    particles.push_back( newPart2);
    this -> type = type;
  }

  if( type == 3){
    // Spark
    particle newPart3( min_pos.x, min_pos.y,
                      vec2( randomf( -2, 2), randomf( -3, -5)),
                      vec2( 0, randomf( 0.1, 0.2)),
                      random( 1, 3), 0xFFAA00, 0xFF0000, random( 10, 50), PIXEL, false);
    particles.push_back( newPart3);
    this -> type = type;
  }
}

// Move
void particle_emitter::move_to( vec2 position){
  max_pos.x += position.x - min_pos.x;
  max_pos.y += position.y - min_pos.y;
  min_pos.x = position.x;
  min_pos.y = position.y;
}

// Update
void particle_emitter::update( int dt){
  // Update each particle
  for( unsigned int i = 0; i < particles.size(); i++){
    if( particles.at(i).dead()){
      particles.erase( particles.begin() + i);
    }
    else{
      particles.at(i).update( dt/4);
    }
  }
}

// Draw
void particle_emitter::draw( BITMAP *tempBitmap){
  // Show how many particles are on screen
  textprintf_ex( tempBitmap, font, 0, 30 + (20 * type), 0xFFFFFF, -1, "Particles:%i", particles.size());

  // Draw emitter
  circle( tempBitmap, (min_pos.x + max_pos.x)/2, (min_pos.y + max_pos.y)/2, 2, 0xFF0000);

  // Update each particle
  for( unsigned int i = 0; i < particles.size(); i++){
    particles.at(i).draw( tempBitmap);
  }
}

