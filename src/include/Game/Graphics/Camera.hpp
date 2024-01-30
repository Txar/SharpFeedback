#ifndef CAMERA_H
#define CAMERA_H

#include "SFML/Graphics.hpp"
#include "Face.hpp"

namespace ShF {

class Camera {
    public:
        double x, y;
        double yaw;
        sf::RenderTexture buffer;
        sf::Texture texture;
        double z, pitch;

        Camera();
        sf::Sprite render(std::vector<Face> &faces, double FOV);
        sf::Sprite floors(std::vector<Face> &faces, double FOV);
};

}

#endif //CAMERA_H