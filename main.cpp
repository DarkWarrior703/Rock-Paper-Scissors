#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

std::string score_string(sf::Int16 user, sf::Int16 comp){
    std::stringstream ss;
    ss << user;
    ss << ":";
    ss << comp;
    return ss.str();
}

int main()
{
    //Antialising
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    //Font

    sf::Font font;
    if(!font.loadFromFile("Roboto-Regular.ttf")){
        std::cerr << "The game doesn't load the font.\n";
    }

    //Some variables
    sf::Int16 user_score = 0;
    sf::Int16 comp_score = 0;
    sf::String title_name("Rock Paper Scissors");

    //Rock, paper, scissors sprites
    sf::Texture rock_texture;
    rock_texture.loadFromFile("rock.png");
    sf::Sprite rock(rock_texture);

    sf::Texture paper_texture;
    paper_texture.loadFromFile("paper.png");
    sf::Sprite paper(paper_texture);

    sf::Texture scissors_texture;
    scissors_texture.loadFromFile("scissors.png");
    sf::Sprite scissors(scissors_texture);

    //Title
    sf::Text title;
    sf::Color main_color(36, 39, 46);
    title.setFillColor(main_color);
    title.setString(title_name);
    title.setFont(font);

    //Main Window
    sf::RenderWindow window(sf::VideoMode(600, 400), title_name, sf::Style::Default, settings);

    //Main loop
    while (window.isOpen())
    {
        //Size of Window and background
        sf::Vector2u size = window.getSize();
        sf::Vector2i pos = window.getPosition();
        sf::Vector2f background_size(size.x, size.y);
        sf::RectangleShape background(background_size);
        background.setFillColor(main_color);

        //Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
                window.close();
            if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect(0.f, 0.f, size.x, size.y)));

        }

        // Title 
        title.setCharacterSize(size.y / 10);
        sf::FloatRect title_rect = title.getLocalBounds();
        title.setPosition(size.x / 2 - title_rect.width / 2, 0);
        sf::Vector2f title_container_size(size.x, title_rect.height + size.y / 20);
        sf::RectangleShape title_container(title_container_size);
        title_container.setFillColor(sf::Color::White);

        // Score
        sf::Text score;
        score.setString(score_string(user_score, comp_score));
        score.setFont(font);
        score.setCharacterSize(size.y / 15);
        sf::FloatRect score_rect = score.getLocalBounds();
        sf::Vector2f score_container_size(title_rect.width / 2 + size.x / 80, title_rect.height / 2 + size.y / 80);
        sf::RectangleShape score_container(score_container_size);
        score_container.setFillColor(main_color);
        score_container.setOutlineColor(sf::Color::White);
        score_container.setOutlineThickness(size.y / 80);
        score_container.setPosition(size.x / 2 - score_container.getSize().x / 2, title_container_size.y + size.y / 40);
        score.setPosition(size.x / 2 - score_rect.width / 2, score_container.getPosition().y - size.y / 60);

        // User and computer containers

        sf::Text user;
        user.setString("User");
        user.setCharacterSize(size.y / 30);
        user.setFont(font);
        sf::FloatRect user_rect = user.getLocalBounds();
        sf::Vector2f user_size(score_container_size.x / 4, score_container_size.y / 2);
        sf::RectangleShape user_container(user_size);
        user_container.setFillColor(sf::Color::Red);
        user_container.setPosition(size.x / 2 - score_container_size.x / 2 - user_container.getSize().x / 2, score_container.getPosition().y + score_container_size.y / 2 - user_container.getSize().y / 2);
        user.setPosition(user_container.getPosition().x + size.x / 100, user_container.getPosition().y - size.y / 100);


        sf::Text comp;
        comp.setString("Comp");
        comp.setCharacterSize(size.y / 30);
        comp.setFont(font);
        sf::FloatRect comp_rect = comp.getLocalBounds();
        sf::Vector2f comp_size(score_container_size.x / 4, score_container_size.y / 2);
        sf::RectangleShape comp_container(comp_size);
        comp_container.setFillColor(sf::Color::Red);
        comp_container.setPosition(size.x / 2 + score_container_size.x / 2 - comp_container.getSize().x / 2, score_container.getPosition().y + score_container_size.y / 2 - comp_container.getSize().y / 2);
        comp.setPosition(comp_container.getPosition().x + size.x / 100, comp_container.getPosition().y - size.y / 100);

        // Rock, paper, scissors appearance
        sf::FloatRect rock_rect = rock.getLocalBounds();
        rock.setPosition(size.x / 2 - rock_rect.width / 2, score_container.getPosition().y + score_container_size.y + 10);
        sf::FloatRect paper_rect = paper.getLocalBounds();
        paper.setPosition(size.x / 2 - rock_rect.width - paper_rect.width, score_container.getPosition().y + score_container_size.y + 10);
        sf::FloatRect scissors_rect = scissors.getLocalBounds();
        scissors.setPosition(size.x / 2 + rock_rect.width, score_container.getPosition().y + score_container_size.y + 10);

        //Window draws
        window.clear();
        window.draw(background);
        window.draw(title_container);
        window.draw(title);
        window.draw(score_container);
        window.draw(score);
        window.draw(user_container);
        window.draw(comp_container);
        window.draw(user);
        window.draw(comp);
        window.draw(rock);
        window.draw(paper);
        window.draw(scissors);
        window.display();
    }   //End of the loop

    return 0;
}