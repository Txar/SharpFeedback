#include "Camera.hpp"
#include "Game/Math/Math.hpp"
#include <iostream>
#include <algorithm>

namespace ShF {


struct DrawFace {
    Face *face;
    double distance;
    Point2Dd point;
    Point2Dd slopeAndOrigin;

    DrawFace(Point2Dd &point, double distance, Face *face, Point2Dd slopeAndOrigin) : distance(distance), face(face), slopeAndOrigin(slopeAndOrigin) {
        this->point.x = point.x;
        this->point.y = point.y;
    };
    DrawFace() {};
};

sf::Sprite Camera::floors(std::vector<Face> &faces, double FOV) {
    int x, y;
    int screenWidth = 1200;
    int screenHeight = 720;

    int xOffset = screenWidth/2;
    int yOffset = screenHeight/2;

    int playerHeight = 32;

    buffer.clear(sf::Color::Black);

    sf::VertexArray point(sf::Points, 1);

    float moveUpDown = (playerHeight + z)/16.0;

    int ys = yOffset, ye = pitch;
    if (moveUpDown < 0) {
        ys = pitch;
        ye = -(yOffset + pitch);
    }

    float sine_ = sin(Math::degreesToRadians(yaw));
    float cosine_ = cos(Math::degreesToRadians(yaw));

    if (moveUpDown == 0) moveUpDown = 0.001;

    for (y = ys; y > ye; y-=2) {
        for (x = xOffset; x > -xOffset; x-=2) {
            float localZ = (float)y - pitch;
            float fx = x / localZ * moveUpDown;
            float fy = ((float)screenHeight/2)/localZ * moveUpDown;

            float rx = fx*sine_-fy*cosine_;
            float ry = fx*cosine_+fy*sine_;

            rx -= this->y/30;
            ry -= this->x/30;

            if (rx < 0) { rx = -rx + 1; }
            if (ry < 0) { ry = -ry + 1; }

            //if (rx <= 0 || ry <= 0 || rx >= 5 || ry >= 5) continue;

            if ((int)rx % 2 == (int) ry % 2) point[0].color = sf::Color::Red;
            else point[0].color = sf::Color::Green;
            point[0].position = {x+xOffset, y+yOffset};
            buffer.draw(point);
        }
    }

    buffer.display();
    return sf::Sprite(buffer.getTexture());
}

sf::Sprite Camera::render(std::vector<Face> &faces, double FOV) {
    Line2Dd initialRay(x, y, 0, 5000);
    Line2Dd ray;
    Point2Dd center(x, y);
    Line2Dd pathTo;
    Point2Dd p(false);

    initialRay.rotate(ShF::Math::degreesToRadians(yaw));
    buffer.clear(sf::Color::Black);

    int lineHeight;

    TextureBoundingRect floorTexture(64, 0, 64, 64);

    sf::VertexArray line(sf::LineStrip, 2);
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;

    int screenWidth = buffer.getSize().x;
    int screenHeight = buffer.getSize().y;

    double cameraPlaneDistance = (screenWidth/2)*tan((Math::PI/2.0) - FOV/2);

    double sine_ = sin(Math::DEG_TO_RAD * yaw);
    double cosine_ = cos(Math::DEG_TO_RAD * yaw);

    sf::Image floorImage;
    floorImage.create(screenWidth, screenHeight);
    
    for (int angle = 0; angle < screenWidth; angle++) {
        double actualAngle = atan((angle - (screenWidth / 2))/cameraPlaneDistance);
        ray = initialRay.getRotated(actualAngle);
        std::vector<DrawFace> facesDistances;
        for (int i = 0; i < (int)faces.size(); i++) {
            p = ray.intersect(faces.at(i).line);
            if (p.exists) {
                pathTo = Line2Dd(ray.A(), p, true);
                facesDistances.push_back(DrawFace(p, pathTo.length()*cos(actualAngle), &faces.at(i), Math::slopeAndOrigin(ray.A(), p)));
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
            double ratio = cameraPlaneDistance/i.distance;

            lineHeight = ratio*i.face->height;
            if (lineHeight <= 0) continue;
            line[0].position = {(float) angle, (float)(screenHeight/2 - ratio*(i.face->z - z) + pitch - lineHeight)};
            line[1].position = {(float) angle, (float)line[0].position.y + lineHeight};

            if (ind == 0 && angle % 2 == 0) {
                int x2, y;

                int xOffset = screenWidth/2;
                int yOffset = line[1].position.y;

                x2 = angle - xOffset;

                int playerHeight = 32;

                sf::VertexArray point(sf::Points, 1);

                float moveUpDown = (playerHeight + z)/16.0;

                int ys = yOffset - pitch, ye = pitch;
                if (moveUpDown < 0) {
                    ys = pitch;
                    ye = -(yOffset + pitch);
                }

                if (moveUpDown == 0) moveUpDown = 0.001;

                for (y = ys; y > ye; y-=2) {
                    if (x2+xOffset < 0 || x2+xOffset >= screenWidth || y+yOffset-pitch < 0 || y+yOffset-pitch >= screenHeight) continue;

                    float localZ = (float)y - pitch;
                    float fx = x2 / localZ * moveUpDown;
                    float fy = ((float)screenHeight/2)/localZ * moveUpDown;

                    float rx = fx*sine_-fy*cosine_;
                    float ry = fx*cosine_+fy*sine_;

                    //float rx = fx;
                    //float ry = fy;

                    rx -= this->y/30;
                    ry -= this->x/30;

                    if (rx < 0) { rx = -rx + 1; }
                    if (ry < 0) { ry = -ry + 1; }

                    //if (rx <= 0 || ry <= 0 || rx >= 5 || ry >= 5) continue;
                    if ((int)rx % 2 == (int) ry % 2) floorImage.setPixel(x2+xOffset, y+yOffset-pitch, sf::Color::Red);
                    else floorImage.setPixel(x2+xOffset, y+yOffset-pitch, sf::Color::Green);
                }
            }

            if (line[0].position.y > line[1].position.y) continue;
                
            if (i.face->noTexture) {
                    line[0].color = i.face->color;
                    line[1].color = i.face->color;
                    buffer.draw(line);
            } else {
                    sf::Sprite s(texture);
                    s.setPosition(line[0].position);
                    Line2Dd textureDistance(i.face->line.A(), i.point.sub(i.face->line.A()));
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
    sf::Texture temp;
    temp.loadFromImage(floorImage);
    sf::Sprite s(temp);
    buffer.draw(s);
    buffer.display();
    s.setTexture(buffer.getTexture());
    s.setScale(1, 1);
    return s;
}

Camera::Camera() {
    buffer.create(1200, 720);
    texture.loadFromFile("assets/texturesheet.png");
}

}