#include "StartScene.h"

#include "UIManager.h"
#include "Button.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "TextManager.h"
#include "InputManager.h"

StartScene::StartScene()
    : UISceneBase("Start")
{
}

void StartScene::OnEnter()
{
    
    GameManager::GetInstance().SetState(GameState::MENU);

    
    UIManager::GetInstance().RemoveAll();

  
    const int btnW = 260;
    const int btnH = 80;
    const int btnX = 1920 / 2 - btnW / 2;
    const int btnY = 1080 / 2 - btnH / 2;

    Button* playBtn = new Button("btn_play", btnX, btnY, btnW, btnH, "PLAY");

    
    playBtn->SetOnClick([]() {
        SceneManager::GetInstance().ChangeScene("Game");
        });

    UIManager::GetInstance().AddElement(playBtn);
}

void StartScene::OnExit()
{
   
    UIManager::GetInstance().RemoveAll();
}

void StartScene::Update()
{
    UIManager::GetInstance().Update();
}

void StartScene::Render(SDL_Renderer* renderer)
{
    
    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
    SDL_Rect bg{ 0,0,1920,1080 };
    SDL_RenderClear(renderer);

    SDL_Color white = { 255, 255, 255, 255 };
    std::string title = "CAT CHASE";
    int tw, th;
    TextManager::GetInstance().GetTextSize(title, "main_font", tw, th);
    TextManager::GetInstance().RenderText(title, "main_font", 960 - tw / 2, 300, white);
    
    UIManager::GetInstance().Render();
}

void StartScene::HandleInput()
{
   
    const auto& events = InputManager::GetInstance().GetFrameEvents();

    for (const auto& e : events)
    {
        
        SDL_Event copy = e;
        UIManager::GetInstance().HandleEvent(copy);
    }

   
    InputManager::GetInstance().ClearFrameEvents();
}
