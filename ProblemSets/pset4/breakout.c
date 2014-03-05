//
// breakout.c
//
// Computer Science 50
// Problem Set 4
// timothy lewis
// tim@tolewis.com
// *** to endable god-mode use "./breakout -god"
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// paddle width
#define pWidth 60

// paddle height
#define pHeight 5

// brick width
#define bWidth 34.5

//brick height
#define bHeight 8

//brick horizontal spacing
#define bSpacing 5

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);
int godMode(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // velocity of ball
    double rVelocity = drand48();
    double xVelocity = rVelocity/4;
    double yVelocity = rVelocity;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // implement godMode
        if (argc == 2)
        {
            char* key = argv[1];
            
            // if the god mode argument was given
            if (strcmp(key, "-god") == 0)
            {
                // ensure paddle follows ball
                double x = getX(ball) - pWidth / 2;
                double y = getHeight(window) - (getHeight(window) / 8);
                setLocation(paddle, x, y);
            } 
            
        }
        else if (argc == 1)
        {
        // check for mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
        
            // if we heard one
            if (event != NULL)
            {
                // if the event was movement
                if (getEventType(event) == MOUSE_MOVED)
                {
                    // ensure paddle follows cursor
                    double x = getX(event) - pWidth / 2;
                    double y = getHeight(window) - (getHeight(window) / 8);
                    setLocation(paddle, x, y);
                }
            }
        }
        //movement of ball
        move(ball, xVelocity, yVelocity);
        
        //detect collision
        GObject object = detectCollision(window, ball);
        
        // if we have a collision
        if (object != NULL)
        {
            //detect collision with paddle
            if (object == paddle)
            {
                yVelocity = -yVelocity;
            }
            
            //detect collision with brick
            else if (strcmp(getType(object), "GRect") == 0)
            {
                yVelocity = -yVelocity;
                removeGWindow(window, object);
                points++;
                bricks--;
                updateScoreboard(window, label, points);
            }
        }    
        //bounce off left or right edges
        if ((getX(ball) + getWidth(ball)) >= getWidth(window) || getX(ball) <= 0)
        {
            xVelocity = -xVelocity;
        }
         //bounce off top edge
        else if (getY(ball) <= 0)
        {
            yVelocity = -yVelocity;
        }
        else if ((getY(ball) + getHeight(ball)) >= getHeight(window))
        {
            // move ball to center of window
            setLocation(ball, (getWidth(window) - getWidth(ball)) / 2, (getHeight(window) - getHeight(ball)) / 2);

            // Loose 1 life
            lives--;
            printf("YOU LOOSE A LIFE!!! lives = %d\n", lives);
            
            // wait for click to restart game
            waitForClick();
        }
        pause(2);
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            GRect rect = newGRect(bSpacing + (j * (bSpacing + bWidth)), 50 + (i * 15), bWidth, bHeight);
            setFilled(rect, true);
            char* brickColors[10] = {"BLUE", "CYAN", "DARK_GRAY", "GREEN", "LIGHT_GRAY", "MAGENTA", "ORANGE", "PINK", "RED", "YELLOW"};
            setColor(rect, brickColors[i]);
            add(window, rect);
        }
    }

}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval oval = newGOval((WIDTH - 15) / 2, (HEIGHT - 15) / 2, 15, 15);
    setFilled(oval, true);
    setColor(oval, "RED");
    add(window, oval);
    return oval;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect rect = newGRect((getWidth(window) - pWidth) / 2, getHeight(window) - (getHeight(window) / 8), pWidth, pHeight);
    setFilled(rect, true);
    setColor(rect, "BLACK");
    add(window, rect);
    return rect;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    //create label for keeping track of points
    char* points = "0";
    GLabel label = newGLabel(points);
    
    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
    
    // format label    
    setColor(label, "GRAY");
    setFont(label, "FreeSans-bold-45");
    
    //add label to window
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
 
