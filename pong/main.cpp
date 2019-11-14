// main.cpp
// Creates the Game object and plays the game
// Patrick Zwierzynski

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "GameObjects/Ball.hpp"
#include "GameObjects/Player.hpp"

#define WIN_INIT_SIZE 1000
#define FRAME_RATE 60

int main(int argc, const char * argv[]) {
    // Load Audio Files
    sf::SoundBuffer audio_buffer_wall;
    sf::SoundBuffer audio_buffer_paddle;
    
    if (!audio_buffer_wall.loadFromFile("GameSounds/wall_bounce.wav")) {
        std::cerr << "Could not load wall bounce audio file!" << std::endl;
        return 9;
    }
    
    if (!audio_buffer_paddle.loadFromFile("GameSounds/paddle_bounce.wav")) {
        std::cerr << "Could not load paddle bounce audio file!" << std::endl;
        return 9;
    }
    
    sf::Sound audio_sound_wall (audio_buffer_wall);
    sf::Sound audio_sound_paddle (audio_buffer_paddle);
    
    // Create a temporary testing window
    sf::RenderWindow window (sf::VideoMode(WIN_INIT_SIZE,WIN_INIT_SIZE), "Temp. Graphics Test");
    window.setFramerateLimit(FRAME_RATE);
    
    // Create a player (left)
    sf::Vector2f p1_pad_pos (WIN_INIT_SIZE/15, WIN_INIT_SIZE/2);
    sf::Vector2f p1_goal_pos (0, 0);
    Player p1 (WIN_INIT_SIZE, WIN_INIT_SIZE, p1_pad_pos, p1_goal_pos);
    
    // Create a player (right)
    sf::Vector2f p2_pad_pos((14 * WIN_INIT_SIZE)/15, WIN_INIT_SIZE/2);
    sf::Vector2f goal_size = p1.getGoalSize();
    sf::Vector2f p2_goal_pos (WIN_INIT_SIZE - goal_size.x, 0);
    Player p2 (WIN_INIT_SIZE, WIN_INIT_SIZE, p2_pad_pos, p2_goal_pos);
    
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
        sf::Vector2f p2_pos {p2.getPaddlePosition()};
        sf::Vector2f p2_size {p2.getPaddleShape()};
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && p1_pos.y > 0)
            p1.dtUpdateUp();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
            p1_pos.y + p1_size.y < WIN_INIT_SIZE)
            p1.dtUpdateDown();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && p2_pos.y > 0)
            p2.dtUpdateUp();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            p2_pos.y + p2_size.y < WIN_INIT_SIZE)
            p2.dtUpdateDown();
        
        // Update Ball Physics
        // -- check against screen bounds
        sf::Vector2f ball_pos {ball.getPosition()};
        float ball_rad {ball.getRadius()};
        
        if (ball_pos.y <= 0 || ball_pos.y + (2 * ball_rad) >= WIN_INIT_SIZE) {
            ball.yDeflect();
            audio_sound_wall.play();
        }
        
        if (ball_pos.x <= 0 || ball_pos.x + (2 * ball_rad) >= WIN_INIT_SIZE) {
            ball.xDeflect();
            audio_sound_wall.play();
        }
        
        // -- check against player 1 bounds
        if (p1.ballHitsPaddleLeftRight(ball)) {
            ball.xDeflect();
            ball.setColor(p1.getColor());
            audio_sound_paddle.play();
        }
        
        // -- check against player 2 bounds
        if (p2.ballHitsPaddleLeftRight(ball)) {
            ball.xDeflect();
            ball.setColor(p2.getColor());
            audio_sound_paddle.play();
        }
        
        // -- update the ball
        ball.dtUpdate();
        
        // Update the graphics shown
        window.clear();
        
        window.draw(p1.getPaddleGraphic());
        window.draw(p1.getGoalGraphic());
        
        window.draw(p2.getPaddleGraphic());
        window.draw(p2.getGoalGraphic());
        
        window.draw(ball.getGraphic());
        window.display();
    }
    return 0;
}
