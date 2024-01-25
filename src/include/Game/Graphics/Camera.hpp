#ifndef CAMERA_H
#define CAMERA_H

#include "SFML/Graphics.hpp"
#include "Face.hpp"

namespace ShF {

class Camera {
    public:
        double x, y;
        double rotation;
        sf::RenderTexture buffer;
        sf::Texture texture;

        Camera();
        sf::Sprite render(std::vector<Face> &faces, double FOV);
};

}

#endif //CAMERA_H