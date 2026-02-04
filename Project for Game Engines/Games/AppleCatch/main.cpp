#include <iostream>
#include "EngineApp.h"
#include "AnimationManager.h"
#include "TextManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "SpriteManager.h"
#include "AppleCollectorGame.h"
#include "AppleStartScene.h"
#include "AppleGameScene.h"
#include "AppleGameOverScene.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

int main(int argc, char* argv[])
{
    EngineApp app(WINDOW_WIDTH, WINDOW_HEIGHT, "Apple Collector");

    if (!app.Init())
        return -1;

    
    AnimationManager::GetInstance().CreateAnimation("red_left", "MediaAppleCatch/Sprites/Players/RedLeft.png", 64, 32, 4, 0.15f, true);
    AnimationManager::GetInstance().CreateAnimation("red_right", "MediaAppleCatch/Sprites/Players/RedRight.png", 64, 32, 4, 0.15f, true);

    AnimationManager::GetInstance().CreateAnimation("green_left", "MediaAppleCatch/Sprites/Players/GreenLeft.png", 64, 32, 4, 0.15f, true);
    AnimationManager::GetInstance().CreateAnimation("green_right", "MediaAppleCatch/Sprites/Players/GreenRight.png", 64, 32, 4, 0.15f, true);

    AnimationManager::GetInstance().CreateAnimation("yellow_left", "MediaAppleCatch/Sprites/Players/YellowLeft.png", 64, 32, 4, 0.15f, true);
    AnimationManager::GetInstance().CreateAnimation("yellow_right", "MediaAppleCatch/Sprites/Players/YellowRight.png", 64, 32, 4, 0.15f, true);

    AnimationManager::GetInstance().CreateAnimation("purple_left", "MediaAppleCatch/Sprites/Players/PurpleLeft.png", 64, 32, 4, 0.15f, true);
    AnimationManager::GetInstance().CreateAnimation("purple_right", "MediaAppleCatch/Sprites/Players/PurpleRight.png", 64, 32, 4, 0.15f, true);

    
    SpriteManager::GetInstance().LoadTexture("apple_red", "MediaAppleCatch/Sprites/Apples/RedApple.png");
    SpriteManager::GetInstance().LoadTexture("apple_green", "MediaAppleCatch/Sprites/Apples/GreenApple.png");
    SpriteManager::GetInstance().LoadTexture("apple_yellow", "MediaAppleCatch/Sprites/Apples/YellowApple.png");
    SpriteManager::GetInstance().LoadTexture("apple_blue", "MediaAppleCatch/Sprites/Apples/PurpleApple.png");

    
    TextManager::GetInstance().LoadFont("main_font", "MediaAppleCatch/Fonts/Roboto/static/Roboto-Regular.ttf", 32);

    
    SoundManager::GetInstance().Init();
    SoundManager::GetInstance().LoadMusic("game_music", "MediaAppleCatch/Audio/bgMusic.mp3");
    SoundManager::GetInstance().SetMusicVolume(0.3f);

   
    static AppleCollectorGame appleGame;

    
    SceneManager::GetInstance().AddScene("AppleStart", new AppleStartScene());
    SceneManager::GetInstance().AddScene("AppleGame", new AppleGameScene(WINDOW_WIDTH, WINDOW_HEIGHT, &appleGame));
    SceneManager::GetInstance().AddScene("GameOver", new AppleGameOverScene(WINDOW_WIDTH, WINDOW_HEIGHT, &appleGame));

    SceneManager::GetInstance().ChangeScene("AppleStart");
    SceneManager::GetInstance().Update();

    app.Run();
    app.Shutdown();

    return 0;
}