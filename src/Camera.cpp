#pragma once
#include "Camera.h"

namespace lumen
{
    void Camera::initialize()
    {
        image_height = image_width / aspectRatio;

        camera_center = lookFrom;

        // Camera
        // Camera position = (0,0,0)
        auto focal_length = (lookFrom - lookAt).length();
        auto vpW = 2.0;  // view port height
        auto vpH = vpW / aspectRatio; // view port width

        // Vectors on the view port edges
        auto horizontal = lumen::vec3(vpW, 0, 0); // view port u
        auto vertical = lumen::vec3(0, -vpH, 0);  // view port v

        // Pitch between pixels in horizontal and vertical directions
        deltaV = horizontal / image_width;
        deltaU = vertical / image_height;

            // Location of upper left corner of the view port
        auto vpRef = camera_center - lumen::vec3(0, 0, focal_length) 
                                - horizontal/2 - vertical/2;
        pXRef = vpRef + 0.5 * (deltaU + deltaV); // Location of upper left pixel
    }
}
