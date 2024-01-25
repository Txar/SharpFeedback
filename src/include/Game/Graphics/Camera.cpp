#include "Camera.hpp"
#include "Game/Math/Math.hpp"
#include <iostream>
#include <algorithm>

namespace ShF {


struct DrawFace {
    double distance;
    Point2Dd point;
    Face *face;

    DrawFace(Point2Dd &point, double distance, Face *face) : distance(distance), face(face) {
        this->point.x = point.x;
        this->point.y = point.y;
    };
    DrawFace() {};
};

sf::Sprite Camera::render(std::vector<Face> &faces, double FOV) {
    Line2Dd initialRay(x, y, 0, 5000);
    Line2Dd ray;
    Point2Dd center(x, y);
    Line2Dd pathTo;
    Point2Dd p(false);

    initialRay.rotate(ShF::Math::degreesToRadians(rotation) - (FOV / 2.0));
    buffer.clear(sf::Color::Black);

    int lineHeight;

    sf::VertexArray line(sf::LineStrip, 2);
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;

    int screenWidth = 1200;
    int screenHeight = 720;

    double cameraPlaneDistance = (screenWidth/2)*tan((Math::PI/2.0) - FOV/2);
    
    double angleStep = (double)FOV/screenWidth;
    for (int angle = 0; angle < screenWidth; angle++) {
        double actualAngle = atan((angle - (screenWidth / 2))/cameraPlaneDistance);
        ray = initialRay.getRotated(actualAngle);
        std::vector<DrawFace> facesDistances;
        for (int i = 0; i < (int)faces.size(); i++) {
            p = ray.intersect(faces.at(i).line);
            if (p.exists) {
                pathTo = Line2Dd(ray.A(), p, true);
                facesDistances.push_back(DrawFace(p, pathTo.length()*Math::fastCos(actualAngle), &faces.at(i)));
            }
        }
        bool done;
        do {
            done = true;
            for (int i = 1; i < (int)facesDistances.size(); i++) {
                if (facesDistances[i-1].distance < facesDistances[i].distance) {
                    done = false;
                    std::iter_swap(facesDistances.begin() + i, facesDistances.begin() + i - 1);
                }
            }
        } while (!done);

        for (int ind = 0; ind < (int)facesDistances.size(); ind++) {
            DrawFace &i = facesDistances[ind];
            lineHeight = (i.face->texture->height/i.distance)*cameraPlaneDistance;
            if (lineHeight <= 0) continue;
            line[0].position = {(double) angle, (double)(screenHeight - lineHeight) / 2};
            line[1].position = {(double) angle, (double)line[0].position.y + lineHeight};
            if (line[0].position.y > line[1].position.y) continue;
            
            if (i.face->noTexture) {
                line[0].color = i.face->color;
                line[1].color = i.face->color;
                buffer.draw(line);
            } else {
                sf::Sprite s(texture);
                s.setPosition(line[0].position);
                Line2Dd textureDistance(i.face->line.A(), p.sub(i.face->line.A()));
                double height = line[1].position.y - line[0].position.y;
                double ratio = (double)lineHeight/i.face->texture->height;
                s.setTextureRect(
                    sf::IntRect(
                        i.face->texture->positionFromFraction(textureDistance.length() / i.face->texture->width),
                        i.face->texture->y,
                        1,
                        i.face->texture->height
                        )
                    );
                s.setScale(1.0, ratio);
                buffer.draw(s);
            }
        }
    }

    buffer.display();
    return sf::Sprite(buffer.getTexture());
}

Camera::Camera() {
    buffer.create(1200, 720);
    texture.loadFromFile("assets/texturesheet.png");
}

}