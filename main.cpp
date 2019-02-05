#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_ttf.h>
#include<algorithm>
#include<vector>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<climits>
#include<cfloat>
#include <fstream>

using namespace std;

//Constants
const int FPS = 60;
const int FRAME_DELAY = 1000/FPS;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
enum GAMESTATES{MAINMENU,SETTINGSMENU,TUTORIAL,CLASSSELECT,PLAYSTATE,PAUSEMENU,GAMEOVER,WONGAME};
enum PLAYERCLASSES{KNIGHT,MAGE};
enum LEVELS{CRYPT,MEDIEVAL};

//Global Variables
unsigned int currentGameState = TUTORIAL;
unsigned int lastPlayState;
unsigned int currentPlayerClass;
unsigned int currentLevel;
unsigned int enemyCount = 5;
bool fullScreen = false;
bool lastFullScreen = fullScreen;
SDL_Rect backgroundRect;

//Global Images
SDL_Surface* backBuffer = NULL;
SDL_Surface* healthBarImage = NULL;
SDL_Surface* buttonImage = NULL;
SDL_Surface* knightImage = NULL;
SDL_Surface* mageImage = NULL;
SDL_Surface* skeletonImage = NULL;
SDL_Surface* zombieImage = NULL;
SDL_Surface* archerImage = NULL;
SDL_Surface* necromancerImage = NULL;
SDL_Surface* swordsmanImage = NULL;
SDL_Surface* tutorialImage = NULL;
SDL_Surface* menuImage = NULL;
SDL_Surface* playImage = NULL;

//Global Fonts
TTF_Font* bungee100 = NULL;
TTF_Font* bungee25 = NULL;

//Global Sounds
Mix_Music* menuMusic = NULL;
Mix_Music* playMusic = NULL;
Mix_Music* gameOverMusic = NULL;
Mix_Chunk* swing = NULL;

//Class Prototypes
class Button;

//Functions
bool InitGame();
bool InitSDL();
bool ProgramIsRunning();
void SetScreen();
SDL_Surface* LoadImage(char*);
bool LoadFiles();
void FreeGame();
bool CheckCollide(const SDL_Rect&,const SDL_Rect&);
void DrawImageFrame(SDL_Surface*,SDL_Surface*,int,int,int,int,int);
void DrawRect(SDL_Surface*,SDL_Rect,int,int,int);
void DrawFillRect(SDL_Surface*,int,int,int,int,int,int,int);
void DrawOutlineText(SDL_Surface*,char*,int,int,TTF_Font*,Uint8,Uint8,Uint8);
void ToggleFullScreenViaKey();
bool CheckWords(char[100],char[100]);
bool SameWords(char[100],char[100]);
void RunProgram();
void DrawScreen();
void ProcessKeyboardInput();
void DrawKeyboardInput();
void RunMainMenu();
void DrawMainMenu();
void RunSettingsMenu();
void DrawSettingsMenu();
void RunTutorial();
void DrawTutorial();
void RunClassSelectMenu();
void DrawClassSelectMenu();
void RunPlayState();
void DrawPlayState();
void InitPlayer();
void InitPlayState();
void CheckLastEnemyDead();
void CheckEnemiesAllDead();
void DeleteAllEnemies();
void LoadLevel();
void RunPauseState();
void DrawPauseState();
void RunGameOverState();
void DrawGameOverState();
void RunWonGameState();
void DrawWonGameState();

class Timer
{
    private:
        int fps;
        int ticks;
    public:
        Timer(int);
        int GetTicks();
        void SetTicks(int);
        void UpdateTimer();
        void ResetTimer();
        float GetSeconds();
};

Timer::Timer(int _fps)
{
    fps = _fps;
}

int Timer::GetTicks()
{
    return ticks;
}

void Timer::SetTicks(int _ticks)
{
    ticks = _ticks;
}

void Timer::UpdateTimer()
{
    if(ticks<INT_MAX)
        ticks++;
}

void Timer::ResetTimer()
{
    ticks = 0;
}

float Timer::GetSeconds()
{
    return (float)ticks/fps;
}

class WordProcessor
{
    private:
        Uint8 lastKeyCode = SDLK_0;
        char word[100] = "";
        const int DELAY = 15;
        unsigned int ticks = DELAY;
        bool activeKey = false;
    public:
        void ProcessKeys();
        Uint8 GetLastKeyCode();
        bool GetLastKeyState();
        char* GetWord();
        void SetWord(string);
        void ClearWord();
        void Draw();
        void Draw(int,int);
};

void WordProcessor::ProcessKeys()
{
    activeKey = false;

    Uint8* keys = SDL_GetKeyState(NULL);

    if(keys[lastKeyCode] == 0)
        ticks = DELAY;

    if(ticks >= DELAY)
    {
        if(keys[SDLK_a])
        {
            strcat(word,"a");
            lastKeyCode = SDLK_a;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_b])
        {
            strcat(word,"b");
            lastKeyCode = SDLK_b;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_c])
        {
            strcat(word,"c");
            lastKeyCode = SDLK_c;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_d])
        {
            strcat(word,"d");
            lastKeyCode = SDLK_d;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_e])
        {
            strcat(word,"e");
            lastKeyCode = SDLK_e;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_f])
        {
            strcat(word,"f");
            lastKeyCode = SDLK_f;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_g])
        {
            strcat(word,"g");
            lastKeyCode = SDLK_g;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_h])
        {
            strcat(word,"h");
            lastKeyCode = SDLK_h;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_i])
        {
            strcat(word,"i");
            lastKeyCode = SDLK_i;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_j])
        {
            strcat(word,"j");
            lastKeyCode = SDLK_j;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_k])
        {
            strcat(word,"k");
            lastKeyCode = SDLK_k;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_l])
        {
            strcat(word,"l");
            lastKeyCode = SDLK_l;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_m])
        {
            strcat(word,"m");
            lastKeyCode = SDLK_m;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_n])
        {
            strcat(word,"n");
            lastKeyCode = SDLK_n;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_o])
        {
            strcat(word,"o");
            lastKeyCode = SDLK_o;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_p])
        {
            strcat(word,"p");
            lastKeyCode = SDLK_p;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_q])
        {
            strcat(word,"q");
            lastKeyCode = SDLK_q;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_r])
        {
            strcat(word,"r");
            lastKeyCode = SDLK_r;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_s])
        {
            strcat(word,"s");
            lastKeyCode = SDLK_s;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_t])
        {
            strcat(word,"t");
            lastKeyCode = SDLK_t;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_u])
        {
            strcat(word,"u");
            lastKeyCode = SDLK_u;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_v])
        {
            strcat(word,"v");
            lastKeyCode = SDLK_v;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_w])
        {
            strcat(word,"w");
            lastKeyCode = SDLK_w;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_x])
        {
            strcat(word,"x");
            lastKeyCode = SDLK_x;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_y])
        {
            strcat(word,"y");
            lastKeyCode = SDLK_y;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_z])
        {
            strcat(word,"z");
            lastKeyCode = SDLK_z;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_BACKSPACE])
        {
            for(int i=strlen(word);i>-1;i--)
            {
                if(word[i]!='\0')
                {
                    word[i] = '\0';
                    break;
                }
            }

            lastKeyCode = SDLK_BACKSPACE;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_SPACE])
        {
            strcat(word," ");
            lastKeyCode = SDLK_SPACE;
            ticks = 0;
            activeKey = true;
        }
        if(keys[SDLK_ESCAPE])
        {
            lastKeyCode = SDLK_ESCAPE;
            ticks = 0;
            activeKey = true;
        }
    }

    if(ticks < INT_MAX)
        ticks++;
}

