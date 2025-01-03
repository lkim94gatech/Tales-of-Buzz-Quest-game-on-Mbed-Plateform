//=================================================================
// The speech class file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#include "speech.h"

#include "globals.h"
#include "hardware.h"

///////////////////////////////
//Static function declarations
///////////////////////////////
/**
 * Draw the speech bubble background.
 */
static void draw_speech_bubble();

/**
 * Erase the speech bubble.
 */
static void erase_speech_bubble();

/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_speech_line(const char* line, int which);


///////////////////////////////
//Drawing function declarations
///////////////////////////////


//***
// HINT: for this function and below: Check out the ULCD demo in the docs to see what
// uLCD methods you can use to draw graphics 

//Link: https://os.mbed.com/users/4180_1/notebook/ulcd-144-g2-128-by-128-color-lcd/
//***


void draw_speech_bubble()
{
    //****************
    // TODO: Implement
    //****************
    uLCD.filled_rectangle(1, 90, 126, 118, WHITE); // White border
    uLCD.filled_rectangle(2, 91, 125, 117, BLACK); // Black interior
    //1. Draw a speech bubble at the bottom of the screen 
    // Hint: You can stack ULCD rectangles to make a border
    
}

void erase_speech_bubble()
{
    //****************
    // TODO: Implement
    //****************
     uLCD.filled_rectangle(1, 90, 126, 118, BLACK); // Overwrite with black rectangle
    //1. Erase the speech bubble at the bottom of the screen
    // Hint: You can overwrite the bubble with a empty (black) one
}

void draw_speech_line(const char* line, int which)
{
    //****************
    // TODO: Implement
    //****************
    //1. Set the location which line of text will go the uLCD
    // Hint: Change the y coordinate based on which line (top or bottom)
    int y = (which == TOP) ? 12 : 13;
    uLCD.locate(2, y);
    uLCD.textbackground_color(BLACK);
    uLCD.color(WHITE);
    uLCD.text_width(1);
    uLCD.text_height(1);

    
    for (int i = 0; line[i] && i < 17; i++)
    {
        //TODO: Write the character
        uLCD.printf("%c", line[i]); // Write each character
        wait_ms(75); 
    }
}

void speech_bubble_wait(GameInputs inputs)
{
    //****************
    // TODO: Implement
    //****************
        while(!inputs.b1) { // Wait until the action button is pressed
        wait_ms(50); // Polling interval
    }
    // 1. Keep waiting until the action button is pressed 
    //   Hint: What type of loop can we use to stay until a condition is met?

}

void speech(const char* line1, const char* line2, GameInputs inputs)
{
    //****************
    // TODO: Implement
    //****************
    const char* lines[] = {line1, line2};
    long_speech(lines, 2, inputs); // Display both lines
    // 1. Place the two lines into an array of lines
    // 2. Pass in to long_speech with the corresponding number of lines
}

void long_speech(const char* lines[], int n, GameInputs inputs)
{

    //****************
    // TODO: Implement
    //****************
     draw_speech_bubble();
    for (int i = 0; i < n; i += 2) {
        if (i < n) {
            draw_speech_line(lines[i], TOP);
        }
        if (i + 1 < n) {
            draw_speech_line(lines[i + 1], BOTTOM);
        }
        speech_bubble_wait(inputs); // Wait for player to press action button
        erase_speech_bubble();
    }

    //1. Create a speech bubble

    //2. For each lines, display only two lines at a time
    //   If two lines are displayed, make sure to wait (call the wait function)

    //3. Erase the speech bubble when you are done

}
