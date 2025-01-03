//=================================================================
// The main program file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


// Projet includes
#include "globals.h"
#include "hardware.h"
#include "hash_table.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"
#include <math.h>

#define CITY_HIT_MARGIN 1
#define CITY_UPPER_BOUND (SIZE_Y-(LANDSCAPE_HEIGHT+MAX_BUILDING_HEIGHT))

// Helper function declarations
void playSound(char* wav);


/////////////////////////
// Struct of Player 
/////////////////////////

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;            // Current locations
    int speed;
    int px, py;         // Previous locations
    bool has_key;       // flag when obtained the key
    bool game_solved;   // flag when game is complete
    bool talked_to_npc; // flag when you've talked to npc
    int lives;
    int potions;
    bool visible;
    //You will need to add more flags as needed

} Player;


/////////////////////////
// Get Action
/////////////////////////

#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define ATTACK_BUTTON 3
#define GO_LEFT 4
#define GO_RIGHT 5
#define GO_UP 6
#define GO_DOWN 7
#define GO_IN 8
#define SPECIAL_ATTACK 9


int get_action(GameInputs inputs)
{
    //******************
    // TODO: Implement
    //******************

    if (inputs.b1) return ACTION_BUTTON;
    if (inputs.b2) return MENU_BUTTON;
    if (inputs.b3) return ATTACK_BUTTON;
    if (inputs.b4) return SPECIAL_ATTACK;

    if (inputs.ns_left) return GO_LEFT;
    if (inputs.ns_right) return GO_RIGHT;
    if (inputs.ns_up) return GO_UP;
    if (inputs.ns_down) return GO_DOWN;
    if (inputs.ns_center) return GO_IN;

    return NO_ACTION;
}




/////////////////////////
// Helper Functions:
/////////////////////////
// Feel free to define any helper functions here for update game





/////////////////////////
// Update Game
/////////////////////////

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
#define MAP_WIDTH 50

enum MenuOption {
    START_GAME,
    VIEW_CONTROLS,
    EXIT
};
bool gamePaused = false;
bool bossDead = false;

void startScreen();
void controls();
MenuOption menuInput();

void startScreen() {
    uLCD.cls();
    uLCD.locate(2, 2);
    uLCD.printf("Tales Of BUZZ\n");
    uLCD.printf("b1. Start Game\n");
    uLCD.printf("b2. View Controls\n");
    uLCD.printf("b3. Exit\n");
}

void controls() {
    uLCD.cls();
    uLCD.locate(2, 2);
    uLCD.printf("Controls:\n");
    uLCD.printf("Move: Nav switch\n");
    uLCD.printf("Select/Talk: B1\n");
    uLCD.printf("Back: B2\n");
    uLCD.printf("ATTACK: B3\n");
    uLCD.printf("\n");
    uLCD.printf("\n");
    uLCD.printf("\n");
    uLCD.printf("\n");
    uLCD.printf("b2 to go back\n");

while (true) {
        GameInputs inputs = read_inputs();
        if (inputs.b2) {
            break;
        }
        wait_ms(100); 
    }
}

MenuOption menuInput() {
GameInputs inputs = read_inputs();

    while (true) {
        inputs = read_inputs(); // Update the inputs

        if (inputs.b1) return START_GAME;
        if (inputs.b2) return VIEW_CONTROLS;
        if (inputs.b3) return EXIT;

        wait_ms(50);
    }
}

    enum GameMenuOption {
        CONTINUE_GAME,
        CHANGE_SPEED,
        VIEW_CONTROL_MENU,
        INVENTORY,
        EXIT_GAME
    };

    GameMenuOption showMenu() {
        gamePaused = true;
        uLCD.cls();
        uLCD.locate(2, 2);
        uLCD.printf("Game Menu\n");
        uLCD.printf("b1. Continue Game\n");
        uLCD.printf("b2. Change Speed\n");
        uLCD.printf("b3. View Controls\n");
        uLCD.printf("center. Inventory\n");
        uLCD.printf("b4. Exit Game\n");

        GameMenuOption selectedOption;
        while (1) {
            GameInputs inputs = read_inputs();
            if (inputs.b2) return CHANGE_SPEED;
            if (inputs.b3) return VIEW_CONTROL_MENU;
            if (inputs.b4) return EXIT_GAME;
            if (inputs.ns_center) return INVENTORY;
            if (inputs.b1) {
                selectedOption = CONTINUE_GAME;
                break;
            }
            wait_ms(100);
        }
        gamePaused = false;
        return selectedOption;
    }


