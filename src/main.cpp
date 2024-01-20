#include <iostream>
#include "SFML/Graphics.hpp"
#include "Game/Math/Math.hpp"
#include "Game/Math/Point2Df.hpp"
#include "Game/Math/Line2Df.hpp"
#include "Game/Graphics/Camera.hpp"

int main(){
    //ShF::Math::initialize();

    //for (int i = -720; i < 720; i += 25) {
    //    printf("Deg: %i, sin(deg): %f, builtin: %f\n", i, ShF::Math::fastSin(ShF::Math::degreesToRadians(i)), sin(ShF::Math::degreesToRadians(i)));
    //}
    

    sf::RenderWindow window({800, 600}, "TEST");
    std::cout << window.isOpen();
    ShF::Camera camera;
    camera.x = 10;
    camera.y = 20;

    std::vector<ShF::Face> faces;
    ShF::Face f;
    f.line = ShF::Line2Df(0, 0, 50, 0);
    faces.push_back(f);
    //f.line = ShF::Line2Df(0, 0, 10, 50);
    //faces.push_back(f);

    /*

    ShF::Point2Df pointA(250, 250), pointB(250, 50);
    pointB.rotateAround(pointA, -ShF::Math::degreesToRadians(45));
    std::cout << pointB.x << " " << pointB.y << std::endl;

    */   
    ShF::Line2Df l(400, 300, 0, -50);
    ShF::Line2Df l2;

    sf::VertexArray line(sf::LineStrip, 2);
    line[0].position = {l.x, l.y};
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;

    sf::VertexArray line2(sf::LineStrip, 2);
    line2[0].position = {400 + faces[0].line.x, 300 + faces[0].line.y};
    line2[1].position = {400 + faces[0].line.x + faces[0].line.x2, 300 + faces[0].line.y + faces[0].line.y2};
    line2[0].color = sf::Color::Green;
    line2[1].color = sf::Color::Green;

    float FOV = (float) ShF::Math::PI / 4.0;

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            camera.rotation -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            camera.rotation += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            camera.y += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            camera.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            camera.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            camera.x -= 1;
        }
        //t = b.getRotated(a, ShF::Math::degreesToRadians(angle));

        window.clear({0, 0, 0});
        //b.rotateAround(a, ShF::Math::degreesToRadians(5));
        window.draw(camera.render(faces));

        /*
        for (int angle = 0; angle < 800; angle++) {
            l2 = l.getRotated(ShF::Math::degreesToRadians(camera.rotation) + FOV*(float)angle/800 - FOV/2.0);
            l2.x = 400 + camera.x;
            l2.y = 300 + camera.y;
            line[0].position = {l2.x, l2.y};
            line[1].position = {l2.x + l2.x2, l2.y + l2.y2};
            window.draw(line);
        }
        */

        
        l2 = l.getRotated(ShF::Math::degreesToRadians(camera.rotation) + (FOV / 2.0));
        l2.x = 400 + camera.x;
        l2.y = 300 + camera.y;
        line[0].position = {l2.x, l2.y};
        line[1].position = {l2.x + l2.x2, l2.y + l2.y2};
        window.draw(line);
        
        window.draw(line2);
        
        window.display();
    }
    
    return 0;
}