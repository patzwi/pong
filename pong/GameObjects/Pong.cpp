//
//  Pong.cpp
//  pong -- Game Implementation
//  Patrick Zwierzynski

#include "Pong.hpp"

Pong::Pong(int win_width, int win_height, int num_p) :
    window_width(win_width), window_height (win_height), num_players(num_p) {
    
    // Initialize Game Window
    game_window = new sf::RenderWindow(sf::VideoMode(window_width, window_height), game_title);
    game_window->setFramerateLimit(frame_rate);
    
    // Create Left Player
    p1_pad_pos = (sf::Vector2f (window_width/player_x_scale,
                                 window_height/player_y_scale));
    p_left = new Player (window_width, window_height, p1_pad_pos, p1_goal_pos);
    
    // Create Right Player
    p2_pad_pos = (sf::Vector2f (((player_x_scale - 1) * window_width) / player_x_scale,
                                 window_height/player_y_scale));
    sf::Vector2f goal_size = p_left->getGoalSize();
    p2_goal_pos = (sf::Vector2f (window_width - goal_size.x, 0));
    p_right = new Player (window_width, window_height, p2_pad_pos, p2_goal_pos);
    
    // Create Ball
    ball_pos = (sf::Vector2f (window_width/2, window_height/2));
    ball = new Ball (ball_pos);
        
    // Assign Player Motion
    switch (num_players) {
        case 0:
            p_left_moveUp = &Pong::basic_ai_Up;
            p_left_moveDown = &Pong::basic_ai_Down;
            p_right_moveUp = &Pong::basic_ai_Up;
            p_right_moveDown = &Pong::basic_ai_Down;
            break;
        case 1:
            p_left_moveUp = &Pong::p_manual_Up;
            p_left_moveDown = &Pong::p_manual_Down;
            p_right_moveUp = &Pong::basic_ai_Up;
            p_right_moveDown = &Pong::basic_ai_Down;
            break;
        case 2:
            p_left_moveUp = &Pong::p_manual_Up;
            p_left_moveDown = &Pong::p_manual_Down;
            p_right_moveUp = &Pong::p_manual_Up;
            p_right_moveDown = &Pong::p_manual_Down;
            break;
        default:
            std::cerr << "Invalid Number of Players" << std::endl;
            throw -1;
    }
}

Pong::~Pong() {
    // Free Game Window Memory
    delete game_window;
    // Free Player Memory
    delete p_left;
    delete p_right;
    // Free Ball Memory
    delete ball;
}

void Pong::play() {
    while (game_window->isOpen()) {
        // First check for closing
        sf::Event e;
        while (game_window->pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    game_window->close();
                default: break;
            }
        }
        
        // Update private members
        p1_pad_pos = p_left->getPaddlePosition();
        sf::Vector2f p1_size {p_left->getPaddleShape()};
        p2_pad_pos = p_right->getPaddlePosition();
        sf::Vector2f p2_size {p_right->getPaddleShape()};
        ball_pos = ball->getPosition();
        
        // Input control
        if ((this->*p_left_moveUp)(ball_pos, p1_pad_pos, p1_size))
            p_left->dtUpdateUp();
        
        if ((this->*p_left_moveDown)(ball_pos, p1_pad_pos, p1_size))
            p_left->dtUpdateDown();
            
        if ((this->*p_right_moveUp)(ball_pos, p2_pad_pos, p2_size))
            p_right->dtUpdateUp();
        
        if ((this->*p_right_moveDown)(ball_pos, p2_pad_pos, p2_size))
            p_right->dtUpdateDown();
        
        // Ball Motion
        // -- check against screen bounds
        float ball_rad {ball->getRadius()};
        if (live && (ball_pos.y <= 0 || ball_pos.y + (2 * ball_rad) >= window_height)) {
            ball->yDeflect();
            game_sounds.play_wall_bounce();
        }
        
        // -- check if hits against left player bounds
        if (live && p_left->ballHitsPaddleLeftRight(*ball)) {
            ball->xDeflect();
            ball->setColor(p_left->getColor());
            game_sounds.play_paddle_bounce();
        }
        
        // -- check if hits against right player bounds
        if (live && p_right->ballHitsPaddleLeftRight(*ball)) {
            ball->xDeflect();
            ball->setColor(p_right->getColor());
            game_sounds.play_paddle_bounce();
        }
        
        // Goal Score Check
        // -- left player wall
        if (live && p_left->ballHitsGoalLeftRight(*ball)) {
            ++p_right_score; // right player scores
            new_round();
        }
        
        // -- right player wall
        if (live && p_right->ballHitsGoalLeftRight(*ball)) {
            ++p_left_score;
            new_round();
        }
        
        // Update the Graphics
        // -- update the ball position
        if (live) ball->dtUpdate();
        
        // -- display the new game state
        game_window->clear();
        
        game_window->draw(p_left->getPaddleGraphic());
        game_window->draw(p_left->getGoalGraphic());
        
        game_window->draw(p_right->getPaddleGraphic());
        game_window->draw(p_right->getGoalGraphic());
        
        game_window->draw(ball->getGraphic());
        
        if (!live) {
            sf::Vector2f ball_vel {ball->getVelocity()};
            sf::Vertex line[] = {
                sf::Vertex (ball_pos + (sf::Vector2f(10,10))),
                sf::Vertex (sf::Vector2f(ball_pos.x + ball_vel.x * 5,
                                         ball_pos.y + ball_vel.y * 5))
            };
            game_window->draw(line, 2, sf::Lines);
            live = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        }
        
        game_window->display();
    }
}

// Modular AI Motion Predicates
// --Up
bool Pong::basic_ai_Up(sf::Vector2f& b_pos, sf::Vector2f& p_pos, sf::Vector2f& p_size) {
    return (b_pos.y < p_pos.y && p_pos.y > 0 && live);
}
// --Down
bool Pong::basic_ai_Down(sf::Vector2f& b_pos, sf::Vector2f& p_pos, sf::Vector2f& p_size) {
    return (b_pos.y > p_pos.y && p_pos.y + p_size.y < window_height && live);
}

// Modular Manual Motion Predicates
// --Up
bool Pong::p_manual_Up(sf::Vector2f& b_pos, sf::Vector2f& p_pos, sf::Vector2f& p_size) {
    return ((p_pos.x < window_width/2 && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) ||
            (p_pos.x > window_width/2 && sf::Keyboard::isKeyPressed(sf::Keyboard::P))) &&
           p_pos.y > 0 && live;
}
// --Down
bool Pong::p_manual_Down(sf::Vector2f& b_pos, sf::Vector2f& p_pos, sf::Vector2f& p_size) {
    return ((p_pos.x < window_width/2 && sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ||
            (p_pos.x > window_width/2 && sf::Keyboard::isKeyPressed(sf::Keyboard::L))) &&
           p_pos.y + p_size.y < window_height && live;
}

void Pong::new_round() {
    live = false;
    ball->setPosition(sf::Vector2f(window_width/2, window_height/2));
    p_left->setPaddlePosition(sf::Vector2f(p1_pad_pos.x, window_height/2));
    p_right->setPaddlePosition(sf::Vector2f(p2_pad_pos.x, window_height/2));
    
    // update score board
}
