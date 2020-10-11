#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define MAX 1000
#define WINDOW_X 640
#define WINDOW_Y 480
#define INCREASE 100
#define STAT_X 500
#define STAT_W 100
#define STAT_H 10

//change screen
int screen = 0;
int x = 288;
int y = 208;

//bool variables
_Bool left = true;
_Bool right = true;
_Bool click = false;
_Bool dog_poop = false;
_Bool death = false;
_Bool stop = true;
_Bool start_over = false;
_Bool show_collision = false;
_Bool quit = false;

//Music and effects
Mix_Chunk* water;
Mix_Chunk* munch;
Mix_Music* music;
Mix_Chunk* fart;
Mix_Chunk* snore;
Mix_Chunk* bouncing;

SDL_Event event;

//Bool collision
typedef struct Collision{
    SDL_bool bowl;
    SDL_bool bed;
    SDL_bool ball;
    SDL_bool bath;
    SDL_bool pooping;
}Collision;

//Rect collision
typedef struct CollisionBox{
    SDL_Rect rect_doge;
    SDL_Rect rect_bowl;
    SDL_Rect rect_ball;
    SDL_Rect rect_bed;
    SDL_Rect rect_tub;
    SDL_Rect rect_tray;
}CollisionBox;

//Move sprite
typedef struct moveSprite{
    SDL_Rect srcrect_dog ;
    SDL_Rect srcrect_sleep ;
    SDL_Rect srcrect_play;
    SDL_Rect srcrect_shower ;
}moveSprite;

//Calculate sprite
typedef struct CalSprite{
    Uint32 ticks ;
    Uint32 seconds ;
    Uint32 sprite ;
}CalSprite;

//Stop animation
typedef struct Stop_animation{
    SDL_Rect dstrect_dog;
    SDL_Rect dstrect_doge_left;
    SDL_Rect dstrect_doge_right;
}Stop_animation;


//Max everystatus
typedef struct AllStat_Max{
    int hungerStat;
    int sleepStat;
    int playStat;
    int cleanStat;
    int poopStat;
}AllStat_Max;

//Rect images
typedef struct RectImage{
    SDL_Rect dstrect_background;
    SDL_Rect dstrect_floor;
    SDL_Rect dstrect_doge_bowl;
    SDL_Rect dstrect_hunger ;
    SDL_Rect dstrect_bed ;
    SDL_Rect dstrect_dog_sleep ;
    SDL_Rect dstrect_pillow ;
    SDL_Rect dstrect_ball;
    SDL_Rect dstrect_play;
    SDL_Rect dstrect_ball_icon ;
    SDL_Rect dstrect_tub ;
    SDL_Rect dstrect_shower ;
    SDL_Rect dstrect_soap;
    SDL_Rect dstrect_poop ;
    SDL_Rect dstrect_poop_icon ;
    SDL_Rect dstrect_tray ;
    SDL_Rect dstrect_start;
    SDL_Rect dstrect_start_button;
    SDL_Rect dstrect_press_enter;
    SDL_Rect dstrect_dog_face;
    SDL_Rect dstrect_restart;
    SDL_Rect dstrect_ghost;
    SDL_Rect dstrect_window;
}RectImage;

//Texture
typedef struct Texture{
    SDL_Texture * texture_background ;
    SDL_Texture * texture_floor;
    SDL_Texture * texture;
    SDL_Texture * texture_doge_bowl;
    SDL_Texture * texture_hunger;
    SDL_Texture * texture_bed ;
    SDL_Texture * texture_pillow;
    SDL_Texture * texture_ball ;
    SDL_Texture * texture_ball_icon ;
    SDL_Texture * texture_tub ;
    SDL_Texture * texture_soap;
    SDL_Texture * texture_poop_icon ;
    SDL_Texture * texture_tray;
    SDL_Texture * texture_start;
    SDL_Texture * texture_startButton;
    SDL_Texture * texture_dog_face ;
    SDL_Texture * texture_press_enter ;
    SDL_Texture * texture_restart;
    SDL_Texture * texture_ghost;
    SDL_Texture * texture_window;
}Texture;

//Dog texture
typedef struct DogeTexture{
    SDL_Texture * texture_image2 ;
    SDL_Texture * texture_doge_left;
    SDL_Texture * texture_doge_right;
    SDL_Texture * texture_eat ;
    SDL_Texture * texture_dog_sleep;
    SDL_Texture * texture_play ;
    SDL_Texture * texture_shower;
    SDL_Texture * texture_poop ;
}DogeTexture;

//Render struct
typedef struct Rend{
    
    SDL_Window *window;
    SDL_Renderer *renderer;
    
}Rend;

//Rect status
typedef struct Status{
    SDL_Rect rect_hunger;
    SDL_Rect rect_sleep;
    SDL_Rect rect_play;
    SDL_Rect rect_clean;
    SDL_Rect rect_poop;
    
}Status;

