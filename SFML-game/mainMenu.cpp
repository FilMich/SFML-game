#include "mainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* window)
{
    this->window = window;
    this->winClose = new sf::RectangleShape();
    this->font = new sf::Font();
    this->image = new sf::Texture();
    this->bg = new sf::Sprite();

    set_values();
}

MainMenu::~MainMenu()
{
    delete window;
    delete winClose;
    delete font;
    delete image;
    delete bg;
}

void MainMenu::run_menu()
{
    while (window->isOpen() && this->run) {
        loop_events();
        draw();
    }
}

bool MainMenu::getRun()
{
    return this->run;
}

int MainMenu::getNext()
{
    return this->next;
}

void MainMenu::set_values()
{
    pos = 0;
    pressed = theselect = false;
    font->loadFromFile("ethn.otf");
    image->loadFromFile("./MainMenu.png");
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
    options = { "THE GAME", "Join Game", "Create Game", "Exit" };
    coords = { {420,70}, {550,340},{535,450},{595,555} };
    sizes = { 60,28,24,24 };

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
    winClose->setFillColor(sf::Color::Transparent);

}

void MainMenu::loop_events()
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
                else if (texts[2].getGlobalBounds().contains(mouse_coord))
                {
                    this->run = false;
                    this->next = 2;
                }
            }
        }
    }
}

void MainMenu::draw()
{
    window->clear();
    window->draw(*bg);
    for (auto t : texts) {
        window->draw(t);
    }
    window->draw(*winClose);
    window->display();
}
