#include <iostream>
#include <SFML/Graphics.hpp>
#include <stack>
#include <map>

struct mousepoint {
    mousepoint(int x, int y, mousepoint *prev) {
        this->x = x;
        this->y = y;
        this->previous = prev;
    };
    int x;
    int y;
    mousepoint *previous;
};

struct controll_key {

    controll_key(){
        this->key = 0;
        this->pressed = 0;
    };

    controll_key(char key) {
        this->key = key;
        this->pressed = false;
    }

    char key;
    bool pressed;
};

struct node {
    node(int x, int y, bool) {

    }
};

std::stack<mousepoint> mouse_motion = std::stack<mousepoint>();
int trail_length = 500;

void updateStates(std::map<char,bool> &key_register, sf::RenderWindow &window) {

};

void drawRoutine(sf::RenderWindow &window) {
    window.clear();

    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition(100.f, 100.f);
    shape.setFillColor(sf::Color::Cyan);

    mousepoint *trial = nullptr;
    mousepoint *prev = nullptr;
    if (!mouse_motion.empty())
        trial = &mouse_motion.top();
    for (int i = 0; i < trail_length && trial != nullptr; i++) {
        if (prev != nullptr && trial != nullptr) {
            sf::VertexArray line(sf::LinesStrip, 2);
            line[0].position = sf::Vector2f(prev->x, prev->y);
            line[1].position = sf::Vector2f(trial->x, trial->y);
            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;
            window.draw(line);
            //std::cout << "x:" << trial->x << " y:" << trial->y << " prev: " << trial->previous << " addr: " << trial << "\n";
        }
        prev = trial;
        trial = trial->previous;

    }


    window.draw(shape);
    window.display();
}
char esc_code = 36;  //ESC
char ctrl_code = 37; //CTRL
char alt_code = 39;  //ALT

int main() {
    std::cout << "Hello, World!" << std::endl;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML App");
    int counter = 0;
    int active_key;
    window.setMouseCursorGrabbed(true);
    char key_arr[5];
    key_arr[0] = esc_code;
    key_arr[1] = ctrl_code;
    key_arr[2] = alt_code;

    std::map<char,bool> key_register;
    for (char key :key_arr) {
        key_register[key] = false;
    }

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseMoved: {
                    sf::Event::MouseMoveEvent *mme = &event.mouseMove;
                    //std::cout << counter << "     " << (*mme).x << " X _ " << (*mme).y << " Y \n";
                    mousepoint *prev = nullptr;
                    if (!mouse_motion.empty())
                        prev = &mouse_motion.top();
                    int x = (*mme).x;
                    int y = (*mme).y;
                    mousepoint point = mousepoint(x, y, prev);
                    mouse_motion.push(point);
                    //std::cout << "x:" << point.x << " y:" << point.y << " prev: " << point.previous << " addr: " << &mouse_motion.top() << "\n";
                }
                    break;
                case sf::Event::KeyPressed:
                    active_key = (int) event.key.code;
                    std::cout << "Pressed: " << active_key;
                    key_register[active_key] = true;
                    std::cout << " newState: " << key_register.at(active_key) << "\n";
                    break;
                case sf::Event::KeyReleased:
                    active_key = (int) event.key.code;
                    std::cout << "Pressed: " << active_key;
                    key_register[active_key] = false;
                    std::cout << " newState: " << key_register.at(active_key) << "\n";
                    break;

            }
        }
        if(key_register.at(esc_code)){
            window.close();
        }

        updateStates(key_register,window);
        drawRoutine(window);
        counter++;

    }
    return 0;
}

