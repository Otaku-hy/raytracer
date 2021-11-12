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

Ray Interaction::SpawnRay(const Interaction &p2)
{
    return Ray(this->pos + this->norm * EPISILON, (p2.pos - this->pos).normalized(), distance(this->pos, p2.pos) - 2 * EPISILON);
}

Ray Interaction::SpawnRay(const Vector3f &direction)
{
    Vector3f dir = direction;
    return Ray(this->pos + this->norm * EPISILON, dir.normalized());
}