//Picture surface
typedef struct RenderPic{
    SDL_Surface * pinkBG;
    SDL_Surface * floor;
    SDL_Surface * doge_bowl;
    SDL_Surface * Food_icon;
    SDL_Surface * bed;
    SDL_Surface * pillow;
    SDL_Surface * ball;
    SDL_Surface * ball_icon;
    SDL_Surface * tub;
    SDL_Surface * soap;
    SDL_Surface * poop;
    SDL_Surface * tray;
    SDL_Surface * start;
    SDL_Surface * start_button;
    SDL_Surface * dog_face;
    SDL_Surface * press_enter;
    SDL_Surface * restart;
    SDL_Surface * ghost;
    SDL_Surface * window;
}RenderPic;

//Doge surface
typedef struct Doge{
    SDL_Surface * image;
    SDL_Surface * image2;
    SDL_Surface * doge_left;
    SDL_Surface * doge_right;
    SDL_Surface * eat;
    SDL_Surface * doge_sleep;
    SDL_Surface * doge_play;
    SDL_Surface * shower;
}Doge;

//global variable declaration
static Status status;
static Rend rend;
static RenderPic render;
static Doge doge;
static Texture StructTexture;
static DogeTexture dogeTexture;
static RectImage rectImage;
static AllStat_Max statMax;
static Stop_animation stopAnimation;
static CalSprite calSprite;
static moveSprite MoveSprite;
static CollisionBox collisionBox;
static Collision collision;

//collision function
void FuncCollision(void){
    collision.bowl = SDL_HasIntersection(&collisionBox.rect_doge, &collisionBox.rect_bowl);
    collision.bed = SDL_HasIntersection(&collisionBox.rect_doge, &collisionBox.rect_bed);
    collision.ball = SDL_HasIntersection(&collisionBox.rect_doge, &collisionBox.rect_ball);
    collision.bath = SDL_HasIntersection(&collisionBox.rect_doge, &collisionBox.rect_tub);
    collision.pooping = SDL_HasIntersection(&collisionBox.rect_doge, &collisionBox.rect_tray);
}

//Hitbox function
void FunccollisionBox(void){
    collisionBox.rect_doge.x = x;
    collisionBox.rect_doge.y = y+170;
    collisionBox.rect_doge.w = 60;
    collisionBox.rect_doge.h = 65;
    
    collisionBox.rect_bowl.x = 500;
    collisionBox.rect_bowl.y = 310;
    collisionBox.rect_bowl.w = 60;
    collisionBox.rect_bowl.h = 50;
    
    collisionBox.rect_ball.x = 300;
    collisionBox.rect_ball.y = 370;
    collisionBox.rect_ball.w = 75;
    collisionBox.rect_ball.h = 75;
    
    collisionBox.rect_bed.x = 10;
    collisionBox.rect_bed.y = 350;
    collisionBox.rect_bed.w = 140;
    collisionBox.rect_bed.h = 70;
    
    collisionBox.rect_tub.x = 100;
    collisionBox.rect_tub.y = 180;
    collisionBox.rect_tub.w = 200;
    collisionBox.rect_tub.h = 150;
    
    collisionBox.rect_tray.x = 370;
    collisionBox.rect_tray.y = 300;
    collisionBox.rect_tray.w = 100;
    collisionBox.rect_tray.h = 50;
    
}

//Function move sprite sheet
void FuncMoveSprite(void){

    MoveSprite.srcrect_dog.x = calSprite.sprite * 75;
    MoveSprite.srcrect_dog.y = 0;
    MoveSprite.srcrect_dog.w = 65;
    MoveSprite.srcrect_dog.h = 350;
    
    MoveSprite.srcrect_sleep.x = calSprite.sprite * 75;
    MoveSprite.srcrect_sleep.y = 0;
    MoveSprite.srcrect_sleep.w = 65;
    MoveSprite.srcrect_sleep.h = 170;
    
    MoveSprite.srcrect_play.x = calSprite.sprite * 120;
    MoveSprite.srcrect_play.y = 0;
    MoveSprite.srcrect_play.w = 100;
    MoveSprite.srcrect_play.h = 200;
    
    MoveSprite.srcrect_shower.x = calSprite.sprite * 100;
    MoveSprite.srcrect_shower.y = 0;
    MoveSprite.srcrect_shower.w = 95;
    MoveSprite.srcrect_shower.h = 80;
    
}

//function calculate sprite
void FuncCalSprite(void){
    calSprite.ticks = SDL_GetTicks();
    calSprite.seconds = calSprite.ticks / 100;
    calSprite.sprite = calSprite.seconds % 4;
}

//function stop animation
void FuncStopAnimation(void){
    stopAnimation.dstrect_dog.x = x;
    stopAnimation.dstrect_dog.y = y;
    stopAnimation.dstrect_dog.w = 65;
    stopAnimation.dstrect_dog.h = 350;

    stopAnimation.dstrect_doge_left.x = x;
    stopAnimation.dstrect_doge_left.y = y;
    stopAnimation.dstrect_doge_left.w = 65;
    stopAnimation.dstrect_doge_left.h = 350;
    
    stopAnimation.dstrect_doge_right.x = x;
    stopAnimation.dstrect_doge_right.y = y;
    stopAnimation.dstrect_doge_right.w = 65;
    stopAnimation.dstrect_doge_right.h = 350;
}

