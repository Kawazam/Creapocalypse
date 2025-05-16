#include "Maths.h"

sf::Vector2f Maths::Normalize(sf::Vector2f vector)
{
    sf::Vector2f normalizedVector;
    const float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (magnitude != 0)
    {
        normalizedVector = vector / magnitude;
    }
    else
    {
        normalizedVector = { 0.0f,0.0f };
    }
    return normalizedVector;
}
