#include <SFML/Graphics.hpp>
#include <functional> 
#include <cmath> 
#include <iostream>


void drawGraph(sf::RenderWindow& window, std::function<float(float)> func, float xMin, float xMax, float scaleX, float scaleY, sf::Color color) {
    sf::VertexArray graph(sf::LinesStrip);

    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = func(x);

        float screenX = 400 + x * scaleX;
        float screenY = 300 - y * scaleY;

        graph.append(sf::Vertex(sf::Vector2f(screenX, screenY), color));
    }

    window.draw(graph);
}

float f1(float x) {
    return x-9;
}

float f2(float x) {
    return 5*x + 10; 
}

int main() {


    sf::RenderWindow window(sf::VideoMode(800, 600), "Application for displaying graphs");


    sf::CircleShape userPoint(5); 
    userPoint.setFillColor(sf::Color::Red);
    bool userPointExists = false; 

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }
    sf::Text coordinatesText;
    coordinatesText.setFont(font);
    coordinatesText.setCharacterSize(20);
    coordinatesText.setFillColor(sf::Color::White);
    coordinatesText.setPosition(10, 10);

    sf::VertexArray xAxis(sf::Lines, 2);
    xAxis[0].position = sf::Vector2f(50, 300); 
    xAxis[0].color = sf::Color::White; 
    xAxis[1].position = sf::Vector2f(750, 300); 
    xAxis[1].color = sf::Color::White;

    sf::VertexArray yAxis(sf::Lines, 2);
    yAxis[0].position = sf::Vector2f(400, 50); 
    yAxis[0].color = sf::Color::White; 
    yAxis[1].position = sf::Vector2f(400, 550); 
    yAxis[1].color = sf::Color::White;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    float mathX = (mousePos.x - 400) / 10.0f;
                    float mathY = -(mousePos.y - 300) / 10.0f;

                    userPoint.setPosition(mousePos.x - userPoint.getRadius(), mousePos.y - userPoint.getRadius());
                    userPointExists = true;



                    std::string pos;

                    if ((mathX - 9) == mathY || (5*mathX + 10) == mathY) {
                        pos = "Граница";
                    }
                    else if (f2(mathX) > mathY && f1(mathX) > mathY) {
                        pos = "2";
                    }
                    else if (f2(mathX) > mathY && f1(mathX) < mathY) {
                        pos = "3";
                    }
                    else if (f2(mathX) < mathY && f1(mathX) < mathY) {
                        pos = "1";
                    }
                    else if ((f2(mathX) < mathY) && (f1(mathX) > mathY) && mathX < 0) {
                        pos = "4";
                    }


                    coordinatesText.setString("Coordinates: (" + std::to_string(mathX) + ", " + std::to_string(mathY) + ")\nPosition: " + pos);
                }
            }
        }


        window.clear();


        window.draw(xAxis);
        window.draw(yAxis);



        drawGraph(window, [](float x) { return x-9; }, -10, 10, 10, 10, sf::Color::Blue);

        drawGraph(window, [](float x) { return 5*x + 10; }, -10, 10, 10, 10, sf::Color::Red);

        if (userPointExists) {
            window.draw(userPoint);
            window.draw(coordinatesText);
        }

        window.display();
    }

    return 0;
}