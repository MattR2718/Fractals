#include <iostream>
#include <complex>
#include <thread>
#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const int MAXITER = 40;
const int ZOOMMULT = 10;

sf::Uint8* pixels = new sf::Uint8[WIDTH * HEIGHT * 4];
bool running = true;
std::pair<double, double> xlin = {-2.25, 0.75};
std::pair<double, double> ylin = {-1.5, 1.5};
int power = 2;
bool solid = false;
std::complex<double> jc(-0.4, -0.59);
std::complex<double> jz(0, 0);


std::vector<double> linspace(double start, double end, int num)
{

  std::vector<double> linspaced;

  if (num == 0) { return linspaced; }
  if (num == 1) 
    {
      linspaced.push_back(start);
      return linspaced;
    }

  double delta = (end - start) / (num - 1);

  for(int i=0; i < num-1; ++i)
    {
      linspaced.push_back(start + delta * i);
    }
  linspaced.push_back(end);
  return linspaced;
}



int mandel(std::complex<double>& c, int maxIter, float power=2){
    std::complex<double> z(0, 0);
    int iterations = 0;
    for (iterations = 0; iterations < maxIter; iterations++){
        z = (std::pow(z, power)) + c;
        if (std::abs(z) > 4){
            if (solid) {return 0; }
            return iterations;
        }
    }
    return iterations;

}

void drawMandelbrot(){
    sf::RenderWindow w(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot");
    w.setFramerateLimit(30);
    while(w.isOpen()){
        // Process events
        sf::Event event;
        while (w.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                w.close();

            else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Vector2i pos = sf::Mouse::getPosition(w);
                std::cout<<pos.x << ' ' << pos.y<<'\n';
                double msx = ((pos.x / (double)WIDTH) * (xlin.second - xlin.first)) + xlin.first;
                double msy = ((pos.y / (double)HEIGHT) * (ylin.second - ylin.first)) + ylin.first;
                double difx = xlin.second - xlin.first;
                difx /= ZOOMMULT;
                double dify = ylin.second - ylin.first;
                dify /= ZOOMMULT;
                xlin.first = msx - difx;
                xlin.second = msx + difx;
                ylin.first = msy - dify;
                ylin.second = msy + dify;
            }
            else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                sf::Vector2i pos = sf::Mouse::getPosition(w);
                std::cout<<pos.x << ' ' << pos.y<<'\n';
                double msx = ((pos.x / (double)WIDTH) * (xlin.second - xlin.first)) + xlin.first;
                double msy = ((pos.y / (double)HEIGHT) * (ylin.second - ylin.first)) + ylin.first;
                double difx = xlin.second - xlin.first;
                difx *= ZOOMMULT;
                double dify = ylin.second - ylin.first;
                dify *= ZOOMMULT;
                xlin.first = msx - difx;
                xlin.second = msx + difx;
                ylin.first = msy - dify;
                ylin.second = msy + dify;
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)){
                std::cout<<"MIDDLE\n";
                sf::Vector2i pos = sf::Mouse::getPosition(w);
                jc.real(((pos.x / (double)WIDTH) * (xlin.second - xlin.first)) + xlin.first);
                jc.imag(((pos.y / (double)HEIGHT) * (ylin.second - ylin.first)) + ylin.first);
            }
            else if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Space){
                    xlin.first = -2.25;
                    xlin.second = 0.75;
                    ylin.first = -1.5;
                    ylin.second = 1.5;
                    std::cout<<"Space\n";
                }
                if (event.key.code == sf::Keyboard::Up){
                    power++;
                }
                if (event.key.code == sf::Keyboard::Down){
                    power--;
                }
                if (event.key.code == sf::Keyboard::Return){
                    std::cout<<"Enter\n";
                    solid = !solid;
                }
                
            }
        }
        sf::Texture mandelbrot;
        mandelbrot.create(WIDTH, HEIGHT);
        mandelbrot.update(pixels);
        sf::Sprite sprite;
        sprite.setTexture(mandelbrot);
        w.clear();
        w.draw(sprite);
        w.display();
    
    }
    running = false;
}