Uint8 WordProcessor::GetLastKeyCode()
{
    return lastKeyCode;
}

bool WordProcessor::GetLastKeyState()
{
    return activeKey;
}

char* WordProcessor::GetWord()
{
    return word;
}

void WordProcessor::SetWord(string newWord)
{
    strcpy(word,newWord.c_str());
}

void WordProcessor::ClearWord()
{
    memset(word,'\0',strlen(word));
}

void WordProcessor::Draw()
{
    DrawOutlineText(backBuffer,word,0,SCREEN_HEIGHT/2,bungee25,0,255,0);
}

void WordProcessor::Draw(int x,int y)
{
    DrawOutlineText(backBuffer,word,0+x,0+y,bungee25,0,255,0);
}

class Button
{
    private:
        SDL_Rect rect;
        SDL_Rect mouse;
        SDL_Rect imageRect;
        int delay = 0;
        bool pressed = false;
        bool lastPressed = pressed;
        int color[3];
        char id[64];
    public:
        Button(int,int,int,int,int,string);
        char* GetID();
        void UpdateMouse();
        void UpdatePressed();
        bool CheckToggle();
        void Draw();
};

Button::Button(int x,int y,int r,int g,int b,string setID)
{
    rect.x = x;
    rect.y = y;
    rect.w = setID.size()*20-(1*setID.size());
    rect.h = 50;
    color[0] = r;
    color[1] = g;
    color[2] = b;
    strcpy(id,setID.c_str());

    imageRect.x = rect.x;
    imageRect.y = rect.y;
}

char* Button::GetID()
{
    return id;
}

void Button::UpdateMouse()
{
    int mouseX,mouseY;

    SDL_GetMouseState(&mouseX,&mouseY);

    mouse.x=mouseX;
    mouse.y=mouseY;
    mouse.h=1;
    mouse.w=1;
}

void Button::UpdatePressed()
{
    lastPressed = pressed;
    pressed = false;

    int mouseX,mouseY;

    SDL_GetMouseState(&mouseX,&mouseY);

    SDL_Rect mouse;
    mouse.x=mouseX;
    mouse.y=mouseY;
    mouse.h=1;
    mouse.w=1;

    if(CheckCollide(mouse,rect) && (SDL_GetMouseState(NULL,NULL)& SDL_BUTTON(1)))
        pressed = true;
}

bool Button::CheckToggle()
{
    if(lastPressed && (pressed == false) && CheckCollide(mouse,rect))
        return true;
    else
        return false;
}

void Button::Draw()
{
    if(pressed)
        DrawFillRect(backBuffer,rect.x,rect.y,rect.w,rect.h,255,255,255);
    else
        DrawFillRect(backBuffer,rect.x,rect.y,rect.w,rect.h,0,0,0);
    DrawRect(backBuffer,rect,200,200,200);
    DrawOutlineText(backBuffer,id,rect.x+5,rect.y+15,bungee25,255,0,255);
}

class Player
{
    protected:
        Button* attackButton = new Button(100,400,0,255,255,"attack");
        Timer* timer = new Timer(FPS);
        Timer* frameTimer = new Timer(FPS);
        SDL_Surface* image = NULL;
        SDL_Surface* keyboardImage = NULL;
        vector<string> words;
        string classID;
        char word[100];
        bool typing = false;
        bool defending = false;
        bool defendingFailed = false;
        bool attack = false;
        bool turnCompleted = false;
        bool firstWordCompleted = false;
        bool useAttackImage = false;
        static const int MAX_HEALTH = 10;
        static const int BASE_DAMAGE = 1;
        int health;
        int damage;
        int damageMod = 0;
        int damageResist = 0;
        int score;
        int time = 3;
        float wpm = 0.0;
        enum MENUSTATE{MAIN,ABILITY,PLAYERTYPING};
        unsigned int currentMenuState = MAIN;
        SDL_Rect rect;
        SDL_Rect imageRect;
        SDL_Rect healthRect;
        SDL_Rect timerRect;
        SDL_Rect keyboardRect;
        SDL_Rect healthImageRect;
    public:
        Player();
        virtual ~Player();
        void SetImage(SDL_Surface*,string);
        SDL_Surface* GetImage(string);
        Uint8 GetLastKeyCode();
        bool GetTurnCompleted();
        void ResetTurnCompleted();
        bool GetDefending();
        void IsDefending();
        void NotDefending();
        bool GetDefendingFailed();
        bool GetAttack();
        void NotAttack();
        int GetDamage();
        int GetHealth();
        void SetMenuStateMain();
        void SetMenuStateTyping();
        void SetMenuStateDefending();
        void TakeDamage(int);
        void SetWPM(bool);
        void Attack(WordProcessor&);
        void Defend(WordProcessor&);
        void PushBackWord(string);
        void ClearWords();
        void ResetVariables();
        void ClearStanceEffects();
        void UpdateStates(WordProcessor&);
        virtual void UpdateAbility(WordProcessor&){};
        void UpdateInput(WordProcessor&);
        virtual void Draw();
        virtual void DrawAbility(){};
};

Player::Player()
{
    rect.x = 125;
    rect.y = 475;
    rect.w = 100;
    rect.h = 200;

    imageRect.x = rect.x;
    imageRect.y = rect.y;

    healthRect.x = rect.x+25;
    healthRect.y = (rect.y+rect.h)+25;
    healthRect.w = rect.w;
    healthRect.h = 20;

    healthImageRect.x = healthRect.x-25;
    healthImageRect.y = healthRect.y;

    timerRect.x = rect.x+300;
    timerRect.y = rect.y-200;
    timerRect.w = 100;
    timerRect.h = 50;

    keyboardRect.x = 350;
    keyboardRect.y = 10;

    health = MAX_HEALTH;
    damage = BASE_DAMAGE;

    score = 0;
}

Player::~Player()
{
    delete attackButton;
    delete timer;
    delete frameTimer;

    attackButton = 0;
    timer = 0;
    frameTimer = 0;

    if(image != NULL)
        SDL_FreeSurface(image);
    if(keyboardImage != NULL)
        SDL_FreeSurface(keyboardImage);
}

