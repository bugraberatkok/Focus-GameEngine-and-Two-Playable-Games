#include "BaseObject.h"
#include "ObjectManager.h"
#include "AnimationManager.h"
#include <SDL.h>

BaseObject::BaseObject()
    : posX(0.0f), posY(0.0f), rot(0.0f),
    texture(nullptr),
    texW(0), texH(0),
    scale(1.0f),
    animState(nullptr),
    flip(SDL_FLIP_NONE),
    manualHitbox(false),
    hitboxOffsetX(0),
    hitboxOffsetY(0),
    velocityX(0.0f),        
    velocityY(0.0f),        
    gravityAffected(false)  
{
    rect = { 0, 0, 0, 0 };
    renderRect = { 0, 0, 0, 0 };

    ObjectManager::GetInstance().AddObject(this);
}

BaseObject::~BaseObject()
{
    if (animState)
    {
        delete animState;
        animState = nullptr;
    }

    
}

void BaseObject::UpdateRenderRect()
{

    if (animState && animState->currentAnimation &&
        !animState->currentAnimation->frames.empty())
    {
        const SDL_Rect& frame = animState->currentAnimation->frames[0];
        renderRect.w = static_cast<int>(frame.w * scale);
        renderRect.h = static_cast<int>(frame.h * scale);
    }
    else if (texW > 0 && texH > 0)
    {
        renderRect.w = static_cast<int>(texW * scale);
        renderRect.h = static_cast<int>(texH * scale);
    }


    renderRect.x = static_cast<int>(posX);
    renderRect.y = static_cast<int>(posY);

    if (manualHitbox)
    {

        int ox = hitboxOffsetX;

        if (flip == SDL_FLIP_HORIZONTAL)
        {

            ox = (renderRect.w - rect.w - hitboxOffsetX);
        }

        rect.x = renderRect.x + ox;
        rect.y = renderRect.y + hitboxOffsetY;
    }
    else
    {
        rect.x = renderRect.x + (renderRect.w - rect.w) / 2;
        rect.y = renderRect.y + (renderRect.h - rect.h) / 2;
    }
}



void BaseObject::Render(SDL_Renderer* renderer)
{
    UpdateRenderRect();

    SDL_Rect finalRect = renderRect;


    if (animState && animState->currentAnimation)
    {
        AnimationManager::GetInstance().RenderAnimation(
            renderer,
            *animState,
            finalRect.x,
            finalRect.y,
            scale,
            flip
        );
    }
    else if (texture && finalRect.w > 0 && finalRect.h > 0)
    {
        SDL_RenderCopyEx(renderer, texture, nullptr, &finalRect, rot, nullptr, flip);
    }
}

void BaseObject::SetPosition(float x, float y)
{
    posX = x;
    posY = y;
    UpdateRenderRect(); 
}

void BaseObject::SetTexture(SDL_Texture* tex)
{
    texture = tex;

    if (texture)
    {
        if (SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH) != 0)
        {
            SDL_Log("SDL_QueryTexture error: %s", SDL_GetError());
            texW = texH = 0;
        }

   
        if (rect.w == 0 && rect.h == 0 && texW > 0 && texH > 0)
        {
            rect.w = texW;
            rect.h = texH;
        }
    }
    else
    {
        texW = texH = 0;
    }
}

void BaseObject::SetScale(float s)
{
    scale = s;

}

void BaseObject::SetAnimation(Animation* anim)
{
    if (!anim)
        return;


    if (!animState)
    {
        animState = new AnimationState();
    }

    animState->currentAnimation = anim;
    animState->currentFrame = 0;
    animState->frameTimer = 0.0f;
    animState->isPlaying = true;
    animState->isFinished = false;


    if (rect.w == 0 && rect.h == 0 && !anim->frames.empty())
    {
        const SDL_Rect& frame = anim->frames[0];
        rect.w = frame.w;
        rect.h = frame.h;
    }
}

void BaseObject::PlayAnimation(Animation* anim, bool restart)
{
    if (!anim)
        return;

    if (animState &&
        animState->currentAnimation == anim &&
        animState->isPlaying &&
        !restart)
    {
        return;
    }

    SetAnimation(anim);
}