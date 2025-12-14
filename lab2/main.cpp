#include <SFML/Graphics.hpp>
#include <cmath>
#include <functional>
#include <string>
#include <iostream>
#include <cstdio> // Для std::snprintf

// --- Функции, определяющие графики ---

float f1(float x) { return x - 9; }
float f2(float x) { return 5 * x + 10; }

// --- Вспомогательные функции для рисования ---


void drawGraph(sf::RenderWindow& window,
          std::function<float(float)> func,
          float xMin, float xMax,
          float scaleX, float scaleY,
          sf::Color color)
{
          const float centerX = 400.f; 
          const float centerY = 450.f; 

          sf::VertexArray graph;
          graph.setPrimitiveType(sf::PrimitiveType::LineStrip);
          for (float x = xMin; x <= xMax; x += 0.01f) {
                    float y = func(x);
                    float sx = centerX + x * scaleX; 
                    float sy = centerY - y * scaleY; 
                    graph.append({ {sx, sy}, color });
          }
          window.draw(graph);
}


std::string determineZone(float x, float y) {
          float y1 = f1(x);
          float y2 = f2(x);
          
          const float intersectionX = -4.75f;
          
          const float eps = 1e-3f;
          
          if (std::fabs(y - y1) < eps || std::fabs(y - y2) < eps) return "Boundary";

              
          
          if (x < intersectionX) {
                    if (y > y1 && y > y2) return "Zone1"; 
                    if (y < y1 && y > y2) return "Zone4"; 
                    if (y < y1 && y < y2) return "Zone2"; 
          } else {
                    if (y > y1 && y > y2) return "Zone1"; 
                    if (y < y2 && y > y1) return "Zone3"; 
                    if (y < y1 && y < y2) return "Zone2"; 
          }
          
          
          return "Zone4";
}


void drawGrid(sf::RenderWindow& window, float stepX, float stepY, float scaleX, float scaleY) {
          sf::Vector2u ws = window.getSize();
          float w = (float)ws.x, h = (float)ws.y;
          sf::VertexArray lines;
          lines.setPrimitiveType(sf::PrimitiveType::Lines);
          
          const float centerX = 400.f;
          const float centerY = 450.f;

          float maxUnitsX = w / (2.f * scaleX);
          for (float x = -maxUnitsX; x <= maxUnitsX; x += stepX) {
                    float sx = centerX + x * scaleX;
                    lines.append({ {sx, 0.f}, sf::Color(120, 120, 120) });
                    lines.append({ {sx, h}, sf::Color(120, 120, 120) });
          }
          
          float maxUnitsY_neg = centerY / scaleY; 
          float maxUnitsY_pos = (h - centerY) / scaleY; 
          
          for (float y = 0; y <= maxUnitsY_neg; y += stepY) {
                    float sy = centerY - y * scaleY; 
                    lines.append({ {0.f, sy}, sf::Color(120, 120, 120) });
                    lines.append({ {w, sy}, sf::Color(120, 120, 120) });
          }
              for (float y = 0; y >= -maxUnitsY_pos; y -= stepY) {
                    float sy = centerY - y * scaleY; 
                    lines.append({ {0.f, sy}, sf::Color(120, 120, 120) });
                    lines.append({ {w, sy}, sf::Color(120, 120, 120) });
          }

          window.draw(lines);
}



int main() {
          sf::RenderWindow window(sf::VideoMode({ 800u, 600u }), "y=x-9 & y=5*x+10");
          window.setFramerateLimit(60);

          sf::CircleShape userPoint(5.f);
          userPoint.setFillColor(sf::Color::Red);
          bool userPointExists = false;

          sf::Font font;
          if (!font.openFromFile("arial.ttf")) {
                    std::cerr << "Error: could not load font arial.ttf. Check file path." << std::endl;
          }

          sf::Text coordText(font, "", 20);
          coordText.setFillColor(sf::Color::White);
          coordText.setPosition({ 10.f, 10.f });

          const float scaleX = 30.f; 
          const float scaleY = 8.f;     
          const float centerX = 400.f; 
          const float centerY = 450.f; 
          while (window.isOpen()) {
                    while (auto evOpt = window.pollEvent()) {
                              const sf::Event& ev = *evOpt;
                              if (ev.is<sf::Event::Closed>()) {
                                        window.close();
                              }
                              if (auto* mb = ev.getIf<sf::Event::MouseButtonPressed>()) {
                                        if (mb->button == sf::Mouse::Button::Left) {
                                                  sf::Vector2i mpos = sf::Mouse::getPosition(window);
                                                  
                                                  float mathX = (mpos.x - centerX) / scaleX;
                                                  float mathY = -(mpos.y - centerY) / scaleY; 

                                                  userPoint.setPosition({ mpos.x - userPoint.getRadius(),
                                                                                                                  mpos.y - userPoint.getRadius() });
                                                  userPointExists = true;

                                                  std::string zone = determineZone(mathX, mathY);
                                                  char buf[100];
                                                  std::snprintf(buf, sizeof(buf), "x=%.2f y=%.2f\n%s", mathX, mathY, zone.c_str());
                                                  coordText.setString(buf);

                                                  std::cout << "Click: mathX=" << mathX << ", mathY=" << mathY
                                                            << ", zone=" << zone << std::endl;
                                        }
                              }
                    }

                    window.clear(sf::Color(10, 10, 40));

                    drawGrid(window, 1.f, 5.f, scaleX, scaleY);

                    // Рисуем оси
                    sf::VertexArray xAxis(sf::PrimitiveType::Lines);
                    xAxis.append({ {0.f, centerY}, sf::Color::White }); 
                    xAxis.append({ {800.f, centerY}, sf::Color::White });
                    sf::VertexArray yAxis(sf::PrimitiveType::Lines);
                    yAxis.append({ {centerX, 0.f}, sf::Color::White }); 
                    yAxis.append({ {centerX, 600.f}, sf::Color::White });
                    window.draw(xAxis);
                    window.draw(yAxis);

                    drawGraph(window, f1, -(400.f / scaleX), (400.f / scaleX), scaleX, scaleY, sf::Color::Red);
                    drawGraph(window, f2, -(400.f / scaleX), (400.f / scaleX), scaleX, scaleY, sf::Color::Cyan);

                    if (userPointExists) {
                              window.draw(userPoint);
                              window.draw(coordText);
                    }

                    window.display();
          }

          return 0;
}
