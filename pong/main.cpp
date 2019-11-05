// main.cpp
// Creates the Game object and plays the game
// Patrick Zwierzynski

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Ball.hpp"
#include "Player.hpp"

#define WIN_INIT_SIZE 1500
#define FRAME_RATE 60

int main(int argc, const char * argv[]) {
    
    // Create a temporary testing window
    sf::RenderWindow window (sf::VideoMode(WIN_INIT_SIZE,WIN_INIT_SIZE), "Temp. Graphics Test");
    window.setFramerateLimit(FRAME_RATE);
    
    // Create a player
    sf::Vector2f p1_pad_pos (WIN_INIT_SIZE/15, WIN_INIT_SIZE/2);
    sf::Vector2f p1_goal_pos (0, 0);
    Player p1 (WIN_INIT_SIZE, WIN_INIT_SIZE, p1_pad_pos, p1_goal_pos);
    
    // Create a ball
    sf::Vector2f ball_pos (WIN_INIT_SIZE/2, WIN_INIT_SIZE/2);
    Ball ball (ball_pos);
    
    
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
        
        // Check keys are pressed == PADDLE INPUT CONTROL ==
        sf::Vector2f p1_pos {p1.getPaddlePosition()};
        sf::Vector2f p1_size {p1.getPaddleShape()};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && p1_pos.y > 0)
            p1.dtUpdateUp();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
            p1_pos.y + p1_size.y < WIN_INIT_SIZE)
            p1.dtUpdateDown();
        
        // Update Ball Physics
        // check against screen bounds
        sf::Vector2f ball_pos {ball.getPosition()};
        float ball_rad {ball.getRadius()};
        if (ball_pos.y <= 0 || ball_pos.y + (2 * ball_rad) >= WIN_INIT_SIZE)
            ball.yDeflect();
        
        if (ball_pos.x <= 0 || ball_pos.x + (2 * ball_rad) >= WIN_INIT_SIZE)
            ball.xDeflect();
        
        // check against player 1 bounds
        if (p1.ballHitsPaddleLeftRight(ball))
            ball.xDeflect();
        
        if (p1.ballHitsPaddleAboveBelow(ball))
            ball.yDeflect();
        
        ball.dtUpdate();
        
        // Update the graphics shown
        window.clear();
        window.draw(p1.getPaddleGraphic());
        window.draw(ball.getGraphic());
        window.display();
    }
    return 0;
}
