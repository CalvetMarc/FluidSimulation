#pragma once
#include <glm/glm.hpp>
#include <utility>

class Plane
{
public:
    float a;
    float b;
    float c;
    float d;

    Plane();
    Plane(float _a, float _b, float _c, float _d);
    Plane(const glm::vec3& NormalizedNormal, float _d);
    bool Collision(glm::vec3 p1, glm::vec3 p2);
    glm::vec3 GetNormal();
    std::pair<glm::vec3, glm::vec3> Mirror(glm::vec3 p2, glm::vec3 v2);


};

