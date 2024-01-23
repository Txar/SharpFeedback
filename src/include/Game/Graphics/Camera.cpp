#include "Camera.hpp"
#include "Game/Math/Math.hpp"
#include <iostream>
#include <algorithm>

namespace ShF {


struct DrawFace {
    float distance;
    Point2Df point;
    Face *face;

    DrawFace(Point2Df &point, float distance, Face *face) : distance(distance), face(face) {
        this->point.x = point.x;
        this->point.y = point.y;
    };
    DrawFace() {};
};

sf::Sprite Camera::render(std::vector<Face> &faces) {
    Line2Df ray(x, y, 0, 500);
    Line2Df pathTo;
    Point2Df p(false);

    float FOV = Math::PI / 3.0;
    ray.rotate(ShF::Math::degreesToRadians(rotation) - (FOV / 2.0));
    //if (ray.intersect(faces[0].line).exists) buffer.clear(sf::Color::White);
    buffer.clear(sf::Color::Black);

    int lineHeight;

    sf::VertexArray line(sf::LineStrip, 2);
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;

    int screenWidth = 1200;
    int screenHeight = 720;
    
    float angleStep = (float)FOV/screenWidth;
    for (int angle = 0; angle < screenWidth; angle++) {
        ray.rotate(angleStep);

        std::vector<DrawFace> facesDistances;
        for (int i = 0; i < (int)faces.size(); i++) {
            p = ray.intersect(faces.at(i).line);
            if (p.exists) {
                pathTo = Line2Df(ray.A(), p, true);
                facesDistances.push_back(DrawFace(p, pathTo.length(), &faces.at(i)));
            }
        }
        bool done;
        do {
            done = true;
            for (int i = 1; i < (int)facesDistances.size(); i++) {
                if (facesDistances[i-1].distance < facesDistances[i].distance) {
                    done = false;
                    //std::cout << "Swapped!" << facesDistances[i-1].distance << " " << facesDistances[i].distance << "\n";
                    DrawFace a = facesDistances[i];
                    facesDistances[i] = facesDistances[i - 1];
                    facesDistances[i - 1] = a;
                    //std::iter_swap(facesDistances.begin() + i, facesDistances.begin() + i - 1);
                }
            }
        } while (!done);

        for (int ind = 0; ind < (int)facesDistances.size(); ind++) {
            DrawFace &i = facesDistances[ind];
            //float ratio1 = i.distance*Math::fastCos(angleStep*angle - (FOV / 2.0));
            float ratio1 = i.distance*Math::fastCos(angleStep*angle - (FOV / 2.0));
            lineHeight = (int)(screenHeight - ratio1);
            if (lineHeight <= 0) continue;
            line[0].position = {(float) angle, (float)(screenHeight - lineHeight) / 2};
            line[1].position = {(float) angle, (float)lineHeight};
            if (line[0].position.y > line[1].position.y) continue;
            
            if (i.face->noTexture) {
                line[0].color = i.face->color;
                line[1].color = i.face->color;
                buffer.draw(line);
            } else {
                sf::Sprite s(texture);
                s.setPosition(line[0].position);
                Line2Df textureDistance(i.face->line.A(), p.sub(i.face->line.A()));
                float height = line[1].position.y - line[0].position.y;
                float ratio = (float)height/i.face->texture->height;
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