void Player::SetImage(SDL_Surface* setImage,string imageType)
{
    if(imageType == "player")
        image = setImage;
    else if(imageType == "keyboard")
        keyboardImage = setImage;
}

SDL_Surface* Player::GetImage(string imageType)
{
    if(imageType == "player")
        return image;
    else if(imageType == "keyboard")
        return keyboardImage;
    else
        return NULL;
}

bool Player::GetTurnCompleted()
{
    return turnCompleted;
}

void Player::ResetTurnCompleted()
{
    turnCompleted = false;
}

bool Player::GetDefending()
{
    return defending;
}

void Player::IsDefending()
{
    defending = true;
    defendingFailed = false;
    ResetVariables();
}

void Player::NotDefending()
{
    defending = false;
}

bool Player::GetDefendingFailed()
{
    return defendingFailed;
}

bool Player::GetAttack()
{
    return attack;
}

void Player::NotAttack()
{
    attack = !attack;
}

int Player::GetDamage()
{
    return damage+damageMod;
}

int Player::GetHealth()
{
    return health;
}

void Player::SetMenuStateMain()
{
    currentMenuState = MAIN;
}

void Player::SetMenuStateTyping()
{
    typing = true;
    ResetVariables();
    currentMenuState = PLAYERTYPING;
}

void Player::SetMenuStateDefending()
{
    turnCompleted = true;
    defending = true;
    ResetVariables();
    currentMenuState = PLAYERTYPING;
}

void Player::TakeDamage(int damageTaken)
{
    damageTaken-=damageResist;

    if(damageTaken<=0)
        damageTaken = 1;

    health-=damageTaken;
}

void Player::SetWPM(bool completedWord)
{
    if(completedWord)
    {
        if(firstWordCompleted)
            wpm = 60/timer->GetSeconds();
        else
            wpm = (wpm + (60/timer->GetSeconds()))/2;
    }
    else
        wpm = wpm/2;
}

void Player::Attack(WordProcessor& externalWordProcessor)
{
    if(CheckWords(externalWordProcessor.GetWord(),word) && externalWordProcessor.GetWord() != "")
        DrawFillRect(backBuffer,500,500,25,25,255,255,255);
    else
        DrawFillRect(backBuffer,500,500,25,25,255,0,0);

    if(SameWords(externalWordProcessor.GetWord(),word))
    {
        firstWordCompleted = true;
        SetWPM(true);
        typing = false;
        attack = true;
        externalWordProcessor.ClearWord();
        turnCompleted = true;
        useAttackImage = true;
        Mix_PlayChannel(-1,swing,0);
        frameTimer->ResetTimer();
    }

    if(timer->GetSeconds() == time)
    {
        SetWPM(false);
        typing = false;
        turnCompleted = true;
    }

    timer->UpdateTimer();
}

void Player::Defend(WordProcessor& externalWordProcessor)
{
    if(CheckWords(externalWordProcessor.GetWord(),word) && externalWordProcessor.GetWord() != "")
            DrawFillRect(backBuffer,500,500,25,25,255,255,255);
    else
        DrawFillRect(backBuffer,500,500,25,25,255,0,0);

    if(SameWords(externalWordProcessor.GetWord(),word))
    {
        firstWordCompleted = true;
        SetWPM(true);
        defending = false;
        defendingFailed = false;
        externalWordProcessor.ClearWord();
        SetMenuStateMain();
    }

    if(timer->GetSeconds() == time)
    {
        SetWPM(false);
        defending = false;
        defendingFailed = true;
        SetMenuStateMain();
    }

    timer->UpdateTimer();
}

void Player::PushBackWord(string word)
{
    words.push_back(word);
}

void Player::ClearWords()
{
    if(!words.empty())
        while(!words.empty())
            words.pop_back();
}

void Player::ResetVariables()
{
    timer->ResetTimer();
    random_shuffle(words.begin(),words.end());
    strcpy(word,words[0].c_str());
}

void Player::ClearStanceEffects()
{
    damageMod = 0;
    damageResist = 0;
}

void Player::UpdateStates(WordProcessor& externalWordProcessor)
{
    switch(currentMenuState)
    {
        case MAIN:
        attackButton->UpdateMouse();
        attackButton->UpdatePressed();

        if(attackButton->CheckToggle())
        {
            currentMenuState = ABILITY;
        }

        if(SameWords(externalWordProcessor.GetWord(),attackButton->GetID()))
        {
            currentMenuState = ABILITY;
            externalWordProcessor.ClearWord();
        }
        break;

        case ABILITY:
        UpdateAbility(externalWordProcessor);
        break;
    }

    if(frameTimer->GetSeconds() >= .2)
        useAttackImage = false;

    if(useAttackImage)
        frameTimer->UpdateTimer();
}

void Player::UpdateInput(WordProcessor& externalWordProcessor)
{
    if(typing)
        Attack(externalWordProcessor);
    else if(defending)
        Defend(externalWordProcessor);
}

void Player::Draw()
{
    if(typing||defending)
    {
        DrawOutlineText(backBuffer,word,rect.x,rect.y-200,bungee25,255,255,255);
        DrawRect(backBuffer,timerRect,0,255,255);
        DrawFillRect(backBuffer,timerRect.x,timerRect.y,timer->GetSeconds()*(timerRect.w/time),timerRect.h,0,255,255);
    }

    if(typing)
        DrawOutlineText(backBuffer,"ATTACKING",500,100,bungee25,255,0,0);
    else if(defending)
        DrawOutlineText(backBuffer,"DEFENDING",500,100,bungee25,255,0,0);

    char word[64];
    sprintf(word,"Damage:%d",damage+damageMod);
    if(damageMod == 0)
        DrawOutlineText(backBuffer,word,0,50,bungee25,255,0,0);
    else
        DrawOutlineText(backBuffer,word,0,50,bungee25,0,255,0);

    sprintf(word,"DAMAGE RESIST:%d",damageResist);
    if(damageResist == 0)
        DrawOutlineText(backBuffer,word,0,100,bungee25,255,0,0);
    else
        DrawOutlineText(backBuffer,word,0,100,bungee25,0,255,0);

    sprintf(word,"WPM:%d.%d",(int)wpm,(int)((wpm-(int)wpm)*100));
    DrawOutlineText(backBuffer,word,1100,0,bungee25,255,255,0);

    SDL_BlitSurface(healthBarImage,NULL,backBuffer,&healthImageRect);
    DrawFillRect(backBuffer,healthRect.x,healthRect.y,(healthRect.w/MAX_HEALTH)*health,healthRect.h,255,0,0);

    SDL_BlitSurface(keyboardImage,NULL,backBuffer,&keyboardRect);

    switch(currentMenuState)
    {
        case MAIN:
        attackButton->Draw();
        break;

        case ABILITY:
        DrawAbility();
        break;

        default:
        break;
    }
}