//function max status
void Maxstat(void){
    statMax.hungerStat = MAX;
    statMax.sleepStat = MAX;
    statMax.playStat = MAX;
    statMax.cleanStat = MAX;
    statMax.poopStat = MAX;
}

//function rect images
void FuncRectImage(void){
    rectImage.dstrect_background.x = 0;
    rectImage.dstrect_background.y = 0;
    rectImage.dstrect_background.w = 640;
    rectImage.dstrect_background.h = 480;
    
    rectImage.dstrect_floor.x = 0;
    rectImage.dstrect_floor.y = 300;
    rectImage.dstrect_floor.w = 640;
    rectImage.dstrect_floor.h = 300;
    
    rectImage.dstrect_doge_bowl.x = 500;
    rectImage.dstrect_doge_bowl.y = 300;
    rectImage.dstrect_doge_bowl.w = 70;
    rectImage.dstrect_doge_bowl.h = 70;
    
    rectImage.dstrect_hunger.x = 470;
    rectImage.dstrect_hunger.y = 8;
    rectImage.dstrect_hunger.w = 20;
    rectImage.dstrect_hunger.h = 20;

    rectImage.dstrect_bed.x = 10;
    rectImage.dstrect_bed.y = 350;
    rectImage.dstrect_bed.w = 140;
    rectImage.dstrect_bed.h = 70;
    
    rectImage.dstrect_dog_sleep.x = 55;
    rectImage.dstrect_dog_sleep.y = 300;
    rectImage.dstrect_dog_sleep.w = 65;
    rectImage.dstrect_dog_sleep.h = 100;
    
    rectImage.dstrect_pillow.x = 470;
    rectImage.dstrect_pillow.y = 28;
    rectImage.dstrect_pillow.w = 20;
    rectImage.dstrect_pillow.h = 20;
    
    rectImage.dstrect_ball.x = 300;
    rectImage.dstrect_ball.y = 370;
    rectImage.dstrect_ball.w = 75;
    rectImage.dstrect_ball.h = 75;
    
    rectImage.dstrect_play.x = 250;
    rectImage.dstrect_play.y = 370;
    rectImage.dstrect_play.w = 80;
    rectImage.dstrect_play.h = 80;
    
    rectImage.dstrect_ball_icon.x = 470;
    rectImage.dstrect_ball_icon.y = 48;
    rectImage.dstrect_ball_icon.w = 20;
    rectImage.dstrect_ball_icon.h = 20;
    
    rectImage.dstrect_tub.x = 100;
    rectImage.dstrect_tub.y = 180;
    rectImage.dstrect_tub.w = 200;
    rectImage.dstrect_tub.h = 180;
    
    rectImage.dstrect_shower.x = 160;
    rectImage.dstrect_shower.y = 180;
    rectImage.dstrect_shower.w = 70;
    rectImage.dstrect_shower.h = 70;
    
    rectImage.dstrect_soap.x = 470;
    rectImage.dstrect_soap.y = 68;
    rectImage.dstrect_soap.w = 20;
    rectImage.dstrect_soap.h = 20;
    
    rectImage.dstrect_poop.x = 400;
    rectImage.dstrect_poop.y = 320;
    rectImage.dstrect_poop.w = 20;
    rectImage.dstrect_poop.h = 20;
    
    rectImage.dstrect_poop_icon.x = 470;
    rectImage.dstrect_poop_icon.y = 88;
    rectImage.dstrect_poop_icon.w = 20;
    rectImage.dstrect_poop_icon.h = 20;
    
    rectImage.dstrect_tray.x = 370;
    rectImage.dstrect_tray.y = 300;
    rectImage.dstrect_tray.w = 100;
    rectImage.dstrect_tray.h = 50;
    
    rectImage.dstrect_start.x = 0;
    rectImage.dstrect_start.y = 0;
    rectImage.dstrect_start.w = 640;
    rectImage.dstrect_start.h = 480;
    
    rectImage.dstrect_start_button.x = 230;
    rectImage.dstrect_start_button.y = 250;
    rectImage.dstrect_start_button.w = 200;
    rectImage.dstrect_start_button.h = 50;
    
    rectImage.dstrect_press_enter.x = 235;
    rectImage.dstrect_press_enter.y = 320;
    rectImage.dstrect_press_enter.w = 180;
    rectImage.dstrect_press_enter.h = 10;
    
    rectImage.dstrect_dog_face.x = 250;
    rectImage.dstrect_dog_face.y = 80;
    rectImage.dstrect_dog_face.w = 150;
    rectImage.dstrect_dog_face.h = 150;
    
    rectImage.dstrect_restart.x = 230;
    rectImage.dstrect_restart.y = 320;
    rectImage.dstrect_restart.w = 180;
    rectImage.dstrect_restart.h = 10;
    
    rectImage.dstrect_ghost.x = 230;
    rectImage.dstrect_ghost.y = 150;
    rectImage.dstrect_ghost.w = 150;
    rectImage.dstrect_ghost.h = 150;
    
    rectImage.dstrect_window.x = 350;
    rectImage.dstrect_window.y = 150;
    rectImage.dstrect_window.w = 150;
    rectImage.dstrect_window.h = 150;
}

