#include <iostream>
#include <SFML/Graphics.hpp>

#include "mandelbrot.cuh"
#include "move.h"

int main(){
    const int WIDTH = 800;
    const int HEIGHT = 800;
    const int MAX_ITER = 400;
    const double ZOOMF = 0.95;
    int total = WIDTH * HEIGHT;
    std::pair<double, double> tl = std::make_pair(-2.25, -1.5);
    std::pair<double, double> br = std::make_pair(0.75, 1.5);
    bool r = true, g = true, b = true, funky = true;

    sf::Uint8* pixels = new sf::Uint8[WIDTH * HEIGHT * 4];
    for (int i = 0; i < WIDTH * HEIGHT * 4; i += 4){
        pixels[i + 3] = 255;
    }
    sf::Texture mandelbrotTexture;
    mandelbrotTexture.create(WIDTH, HEIGHT);
    mandelbrotTexture.update(pixels);
    sf::Sprite sprite;
    sprite.setTexture(mandelbrotTexture);


    int numIterations[total];
    mandelbrot(WIDTH, HEIGHT, tl, br, MAX_ITER, numIterations);

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    bool show = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                zoomIn(window, WIDTH, HEIGHT, tl, br, ZOOMF);
                show = true;
            }else if (event.type == sf::Event::MouseWheelScrolled){
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
                    //std::cout<<event.mouseWheelScroll.delta<<'\n';
                    if (event.mouseWheelScroll.delta > 0){
                        zoomIn(window, WIDTH, HEIGHT, tl, br, ZOOMF);
                    } else if (event.mouseWheelScroll.delta < 0){
                        zoomOut(window, WIDTH, HEIGHT, tl, br, ZOOMF);
                    }
                    show = true;
                }
            } else if (event.type == sf::Event::KeyPressed){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){ r = !r;}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)){ g = !g;}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)){ b = !b;}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ funky = !funky;}
                show = true;
            }
        }

        window.clear();
        if (show){
            mandelbrot(WIDTH, HEIGHT, tl, br, MAX_ITER, numIterations);
            for (int i = 0; i < total; i++){
                if (!funky){
                    pixels[i * 4 + 0] = 0;
                    pixels[i * 4 + 1] = 0;
                    pixels[i * 4 + 2] = 0;
                }
                if (r) { pixels[i * 4 + 0] = ((double)numIterations[i] / MAX_ITER) * 255; }
                if (g) { pixels[i * 4 + 1] = ((double)numIterations[i] / MAX_ITER) * 255; }
                if (b) { pixels[i * 4 + 2] = ((double)numIterations[i] / MAX_ITER) * 255; }
            }
            show = false;
        }
        mandelbrotTexture.update(pixels);
        sprite.setTexture(mandelbrotTexture);
        window.draw(sprite);
        window.display();
    }

}