class Knight: public Player
{
    protected:
        Button* attackStanceButton = new Button(50,400,0,255,255,"attack stance");
        Button* defenceStanceButton = new Button(50,300,0,255,255,"defence stance");
        Button* swordSwipeButton = new Button(50,200,0,255,255,"sword swipe");
        enum STANCE{ATTACKSTANCE,DEFENCESTANCE};
        unsigned int currentStance;
    public:
        Knight();
        ~Knight();
        void UpdateAbility(WordProcessor&);
        void DrawAbility();
        void Draw();
};

Knight::Knight()
{
    damageMod = 1;
    currentStance = ATTACKSTANCE;

    rect.w = 372;
    rect.h = 208;
}

Knight::~Knight()
{
    delete attackStanceButton;
    delete defenceStanceButton;
    delete swordSwipeButton;

    attackStanceButton = 0;
    defenceStanceButton = 0;
    swordSwipeButton = 0;
}

void Knight::UpdateAbility(WordProcessor& externalWordProcessor)
{
    swordSwipeButton->UpdateMouse();
    swordSwipeButton->UpdatePressed();
    attackStanceButton->UpdateMouse();
    attackStanceButton->UpdatePressed();
    defenceStanceButton->UpdateMouse();
    defenceStanceButton->UpdatePressed();

    if(swordSwipeButton->CheckToggle())
        SetMenuStateTyping();
    else if(SameWords(externalWordProcessor.GetWord(),swordSwipeButton->GetID()))
    {
        SetMenuStateTyping();
        externalWordProcessor.ClearWord();
    }

    switch(currentStance)
    {
        case ATTACKSTANCE:
        if(defenceStanceButton->CheckToggle())
        {
            ClearStanceEffects();
            damageResist = 1;
            SetMenuStateDefending();
            currentStance = DEFENCESTANCE;
        }
        else if(SameWords(externalWordProcessor.GetWord(),defenceStanceButton->GetID()))
        {
            ClearStanceEffects();
            damageResist = 1;
            SetMenuStateDefending();
            currentStance = DEFENCESTANCE;
            externalWordProcessor.ClearWord();
        }
        return;

        case DEFENCESTANCE:
        if(attackStanceButton->CheckToggle())
        {
            ClearStanceEffects();
            damageMod = 1;
            SetMenuStateDefending();
            currentStance = ATTACKSTANCE;
        }
        else if(SameWords(externalWordProcessor.GetWord(),attackStanceButton->GetID()))
        {
            ClearStanceEffects();
            damageMod = 1;
            SetMenuStateDefending();
            currentStance = ATTACKSTANCE;
            externalWordProcessor.ClearWord();
        }
        return;
    }
}

void Knight::DrawAbility()
{
    swordSwipeButton->Draw();

    switch(currentStance)
    {
        case ATTACKSTANCE:
        defenceStanceButton->Draw();
        return;

        case DEFENCESTANCE:
        attackStanceButton->Draw();
        return;
    }
}

void Knight::Draw()
{
    if(currentStance == ATTACKSTANCE)
        DrawOutlineText(backBuffer,"ATTACK STANCE ACTIVE",0,0,bungee25,0,255,0);
    else
        DrawOutlineText(backBuffer,"DEFENCE STANCE ACTIVE",0,0,bungee25,0,255,0);

    if(useAttackImage)
        DrawImageFrame(knightImage,backBuffer,rect.x,rect.y,rect.w,rect.h,0);
    else
        DrawImageFrame(knightImage,backBuffer,rect.x,rect.y,rect.w,rect.h,1);
    Player::Draw();
}

class Mage: public Player
{
    protected:
        Button* fireBallButton = new Button(50,200,0,255,255,"fire ball");
    public:
        Mage();
        ~Mage();
        void UpdateAbility(WordProcessor&);
        void DrawAbility();
        void Draw();
};

Mage::Mage()
{
}

Mage::~Mage()
{
    delete fireBallButton;

    fireBallButton = 0;
}

void Mage::UpdateAbility(WordProcessor& externalWordProcessor)
{
    fireBallButton->UpdateMouse();
    fireBallButton->UpdatePressed();

    if(fireBallButton->CheckToggle())
        SetMenuStateTyping();
    else if(SameWords(externalWordProcessor.GetWord(),fireBallButton->GetID()))
    {
        SetMenuStateTyping();
        externalWordProcessor.ClearWord();
    }
}

void Mage::DrawAbility()
{
    fireBallButton->Draw();
}

void Mage::Draw()
{
    SDL_BlitSurface(mageImage,NULL,backBuffer,&imageRect);
    Player::Draw();
}

class Enemy
{
    protected:
        SDL_Surface* image = NULL;
        static const int MAX_HEALTH = 3;
        int health;
        int damage = 0;
        SDL_Rect rect;
        SDL_Rect healthRect;
        SDL_Rect healthRectImage;
    public:
        Enemy();
        void SetImage(SDL_Surface*);
        SDL_Surface* GetImage();
        void FreeImage();
        int GetDamage();
        int GetHealth();
        void SetPos(int,int);
        virtual void TakeDamage(int);
        virtual void Draw();
        virtual void UpdateChosenMove(){};
};

Enemy::Enemy()
{
    rect.x = 900;
    rect.y = 500;
    rect.w = 100;
    rect.h = 200;

    healthRect.x = rect.x;
    healthRect.y = (rect.y+rect.h);
    healthRect.w = rect.w;
    healthRect.h = 20;

    healthRectImage.x = healthRect.x-25;
    healthRectImage.y = healthRect.y;

    health = MAX_HEALTH;
}

void Enemy::SetImage(SDL_Surface* setImage)
{
    image = setImage;
}

SDL_Surface* Enemy::GetImage()
{
    return image;
}

void Enemy::FreeImage()
{
    SDL_FreeSurface(image);
}

int Enemy::GetDamage()
{
    return damage;
}

int Enemy::GetHealth()
{
    return health;
}

void Enemy::SetPos(int x,int y)
{
    rect.x = x;
    rect.y = y;
    healthRect.x = rect.x;
    healthRect.y = (rect.y+rect.h);
    healthRectImage.x = healthRect.x-25;
    healthRectImage.y = healthRect.y;
}

void Enemy::TakeDamage(int damage)
{
    if((health-damage)<0)
        health = 0;
    else
        health-=damage;
}

void Enemy::Draw()
{
    SDL_BlitSurface(healthBarImage,NULL,backBuffer,&healthRectImage);
    DrawFillRect(backBuffer,healthRect.x,healthRect.y,(healthRect.w/MAX_HEALTH)*health,healthRect.h,255,0,0);
}