//function doge texture
void FuncDogeTexture(void){
    dogeTexture.texture_image2 = SDL_CreateTextureFromSurface(rend.renderer,
    doge.image2);
    dogeTexture.texture_doge_left = SDL_CreateTextureFromSurface(rend.renderer,
    doge.doge_left);
    dogeTexture.texture_doge_right = SDL_CreateTextureFromSurface(rend.renderer,
    doge.doge_right);
    dogeTexture.texture_eat = SDL_CreateTextureFromSurface(rend.renderer,
    doge.eat);
    dogeTexture.texture_dog_sleep = SDL_CreateTextureFromSurface(rend.renderer,
    doge.doge_sleep);
    dogeTexture.texture_play = SDL_CreateTextureFromSurface(rend.renderer,
    doge.doge_play);
    dogeTexture.texture_shower = SDL_CreateTextureFromSurface(rend.renderer,
    doge.shower);
    dogeTexture.texture_poop = SDL_CreateTextureFromSurface(rend.renderer,
    render.poop);
}

//function create texture
void FuncTexture(void){
    StructTexture.texture_background = SDL_CreateTextureFromSurface(rend.renderer,
    render.pinkBG);
    StructTexture.texture_floor = SDL_CreateTextureFromSurface(rend.renderer,
    render.floor);
    StructTexture.texture = SDL_CreateTextureFromSurface(rend.renderer,
    doge.image);
    StructTexture.texture_doge_bowl = SDL_CreateTextureFromSurface(rend.renderer,
    render.doge_bowl);
    StructTexture.texture_hunger = SDL_CreateTextureFromSurface(rend.renderer,
    render.Food_icon);
    StructTexture.texture_bed = SDL_CreateTextureFromSurface(rend.renderer,
    render.bed);
    StructTexture.texture_pillow = SDL_CreateTextureFromSurface(rend.renderer,
    render.pillow);
    StructTexture.texture_ball = SDL_CreateTextureFromSurface(rend.renderer,
    render.ball);
    StructTexture.texture_ball_icon = SDL_CreateTextureFromSurface(rend.renderer,
    render.ball_icon);
    StructTexture.texture_tub = SDL_CreateTextureFromSurface(rend.renderer,
    render.tub);
    StructTexture.texture_soap = SDL_CreateTextureFromSurface(rend.renderer,
    render.soap);
    StructTexture.texture_poop_icon = SDL_CreateTextureFromSurface(rend.renderer,
    render.poop);
    StructTexture.texture_tray = SDL_CreateTextureFromSurface(rend.renderer,
    render.tray);
    StructTexture.texture_start = SDL_CreateTextureFromSurface(rend.renderer,
    render.start);
    StructTexture.texture_startButton = SDL_CreateTextureFromSurface(rend.renderer,
    render.start_button);
    StructTexture.texture_dog_face = SDL_CreateTextureFromSurface(rend.renderer,
    render.dog_face);
    StructTexture.texture_press_enter = SDL_CreateTextureFromSurface(rend.renderer,
    render.press_enter);
    StructTexture.texture_restart = SDL_CreateTextureFromSurface(rend.renderer,
    render.restart);
    StructTexture.texture_ghost = SDL_CreateTextureFromSurface(rend.renderer,
    render.ghost);
    StructTexture.texture_window = SDL_CreateTextureFromSurface(rend.renderer, render.window);
    
}

//function status bar
void Dstatus(void) {
    //hunger stat
    status.rect_hunger.x = STAT_X;
    status.rect_hunger.y = 10;
    status.rect_hunger.w = STAT_W;
    status.rect_hunger.h = STAT_H;
    
    //sleep stat
    status.rect_sleep.x = STAT_X;
    status.rect_sleep.y = 30;
    status.rect_sleep.w = STAT_W;
    status.rect_sleep.h = STAT_H;
    
    //play stat
    status.rect_play.x = STAT_X;
    status.rect_play.y = 50;
    status.rect_play.w = STAT_W;
    status.rect_play.h = STAT_H;
    
    //clean stat
    status.rect_clean.x = STAT_X;
    status.rect_clean.y = 70;
    status.rect_clean.w = STAT_W;
    status.rect_clean.h = STAT_H;
    
    //poop stat
    status.rect_poop.x = STAT_X;
    status.rect_poop.y = 90;
    status.rect_poop.w = STAT_W;
    status.rect_poop.h = STAT_H;
    
}

