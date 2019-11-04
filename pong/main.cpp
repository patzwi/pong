// main.cpp
// Creates the Game object and plays the game
// Patrick Zwierzynski

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Ball.hpp"

#define WIN_INIT_SIZE 1500
#define BALL_DX 10.f
#define FRAME_RATE 60
#define MAX_VEL 50
#define NUM_BALLS 100

int main(int argc, const char * argv[]) {
    
    // Create a temporary testing window
    sf::RenderWindow window (sf::VideoMode(WIN_INIT_SIZE,WIN_INIT_SIZE), "Temp. Graphics Test");
    window.setFramerateLimit(FRAME_RATE);
    
    // Create balls
    std::vector<Ball> balls;
    for (int i = 0; i < NUM_BALLS; ++i) {
        sf::Vector2f init_ball_pos ((float)WIN_INIT_SIZE/2, (float)WIN_INIT_SIZE/2);
        sf::Vector2f init_ball_vel ((rand() % MAX_VEL) - (MAX_VEL/2), (rand() % MAX_VEL) - (MAX_VEL/2));
        Ball ball(init_ball_vel, init_ball_pos);
        balls.push_back(ball);
    }
    
    // Display the window
    while (window.isOpen()) {
        // Check for events
        sf::Event e;
        while (window.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default: break;
            }
        }
        
//        // Check keys are pressed
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//            sf::Vector2f pos = ball.getPosition();
//            ball.setPosition(sf::Vector2f (pos.x, pos.y - BALL_DX));
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//            sf::Vector2f pos = ball.getPosition();
//            ball.setPosition(sf::Vector2f (pos.x, pos.y + BALL_DX));
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//            sf::Vector2f pos = ball.getPosition();
//            ball.setPosition(sf::Vector2f (pos.x - BALL_DX, pos.y));
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//            sf::Vector2f pos = ball.getPosition();
//            ball.setPosition(sf::Vector2f (pos.x  + BALL_DX, pos.y));
//        }
        
        // Update the graphics shown
        window.clear();
        for (auto& ball : balls) {
            // Check for deflection
            sf::Vector2f pos = ball.getPosition();
            if (pos.y - BALL_INIT_SIZE < -13 || pos.y + BALL_INIT_SIZE > WIN_INIT_SIZE - 20)
                ball.yDeflect();
            
            if (pos.x - BALL_INIT_SIZE < -13 || pos.x + BALL_INIT_SIZE > WIN_INIT_SIZE - 20)
                ball.xDeflect();
            
            ball.dtUpdate();
            window.draw(ball.getGraphic());
        }
        window.display();
    }
    return 0;
}
