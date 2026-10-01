/**

* Author: Wasi Genius

* Assignment: Pong Clone

* Date due: Simple 2D Scene

* I pledge that I have completed this assignment without

* collaborating with anyone else, in conformance with the

* NYU School of Engineering Policies and Procedures on

* Academic Misconduct.

**/

// Includes the course's raylib helper definitions, such as AppStatus and ColorFromHex.
#include "CS3113/cs3113.h"
#include "math.h"

// Global constants are values shared throughout this file that do not change while the game runs.
// constexpr asks C++ to determine these values at compile time when possible.
constexpr int SCREEN_WIDTH = 1600,
              SCREEN_HEIGHT = 900,
              FPS = 60;

// The background color is written as a hexadecimal color string and converted by ColorFromHex().
constexpr char BG_COLOUR[] = "#B2AAC6";

// Global variables hold state that multiple game functions need to read or change.
// RUNNING and TERMINATED are status values supplied by the course helper library.
AppStatus gAppStatus = RUNNING;

// The image file loaded as the sprite. The path is relative to the program's working directory.
constexpr char Verity[] = "verity.png";

// Vector2 is raylib's two-number type, commonly used for positions and sizes.
// ORIGIN is the center point of the window; dividing by 2.0f makes floating-point coordinates.
constexpr Vector2 ORIGIN = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};

// The texture starts at this width and height, measured in screen pixels when drawn.
constexpr Vector2 BASE_SIZE = {500.0f, 500.0f};

// Texture2D stores the image data raylib needs to draw a texture.
// It is filled in initialise() after the graphics window exists.
Texture2D gTexture;

// These values describe the sprite's current drawing position and size.
// Starting at ORIGIN and BASE_SIZE gives the sprite its initial placement and dimensions.
Vector2 gPosition = ORIGIN;
Vector2 gScale = BASE_SIZE;

// DrawTexturePro() uses this angle in degrees. Zero means no rotation.
constexpr float gAngle = 0.0f;

// gPulseTime is the animation's running phase, measured in radians for cos().
float gPulseTime = 0.0f;

// The maximum amount added to or subtracted from the base width and height.
float MAX_AMP = 100.0f;

// Stores the previous GetTime() result so update() can calculate time between frames.
float gPrevTicks = 0.0f;

// Function declarations tell the compiler these functions exist before their definitions below.
// Keeping the game loop split into stages makes input, simulation, drawing, and cleanup easier to follow.
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Set up the window and graphics resources before entering the game loop.
void initialise()
{
    // Create the raylib window. Drawing and input happen through this window.
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures & Delta Time");

    // Load the image from disk into a GPU-ready raylib texture.
    gTexture = LoadTexture(Verity);

    // Ask raylib to aim for this many frames per second; update() still uses elapsed time
    // so the animation speed does not depend on hitting this exact frame rate.
    SetTargetFPS(FPS);
}

// Read player/window input. This example only checks whether the window should close.
void processInput()
{
    // WindowShouldClose() is raylib's standard close/quit check.
    // Changing the status makes the while loop in main() stop on its next check.
    if (WindowShouldClose())
        gAppStatus = TERMINATED;
}

// Advance the animation state. This function changes values but does not draw anything.
void update()
{

    // GetTime() returns seconds since the program started.
    float ticks = static_cast<float>(GetTime());

    // Delta time is the time elapsed since the previous update, in seconds.
    // Using it makes motion time-based instead of moving a fixed amount per frame.
    float deltaTime = ticks - gPrevTicks;

    // Save this frame's time so the next update can calculate its own delta time.
    gPrevTicks = ticks;

    // Advance the animation phase at 5 radians per second (5 * seconds elapsed).
    gPulseTime += 5.0f * deltaTime;

    // Cosine smoothly moves between -1 and +1. Multiplying by MAX_AMP makes
    // the sprite vary by up to 100 pixels around its 500-pixel base size.
    // Applying the same calculation to x and y keeps the sprite's proportions square.
    gScale = {
        BASE_SIZE.x + MAX_AMP * cos(gPulseTime),
        BASE_SIZE.y + MAX_AMP * cos(gPulseTime)};
}

void render()
{
    // Begin a frame. Raylib collects the drawing commands until EndDrawing().
    BeginDrawing();

    // Clear the previous frame so old pixels do not remain behind the new drawing.
    ClearBackground(ColorFromHex(BG_COLOUR));

    // This source rectangle selects which part of the loaded image to use.
    // Starting at (0, 0) and using the texture's full width and height selects all of it.
    Rectangle textureArea = {
        0.0f, 0.0f,
        static_cast<float>(gTexture.width),
        static_cast<float>(gTexture.height)};

    // This destination rectangle says where and how large the selected image should appear.
    // gPosition is the rectangle's anchor position; gScale supplies its current dimensions.
    Rectangle destinationArea = {
        gPosition.x,
        gPosition.y,

        static_cast<float>(gScale.x),
        static_cast<float>(gScale.y)};

    // DrawTexturePro() positions the destination rectangle relative to an origin offset.
    // Half the width and height makes that origin its center, so the sprite pulses around
    // gPosition instead of appearing to grow only down and to the right.
    Vector2 originOffset = {
        static_cast<float>(gScale.x) / 2.0f,
        static_cast<float>(gScale.y) / 2.0f};

    // Draw the texture: source area, destination area, center offset, rotation, and tint color.
    // WHITE means no color tint is applied to the original image.
    DrawTexturePro(
        gTexture,
        textureArea,
        destinationArea,
        originOffset,
        gAngle,
        WHITE);

    // Finish presenting this frame and let raylib apply frame timing as needed.
    EndDrawing();
}

// Release resources when the game loop has ended.
void shutdown()
{
    // Close the raylib window and release the loaded image texture.
    CloseWindow();
    UnloadTexture(gTexture);
}

// The program starts here. int main(void) means main takes no arguments and returns an integer.
int main(void)
{
    // Create the window and load the texture before any update or drawing calls.
    initialise();

    // The game loop repeats input, update, and render while the app is still running.
    // This repeated cycle is the basic structure used by many real-time games.
    while (gAppStatus == RUNNING)
    {
        // Handle events first, then update the game's state, then draw that state.
        processInput();
        update();
        render();
    }

    // Clean up after the loop so resources are not left allocated.
    shutdown();

    // Return 0 to tell the operating system the program finished successfully.
    return 0;
}
