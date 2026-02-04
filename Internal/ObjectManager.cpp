#include "ObjectManager.h"
#include "BaseObject.h"
#include <algorithm>

ObjectManager::~ObjectManager()
{
    
    for (BaseObject* obj : objects)
        delete obj;

    objects.clear();
    destroyQueue.clear();
}

void ObjectManager::SetRenderer(SDL_Renderer* r)
{
    renderer = r;
}

void ObjectManager::AddObject(BaseObject* newObject)
{
    if (!newObject) return;

    
    if (std::find(objects.begin(), objects.end(), newObject) != objects.end())
        return;

    objects.push_back(newObject);
}

void ObjectManager::RemoveObject(BaseObject* object)
{
    if (!object) return;

    auto it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end())
        objects.erase(it);
}

void ObjectManager::DestroyObject(BaseObject* object)
{
    
    RequestDestroy(object);
}

void ObjectManager::RequestDestroy(BaseObject* obj)
{
    if (!obj) return;

    
    if (std::find(destroyQueue.begin(), destroyQueue.end(), obj) != destroyQueue.end())
        return;

    destroyQueue.push_back(obj);
}

void ObjectManager::FlushDestroyQueue()
{
    if (destroyQueue.empty()) return;

   
    for (BaseObject* obj : destroyQueue)
        RemoveObject(obj);

    
    for (BaseObject* obj : destroyQueue)
        delete obj;

    destroyQueue.clear();
}

void ObjectManager::Update()
{
    
    for (BaseObject* obj : objects)
    {
        if (obj)
            obj->Update();
    }

    
    FlushDestroyQueue();
}


void ObjectManager::ClearAll() 
{
    for (BaseObject* obj : objects)
    {
        if (obj) delete obj;
    }
    objects.clear();
    destroyQueue.clear();
}

void ObjectManager::RenderAll()
{
    if (!renderer) return;

    for (BaseObject* obj : objects)
    {
        if (obj)
            obj->Render(renderer);
    }
}


