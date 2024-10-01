# Lumen
Building a ray tracer based on the book Ray Tracing in One Weekend Peter Shirley edited by Steve Hollasch and Trevor David Black.

![display pic](https://github.com/AveAng02/Lumen/blob/RTOW-1/output/output_beauty.png)



## Build

* mkdir build
* cd build
* cmake ../
* cmake --build .
* ./lumen

[View using this site](https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html)


image_height = image_width / aspectRatio;

            camera_center = lookFrom;

            // Camera
            // Camera position = (0,0,0)
            auto focal_length = (lookFrom - lookAt).length();
            auto theta = degreeToRadians(vfov);
            auto h = std::tan(theta/2);
            auto viewport_height = 2 * h * focal_length;
            auto viewport_width = viewport_height * (double(image_width)/image_height);

            // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
            w = (lookFrom - lookAt).normalize();
            u = vup.cross(w).normalize();
            v = w.cross(u);

            // Vectors on the view port edges
            vec3 horizontal = viewport_width * u; // view port u
            vec3 vertical = viewport_height * -v; // view port v

            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            deltaU = horizontal / image_width;
            deltaV = vertical / image_height;

            // Calculate the location of the upper left pixel.
            auto viewport_upper_left = camera_center - (focal_length * w) 
                                        - horizontal/2 - vertical/2;
            pXRef = viewport_upper_left + 0.5 * (deltaU + deltaV);