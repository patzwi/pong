//
//  Pong.hpp
//  pong -- Game Interface
//  Patrick Zwierzynski

#ifndef Pong_hpp
#define Pong_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Audio.hpp"
#include "Player.hpp"

class Pong {
    // Graphical Parameters
    const int frame_rate = 60;
    int window_width, window_height;
    const char* game_title = "Pat Pong";
    
    sf::RenderWindow * game_window;
    
    // Player Parameters
    sf::Vector2f p1_pad_pos {0,0};
    sf::Vector2f p1_goal_pos {0,0};
    
    sf::Vector2f p2_pad_pos {0,0};
    sf::Vector2f p2_goal_pos {0,0};
    
    const int player_x_scale = 15;
    const int player_y_scale = 2;
    
    Player * p_left;
    Player * p_right;
    
    // Ball Parameters
    sf::Vector2f ball_pos {0,0};
    const int ball_pos_scale = 2;

    Ball * ball;
    
    // Audio Data
    const Audio game_sounds;
    
    // Gameplay Parameters
    int num_players;
    bool newRound = true;
    
    // Modular Motion
    // For convenience
    typedef bool (Pong::*MotionPred_ptr)(sf::Vector2f&, sf::Vector2f&, sf::Vector2f&);
    typedef bool MotionPred(sf::Vector2f&, sf::Vector2f&, sf::Vector2f&);
    
    MotionPred_ptr p_left_moveUp;
    MotionPred_ptr p_left_moveDown;
    MotionPred_ptr p_right_moveUp;
    MotionPred_ptr p_right_moveDown;
    
    MotionPred basic_ai_Up;
    MotionPred basic_ai_Down;
    MotionPred p_left_manualUp;
    MotionPred p_left_manualDown;
    MotionPred p_right_manualUp;
    MotionPred p_right_manualDown;
    
public:
    // Constructor
    Pong(int win_width, int win_height, int num_p);
    
    // Destructor
    ~Pong();
    
    // Play Game
    void play();
};

#endif /* Pong_hpp */
