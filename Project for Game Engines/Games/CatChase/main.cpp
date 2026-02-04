#include <iostream>
#include "EngineApp.h"
#include "AnimationManager.h"
#include "TextManager.h"
#include "SceneManager.h"
#include "SoundManager.h"  
#include "CatChaseGame.h"
#include "StartScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

int main(int argc, char* argv[])
{
    
    EngineApp app(1920, 1080, "Cat Chase");

    if (!app.Init()) return -1;

   
    AnimationManager::GetInstance().CreateAnimation("cat_walk", "MediaCatChase/Sprites/CatWalk.png", 48, 48, 6, 0.1f, true);
    AnimationManager::GetInstance().CreateAnimation("cat_attack", "MediaCatChase/Sprites/CatAttack.png", 48, 48, 4, 0.1f, false);
    AnimationManager::GetInstance().CreateAnimation("cat_idle", "MediaCatChase/Sprites/CatIdle.png", 48, 48, 4, 0.15f, true);
    AnimationManager::GetInstance().CreateAnimation("mouse_walk", "MediaCatChase/Sprites/RatWalk.png", 32, 32, 4, 0.1f, true);
    AnimationManager::GetInstance().CreateAnimation("mouse_death", "MediaCatChase/Sprites/RatDeath.png", 32, 32, 4, 0.1f, false);
    AnimationManager::GetInstance().CreateAnimation("dog_walk", "MediaCatChase/Sprites/DogWalk.png", 48, 48, 6, 0.1f, true);
    AnimationManager::GetInstance().CreateAnimation("dog_idle", "MediaCatChase/Sprites/DogIdle.png", 48, 48, 4, 0.15f, true);

   
    TextManager::GetInstance().LoadFont("main_font", "MediaCatChase/Fonts/Roboto/static/Roboto-Regular.ttf", 32);

    
    SoundManager::GetInstance().Init();
    SoundManager::GetInstance().LoadMusic("game_music", "MediaCatChase/Sounds/BackgroundMusic.mp3");  
    SoundManager::GetInstance().LoadSound("bite_sound", "MediaCatChase/Sounds/CatSoundEffect.wav");
    SoundManager::GetInstance().SetMusicVolume(0.3f); 
    SoundManager::GetInstance().SetSFXVolume(0.5f);    

    static CatChaseGame sharedGame;

    SceneManager::GetInstance().AddScene("Start", new StartScene());
    SceneManager::GetInstance().AddScene("Game", new GameScene(WINDOW_WIDTH, WINDOW_HEIGHT, &sharedGame));
    SceneManager::GetInstance().AddScene("GameOver", new GameOverScene(WINDOW_WIDTH, WINDOW_HEIGHT, &sharedGame));

    SceneManager::GetInstance().ChangeScene("Start");
    SceneManager::GetInstance().Update();

    app.Run();
    app.Shutdown();
    return 0;
}