//function render images
void tryRenderPic(void){
    render.pinkBG = SDL_LoadBMP("background.bmp");
    render.floor = SDL_LoadBMP("floor.bmp");
    render.doge_bowl = SDL_LoadBMP("dog_bowl.bmp");
    render.Food_icon = SDL_LoadBMP("Food.bmp");
    render.bed = SDL_LoadBMP("Bed.bmp");
    render.pillow = SDL_LoadBMP("Pillow.bmp");
    render.ball = SDL_LoadBMP("ball.bmp");
    render.ball_icon = SDL_LoadBMP("ball_icon.bmp");
    render.tub = SDL_LoadBMP("tub.bmp");
    render.soap  = SDL_LoadBMP("soap.bmp");
    render.poop = SDL_LoadBMP("poop.bmp");
    render.tray = SDL_LoadBMP("tray.bmp");
    render.start = SDL_LoadBMP("start.bmp");
    render.start_button = SDL_LoadBMP("startButton.bmp");
    render.dog_face = SDL_LoadBMP("dog_face.bmp");
    render.press_enter = SDL_LoadBMP("press_enter.bmp");
    render.restart = SDL_LoadBMP("restart.bmp");
    render.ghost = SDL_LoadBMP("ghost.bmp");
    render.window = SDL_LoadBMP("Window.bmp");
}

//function render doge imgaes
void tryDoge(void){
    doge.image = SDL_LoadBMP("doge.bmp");
    doge.image2 = SDL_LoadBMP("doge_flip.bmp");
    doge.doge_left  = SDL_LoadBMP("doge_stop_left.bmp");
    doge.doge_right = SDL_LoadBMP("doge_stop_right.bmp");
    doge.eat = SDL_LoadBMP("Eat.bmp");
    doge.doge_sleep= SDL_LoadBMP("doge_sleep.bmp");
    doge.doge_play = SDL_LoadBMP("dog_play.bmp");
    doge.shower  = SDL_LoadBMP("dog_shower.bmp");
}

//function free surface
void freeSurface(void){
    SDL_FreeSurface(doge.image);
    SDL_FreeSurface(render.pinkBG);
    SDL_FreeSurface(render.floor);
    SDL_FreeSurface(doge.image2);
    SDL_FreeSurface(doge.doge_right);
    SDL_FreeSurface(doge.doge_left);
    SDL_FreeSurface(render.doge_bowl);
    SDL_FreeSurface(render.Food_icon);
    SDL_FreeSurface(doge.eat);
    SDL_FreeSurface(render.bed);
    SDL_FreeSurface(doge.doge_sleep);
    SDL_FreeSurface(render.pillow);
    SDL_FreeSurface(render.ball);
    SDL_FreeSurface(doge.doge_play);
    SDL_FreeSurface(render.ball_icon);
    SDL_FreeSurface(render.tub);
    SDL_FreeSurface(doge.shower);
    SDL_FreeSurface(render.soap);
    SDL_FreeSurface(render.poop);
    SDL_FreeSurface(render.tray);
    SDL_FreeSurface(render.start);
    SDL_FreeSurface(render.start_button);
    SDL_FreeSurface(render.dog_face);
    SDL_FreeSurface(render.press_enter);
    SDL_FreeSurface(render.restart);
    SDL_FreeSurface(render.ghost);
}

//function create window
void window(void) {
    SDL_Init(SDL_INIT_VIDEO);
    rend.window = SDL_CreateWindow("The Doge",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_X, WINDOW_Y, 0);
    rend.renderer = SDL_CreateRenderer(rend.window, -1, 0);
}

//function render copy
void renderCPY(void){
    SDL_RenderClear(rend.renderer);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_start, NULL, &rectImage.dstrect_start);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_startButton, NULL, &rectImage.dstrect_start_button);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_dog_face, NULL, &rectImage.dstrect_dog_face);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_press_enter, NULL, &rectImage.dstrect_press_enter);
    SDL_RenderPresent(rend.renderer);
}

//function death
void Death(void){
    statMax.playStat = 0;
    statMax.poopStat = 0;
    statMax.sleepStat = 0;
    statMax.cleanStat = 0;
    statMax.hungerStat = 0;
}

//function check boundary
void Bondary(){
    // right boundary
    if (collisionBox.rect_doge.x + collisionBox.rect_doge.w > WINDOW_X)
        x = WINDOW_X - stopAnimation.dstrect_dog.w;

    // left boundary
    if (collisionBox.rect_doge.x < 0)
        x = 0;

    // bottom boundary
    if (collisionBox.rect_doge.y + collisionBox.rect_doge.h > WINDOW_X-150)
        y = 255;

    // upper boundary
    if (collisionBox.rect_doge.y-20 < WINDOW_Y/2)
        y = 90;
}

