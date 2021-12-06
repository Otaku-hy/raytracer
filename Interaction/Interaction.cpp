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
than the surface, that is the direction is out the surface, or a little bit lower than the 
surface, that is the direction is in the surface
*/

Ray Interaction::SpawnRay(const Interaction &p2)
{
    Vector3f direction = (p2.pos - this->pos).normalized();
    bool out = SameHemisphere(direction, norm);
    float originOffset = out ? EPISILON : -EPISILON;
    return Ray(this->pos + this->norm * originOffset, direction, distance(this->pos, p2.pos) - 2 * EPISILON);
}

Ray Interaction::SpawnRay(const Vector3f &direction)
{
    Vector3f dir = direction.normalized();
    bool out = SameHemisphere(dir, norm);
    float originOffset = out ? EPISILON : -EPISILON;
    return Ray(this->pos + this->norm * originOffset, dir);
}