class Skeleton: public Enemy
{
    protected:
        const int BONE_CLUB_DAMAGE = 9;
        const int BONE_STRIKE_DAMAGE = 1;
        const string ID = "Skeleton";
        char id[64];
    public:
        Skeleton();
        ~Skeleton(){};
        void TakeDamage(int _damage){Enemy::TakeDamage(_damage);};
        void UpdateChosenMove();
        void Draw();
};

Skeleton::Skeleton()
{
    damage = BONE_STRIKE_DAMAGE;
    strcpy(id,ID.c_str());
}

void Skeleton::UpdateChosenMove()
{
    int randNum = rand()%100+1;

    if(randNum<50)
        damage = BONE_CLUB_DAMAGE;
    else
        damage = BONE_STRIKE_DAMAGE;
}

void Skeleton::Draw()
{
    Enemy::Draw();
    DrawOutlineText(backBuffer,id,rect.x,rect.y-25,bungee25,255,0,0);
    SDL_BlitSurface(skeletonImage,NULL,backBuffer,&rect);
}

class Zombie: public Enemy
{
    protected:
        const int BITE_DAMAGE = 2;
        const string ID = "Zombie";
        char id[64];
    public:
        Zombie();
        ~Zombie(){};
        void TakeDamage(int _damage){Enemy::TakeDamage(_damage);};
        void UpdateChosenMove();
        void Draw();
};

Zombie::Zombie()
{
    damage = BITE_DAMAGE;
    strcpy(id,ID.c_str());
}

void Zombie::UpdateChosenMove()
{
}

void Zombie::Draw()
{
    Enemy::Draw();
    DrawOutlineText(backBuffer,id,rect.x,rect.y-25,bungee25,255,0,0);
    SDL_BlitSurface(zombieImage,NULL,backBuffer,&rect);
}

class Necromancer: public Enemy
{
    protected:
        Enemy* minion;
        const int CREEPING_DEATH_DAMAGE = 3;
        const string ID = "Necromancer";
        char id[64];
    public:
        Necromancer();
        ~Necromancer();
        void TakeDamage(int);
        void UpdateChosenMove();
        void Draw();
};

Necromancer::Necromancer()
{
    damage = CREEPING_DEATH_DAMAGE;
    strcpy(id,ID.c_str());

    minion = new Skeleton();
    minion->SetPos(600,500);
}

Necromancer::~Necromancer()
{
    delete minion;
    minion = 0;
}

void Necromancer::TakeDamage(int _damage)
{
    if(minion->GetHealth() > 0)
        minion->TakeDamage(_damage);
    else
        Enemy::TakeDamage(_damage);
}

void Necromancer::UpdateChosenMove()
{
    damage = 0;

    if(minion->GetHealth() > 0)
        damage += minion->GetDamage();

    damage += CREEPING_DEATH_DAMAGE;
}

void Necromancer::Draw()
{
    Enemy::Draw();

    if(minion->GetHealth() > 0)
        minion->Draw();

    DrawOutlineText(backBuffer,id,rect.x,rect.y-25,bungee25,255,0,0);
    SDL_BlitSurface(necromancerImage,NULL,backBuffer,&rect);
}

class Archer: public Enemy
{
    protected:
        const int ARROW_DAMAGE = 3;
        const string ID = "Archer";
        char id[64];
    public:
        Archer();
        ~Archer(){};
        void TakeDamage(int _damage){Enemy::TakeDamage(_damage);};
        void UpdateChosenMove();
        void Draw();
};

Archer::Archer()
{
    damage = ARROW_DAMAGE;
    strcpy(id,ID.c_str());
}

void Archer::UpdateChosenMove()
{
}

void Archer::Draw()
{
    Enemy::Draw();
    DrawOutlineText(backBuffer,id,rect.x,rect.y-25,bungee25,255,0,0);
    SDL_BlitSurface(archerImage,NULL,backBuffer,&rect);
}

class Swordsman: public Enemy
{
    protected:
        const int SLAH_DAMAGE = 3;
        const string ID = "Swordsman";
        char id[64];
    public:
        Swordsman();
        ~Swordsman(){};
        void TakeDamage(int _damage){Enemy::TakeDamage(_damage);};
        void UpdateChosenMove();
        void Draw();
};

Swordsman::Swordsman()
{
    damage = SLAH_DAMAGE;
    strcpy(id,ID.c_str());
}

void Swordsman::UpdateChosenMove()
{
}

void Swordsman::Draw()
{
    Enemy::Draw();
    DrawOutlineText(backBuffer,id,rect.x,rect.y-25,bungee25,255,0,0);
    SDL_BlitSurface(swordsmanImage,NULL,backBuffer,&rect);
}

class TurnManager
{
    private:
        bool playerTurn = true;
    public:
        void NotPlayerTurn();
        bool GetPlayerTurn();
        void IsPlayerTurn();
};

void TurnManager::NotPlayerTurn()
{
    playerTurn = false;
}

bool TurnManager::GetPlayerTurn()
{
    return playerTurn;
}

void TurnManager::IsPlayerTurn()
{
    playerTurn = true;
}

//Class Instances
WordProcessor wordProcessor;
Button settingsButton(500,600,255,255,255,"settings");
Button playStateButton(500,500,255,255,255,"play");
Button fullScreenButton(500,500,255,255,255,"full screen");
Button knightClassButton(450,400,255,255,255,"knight");
Button mageClassButton(700,400,255,255,255,"mage");
Button returnMainMenuButton(500,600,255,255,255,"main menu");
Player* player;
vector<Enemy*> enemies;
TurnManager turnManager;

int main(int argc, char*argv[])
{
    if(!InitGame())
    {
        FreeGame();
        printf("failed");
        return 0;
    }

    while(ProgramIsRunning())
    {
        long int oldTime = SDL_GetTicks();
        SDL_FillRect(backBuffer,NULL,0);

        RunProgram();

        int frameTime = SDL_GetTicks() - oldTime;

        if(frameTime < FRAME_DELAY)
            SDL_Delay(FRAME_DELAY - frameTime);
        SDL_Flip(backBuffer);
    }

    FreeGame();
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    return 0;
}

void RunProgram()
{
    lastPlayState = currentGameState;

    switch(currentGameState)
    {
        case MAINMENU:
        RunMainMenu();
        break;

        case SETTINGSMENU:
        RunSettingsMenu();
        break;

        case TUTORIAL:
        RunTutorial();
        break;

        case CLASSSELECT:
        RunClassSelectMenu();
        break;

        case PLAYSTATE:
        RunPlayState();
        break;

        case PAUSEMENU:
        RunPauseState();
        break;

        case GAMEOVER:
        RunGameOverState();
        break;

        case WONGAME:
        RunWonGameState();
        break;
    }

    ProcessKeyboardInput();

    DrawScreen();
}