//function render copy
void ShowPic(void){
    SDL_RenderClear(rend.renderer);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_background, NULL, &rectImage.dstrect_background);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_floor, NULL, &rectImage.dstrect_floor);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_doge_bowl, NULL, &rectImage.dstrect_doge_bowl);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_pillow, NULL, &rectImage.dstrect_pillow);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_hunger, NULL, &rectImage.dstrect_hunger);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_bed, NULL, &rectImage.dstrect_bed);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_ball, NULL, &rectImage.dstrect_ball);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_ball_icon, NULL, &rectImage.dstrect_ball_icon);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_tub, NULL, &rectImage.dstrect_tub);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_soap, NULL, &rectImage.dstrect_soap);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_poop_icon, NULL, &rectImage.dstrect_poop_icon);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_tray, NULL, &rectImage.dstrect_tray);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_window, NULL, &rectImage.dstrect_window);
}

//function gameover
void GameOver(void){
    if(statMax.poopStat <= 0 && statMax.cleanStat <= 0 && statMax.hungerStat <= 0
       && statMax.playStat <= 0 && statMax.sleepStat <= 0)
    {
        death = true;
        screen = 2;
    }
}

//function doge walk
void DogeWalk(void){
    if(right == true && !death)
    {
        
        //Stop animation
        if(stop == true)
            SDL_RenderCopy(rend.renderer, dogeTexture.texture_doge_right, NULL, &stopAnimation.dstrect_doge_right);
        
        //Walk to the right animation
        else
            SDL_RenderCopy(rend.renderer, StructTexture.texture, &MoveSprite.srcrect_dog, &stopAnimation.dstrect_dog);
    }
    else if(left == true && !death)
    {
        
        //Stop animation
        if(stop == true)
            SDL_RenderCopy(rend.renderer, dogeTexture.texture_doge_left, NULL, &stopAnimation.dstrect_doge_left);
        
        //Walk to the left animation
        else
            SDL_RenderCopy(rend.renderer, dogeTexture.texture_image2, &MoveSprite.srcrect_dog, &stopAnimation.dstrect_dog);
    }
}

//function status decrease
void StatDecrease(void){
    //Hunger status decreasing
    if (statMax.hungerStat > 0)
        statMax.hungerStat -= calSprite.sprite/2.5;
    
    //Sleep status decreasing
    if (statMax.sleepStat > 0)
        statMax.sleepStat -= calSprite.sprite/1.5;
    
    //Play status decreasing
    if (statMax.playStat >0 )
        statMax.playStat -= calSprite.sprite;
    
    //Clean status decreasing
    if(statMax.cleanStat>0)
        statMax.cleanStat -= calSprite.sprite/2;
    
    //Poop status decreasing
    if(statMax.poopStat > 0)
        statMax.poopStat -= calSprite.sprite/3;
    
}

//function status increase
void StatIncrease(void){
    //Hunger status increasing
        if(collision.bowl && click )
        {
            click = false;
            status.rect_hunger.w = statMax.hungerStat;
            statMax.hungerStat += INCREASE;
            left = false;
            right = false;
            
            //Play effect
            Mix_PlayChannel(-1,munch,0);
        
            if (statMax.hungerStat > MAX)
                statMax.hungerStat = MAX;
        }
            
        //Sleep status increasing
        if(collision.bed && click)
        {
            click = false;
            status.rect_sleep.w = statMax.sleepStat;
            statMax.sleepStat += INCREASE;
            left = false;
            right = false;
            
            //Play effect
            Mix_PlayChannel(-1,snore,0);
            
            if (statMax.sleepStat > MAX)
                statMax.sleepStat = MAX;
        }
        
        //Play status increasing
        if(collision.ball && click )
        {
            click = false;
            status.rect_play.w = statMax.playStat;
            statMax.playStat += INCREASE;
            left = false;
            right = false;
            
            //Play effect
            Mix_PlayChannel(-1,bouncing,0);

            if (statMax.playStat > MAX)
                statMax.playStat = MAX;
        }
        
        //Clean status increasing
        if(collision.bath && click )
        {
            click = false;
            status.rect_clean.w = statMax.cleanStat;
            statMax.cleanStat += INCREASE;
            left = false;
            right = false;
            
            //Play effect
            Mix_PlayChannel(-1,water,0);
            
            if(statMax.cleanStat > MAX)
                statMax.cleanStat = MAX;
        }
        
        //Poop status increasing
        if(collision.pooping && click)
        {
            
            //Play effect
            Mix_PlayChannel(0,fart,0);
            
            dog_poop = true;
            statMax.poopStat = MAX;
            if(dog_poop == true)
            {
                SDL_RenderCopy(rend.renderer, dogeTexture.texture_poop, NULL, &rectImage.dstrect_poop);
                dog_poop = false;
            }
        }
    
}

