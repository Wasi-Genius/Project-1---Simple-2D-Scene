/**

* Author: Wasi Genius

* Assignment: Pong Clone

* Date due: Simple 2D Scene

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

/*

Completed:
- The Sun Will be Scaling and moving in a up and down wave pattern and back and forth along the x-axis.

To-Do:
- The moon will move in relative position to the sun.
- - The moon will be doing the orbiting around the sun.
- The verity will be zig zagging around the screen and rotating.
*/

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
constexpr Vector2 BASE_SIZE = {400.0f, 400.0f};

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
Vector2 gMoonScale = {250.0f, 250.0f};
float gMoonAngle = 0.0f;
float gMoonPulseTime = 0.0f;

// Verity Texture Info
Texture2D gVerityTexture;
Vector2 gVerityPosition = {(SCREEN_WIDTH / 2.0f) - 500.0f, (SCREEN_HEIGHT / 2.0f) - 200.0f};
Vector2 gVerityScale = {150.0f, 150.0f};
float gVerityAngle = 0.0f;
float gVerityPulseTime = 0.0f;

// Background Texture Info
constexpr char Background[] = "assets/space background.png";
Texture2D gBackgroundTexture;

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
    gBackgroundTexture = LoadTexture(Background);

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

    gSunPulseTime += 2.0f * deltaTime;
    gMoonPulseTime += 3.0f * deltaTime;
    gVerityPulseTime += 3.0f * deltaTime;

    // Sun Pulsing Affect
    gSunScale = {
        BASE_SIZE.x + MAX_AMP * cos(gSunPulseTime),
        BASE_SIZE.y + MAX_AMP * cos(gSunPulseTime)};

    // Sun Translation Affect (Moving up and down in a curve along the x-axis)
    gSunPosition.x = ORIGIN.x + 550.0f * sin(gSunPulseTime);
    gSunPosition.y = ORIGIN.y + MAX_AMP * sin((gSunPosition.x - ORIGIN.x) / 70.0f);

    // Moon orbiting around the sun
    gMoonPosition.x = gSunPosition.x + 350.0f * cos(gMoonPulseTime);
    gMoonPosition.y = gSunPosition.y + 350.0f * sin(gMoonPulseTime);

    // Verity rotating
    gVerityAngle += gVerityPulseTime * 0.03f;

    // Verity motion
    gVerityPosition.x = ORIGIN.x + 400.0f * sin(gVerityPulseTime);
    gVerityPosition.y = ORIGIN.y + 400.0f * sin(gVerityPulseTime);
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

    Rectangle textureBackgroundArea = {
        0.0f, 0.0f,
        static_cast<float>(gBackgroundTexture.width),
        static_cast<float>(gBackgroundTexture.height)};

    Rectangle destinationBackgroundArea = {
        0.0f, 0.0f,
        static_cast<float>(SCREEN_WIDTH),
        static_cast<float>(SCREEN_HEIGHT)};

    Vector2 originSunOffset = {
        static_cast<float>(gSunScale.x) / 2.0f,
        static_cast<float>(gSunScale.y) / 2.0f};

    Vector2 originMoonOffset = {
        static_cast<float>(gMoonScale.x) / 2.0f,
        static_cast<float>(gMoonScale.y) / 2.0f};

    Vector2 originVerityOffset = {
        static_cast<float>(gVerityScale.x) / 2.0f,
        static_cast<float>(gVerityScale.y) / 2.0f};

    // Draw the images onto the screen

    DrawTexturePro(
        gBackgroundTexture,
        textureBackgroundArea,
        destinationBackgroundArea,
        {0.0f, 0.0f},
        0.0f,
        WHITE);

    DrawTexturePro(
        gVerityTexture,
        textureVerityArea,
        destinationVerityArea,
        originVerityOffset,
        gVerityAngle,
        WHITE);

    DrawTexturePro(
        gSunTexture,
        textureSunArea,
        destinationSunArea,
        originSunOffset,
        gSunAngle,
        WHITE);

    DrawTexturePro(
        gMoonTexture,
        textureMoonArea,
        destinationMoonArea,
        originMoonOffset,
        gMoonAngle,
        WHITE);

    EndDrawing();
}

void shutdown()
{
    CloseWindow();
    UnloadTexture(gSunTexture);
    UnloadTexture(gMoonTexture);
    UnloadTexture(gVerityTexture);
    UnloadTexture(gBackgroundTexture);
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