void DrawScreen()
{
    if(lastPlayState == currentGameState)
    {
        switch(currentGameState)
        {
            case MAINMENU:
            DrawMainMenu();
            break;

            case SETTINGSMENU:
            DrawSettingsMenu();
            break;

            case TUTORIAL:
            DrawTutorial();
            break;

            case CLASSSELECT:
            DrawClassSelectMenu();
            break;

            case PLAYSTATE:
            DrawPlayState();
            break;

            case PAUSEMENU:
            DrawPauseState();
            break;

            case GAMEOVER:
            DrawGameOverState();
            break;

            case WONGAME:
            DrawWonGameState();
            break;
        }
    }

    DrawKeyboardInput();
}

void ProcessKeyboardInput()
{
    wordProcessor.ProcessKeys();

    if(string(wordProcessor.GetWord()).length() >= 15)
        wordProcessor.SetWord(string(wordProcessor.GetWord()).substr(1,14));
}

void DrawKeyboardInput()
{
    DrawOutlineText(backBuffer,"INPUT:",390,750,bungee25,0,255,0);
    wordProcessor.Draw(500,750);
}

void RunMainMenu()
{
    settingsButton.UpdateMouse();
    settingsButton.UpdatePressed();
    playStateButton.UpdateMouse();
    playStateButton.UpdatePressed();

    if(settingsButton.CheckToggle())
        currentGameState = SETTINGSMENU;
    if(playStateButton.CheckToggle())
    {
        currentGameState = CLASSSELECT;
        Mix_HaltMusic();
        Mix_PlayMusic(playMusic,-1);
    }

    if(SameWords(wordProcessor.GetWord(),settingsButton.GetID()))
    {
        currentGameState = SETTINGSMENU;
        wordProcessor.ClearWord();
    }

    if(SameWords(wordProcessor.GetWord(),playStateButton.GetID()))
    {
        currentGameState = CLASSSELECT;
        wordProcessor.ClearWord();
        Mix_HaltMusic();
        Mix_PlayMusic(playMusic,-1);
    }
}

void DrawMainMenu()
{
    SDL_BlitSurface(menuImage,NULL,backBuffer,&backgroundRect);
    DrawOutlineText(backBuffer,"MAIN MENU",300,100,bungee100,255,255,255);
    settingsButton.Draw();
    playStateButton.Draw();
}

void RunSettingsMenu()
{
    returnMainMenuButton.UpdateMouse();
    returnMainMenuButton.UpdatePressed();

    if(returnMainMenuButton.CheckToggle())
        currentGameState = MAINMENU;

    fullScreenButton.UpdateMouse();
    fullScreenButton.UpdatePressed();

    if(fullScreenButton.CheckToggle())
    {
        fullScreen = !fullScreen;
        SetScreen();
    }

    if(SameWords(wordProcessor.GetWord(),returnMainMenuButton.GetID()))
    {
        currentGameState = MAINMENU;
        wordProcessor.ClearWord();
    }

    if(SameWords(wordProcessor.GetWord(),fullScreenButton.GetID()))
    {
        fullScreen = !fullScreen;
        SetScreen();
        wordProcessor.ClearWord();
    }
}

void DrawSettingsMenu()
{
    SDL_BlitSurface(menuImage,NULL,backBuffer,&backgroundRect);
    DrawOutlineText(backBuffer,"SETTINGS MENU",300,100,bungee100,255,255,255);
    returnMainMenuButton.Draw();
    fullScreenButton.Draw();
}

void RunTutorial()
{
    returnMainMenuButton.UpdateMouse();
    returnMainMenuButton.UpdatePressed();

    if(returnMainMenuButton.CheckToggle())
        currentGameState = MAINMENU;

    if(SameWords(wordProcessor.GetWord(),returnMainMenuButton.GetID()))
    {
        currentGameState = MAINMENU;
        wordProcessor.ClearWord();
    }
}

void DrawTutorial()
{
    SDL_BlitSurface(menuImage,NULL,backBuffer,&backgroundRect);
    SDL_BlitSurface(tutorialImage,NULL,backBuffer,&backgroundRect);
    DrawOutlineText(backBuffer,"Tutorial",300,50,bungee100,0,0,0);
    returnMainMenuButton.Draw();
}

void RunClassSelectMenu()
{
    knightClassButton.UpdateMouse();
    knightClassButton.UpdatePressed();
    mageClassButton.UpdateMouse();
    mageClassButton.UpdatePressed();

    if(knightClassButton.CheckToggle())
        currentPlayerClass = KNIGHT;
    else if(mageClassButton.CheckToggle())
        currentPlayerClass = MAGE;

    if(knightClassButton.CheckToggle() || mageClassButton.CheckToggle())
    {
        currentGameState = PLAYSTATE;
        InitPlayState();
    }

    if(SameWords(wordProcessor.GetWord(),knightClassButton.GetID()))
    {
        currentPlayerClass = KNIGHT;
        currentGameState = PLAYSTATE;
        InitPlayState();
        wordProcessor.ClearWord();
    }

    if(SameWords(wordProcessor.GetWord(),mageClassButton.GetID()))
    {
        currentPlayerClass = MAGE;
        currentGameState = PLAYSTATE;
        InitPlayState();
        wordProcessor.ClearWord();
    }
}

void DrawClassSelectMenu()
{
    SDL_BlitSurface(menuImage,NULL,backBuffer,&backgroundRect);
    DrawOutlineText(backBuffer,"PICK CLASS",300,100,bungee100,255,255,255);
    knightClassButton.Draw();
    mageClassButton.Draw();
}

void RunPlayState()
{
    if(player->GetHealth() <= 0)
    {
       currentGameState = GAMEOVER;
       Mix_HaltMusic();
       Mix_PlayMusic(gameOverMusic,-1);
    }

    CheckLastEnemyDead();
    CheckEnemiesAllDead();

    player->UpdateStates(wordProcessor);

    if(turnManager.GetPlayerTurn())
    {
        player->UpdateInput(wordProcessor);


        if(player->GetAttack())
        {
            player->NotAttack();
            enemies[enemies.size()-1]->TakeDamage(player->GetDamage());
            wordProcessor.ClearWord();
        }

        if(player->GetTurnCompleted())
        {
            turnManager.NotPlayerTurn();
            player->IsDefending();
            player->ResetTurnCompleted();
            enemies[enemies.size()-1]->UpdateChosenMove();
            wordProcessor.ClearWord();
        }
    }
    if(!turnManager.GetPlayerTurn())
    {
        player->UpdateInput(wordProcessor);

        if(player->GetDefendingFailed())
        {
            player->TakeDamage(enemies[enemies.size()-1]->GetDamage());
            wordProcessor.ClearWord();
        }

        if(!player->GetDefending())
        {
            turnManager.IsPlayerTurn();
            wordProcessor.ClearWord();
        }
    }

    if(wordProcessor.GetLastKeyCode() == SDLK_ESCAPE && wordProcessor.GetLastKeyState())
    {
        currentGameState = PAUSEMENU;
        wordProcessor.ClearWord();
    }
}

