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

#define DEBUG_PHEIGHT 30.f
#define DEBUG_PWIDTH 60.f
#define DEBUG_GHEIGHT 1000.f
#define DEBUG_GWIDTH 10.f
#define PADDLE_SCALE 15
#define GOAL_SCALE 30

#include <SFML/Graphics.hpp>

class Player {
    // Describes the velocity of the Paddle
    float speed {PADDLE_INIT_SPD};
    
    // Describes the graphical shape of the Paddle
    sf::RectangleShape paddle;
    
    // Describes the graphical shape of the Goal Line
    sf::RectangleShape goal;
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
    bool hitsPaddleAboveBelow(const sf::Vector2f coord);
    
    // Hits Left/Right Predicate
    bool hitsPaddleLeftRight(const sf::Vector2f coord);
    
    // GOAL METHODS //////////////////////////////////////
    // Get Graphical SFML Goal Object
    const sf::RectangleShape& getGoalGraphic();
    
    // Get Goal Line Position
    const sf::Vector2f& getGoalPosition();
    
    // Set Goal Line Position
    void setGoalPosition(const sf::Vector2f& new_pos);
    
    // Huts Left/Right Predicate
    bool hitsGoalLeftRight(const sf::Vector2f coord);
};

#endif /* Player_hpp */
