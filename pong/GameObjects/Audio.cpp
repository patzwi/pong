//
//  Audio.cpp
//  pong -- Audio Implementation
//  Patrick Zwierzynski

#include "Audio.hpp"

Audio::Audio () {
    // Initialize Buffers from Sound File Data
    if (!audio_buffer_wall.loadFromFile(filename_wall_bounce))
        std::cerr << "Could not load Wall Bounce Audio!" << std::endl;
    
    if (!audio_buffer_paddle.loadFromFile(filename_paddle_bounce))
        std::cerr << "Could not load Paddle Bounce Audio!" << std::endl;
    
    // Initialize Sound Objects from Buffer Objects
    audio_sound_wall.setBuffer(audio_buffer_wall);
    audio_sound_paddle.setBuffer(audio_buffer_paddle);
}

void Audio::play_wall_bounce() { audio_sound_wall.play(); }

void Audio::play_paddle_bounce() { audio_sound_paddle.play(); }