void DrawPlayState()
{
    SDL_BlitSurface(playImage,NULL,backBuffer,&backgroundRect);
    player->Draw();
    enemies[enemies.size()-1]->Draw();
}

void InitPlayer()
{
    fstream wordList;

    switch(currentPlayerClass)
    {
        case KNIGHT:
        player = new Knight;
        wordList.open("wordLists/Knight Word List.txt");
        break;

        case MAGE:
        player = new Mage;
        wordList.open("wordLists/Mage Word List.txt");
        break;
    }

    string word;

    while(!wordList.eof())
    {
        wordList>>word;
        player->PushBackWord(word);
    }

    wordList.close();

    player->SetImage(LoadImage("graphics/kbqwerty.bmp"),"keyboard");
}

void DeletePlayer()
{
    delete player;
    player = 0;
}

void InitPlayState()
{
    srand(time(NULL));
    currentLevel = CRYPT;
    InitPlayer();
    LoadLevel();
}

void CheckLastEnemyDead()
{
    if(!enemies.empty())
    {
        if(enemies[enemies.size()-1]->GetHealth() <= 0)
        {
            player->NotDefending();
            player->ResetTurnCompleted();
            player->SetMenuStateMain();
            turnManager.IsPlayerTurn();
            delete enemies[enemies.size()-1];
            enemies[enemies.size()-1] = 0;
            enemies.pop_back();
        }
    }
}

void CheckEnemiesAllDead()
{
    if(enemies.empty())
    {
        if(currentLevel == MEDIEVAL+1)
            currentGameState = WONGAME;
        else
         LoadLevel();
    }
}

void DeleteAllEnemies()
{
    if(!enemies.empty())
    {
        for(unsigned int i=0;i<enemies.size();i++)
        {
            delete enemies[i];
            enemies[i] = 0;
        }
        enemies.clear();
    }
}

void LoadLevel()
{
    int randNum;

    switch(currentLevel)
    {
        case CRYPT:
        enemies.push_back(new Necromancer());

        for(unsigned int i=0;i<enemyCount;i++)
        {
            randNum = rand()%2+1;

            if(randNum <= 1)
                enemies.push_back(new Skeleton());
            else
                enemies.push_back(new Zombie());
        }

        currentLevel++;
        break;

        case MEDIEVAL:
        for(unsigned int i=0;i<enemyCount;i++)
        {
            randNum = rand()%2+1;

            if(randNum <= 1)
                enemies.push_back(new Archer());
            else
                enemies.push_back(new Swordsman());
        }

        currentLevel++;
        break;
    }
}

void DeleteAll()
{
    DeleteAllEnemies();
    DeletePlayer();
}

void RunPauseState()
{
    returnMainMenuButton.UpdateMouse();
    returnMainMenuButton.UpdatePressed();

    if(returnMainMenuButton.CheckToggle())
    {
        currentGameState = MAINMENU;
        DeleteAll();
        Mix_HaltMusic();
        Mix_PlayMusic(menuMusic,-1);
    }
    else if(SameWords(wordProcessor.GetWord(),returnMainMenuButton.GetID()))
    {
        currentGameState = MAINMENU;
        DeleteAll();
        wordProcessor.ClearWord();
        Mix_HaltMusic();
        Mix_PlayMusic(menuMusic,-1);
    }

    else if(wordProcessor.GetLastKeyCode() == SDLK_ESCAPE && wordProcessor.GetLastKeyState())
        currentGameState = PLAYSTATE;
}

void DrawPauseState()
{
    SDL_BlitSurface(menuImage,NULL,backBuffer,&backgroundRect);
    returnMainMenuButton.Draw();
}

void RunGameOverState()
{
    returnMainMenuButton.UpdateMouse();
    returnMainMenuButton.UpdatePressed();

    if(returnMainMenuButton.CheckToggle())
    {
        currentGameState = MAINMENU;
        DeleteAll();
        Mix_HaltMusic();
        Mix_PlayMusic(menuMusic,-1);
    }
    else if(SameWords(wordProcessor.GetWord(),returnMainMenuButton.GetID()))
    {
        currentGameState = MAINMENU;
        DeleteAll();
        wordProcessor.ClearWord();
        Mix_HaltMusic();
        Mix_PlayMusic(menuMusic,-1);
    }
}

void DrawGameOverState()
{
    SDL_BlitSurface(menuImage,NULL,backBuffer,&backgroundRect);
    DrawOutlineText(backBuffer,"GAME OVER",200,100,bungee100,255,0,0);
    returnMainMenuButton.Draw();
}

void RunWonGameState()
{
    returnMainMenuButton.UpdateMouse();
    returnMainMenuButton.UpdatePressed();

    if(returnMainMenuButton.CheckToggle())
    {
        currentGameState = MAINMENU;
        DeleteAll();
    }
    else if(SameWords(wordProcessor.GetWord(),returnMainMenuButton.GetID()))
    {
        currentGameState = MAINMENU;
        DeleteAll();
        wordProcessor.ClearWord();
    }
}

void DrawWonGameState()
{
    DrawOutlineText(backBuffer,"YOU WIN",200,100,bungee100,255,0,0);

    returnMainMenuButton.Draw();
}

void ToggleFullScreenViaKey()
{
    if(wordProcessor.GetLastKeyCode() == SDLK_f && wordProcessor.GetLastKeyState())
    {
        fullScreen = !fullScreen;
        printf("TOGGLE:%d and %d \n",wordProcessor.GetLastKeyCode(),wordProcessor.GetLastKeyState());
    }

    if(lastFullScreen != fullScreen)
    {
        SetScreen();
        lastFullScreen = fullScreen;
    }

    printf("LastFullScreen:%d\nFullScreen:%d\n",lastFullScreen,fullScreen);
}

bool CheckWords(char word[100],char testWord[100])
{
    if((word == "" || testWord == "") && word != testWord)
        return true;

    for(unsigned int i=0;i<strlen(word);i++)
    {
        if(word[i]!=testWord[i])
            return false;
    }

    return true;
}

bool SameWords(char word[100],char testWord[100])
{
    for(unsigned int i=0;i<strlen(testWord);i++)
    {
        if(word[i]!=testWord[i])
            return false;
    }

    return true;
}

void DrawFillRect(SDL_Surface* surface,int x,int y,int width,int height,int r,int g,int b)
{
    SDL_Rect rect;
    rect.x=x;
    rect.y=y;
    rect.w=width;
    rect.h=height;

    Uint32 color = SDL_MapRGB(surface->format,r,g,b);
    SDL_FillRect(surface,&rect,color);
}

void DrawRect(SDL_Surface* surface,SDL_Rect rect,int r,int g,int b)
{
    DrawFillRect(surface,rect.x,rect.y,rect.w,1,r,g,b);
    DrawFillRect(surface,rect.x,rect.y+rect.h,rect.w,1,r,g,b);
    DrawFillRect(surface,rect.x,rect.y,1,rect.h,r,g,b);
    DrawFillRect(surface,rect.x+rect.w,rect.y,1,rect.h,r,g,b);
}

