#include "move.h"

std::pair<double, double> mouseToPlane(sf::Vector2i& mp, std::pair<double, double>& tl, std::pair<double, double>& br, const int& width, const int& height){
    int x = mp.x;
    int y = mp.y;
    double px = tl.first + (((double)x / width) * (br.first - tl.first));
    double py = tl.second + (((double)y / height) * (br.second - tl.second));
    return std::make_pair(px, py);
}

void zoomIn(sf::RenderWindow& window, const int& width, const int& height, std::pair<double, double>& tl, std::pair<double, double>& br, float factor){
    sf::Vector2i mp = sf::Mouse::getPosition(window);
    std::pair<double, double> p = mouseToPlane(mp, tl, br, width, height);
    double ntlx = tl.first + ((p.first - tl.first) * (1 - factor));
    double ntly = tl.second - ((tl.second - p.second) * (1 - factor));
    double nbrx = br.first - ((br.first - p.first) * (1 - factor));
    double nbry = br.second + ((p.second - br.second) * (1 - factor));
    tl = std::make_pair(ntlx, ntly);
    br = std::make_pair(nbrx, nbry);
}

void zoomOut(sf::RenderWindow& window, const int& width, const int& height, std::pair<double, double>& tl, std::pair<double, double>& br, float factor){
    sf::Vector2i mp = sf::Mouse::getPosition(window);
    std::pair<double, double> p = mouseToPlane(mp, tl, br, width, height);
    double ntlx = tl.first - ((p.first - tl.first) * (1 - factor));
    double ntly = tl.second + ((tl.second - p.second) * (1 - factor));
    double nbrx = br.first + ((br.first - p.first) * (1 - factor));
    double nbry = br.second - ((p.second - br.second) * (1 - factor));
    tl = std::make_pair(ntlx, ntly);
    br = std::make_pair(nbrx, nbry);
}