//function collision
void CollisionAnimation(void){
    //Hunger
    if(left == false && right == false && collision.bowl)
        SDL_RenderCopy(rend.renderer, dogeTexture.texture_eat, &MoveSprite.srcrect_dog, &stopAnimation.dstrect_dog);
    
    //Sleep
    else if (left == false && right == false && collision.bed)
        SDL_RenderCopy(rend.renderer, dogeTexture.texture_dog_sleep, &MoveSprite.srcrect_sleep, &rectImage.dstrect_dog_sleep);
    
    //Play
    else if (left == false && right == false && collision.ball)
        SDL_RenderCopy(rend.renderer, dogeTexture.texture_play, &MoveSprite.srcrect_play, &rectImage.dstrect_play);
    
    //Bath
    else if (left == false && right == false && collision.bath)
        SDL_RenderCopy(rend.renderer, dogeTexture.texture_shower, &MoveSprite.srcrect_shower, &rectImage.dstrect_shower);
}
void Collider(void){
    if(show_collision == true)
    {
                   
        //Rect dog
        SDL_SetRenderDrawColor(rend.renderer, 255, 100,100, 255);
        SDL_RenderFillRect(rend.renderer, &collisionBox.rect_doge);
        
        //Rect bowl
        SDL_SetRenderDrawColor(rend.renderer, 255, 100,100, 255);
        SDL_RenderFillRect(rend.renderer, &collisionBox.rect_bowl);
                   
        //Rect ball
        SDL_SetRenderDrawColor(rend.renderer, 255, 100,100, 255);
        SDL_RenderFillRect(rend.renderer, &collisionBox.rect_ball);
                   
        //Rect bed
        SDL_SetRenderDrawColor(rend.renderer, 255, 100,100, 255);
        SDL_RenderFillRect(rend.renderer, &collisionBox.rect_bed);
                   
        //Rect tub
        SDL_SetRenderDrawColor(rend.renderer, 255, 100,100, 255);
        SDL_RenderFillRect(rend.renderer, &collisionBox.rect_tub);
                   
        //Rect tray
        SDL_SetRenderDrawColor(rend.renderer, 255, 100,100, 255);
        SDL_RenderFillRect(rend.renderer, &collisionBox.rect_tray);
                   
    }
}

//function status bar
void StatusBar(void){
    //hunger status
     SDL_SetRenderDrawColor(rend.renderer, 255, 100,100, 255);
     status.rect_hunger.w = statMax.hungerStat/10;
     SDL_RenderFillRect(rend.renderer, &status.rect_hunger);
     
     //sleep status
     SDL_SetRenderDrawColor(rend.renderer, 100, 100, 255, 255);
     status.rect_sleep.w = statMax.sleepStat/10;
     SDL_RenderFillRect(rend.renderer, &status.rect_sleep);
     
     //play status
     SDL_SetRenderDrawColor(rend.renderer, 100, 255, 100, 255);
     status.rect_play.w = statMax.playStat/10;
     SDL_RenderFillRect(rend.renderer, &status.rect_play);
     
     //clean status
     SDL_SetRenderDrawColor(rend.renderer, 255, 255, 100, 255);
     status.rect_clean.w = statMax.cleanStat/10;
     SDL_RenderFillRect(rend.renderer, &status.rect_clean);
    
     //poop status
     SDL_SetRenderDrawColor(rend.renderer, 100, 255, 255, 255);
     status.rect_poop.w = statMax.poopStat/10;
     SDL_RenderFillRect(rend.renderer, &status.rect_poop);
}

//function death screen
void ShowDeath(void){
    SDL_RenderClear(rend.renderer);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_start, NULL, &rectImage.dstrect_start);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_restart, NULL, &rectImage.dstrect_restart);
    SDL_RenderCopy(rend.renderer, StructTexture.texture_ghost, NULL, &rectImage.dstrect_ghost);
    SDL_RenderPresent(rend.renderer);
}

//function cleanup music
void CleanMusic(void){
    Mix_FreeChunk(water);
    Mix_FreeChunk(munch);
    Mix_FreeChunk(fart);
    Mix_FreeChunk(snore);
    Mix_FreeChunk(bouncing);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
}

//function cleanup SDL
void CleanUpSDL(void){
    SDL_DestroyTexture(StructTexture.texture);
    SDL_DestroyTexture(StructTexture.texture_bed);
    SDL_DestroyTexture(dogeTexture.texture_eat);
    SDL_DestroyTexture(StructTexture.texture_tub);
    SDL_DestroyTexture(StructTexture.texture_ball);
    SDL_DestroyTexture(dogeTexture.texture_play);
    SDL_DestroyTexture(dogeTexture.texture_poop);
    SDL_DestroyTexture(StructTexture.texture_soap);
    SDL_DestroyTexture(StructTexture.texture_tray);
    SDL_DestroyTexture(StructTexture.texture_floor);
    SDL_DestroyTexture(StructTexture.texture_hunger);
    SDL_DestroyTexture(dogeTexture.texture_image2);
    SDL_DestroyTexture(StructTexture.texture_pillow);
    SDL_DestroyTexture(dogeTexture.texture_shower);
    SDL_DestroyTexture(StructTexture.texture_ball_icon);
    SDL_DestroyTexture(dogeTexture.texture_dog_sleep);
    SDL_DestroyTexture(StructTexture.texture_doge_bowl);
    SDL_DestroyTexture(dogeTexture.texture_doge_left);
    SDL_DestroyTexture(StructTexture.texture_poop_icon);
    SDL_DestroyTexture(StructTexture.texture_background);
    SDL_DestroyTexture(dogeTexture.texture_doge_right);
    SDL_DestroyTexture(StructTexture.texture_ghost);
    SDL_DestroyTexture(StructTexture.texture_restart);
    SDL_DestroyTexture(StructTexture.texture_press_enter);
    SDL_DestroyTexture(StructTexture.texture_dog_face);
    SDL_DestroyTexture(StructTexture.texture_startButton);
    SDL_DestroyTexture(StructTexture.texture_start);

    SDL_DestroyRenderer(rend.renderer);
    SDL_DestroyWindow(rend.window);
    SDL_Quit();
}