void DrawOutlineText(SDL_Surface* surface,char* string,int x,int y,TTF_Font* font,Uint8 r,Uint8 g,Uint8 b)
{
    SDL_Surface* renderedText = NULL;

    SDL_Color color;

    color.r = r;
    color.g = g;
    color.b = b;

    renderedText = TTF_RenderText_Solid(font,string,color);

    SDL_Rect pos;

    pos.x = x;
    pos.y = y;

    SDL_BlitSurface(renderedText,NULL,surface,&pos);
    SDL_FreeSurface(renderedText);
}

void DrawImageFrame(SDL_Surface* image,SDL_Surface* destSurface,int x,int y,int width,int height,int frame)
{
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;

    int columns = image->w/width;

    SDL_Rect sourceRect;
    sourceRect.y = (frame/columns)*height;
    sourceRect.x = (frame%columns)*width;
    sourceRect.w = width;
    sourceRect.h = height;

    SDL_BlitSurface(image, &sourceRect, destSurface, &destRect);
}

bool CheckCollide(const SDL_Rect& rect1,const SDL_Rect& rect2)
{
    if((rect1.x >= rect2.x  - rect1.w) && (rect1.x <= rect2.x + rect2.w) && (rect1.y <= rect2.y + rect2.h) && (rect1.y >= rect2.y - rect1.h))
        return true;
    else
        return false;
}

SDL_Surface* LoadImage(char* fileName)
{
    SDL_Surface* imageLoaded = NULL;
    SDL_Surface* processedImage = NULL;

    imageLoaded = IMG_Load(fileName);

    if(imageLoaded != NULL)
    {
        processedImage = SDL_DisplayFormat(imageLoaded);
        SDL_FreeSurface(imageLoaded);

        if(processedImage != NULL)
        {
            Uint32 colorKey = SDL_MapRGB(processedImage->format, 255, 0, 255);
            SDL_SetColorKey(processedImage, SDL_SRCCOLORKEY, colorKey);
        }

    }

    return processedImage;
}

void FreeGame()
{
    SDL_FreeSurface(healthBarImage);
    SDL_FreeSurface(buttonImage);
    SDL_FreeSurface(knightImage);
    SDL_FreeSurface(mageImage);
    SDL_FreeSurface(skeletonImage);
    SDL_FreeSurface(zombieImage);
    SDL_FreeSurface(archerImage);
    SDL_FreeSurface(necromancerImage);
    SDL_FreeSurface(swordsmanImage);
    SDL_FreeSurface(tutorialImage);
    SDL_FreeSurface(menuImage);
    SDL_FreeSurface(playImage);

    TTF_CloseFont(bungee100);
    TTF_CloseFont(bungee25);

    Mix_FreeMusic(menuMusic);
    Mix_FreeMusic(playMusic);
    Mix_FreeMusic(gameOverMusic);
    Mix_FreeChunk(swing);
}

bool LoadFiles()
{
    SDL_Surface* testKeyboardImage = NULL;

    ifstream testWordsFile;
    testWordsFile.open("wordLists/wordList.txt");

    testKeyboardImage = LoadImage("graphics/kbqwerty.bmp");
    healthBarImage = LoadImage("graphics/healthBar.bmp");
    buttonImage = LoadImage("graphics/buttonImage.bmp");
    knightImage = LoadImage("graphics/KnightSpriteSheet.bmp");
    mageImage = LoadImage("graphics/Mage.bmp");
    skeletonImage = LoadImage("graphics/Skeleton.bmp");
    zombieImage = LoadImage("graphics/Zombie.bmp");
    archerImage = LoadImage("graphics/Archer.bmp");
    necromancerImage = LoadImage("graphics/necromancer.bmp");
    swordsmanImage = LoadImage("graphics/swordsman.bmp");
    tutorialImage = LoadImage("graphics/tutorial.bmp");
    menuImage = LoadImage("graphics/stoneBackground.bmp");
    playImage = LoadImage("graphics/DungeonBackground.bmp");

    bungee100 = TTF_OpenFont("fonts/bungee.ttf",100);
    bungee25 = TTF_OpenFont("fonts/bungee.ttf",25);

    menuMusic = Mix_LoadMUS("audio/Menu.wav");
    playMusic = Mix_LoadMUS("audio/Gameplay.wav");
    gameOverMusic = Mix_LoadMUS("audio/Game_Over.wav");
    swing = Mix_LoadWAV("audio/swing.wav");

    if(testKeyboardImage == NULL)
        return false;
    if(healthBarImage == NULL)
        return false;
    if(buttonImage == NULL)
        return false;
    if(knightImage == NULL)
        return false;
    if(mageImage == NULL)
        return false;
    if(skeletonImage == NULL)
        return false;
    if(zombieImage == NULL)
        return false;
    if(archerImage == NULL)
        return false;
    if(necromancerImage == NULL)
        return false;
    if(swordsmanImage == NULL)
        return false;
    if(tutorialImage == NULL)
        return false;
    if(menuImage == NULL)
        return false;
    if(playImage == NULL)
        return false;

    if(bungee100 == NULL)
        return false;
    if(bungee25 == NULL)
        return false;

    if(menuMusic == NULL)
        return false;
    if(playMusic == NULL)
        return false;
    if(gameOverMusic == NULL)
        return false;
    if(swing == NULL)
        return false;

    if(testWordsFile.fail())
        return false;

    SDL_FreeSurface(testKeyboardImage);

    testWordsFile.close();

    return true;
}

void SetScreen()
{
    if(fullScreen)
        backBuffer = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,SDL_SWSURFACE | SDL_FULLSCREEN);
    else
        backBuffer = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,SDL_SWSURFACE);
}

bool ProgramIsRunning()
{
    SDL_Event event;

   while(SDL_PollEvent(&event))
        if(event.type == SDL_QUIT)
            return false;

    return true;
}

bool InitSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        printf("SDL_INIT" );
        return false;
    }

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1 )
    {
        printf("MIX_OpenAudio ");
        return false;
    }

    if(TTF_Init() == -1)
    {
        printf("TTF_Init ");
        return false;
    }

    SetScreen();

    if(backBuffer == NULL)
    {
        printf("SDL_SetVideoMode ");
        return false;
    }

    return true;
}

bool InitGame()
{
    if(!InitSDL())
    {
        printf("LoadSDL() ");
        return false;
    }
    if(!LoadFiles())
    {
        printf("LoadFiles() ");
        return false;
    }

    SDL_WM_SetCaption("Typing Game",NULL);
    Mix_PlayMusic(menuMusic,-1);

    backgroundRect.x = 0;
    backgroundRect.y = 0;

    return true;
}
