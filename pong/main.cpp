#include <SFML/System.hpp>
#include <iostream>

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    std::cout << "Gimme a sec!" << std::endl;
    sf::sleep(sf::seconds(1.f));
    return 0;
}
