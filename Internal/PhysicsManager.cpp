#include "PhysicsManager.h"
#include "BaseObject.h"
#include "ObjectManager.h"
#include <iostream>

PhysicsManager::PhysicsManager()
    : gravity(980.0f),        
    gravityEnabled(true)
{
}

bool PhysicsManager::CheckCollision(const SDL_Rect& a, const SDL_Rect& b)
{
    return (a.x < b.x + b.w &&
        a.x + a.w > b.x &&
        a.y < b.y + b.h &&
        a.y + a.h > b.y);
}

void PhysicsManager::DetectAllCollisions()
{
    const auto& objs = ObjectManager::GetInstance().GetObjects();

    for (size_t i = 0; i < objs.size(); i++)
    {
        for (size_t j = i + 1; j < objs.size(); j++)
        {
            if (!objs[i] || !objs[j]) continue;

            if (CheckCollision(objs[i]->GetRect(), objs[j]->GetRect()))
            {
                std::cout << "Collision detected between objects "
                    << i << " and " << j << std::endl;
            }
        }
    }
}