//function key input (strart screen)
void KeyInput_screen0(void){
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        quit = true;
        break;
            
    case SDL_KEYDOWN:
    
        switch (event.key.keysym.sym)
        {
            case SDLK_RETURN:
                screen = 1;
                break;
        }
            break;
    }
}

//function key input (screen2)
void KeyInput_screen1(void){
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        quit = true;
        break;
    
    //Handling Keyboard Event
    case SDL_KEYDOWN:
    
        switch (event.key.keysym.sym)
        {
            //Left arrow
            case SDLK_LEFT:
                left = true;
                right = false;
                stop = false;
                x-=5;
                break;
                
            //Right arrow
            case SDLK_RIGHT:
                left = false;
                right = true;
                stop = false;
                x+=5;
                break;
                
            //Up arrow
            case SDLK_UP:
                stop = false;
                right = true;
                y-=5;
                break;
                
            //Down arrow
            case SDLK_DOWN:
                stop = false;
                left = true;
                y+=5;
                break;

            //Y
            case SDLK_y:
                start_over = true;
                break;
                
            //Spacebar
            case SDLK_SPACE:
                click = true;
                break;
            
            case SDLK_1:
                show_collision = true;
                break;
            
            case SDLK_2:
                Death();
                break;
                
            default:
                stop = false;
                
        }
            
    break;
        case SDL_KEYUP:
            show_collision = false;
            stop = true;
            dog_poop = false;
            break;
    }
}

//function key input (Death screen)
void KeyInput_screen2(void){
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        quit = true;
            
        break;
    case SDL_KEYDOWN:
    
        switch (event.key.keysym.sym)
        {
            case SDLK_RETURN:
                screen = 1;
                Maxstat();
                death = false;
                break;
        }
            break;
    }
}

//main
int main(int argc, char ** argv)
{
    //Import images file
    tryRenderPic();
    tryDoge();
    
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    //Import music file
    music = Mix_LoadMUS("sound1.wav");
    water = Mix_LoadWAV("water.wav");
    munch = Mix_LoadWAV("Munch.wav");
    fart = Mix_LoadWAV("Bloop.wav");
    snore = Mix_LoadWAV("Snore.wav");
    bouncing = Mix_LoadWAV("bouncing.wav");
    
    //Play music
    Mix_PlayMusic(music, -1);
    
    //Status max when start game
    Maxstat();
    
    //Create SDL window
    window();
    
    //SDL Texture
    FuncTexture();
    FuncDogeTexture();
    freeSurface();
    
    // handle events
    SDL_SetRenderDrawColor(rend.renderer, 168, 230, 255, 255);
    SDL_RenderClear(rend.renderer);
    
    //Rect Status( Position and width and hight of status)
    Dstatus();
    
    //Position and width and hight of images
    FuncRectImage();
    
    //Game loop
    while (!quit)
    {
        //Start screen
        if(screen == 0)
        {
            KeyInput_screen0();
            renderCPY();
        }
        
        //Play screen
        else if(screen == 1)
        {
            //Stop animation
            stop = true;
            FuncStopAnimation();
            
            //Calulate Sprite sheet
            FuncCalSprite();
            
            //Move sprite sheet
            FuncMoveSprite();
            
            //Rect doge
            FunccollisionBox();
          
            //Collision
            FuncCollision();
            
            KeyInput_screen1();
            
            //Check bondary
            Bondary();

            //SDL RenderCopy
            //Show Images
            ShowPic();
            
            //Game over
            GameOver();
            
            //Dog walk animation
            DogeWalk();
            
            //Stat decrease
            StatDecrease();

            //Stat increase
            StatIncrease();
            
            //Collision animation
            CollisionAnimation();

            //Square check collision
            Collider();
            
            //Status bar
            StatusBar();
            
            SDL_RenderPresent(rend.renderer);
            // calculates to 60 fps
            SDL_Delay(1000 / 60);
            }
            
        //Death screen
        else if(screen == 2)
        {
            KeyInput_screen2();
            ShowDeath();
        }
    }
    
    //cleanup music
    CleanMusic();
 
    // cleanup SDL
    CleanUpSDL();
 
    return 0;
}
