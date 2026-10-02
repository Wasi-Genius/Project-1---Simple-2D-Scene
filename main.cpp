/**

* Author: Wasi Genius

* Assignment: Pong Clone

* Date due: Simple 2D Scene

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

#include "CS3113/cs3113.h"
#include "math.h"

constexpr int SCREEN_WIDTH = 1600,
              SCREEN_HEIGHT = 900,
              FPS = 60;

constexpr char BG_COLOUR[] = "#B2AAC6";

AppStatus gAppStatus = RUNNING;

// Sun Image
constexpr char Sun[] = "assets/sun.png";

// Moon Image
constexpr char Moon[] = "assets/moon.png";

// Verity image
constexpr char Verity[] = "assets/verity.png";

Vector2 ORIGIN = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};

// The texture starts at this width and height, measured in screen pixels when drawn.
constexpr Vector2 BASE_SIZE = {500.0f, 500.0f};

// Sun Texture Info
// Texture2D stores the image data raylib needs to draw a texture.
Texture2D gSunTexture;
Vector2 gSunPosition = ORIGIN;
Vector2 gSunScale = BASE_SIZE;
float gSunAngle = 0.0f;
float gSunPulseTime = 0.0f;

// Moon Texture Info
Texture2D gMoonTexture;
Vector2 gMoonPosition = {(SCREEN_WIDTH / 2.0f) + 500.0f, SCREEN_HEIGHT / 2.0f};
Vector2 gMoonScale = BASE_SIZE;
float gMoonAngle = 0.0f;
float gMoonPulseTime = 0.0f;

// Verity Texture Info
Texture2D gVerityTexture;
Vector2 gVerityPosition = {(SCREEN_WIDTH / 2.0f) - 500.0f, SCREEN_HEIGHT / 2.0f};
Vector2 gVerityScale = BASE_SIZE;
float gVerityAngle = 0.0f;
float gVerityPulseTime = 0.0f;

float MAX_AMP = 100.0f;

float gPrevTicks = 0.0f;

void initialise();
void processInput();
void update();
void render();
void shutdown();

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures & Delta Time");

    gSunTexture = LoadTexture(Sun);
    gMoonTexture = LoadTexture(Moon);
    gVerityTexture = LoadTexture(Verity);

    SetTargetFPS(FPS);
}

void processInput()
{
    if (WindowShouldClose())
        gAppStatus = TERMINATED;
}

void update()
{
    float ticks = static_cast<float>(GetTime());

    float deltaTime = ticks - gPrevTicks;

    gPrevTicks = ticks;

    gSunPulseTime += 5.0f * deltaTime;
    gMoonPulseTime += 5.0f * deltaTime;
    gVerityPulseTime += 5.0f * deltaTime;

    gSunScale = {
        BASE_SIZE.x + MAX_AMP * cos(gSunPulseTime),
        BASE_SIZE.y + MAX_AMP * cos(gSunPulseTime)};

    gMoonScale = {
        BASE_SIZE.x + MAX_AMP * cos(gMoonPulseTime),
        BASE_SIZE.y + MAX_AMP * cos(gMoonPulseTime)};

    gVerityScale = {
        BASE_SIZE.x + MAX_AMP * cos(gVerityPulseTime),
        BASE_SIZE.y + MAX_AMP * cos(gVerityPulseTime)};
}

void render()
{
    BeginDrawing();

    ClearBackground(ColorFromHex(BG_COLOUR));

    // Rectangle areas where the images will appear.
    Rectangle textureSunArea = {
        0.0f, 0.0f,
        static_cast<float>(gSunTexture.width),
        static_cast<float>(gSunTexture.height)};

    Rectangle textureMoonArea = {
        0.0f, 0.0f,
        static_cast<float>(gMoonTexture.width),
        static_cast<float>(gMoonTexture.height)};

    Rectangle textureVerityArea = {
        0.0f, 0.0f,
        static_cast<float>(gVerityTexture.width),
        static_cast<float>(gVerityTexture.height)};

    Rectangle destinationSunArea = {
        gSunPosition.x,
        gSunPosition.y,

        static_cast<float>(gSunScale.x),
        static_cast<float>(gSunScale.y)};

    Rectangle destinationMoonArea = {
        gMoonPosition.x,
        gMoonPosition.y,

        static_cast<float>(gMoonScale.x),
        static_cast<float>(gMoonScale.y)};

    Rectangle destinationVerityArea = {
        gVerityPosition.x,
        gVerityPosition.y,

        static_cast<float>(gVerityScale.x),
        static_cast<float>(gVerityScale.y)};

    Vector2 originOffset = {
        static_cast<float>(gSunScale.x) / 2.0f,
        static_cast<float>(gSunScale.y) / 2.0f};

    // Draw the images onto the screen

    DrawTexturePro(
        gSunTexture,
        textureSunArea,
        destinationSunArea,
        originOffset,
        gSunAngle,
        WHITE);

    DrawTexturePro(
        gMoonTexture,
        textureMoonArea,
        destinationMoonArea,
        originOffset,
        gMoonAngle,
        WHITE);

    DrawTexturePro(
        gVerityTexture,
        textureVerityArea,
        destinationVerityArea,
        originOffset,
        gVerityAngle,
        WHITE);

    EndDrawing();
}

void shutdown()
{
    CloseWindow();
    UnloadTexture(gSunTexture);
    UnloadTexture(gMoonTexture);
    UnloadTexture(gVerityTexture);
}

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}
