#include "camera.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "CGL/misc.h"
#include "CGL/vector2D.h"
#include "CGL/vector3D.h"

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::ifstream;
using std::ofstream;

namespace CGL {

using Collada::CameraInfo;

Ray Camera::generate_ray_for_thin_lens(double x, double y, double rndR, double rndTheta) const {
    
    // TODO Project 3-2: Part 4
    // compute position and direction of ray from the input sensor sample coordinate.
    // Note: use rndR and rndTheta to uniformly sample a unit disk.
    double imgWidth = 2.0 * tan(0.5 * radians(hFov));
    double imgHeight = 2.0 * tan(0.5 * radians(vFov));
    double x0_camera = -tan(0.5 * radians(hFov));
    double y0_camera = -tan(0.5 * radians(vFov));
    Vector3D sensor = Vector3D(x0_camera + x * imgWidth, y0_camera + y * imgHeight, -1);
    //auto sensor = Vector3D((1 - x) * left.x + x * right.x, (1 - y) * left.y + y * right.y, -1);
    Vector3D lensSample = Vector3D(lensRadius * sqrt(rndR) * cos(2 * PI * rndTheta),
                         lensRadius * sqrt(rndR) * sin(2 * PI * rndTheta), 0);
    Vector3D focus = sensor * focalDistance - lensSample;
    Vector3D dir = c2w * focus;
    dir.normalize();
    Ray ray = Ray(c2w * lensSample + pos, dir, fClip, 0);
    ray.min_t = nClip;
    return ray;
}


} // namespace CGL
