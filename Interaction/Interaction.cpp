#include "Interaction.hpp"

Interaction::~Interaction()
{
}

bool Interaction::IsSurfaceInteraction()
{
    if (norm.isZero())
    {
        return false;
    }
    return true;
}

/* note that when spawn ray, it's important that the offset value set either a little bit upper 
than the surface, that is the direction is outside the surface, or a little bit lower than the 
surface, that is the direction is inside the surface
*/

Ray Interaction::SpawnRay(const Interaction &p2) const 
{
    Vector3f direction = (p2.pos - this->pos).normalized();
    bool out = SameHemisphere(direction, norm);
    float originOffset = out ? EPISILON : -EPISILON;
    return Ray(pos + norm * originOffset, direction, distance(pos, p2.pos) - 2 * EPISILON);
}

Ray Interaction::SpawnRay(const Vector3f &direction) const
{
    Vector3f dir = direction.normalized();
    bool out = SameHemisphere(dir, norm);
    float originOffset = out ? EPISILON : -EPISILON;
    return Ray(pos + norm * originOffset, dir);
}