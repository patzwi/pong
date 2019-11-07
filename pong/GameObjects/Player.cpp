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
    paddle.setSize(sf::Vector2f (win_width/PADDLE_SCALE_W,
                                 win_height/PADDLE_SCALE_H));
    
    goal.setSize(sf::Vector2f (win_width/GOAL_SCALE,
                               win_height));
    
    // Color the player
    c = sf::Color (rand() % 255, rand() % 255, rand() % 255);
    paddle.setFillColor(c);
    goal.setFillColor(c);
    
    // define the position of the paddle and goal line
    paddle.setPosition(pad_pos);
    goal.setPosition(goal_pos);

}

// DEBUGGING CONSTRUCTOR
Player::Player(sf::Vector2f& pad_pos, sf::Vector2f& goal_pos) {
    // define the size of the paddle and goal line
    paddle.setSize(sf::Vector2f (DEBUG_PWIDTH,
                                 DEBUG_PHEIGHT));
    goal.setSize(sf::Vector2f (DEBUG_GWIDTH,
                               DEBUG_GHEIGHT));
    // define the position of the paddle and goal line
    paddle.setPosition(pad_pos);
    goal.setPosition(goal_pos);
}

// Get Ball Color
const sf::Color& Player::getColor() {
    return c;
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
void Player::dtUpdateUp() { paddle.move(0, -speed); }

void Player::dtUpdateDown() { paddle.move(0, speed); }

// helper
bool Player::hit_helper_y(const sf::Vector2f b_pos, float b_rad,
                          float p_x, float p_y, const sf::Vector2f p_size) {
    return ((p_y >= b_pos.y && p_y <= (b_pos.y + (2 * b_rad))) &&
            ((b_pos.x >= p_x && b_pos.x <= p_x + p_size.x) ||
             (b_pos.x + (2 * b_rad) >= p_x && b_pos.x + (2 * b_rad) <= p_x + p_size.x)));
}

// Hits Top/Bottom Predicate
bool Player::ballHitsPaddleAboveBelow(Ball& ball) {
    sf::CircleShape b {ball.getGraphic()};
    // ball properties
    sf::Vector2f b_pos {b.getPosition()};
    float b_rad {b.getRadius()};
    // paddle properties
    sf::Vector2f p_pos {paddle.getPosition()};
    sf::Vector2f p_size {paddle.getSize()};
    float up_y = p_pos.y;
    float down_y = p_pos.y + p_size.y;
    // collision logic
    if (hit_helper_y(b_pos, b_rad, p_pos.x, up_y, p_size)) {
        ball.setPosition(sf::Vector2f(b_pos.x, up_y - (2 * b_rad)));
        return true;
    }
    
    if (hit_helper_y(b_pos, b_rad, p_pos.x, down_y, p_size)) {
        ball.setPosition(sf::Vector2f(b_pos.x, down_y));
        return true;
    }
    
    return false;
}

// helper
bool Player::hit_helper_x(const sf::Vector2f b_pos, float b_rad,
                float p_x, float p_y, const sf::Vector2f p_size) {
    return ((p_x >= b_pos.x && p_x <= (b_pos.x + (2 * b_rad))) &&
            ((b_pos.y >= p_y && b_pos.y <= p_y + p_size.y) ||
             (b_pos.y + (2 * b_rad) >= p_y && b_pos.y + (2 * b_rad) <= p_y + p_size.y)));
}

// Hits Left/Right Predicate
bool Player::ballHitsPaddleLeftRight(Ball& ball) {
    sf::CircleShape b {ball.getGraphic()};
    // ball properties
    sf::Vector2f b_pos {b.getPosition()};
    float b_rad {b.getRadius()};
    // paddle properties
    sf::Vector2f p_pos {paddle.getPosition()};
    sf::Vector2f p_size {paddle.getSize()};
    float left_x = p_pos.x;
    float right_x = p_pos.x + p_size.x;
    // collision logic
    if (hit_helper_x(b_pos, b_rad, left_x, p_pos.y, p_size)) {
        ball.setPosition(sf::Vector2f(left_x - (2 * b_rad), b_pos.y));
        return true;
    }
    
    if (hit_helper_x(b_pos, b_rad, right_x, p_pos.y, p_size)) {
        ball.setPosition(sf::Vector2f(right_x, b_pos.y));
        return true;
    }
    
    return false;
}

// Gets the size of the Paddle
const sf::Vector2f& Player::getPaddleShape() {
    return paddle.getSize();
}

// GOAL METHODS //////////////////////////////////////
// Get Graphical SFML Goal Object
const sf::RectangleShape& Player::getGoalGraphic() { return goal; }

// Get Goal Line Position
const sf::Vector2f& Player::getGoalPosition() { return goal.getPosition(); }

// Set Goal Line Position
void Player::setGoalPosition(const sf::Vector2f& new_pos) { goal.setPosition(new_pos); }

// Huts Left/Right Predicate
bool Player::ballHitsGoalLeftRight(Ball& ball) {
    // TODO
    return false;
}

const sf::Vector2f& Player::getGoalSize() {
    return goal.getSize();
}

