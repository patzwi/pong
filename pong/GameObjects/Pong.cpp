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
            p_left_moveUp = &Pong::p_left_manualUp;
            p_left_moveDown = &Pong::p_left_manualDown;
            p_right_moveUp = &Pong::basic_ai_Up;
            p_right_moveDown = &Pong::basic_ai_Down;
            break;
        case 2:
            p_left_moveUp = &Pong::p_left_manualUp;
            p_left_moveDown = &Pong::p_left_manualDown;
            p_right_moveUp = &Pong::p_right_manualUp;
            p_right_moveDown = &Pong::p_right_manualDown;
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
        
        // 
    }
}

// Modular AI Motion Predicates
// --Up
bool Pong::basic_ai_Up(sf::Vector2f& b_pos, sf::Vector2f& p_pos, sf::Vector2f& p_size) {
    // TODO
    return false;
}
// --Down
bool Pong::basic_ai_Down(sf::Vector2f& b_pos, sf::Vector2f& p_pos, sf::Vector2f& p_size) {
    // TODO
    return false;
}

// Modular Player Motion Predicates
// --Left & Up
bool Pong::p_left_manualUp(sf::Vector2f& b_pos, sf::Vector2f& p_pos, sf::Vector2f& p_size) {
    // TODO
    return false;
}
// --Left & Down
bool Pong::p_left_manualDown(sf::Vector2f& b_pos, sf::Vector2f& p_pos, sf::Vector2f& p_size) {
    // TODO
    return false;
}
// --Right & Up
bool Pong::p_right_manualUp(sf::Vector2f& b_pos, sf::Vector2f& p_pos, sf::Vector2f& p_size) {
    // TODO
    return false;
}
// --Right & Down
bool Pong::p_right_manualDown(sf::Vector2f& b_pos, sf::Vector2f& p_pos, sf::Vector2f& p_size) {
    // TODO
    return false;
}
