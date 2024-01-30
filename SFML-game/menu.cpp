#include "menu.h"

Menu::Menu(sf::RenderWindow* window)
{
    this->window = window;
    this->winClose = new sf::RectangleShape();
    this->font = new sf::Font();
    this->image = new sf::Texture();
    this->bg = new sf::Sprite();

    set_values();
}

Menu::~Menu()
{
    //delete window;
    delete winClose;
    delete font;
    delete image;
    delete bg;
}

void Menu::run_menu()
{
    while (window->isOpen() && this->run) {
        this->loop_events();
        this->draw();
    }
}

bool Menu::getRun()
{
    return this->run;
}

int Menu::getNext()
{
    return this->next;
}

void Menu::set_values()
{
    pos = 0;
    pressed = theselect = false;
    font->loadFromFile("ethn.otf");
    image->loadFromFile("./StartMenu.png");
    bg->setTexture(*image);

    sf::Vector2u windowSize = window->getSize();

    // Get the size of the loaded texture
    sf::Vector2u textureSize = image->getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    bg->setScale(scaleX, scaleY);

    pos_mouse = { 0,0 };
    mouse_coord = { 0, 0 };
    texts.resize(4);
    options = { "THE GAME", "Play", "Settings", "About" };
    coords = { {330,150}, {590,375},{575,465},{590,565} };
    sizes = { 100,28,24,24 };

    for (std::size_t i = 0; i < texts.size(); i++) {
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setPosition(coords[i]);
    }
    texts[0].setOutlineThickness(4);
    texts[1].setOutlineThickness(4);
    //pos = 0;

    winClose->setSize(sf::Vector2f(23, 26));
    winClose->setPosition(1178, 39);
    winClose->setFillColor(sf::Color::Green);

}

void Menu::loop_events()
{
    pos_mouse = sf::Mouse::getPosition(*window);
    mouse_coord = window->mapPixelToCoords(pos_mouse);

    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.key.code == sf::Mouse::Left) {
                if (texts[1].getGlobalBounds().contains(mouse_coord))
                {
                    this->run = false;
                    this->next = 1;
                }
            }
        }
    }
}

void Menu::draw()
{
    window->clear();
    window->draw(*bg);
    for (auto t : texts) {
        window->draw(t);
    }
    window->draw(*winClose);
    window->display();
}
