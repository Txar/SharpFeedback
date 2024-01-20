#include "Camera.hpp"
#include "Game/Math/Math.hpp"
#include <iostream>

namespace ShF {

sf::Sprite Camera::render(std::vector<Face> &faces) {
    Line2Df ray(x, y, 0, 50);
    Line2Df pathTo;
    Point2Df p(false);

    float FOV = Math::PI / 2.0;
    ray.rotate(ShF::Math::degreesToRadians(rotation - (FOV / 2.0)));
    //if (ray.intersect(faces[0].line).exists) buffer.clear(sf::Color::White);
    buffer.clear(sf::Color::Black);

    int lineHeight;

    sf::RectangleShape line;
    line.setOutlineColor(sf::Color::Red);
    line.setFillColor(sf::Color::Red);
    int screenWidth = 800;
    
    for (int angle = 0; angle < screenWidth; angle++) {
        ray.rotate(FOV * (float)angle/screenWidth);
        for (Face i : faces) {
            p = ray.intersect(i.line);
            if (p.exists) {
                pathTo = Line2Df(ray.A(), p, true);
                lineHeight = (int)(600.0 - (int)pathTo.length());
                //std::cout << p.x << " " << p.y << std::endl;
                line = sf::RectangleShape({1, (float)lineHeight});
                line.setPosition(angle, (600.0 - lineHeight) / 2);
                buffer.draw(line);
                break;
            }
            //else {
            //    std::cout << "aa\n";
            //}
        }
    }
    

    buffer.display();
    

    return sf::Sprite(buffer.getTexture());
}

Camera::Camera() {
    buffer.create(800, 600);
    //texture.loadFromFile("assets/texturesheet.png");
}

}