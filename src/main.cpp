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
    

    sf::RenderWindow window({1200, 720}, "TEST");
    ShF::Camera camera;
    camera.x = 10;
    camera.y = 20;

    ShF::TextureBoundingRect bricks;
    bricks.height = 64;
    bricks.width = 64;
    bricks.x = 0,
    bricks.y = 0;

    std::vector<ShF::Face> faces;
    ShF::Face f;
    f.texture = &bricks;
    
    f.line = ShF::Line2Df(0, 0, 500, 25);
    f.color = sf::Color::Green;
    f.noTexture = false;
    //f.noTexture = true;
    faces.push_back(f);
    /*
    f.line = ShF::Line2Df(0, 0, 10, 50);
    f.color = sf::Color::Red;
    faces.push_back(f);
    f.line = ShF::Line2Df(50, 20, 10, 50);
    faces.push_back(f);
    f.line = ShF::Line2Df(20, 20, 50, 0);
    */
    faces.push_back(f);


    f.line.x += 400;
    f.line.y += 300;

    //ShF::Line2Df l1(0, 0, 3, 3);
    //
    //ShF::Line2Df l2(3, 0, -3, 3);
    //ShF::Point2Df a = l1.intersect(l2);
    //std::cout << "AAAA" << l1.x << l1.y << "\n";

    /*

    ShF::Point2Df pointA(250, 250), pointB(250, 50);
    pointB.rotateAround(pointA, -ShF::Math::degreesToRadians(45));
    std::cout << pointB.x << " " << pointB.y << std::endl;

    */   
    

    ShF::Line2Df l(400, 300, 0, 50);
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

    //float FOV = (float) ShF::Math::PI / 4.0;

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            camera.rotation -= 1.5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            camera.rotation += 1.5;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            ShF::Point2Df p = ShF::Line2Df(camera.x, camera.y, 0, -1).getRotated(ShF::Math::degreesToRadians(camera.rotation)).B();
            camera.x += p.x;
            camera.y += p.y;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            ShF::Point2Df p = ShF::Line2Df(camera.x, camera.y, 0, 1).getRotated(ShF::Math::degreesToRadians(camera.rotation)).B();
            camera.x += p.x;
            camera.y += p.y;
            //camera.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            ShF::Point2Df p = ShF::Line2Df(camera.x, camera.y, 1, 0).getRotated(ShF::Math::degreesToRadians(camera.rotation)).B();
            camera.x -= p.x;
            camera.y -= p.y;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            ShF::Point2Df p = ShF::Line2Df(camera.x, camera.y, 1, 0).getRotated(ShF::Math::degreesToRadians(camera.rotation)).B();
            camera.x += p.x;
            camera.y += p.y;
        }
        //t = b.getRotated(a, ShF::Math::degreesToRadians(angle));

        window.clear({0, 0, 0});
        //b.rotateAround(a, ShF::Math::degreesToRadians(5));
        window.draw(camera.render(faces));

        /*
        l2 = l.getRotated(ShF::Math::degreesToRadians(camera.rotation) + (FOV / 2.0));
        l2.x = 400 + camera.x;
        l2.y = 300 + camera.y;
        line[0].position = {l2.x, l2.y};
        line[1].position = {l2.x + l2.x2, l2.y + l2.y2};

        if (l2.intersect(f.line).exists) {
            line2[0].color = sf::Color::Blue;
            line2[1].color = sf::Color::Blue;
        } else {
            line2[0].color = sf::Color::Green;
            line2[1].color = sf::Color::Green;
            //std::cout << f.line.x << " " << l2.x << std::endl;
        }

        window.draw(line);
        
        window.draw(line2);
        */
        
        window.display();
    }
    
    return 0;
}