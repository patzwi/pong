//
//  Player.cpp
//  pong
//
//  Created by Patrick Z on 11/4/19.
//  Copyright © 2019 Patrick Z. All rights reserved.
//

#include "Player.hpp"

// ACTUAL CONSTRUCTOR
Player::Player(float win_height, float win_width,
               sf::Vector2f& pad_pos,
               sf::Vector2f& goal_pos) {
    // define the size of the paddle and goal line
    paddle.setSize(sf::Vector2f (win_height/PADDLE_SCALE,
                                 win_width/PADDLE_SCALE));
    goal.setSize(sf::Vector2f (win_height,
                               win_width/GOAL_SCALE));
    // define the position of the paddle and goal line
    paddle.setPosition(pad_pos);
    goal.setPosition(goal_pos);
}

// DEBUGGING CONSTRUCTOR
Player::Player(sf::Vector2f& pad_pos, sf::Vector2f& goal_pos) {
    // define the size of the paddle and goal line
    paddle.setSize(sf::Vector2f (DEBUG_PHEIGHT,
                                 DEBUG_PWIDTH));
    goal.setSize(sf::Vector2f (DEBUG_GHEIGHT,
                               DEBUG_GWIDTH));
    // define the position of the paddle and goal line
    paddle.setPosition(pad_pos);
    goal.setPosition(goal_pos);
}

// PADDLE METHODS ////////////////////////////////////
// Get Graphical SFML Paddle Object
const sf::RectangleShape& Player::getPaddleGraphic() { return paddle; }

// Get Paddle Velocity
float Player::getSpeed() { return speed; }

// Get Paddle Position -- returns XXXX coordinate
const sf::Vector2f& Player::getPaddlePosition() { return paddle.getPosition(); }

// Set Paddle Position
void Player::setPaddlePosition(const sf::Vector2f& new_pos) { paddle.setPosition(new_pos); }

// Update motion
void Player::dtUpdateUp() { paddle.move(0, speed); }

void Player::dtUpdateDown() { paddle.move(0, -speed); }

// Hits Top/Bottom Predicate
bool Player::hitsPaddleAboveBelow(const sf::Vector2f coord) {
    // TODO
    return false;
}

// Hits Left/Right Predicate
bool Player::hitsPaddleLeftRight(const sf::Vector2f coord) {
    // TODO
    return false;
}

// GOAL METHODS //////////////////////////////////////
// Get Graphical SFML Goal Object
const sf::RectangleShape& Player::getGoalGraphic() { return goal; }

// Get Goal Line Position
const sf::Vector2f& Player::getGoalPosition() { return goal.getPosition(); }

// Set Goal Line Position
void Player::setGoalPosition(const sf::Vector2f& new_pos) { goal.setPosition(new_pos); }

// Huts Left/Right Predicate
bool Player::hitsGoalLeftRight(const sf::Vector2f coord) {
    // TODO
    return false;
}
