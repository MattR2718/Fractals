#ifndef MOVE
#define MOVE

#include <iostream>
#include <SFML/Graphics.hpp>

void zoomIn(sf::RenderWindow& window, const int& width, const int& height, std::pair<double, double>& tl, std::pair<double, double>& br, float factor);
void zoomOut(sf::RenderWindow& window, const int& width, const int& height, std::pair<double, double>& tl, std::pair<double, double>& br, float factor);

#endif