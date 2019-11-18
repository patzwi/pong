//
//  Audio.hpp
//  pong -- Audio Interface
//  Patrick Zwierzynski

#ifndef Audio_hpp
#define Audio_hpp

#include <iostream>
#include <SFML/Audio.hpp>


class Audio {
    // Filenames
    const char * filename_wall_bounce = "GameSounds/wall_bounce.wav";
    const char * filename_paddle_bounce = "GameSounds/paddle_bounce.wav";
    
    // Sound Buffer Objects
    sf::SoundBuffer audio_buffer_wall;
    sf::SoundBuffer audio_buffer_paddle;
    
    // Sound Objects
    sf::Sound audio_sound_wall;
    sf::Sound audio_sound_paddle;
public:
    // Constructor
    Audio();
    
    // Play Sounds
    void play_wall_bounce();
    void play_paddle_bounce();
};

#endif /* Audio_hpp */
