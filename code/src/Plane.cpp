#include "Plane.h"
Plane::Plane()
{
    a = 0;
    b = 0;
    c = 0;
    d = 0;
}

Plane::Plane(float _a, float _b, float _c, float _d)
{
    a = _a;
    b = _b;
    c = _c;
    d = _d;
}
Plane::Plane(const glm::vec3& NormalizedNormal, float _d)
{
    a = NormalizedNormal.x;
    b = NormalizedNormal.y;
    c = NormalizedNormal.z;
    d = _d;
}
float  DotProduct(glm::vec3 p1, glm::vec3 p2)
{
    return (p1.x * p2.x + p1.y * p2.y + p1.z * p2.z);
}
bool Plane::Collision(glm::vec3 p1, glm::vec3 p2)
{
    return (((DotProduct(GetNormal(),p1) + d) * (DotProduct(GetNormal(), p2) + d)) <= 0);
}
std::pair<glm::vec3, glm::vec3> Plane::Mirror(glm::vec3 p2, glm::vec3 v2)
{
    float epsilon = 0.6f;

    glm::vec3 pCalculations = ((DotProduct(GetNormal(), p2) + d) * GetNormal());
    pCalculations *= (1 + epsilon);
    p2 = p2 - pCalculations;

    glm::vec3 vCalculations = (DotProduct(GetNormal(), v2) * GetNormal());
    vCalculations *= (1 + epsilon);
    v2 = v2  - vCalculations;
    return std::pair<glm::vec3, glm::vec3> (p2, v2);
  
}
glm::vec3 Plane::GetNormal()
{
    return glm::vec3(a, b, c);
}

