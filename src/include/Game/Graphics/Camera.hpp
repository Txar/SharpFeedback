#ifndef CAMERA_H
#define CAMERA_H

#include "SFML/Graphics.hpp"
#include "Face.hpp"

namespace ShF {

class Camera {
    public:
        float x, y;
        float rotation;
        sf::RenderTexture buffer;
        sf::Texture texture;

        Camera();
        sf::Sprite render(std::vector<Face> &faces);
};

}

#endif //CAMERA_H