void draw_game(int init)
{
    // Draw game border first
    if(init) draw_border();
    

    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
//            if (init && i == 0 && j == 0) // Only draw the player on init
            if ( i == 0 && j == 0) // always draw the player
            {
                draw_player(u, v, Player.has_key, Player.visible);
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
                else if (curr_item && curr_item->type == CLEAR)
                {
                    // This is a special case for erasing things like doors.
                    draw = curr_item->draw; // i.e. draw_nothing
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars    
    draw_upper_status();
    draw_lower_status();

    uLCD.locate(1, 1);
    uLCD.textbackground_color(BLACK);
    uLCD.text_width(1);
    uLCD.text_height(1);
    uLCD.color(WHITE);
    uLCD.printf("Player Position: (%d, %d) Lives: %d", Player.x, Player.y, Player.lives);
}


/////////////////////////
// Map Intialization
/////////////////////////

// Important locations for all maps
int cb_loc[2] = {5,20}; //Location of the center of the cave

void init_main_map()
{
    //Initialize and sets current map to the first map
    Map* map = set_active_map(0);

    /////////////////////////
    //Initial Environmnet
    /////////////////////////

    //Adding random plants
    pc.printf("Adding Plants!\r\n");
    for(int i = map_width() + 3; i < map_area(); i += 39)
    {
        add_plant(i % map_width(), i / map_width());
    }

     pc.printf("Adding Earth!\r\n");
    for(int i = map_width() + 6; i < map_area(); i += 39)
    {
        add_earth(i % map_width(), i / map_width());
    }

     pc.printf("Adding Water!\r\n");
    for(int i = map_width() + 11; i < map_area(); i += 39)
    {
        add_water(i % map_width(), i / map_width());
    }

    //Adding wall borders 
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    
    //Adding extra chamber borders 
    pc.printf("Add extra chamber\r\n");
    add_wall(30, 0, VERTICAL, 10);
    add_wall(30, 10, HORIZONTAL, 10);
    add_wall(39, 0, VERTICAL, 10);
    add_door(33, 10, HORIZONTAL, 4);

    //Adding extra cave to Buzz's evil lair
    pc.printf("Add cave\r\n");
    add_cave(cb_loc[0],cb_loc[1],1,1,5,5);      //Cave is set as a 4x4 block to be bigger
    add_cave(cb_loc[0]+1,cb_loc[1],2,1,5,5);
    add_cave(cb_loc[0],cb_loc[1]+1,3,1,5,5);
    add_cave(cb_loc[0]+1,cb_loc[1]+1,4,1,5,5);

    pc.printf("Initial environment completed\r\n");

    /////////////////////////////////
    // Characters and Items for the map
    /////////////////////////////////

    // Add NPC
    add_npc(10, 5);  //NPC is initialized to (x,y) = 10, 5. Feel free to move him around
    add_badguy1(15, 10);
    add_badguy2(20, 10);
    add_banyan(10,15);
    add_banyan(10,16);
    add_banyan(10,17);
    add_banyan(10,18);
    add_banyan(10,19);
    add_banyan(10,20);
    add_banyan(10,21);
    add_banyan(11,15);
    add_banyan(11,16);
    add_banyan(11,17);
    add_banyan(11,18);
    add_banyan(11,19);
    add_banyan(11,20);
    add_banyan(11,21);
    add_banyan(12,15);
    add_banyan(12,16);
    add_banyan(12,17);
    add_banyan(12,18);
    add_banyan(12,19);
    add_banyan(12,20);
    add_banyan(12,21);
    add_stairs(5, 15, 1, 2, 2);
    add_christmas_tree(1, 1);
    

    
    //***********************************
    // TODO: Implement As Needed
    //***********************************

    //Add any extra characters/items here for your project




    //Prints out map
    print_map();
}

void init_small_map()
{
    //Sets current map to the second map
    set_active_map(1);

    pc.printf("Adding walls to the small map\r\n");
    add_wall(0, 0, HORIZONTAL, 16);
    add_wall(0, 15, HORIZONTAL, 16);
    add_wall(0, 0, VERTICAL, 16);
    add_wall(15, 0, VERTICAL, 16);

    pc.printf("Adding the boss\r\n");
    add_boss(8,8);
    bossDead = false;

    pc.printf("Adding the boss\r\n");
    add_buzz(8,13);

    pc.printf("Adding Fire!\r\n");
        for(int i = map_width() + 3; i < map_area(); i += 39)
        {
            add_fire(i % map_width(), i / map_width());
        }


    pc.printf("Adding stairs back to the main map\r\n");
    // You may add any extra characters/items here for your project


    // Add stairs back to main (map 0)
    pc.printf("Adding stairs back to the main map\r\n");
    add_stairs(4, 6, 0, cb_loc[0], cb_loc[1]);

    pc.printf("Small map initialized\r\n");

    print_map();
    
}


 void show_game_over_screen() {
uLCD.cls();
    uLCD.color(RED);
    uLCD.locate(1, 4);
    uLCD.printf("GAME OVER\n");

    // Provide only the option to restart
    uLCD.locate(1, 6);
    uLCD.printf("B1: Restart\n");

    // Wait for player input
    while (true) {
        GameInputs inputs = read_inputs();
        if (inputs.b1) {
            Player.x = Player.y = 5;
            Player.has_key = false;
            Player.game_solved = false;
            Player.talked_to_npc = false;

            maps_init();
            init_main_map();
            init_small_map();

            draw_game(true);
            break;
        }
        wait_ms(50); // Polling delay
    }
 }


int update_game(int action, GameInputs inputs)
{
    
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    
    MapItem* item = NULL;
    

    //******************
    // TODO: Implement
    //******************

    bool fullRedraw = false;
    

    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.

    switch(action)
    {
        case GO_UP:
            item = get_north(Player.x, Player.y);
            if (item != NULL && item->type == FIRE) {
                Player.lives--;
                
                if (Player.lives <= 0) {
                    show_game_over_screen();
                    return GAME_OVER;
                }
            }
            if (item != NULL && item->type == CHEST) {
                Player.potions++;
                map_erase(Player.x, Player.y - 1);
            }
            if (Player.x >= 10 && Player.x <= 11 && Player.y >= 15 && Player.y <= 21) {
                Player.visible = false;
            } else {
                Player.visible = true;
            }
            if (item == NULL || (item->walkable)) {
                Player.y -= Player.speed;
                fullRedraw = true;
            }
            break;
            
        case GO_LEFT:
            //TODO: Implement
            item = get_west(Player.x, Player.y);
            if (item != NULL && item->type == FIRE) {
                Player.lives--;
                
                if (Player.lives <= 0) {
                    show_game_over_screen();
                    return GAME_OVER;
                }
            }
            if (item != NULL && item->type == CHEST) {
                Player.potions++;
                map_erase(Player.x - 1, Player.y);
            }
            if (Player.x >= 10 && Player.x <= 11 && Player.y >= 15 && Player.y <= 21) {
                Player.visible = false;
            } else {
                Player.visible = true;
            }
            if (item == NULL || (item->walkable)) {
                Player.x -= Player.speed;
                fullRedraw = true;
            }
            break;
            
        case GO_DOWN:
            //TODO: Implement
            item = get_south(Player.x, Player.y);
            if (item != NULL && item->type == FIRE) {
                Player.lives--;
                
                if (Player.lives <= 0) {
                    show_game_over_screen();
                    return GAME_OVER;
                }
            }
            if (item != NULL && item->type == CHEST) {
                Player.potions++;
                map_erase(Player.x, Player.y + 1);
            }
            if (Player.x >= 10 && Player.x <= 11 && Player.y >= 15 && Player.y <= 21) {
                Player.visible = false;
            } else {
                Player.visible = true;
            }
            if (item == NULL || (item->walkable)) {
                Player.y += Player.speed;
                fullRedraw = true;
            }
            break;
            
        case GO_RIGHT:
            //TODO: Implement
            item = get_east(Player.x, Player.y);
            if (item != NULL && item->type == FIRE) {
                Player.lives--;
                
                if (Player.lives <= 0) {
                    show_game_over_screen();
                    return GAME_OVER;
                }
            }
            if (item != NULL && item->type == CHEST) {
                Player.potions++;
                map_erase(Player.x + 1, Player.y);
            }
            if (Player.x >= 10 && Player.x <= 11 && Player.y >= 15 && Player.y <= 21) {
                Player.visible = false;
            } else {
                Player.visible = true;
            }
            if (item == NULL || (item->walkable)) {
                Player.x += Player.speed;
                fullRedraw = true;
            }
            break;
            
        case GO_IN: {

            item = get_here(Player.x, Player.y);

            MapItem* item = get_here(Player.x, Player.y);
            if (item && item->type == STAIRS) {
                // Logic for using stairs
                StairsData* stairsData = (StairsData*)item->data;
                if (stairsData) {
                    set_active_map(stairsData->tm);
                    Player.x = stairsData->tx;
                    Player.y = stairsData->ty;
                    return FULL_DRAW;
                }
            }
            break;
    }
    return fullRedraw ? FULL_DRAW : NO_RESULT;

        case ACTION_BUTTON:   
            item = detect_near(Player.x, Player.y);
              if (item) {
        switch (item->type) {

            case NPC:
                if (Player.game_solved) {
                    Player.has_key = true;
                    speech("Here is the key", "Good Job!", inputs);
                } else {
                    speech("Go defeat Buzz", "Take the stairs!", inputs);
                }
                Player.talked_to_npc = true;
                break;

            case DOOR:
                // Logic for door interaction
                if (Player.has_key) {
                    Player.game_solved = true;
                    return GAME_OVER;
                } else {
                    speech("You need a key.", "Go find it!", inputs);
                }
                break;


            case CAVE:
                if (Player.talked_to_npc) {
                    set_active_map(1);
                    Player.x = 1;
                    Player.y = 1;
                    speech("You have entered the cave!", "Prepare for the battle with Buzz!", inputs);
                    return FULL_DRAW; 
                }
                break;
                

            // Add more cases for other interactable items

        }
            }
            fullRedraw = true;
            break;

        case MENU_BUTTON: {
            GameMenuOption selectedOption = showMenu();

            switch (selectedOption) {
                case CONTINUE_GAME:
                    break;
                case CHANGE_SPEED:
                    if (Player.speed == 1) {
                        Player.speed = 2;
                    } else {
                        Player.speed = 1;
                    }
                    break;
                case VIEW_CONTROL_MENU:
                    controls();
                    break;
                case INVENTORY:
                    if (Player.potions > 0 && Player.lives < 3) {
                        Player.lives++;
                        Player.potions--;
                        uLCD.cls(); // Clear the screen
                    } else if (Player.potions <= 0) {
                        uLCD.cls(); // Clear the screen
                    } else if (Player.lives >= 3) {
                        uLCD.cls(); // Clear the screen
                    }
                break;
                case EXIT_GAME:
                    show_game_over_screen();
                    break;
            }
            break;
        }
        case ATTACK_BUTTON:
        item = detect_enemy_near(Player.x, Player.y);

        if (item) {
        int enemy_x = Player.x;
        int enemy_y = Player.y;

        // Determine the enemy's position based on its type
        if (get_north(Player.x, Player.y) == item) {
            enemy_y -= 1; // Enemy is to the north
        } else if (get_south(Player.x, Player.y) == item) {
            enemy_y += 1; // Enemy is to the south
        } else if (get_east(Player.x, Player.y) == item) {
            enemy_x += 1; // Enemy is to the east
        } else if (get_west(Player.x, Player.y) == item) {
            enemy_x -= 1; // Enemy is to the west
        }


            switch (item->type) {
                case BADGUY1:
                    add_chest(enemy_x, enemy_y);
                    break;

                case BADGUY2:
                    add_chest(enemy_x, enemy_y);
                    break;

                case BOSS:
                    add_slain_enemy(enemy_x, enemy_y);
                    bossDead = true;
                    break;

                case BUZZ:
                    add_fire(enemy_x, enemy_y);
                    Player.game_solved = true;
                    break;

                // Add more cases for different types of enemies or combat scenarios

            }
        }
        fullRedraw = true;
            break;

        case SPECIAL_ATTACK:
            if (bossDead) {
                int max_x = min(Player.x + 3, map_width() - 1);
                for (int i = Player.x + 1; i <= max_x; i++) {
                    add_fire(i, Player.y);
                }
                break;
            }
            switch (item->type) {
                case BUZZ:
                    add_fire(8, 13);
                    Player.game_solved = true;
                break;
            }

    }
    
    return fullRedraw ? FULL_DRAW : NO_RESULT;
}




/////////////////////////
// Draw Game
/////////////////////////

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */


/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */






int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");

    startScreen();

    MenuOption selected = menuInput();

    switch (selected) {
        case START_GAME:
        // Initialize the maps
    maps_init();
    init_main_map();
    init_small_map();
    
    // Initialize game state
    set_active_map(0);
    Player.x = Player.y = 5;
    Player.speed = 1;
    Player.has_key = false;
    Player.game_solved = false;
    Player.talked_to_npc = false;
    Player.lives = 3;
    Player.potions = 0;
    Player.visible = true;

    // Initial drawing
    draw_game(true);

    // Main game loop
    while(1)
    {

        ////////////////////////////////
        // TODO: Implement 
        ////////////////////////////////

        // Timer to measure game update speed
        Timer t;
        t.start();
        
        // Actually do the game update:
        // 1. Read inputs        
        GameInputs inputs = read_inputs();

        // 2. Determine action (get_action)       
        int action = get_action(inputs);

        // 3. Update game (update_game)
        int result = update_game(action, inputs);
        
        // 3b. Check for game over based on update game result
        if (result == GAME_OVER) {
            // game over logic
            show_game_over_screen();
            break;  // or navigate to a game over screen
        }

        // 4. Draw screen to uLCD
        bool full_draw = (result == FULL_DRAW);
        if (result == FULL_DRAW) full_draw = true;
        draw_game(full_draw);
        
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
    break;

    case VIEW_CONTROLS:
        controls();
        break;

    case EXIT:
        show_game_over_screen();
    }

    return 0;

}




/////////////////////////////
//Advanced Features
/////////////////////////////

// Plays a wavfile
void playSound(char* wav)
{
    //open wav file
    FILE *wave_file;
    wave_file=fopen(wav,"r");
    
    if(wave_file != NULL) 
    {
        printf("File opened successfully\n");

        //play wav file
        printf("Sound playing...\n");
        waver.play(wave_file);
    
        //close wav file
        printf("Sound stopped...\n");
        fclose(wave_file);
        return;
    }
    
    printf("Could not open file for reading - %s\n", wav);
    return;
} 