int julia(std::complex<double> z, float power=2){
    int iterations = 0;
    for (iterations = 0; iterations < MAXITER; iterations++){
        z = (std::pow(z, 2)) + jc;
        if (std::abs(z) > 4){
            if (solid) {return 0; }
            return iterations;
        }
    }
    return iterations;
}

void drawJulia(){
    sf::RenderWindow w(sf::VideoMode(WIDTH, HEIGHT), "Julia");
    w.setFramerateLimit(30);
    sf::Uint8* jpixels = new sf::Uint8[WIDTH * HEIGHT * 4];

    for (uint i = 0; i < HEIGHT*WIDTH; i++)
    {
        jpixels[i*4 + 3] = 255;
        jpixels[i*4 + 2] = 0;
    }


    while (running){

        std::vector<double> xvalues = linspace(-2, 2, WIDTH);
        std::vector<double> yvalues = linspace(-2, 2, HEIGHT);
        //std::cout<<jc.real()<<' '<<jc.imag()<<'\n';
        for (int i = 0; i < WIDTH; i++){
            for (int j = 0; j < HEIGHT; j++){
                std::complex<double> z(xvalues[i], yvalues[j]);
                //std::cout<<jz.real()<<' '<<jz.imag()<<'\n';
                int iter = julia(z, power);
                //int iter = mandel(jz, MAXITER, power);
                //std::cout<< iter <<' ';
                //std::cout<<(iter/MAXITER)<<' ';
                jpixels[((j * WIDTH) + i) * 4 + 1] = ((double)iter / MAXITER) * 255;
            }
        }




        sf::Texture julia;
        julia.create(WIDTH, HEIGHT);
        julia.update(jpixels);
        sf::Sprite sprite;
        sprite.setTexture(julia);
        w.clear();
        w.draw(sprite);
        w.display();
    }
}

/*void test(){
    while(window.isOpen()){
        sf::Event event;
        std::cout<<"Thread Running\n";
    }
}*/






int main()
{
    XInitThreads();


    // Create the main window
    //sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot");

    //sf::Texture mandelbrot;
    //mandelbrot.create(WIDTH, HEIGHT);
    //sf::Uint8* pixels = new sf::Uint8[WIDTH * HEIGHT * 4];
    for (uint i = 0; i < HEIGHT*WIDTH; i++)
    {
        pixels[i*4 + 3] = 255;
        pixels[i*4 + 2] = 0;
    }
    //mandelbrot.update(pixels);
    //sf::Sprite sprite;
    //sprite.setTexture(mandelbrot);


    /*std::pair<double, double> xlin = {-2.25, 0.75};
    std::pair<double, double> ylin = {-1.5, 1.5};*/
    
    //XInitThreads();
    std::thread mandelbrotThread = std::thread(drawMandelbrot);
    std::thread juliaThread = std::thread(drawJulia);
    
    // Start the game loop
    while (running)
    {
        

        /*sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                std::cout<<pos.x << ' ' << pos.y<<'\n';
            }
        }*/



        std::vector<double> xvalues = linspace(xlin.first, xlin.second, WIDTH);
        std::vector<double> yvalues = linspace(ylin.first, ylin.second, HEIGHT);
        int xlen = xvalues.size();
        int ylen = yvalues.size();
        //std::cout<<xlen<<' '<<ylen<<'\n';

        for (int i = 0; i < xlen; i++){
            for (int j = 0; j < ylen; j++){
                double cx = xvalues[i];
                double cy = yvalues[j];
                std::complex<double> c(cx, cy);
                int iter = mandel(c, MAXITER, power);
                //std::cout<< iter <<' ';
                //std::cout<<(iter/MAXITER)<<' ';
                pixels[((j * xlen) + i) * 4 + 1] = ((double)iter / MAXITER) * 255;
            }
            //std::cout<<'\n';
        }
        //std::cout<<"SET TEXTURE\n";
        //mandelbrot.update(pixels);
        //sprite.setTexture(mandelbrot);


        // Clear screen
        //window.clear();

        //window.draw(sprite);

        // Update the window
        //window.display();
    }
}
