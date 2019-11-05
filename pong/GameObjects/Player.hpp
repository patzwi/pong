//
//  Player.hpp
//  pong
//
//  Created by Patrick Z on 11/4/19.
//  Copyright © 2019 Patrick Z. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp
#define PADDLE_INIT_SPD 10
#define PADDLE_WIDTH 60.f
#define GOAL_WIDTH 10.f

#define DEBUG_PWIDTH 30.f
#define DEBUG_PHEIGHT 60.f
#define DEBUG_GWIDTH 10.f
#define DEBUG_GHEIGHT 1000.f
#define PADDLE_SCALE_H 15
#define PADDLE_SCALE_W 40
#define GOAL_SCALE 100

#include <SFML/Graphics.hpp>
#include "Ball.hpp"
#include <iostream>

class Player {
    // Describes the velocity of the Paddle
    float speed {PADDLE_INIT_SPD};
    
    // Describes the graphical shape of the Paddle
    sf::RectangleShape paddle;
    
    // Describes the graphical shape of the Goal Line
    sf::RectangleShape goal;
    
    // Helps with collision detection, left and right walls
    bool hit_helper_x(const sf::Vector2f b_pos, float b_rad,
                      float p_x, float p_y, const sf::Vector2f p_size);
    
    // Helps with collision detection, top and bottom walls
    bool hit_helper_y(const sf::Vector2f b_pos, float b_rad,
                      float p_x, float p_y, const sf::Vector2f p_size);
public:
    // Construct both the Paddle and the Goal Line
    Player(float win_height, float win_width,
           sf::Vector2f& pad_pos,
           sf::Vector2f& goal_pos);
    
    // DEBUGGING CONSTRUCTOR
    Player(sf::Vector2f& pad_pos, sf::Vector2f& goal_pos);
    
    // PADDLE METHODS ////////////////////////////////////
    // Get Graphical SFML Paddle Object
    const sf::RectangleShape& getPaddleGraphic();
    
    // Get Paddle Velocity
    float getSpeed();
    
    // Get Paddle Position -- returns XXXX coordinate
    const sf::Vector2f& getPaddlePosition();
    
    // Set Paddle Position
    void setPaddlePosition(const sf::Vector2f& new_pos);
    
    // Update motion up
    void dtUpdateUp();
    
    // Update motion down
    void dtUpdateDown();
    
    // Hits Top/Bottom Predicate
    bool ballHitsPaddleAboveBelow(Ball& b);
    
    // Hits Left/Right Predicate
    bool ballHitsPaddleLeftRight(Ball& b);
    
    // Gets the size of the Paddle
    const sf::Vector2f& getPaddleShape();
    
    // GOAL METHODS //////////////////////////////////////
    // Get Graphical SFML Goal Object
    const sf::RectangleShape& getGoalGraphic();
    
    // Get Goal Line Position
    const sf::Vector2f& getGoalPosition();
    
    // Set Goal Line Position
    void setGoalPosition(const sf::Vector2f& new_pos);
    
    // Huts Left/Right Predicate
    bool ballHitsGoalLeftRight(Ball& ball);
};

#endif /* Player_hpp */
