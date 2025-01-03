//=================================================================
// The map class file.
//
// Copyright 2023 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================

#include "map.h"
#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items; // Hashtables for all items of the map
    int w, h;         // Map dimensions
    int index;        // Index of map (tells if its the first map or second map)
};

typedef struct {
    int tm;
    int tx, ty;
} stairsData;

///////////////////////
//Important Definitions
///////////////////////

#define MHF_NBUCKETS 97     //  Hashing value
#define NUM_MAPS 2          //  You may add more maps here
#define MAP_WIDTH 50
#define MAP_HEIGHT 50
static Map maps[NUM_MAPS];  //  Array of maps
static int active_map;      //  Current active map on screen


//To erase a MapItem, we can simply replace it 
//with a clear type item called clear sentinel
static const MapItem CLEAR_SENTINEL = { 
    .type = CLEAR,
    .draw = draw_nothing
};


/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {

    //****************
    // TODO: Implement
    //****************

    return Y * MAP_WIDTH + X;

    // 1. Return the 1-D XY key
    // Hint: Think about how you accessed location previous projects/hw

}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    //****************
    // TODO: Implement
    //****************

    return key % MHF_NBUCKETS;

    // Hint: what math operator can be used as an easy way to hash a key?
    // 1. Use MHF_NBUCKETS defined at the top as the value to hash for your hash function
    // 2. Return the hashed key
}

/**
 * Initializes the map, using a hash_table, setting the width and height.
 */
void maps_init()
{
    //****************
    // TODO: Implement
    //****************

    for (int i = 0; i < NUM_MAPS; i++) {
        maps[i].items = createHashTable(map_hash, MHF_NBUCKETS);
        maps[i].w = MAP_WIDTH;  // Assuming MAP_WIDTH and MAP_HEIGHT are defined
        maps[i].h = MAP_HEIGHT;
        maps[i].index = i;

    }
    active_map = 0;
    // 1. Loop through all possible maps, where for each map's items, create a hashtable 
    // 2. Set width & height for any maps 
    // 3. Set the first map to be active
}


Map* get_active_map()
{
    //****************
    // TODO: Implement
    //****************

    return &maps[active_map];
    // 1. Return a pointer to the current map based on which map is active (active_map)
    //    Hint: What operator do we use for returning addresses?
    //    Note: active_map is set as a Global Variable 

}

int get_active_map_index()
{
    //****************
    // TODO: Implement
    //****************

    return active_map;
    
    // 1. Return the index to the current map based on which map is active (active_map)
}

Map* set_active_map(int m)
{
    //****************
    // TODO: Implement
    //****************

    active_map = m;
    return &maps[active_map];

    // 1. Set the Global Variable for active map to the map index passed in
    // 2. Return a pointer to the current map based on which map is active (active_map)
 
   
}

/**
 *  Prints out the map for debugging on the terminal
 */

void print_map()
{
    // NOTE: As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'D', 'P', 'A', 'K', 'C', 'N',' ','S'};
    Map* map = get_active_map();
    for(int j = 0; j < map->h; j++)
    {
        for (int i = 0; i < map->w; i++)
        {
            MapItem* item = (MapItem*)getItem(map->items, XY_KEY(i, j));
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}


/**
 * Returns width of active map
 */
int map_width()
{
    //****************
    // TODO: Implement 
    //****************

    return get_active_map()->w;
    // Hint 1 for this and below functions: use another function to GET the current active map
    // Hint 2: check the struct of a map item
}

/**
 * Returns height of active map
 */
int map_height()
{
    //****************
    // TODO: Implement  
    //****************

    return get_active_map()->h;
}

/**
 * Returns the area of the active map
 */
int map_area()
{
    //****************
    // TODO: Implement  
    //****************

    Map* map = get_active_map();
    return map->w * map->h;
    // HINT: You have the width and height to compute area
}

/**
 * Returns the MapItem immediately above the given location.
 */
MapItem* get_north(int x, int y)
{
    //****************
    // TODO: Implement
    //****************

    return (y > 0) ? (MapItem*)getItem(get_active_map()->items, XY_KEY(x, y - 1)) : NULL;

    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 
}

/**
 * Returns the MapItem immediately below the given location.
 */
MapItem* get_south(int x, int y)
{
    //****************
    // TODO: Implement
    //****************

    return (y < map_height() - 1) ? (MapItem*)getItem(get_active_map()->items, XY_KEY(x, y + 1)) : NULL;
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 
}

/**
 * Returns the MapItem immediately right the given location.
 */
MapItem* get_east(int x, int y)
{
   //****************
    // TODO: Implement
    //****************
    return (x < map_width() - 1) ? (MapItem*)getItem(get_active_map()->items, XY_KEY(x + 1, y)) : NULL;
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 
}

/**
 * Returns the MapItem immediately left the given location.
 */
MapItem* get_west(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    return (x > 0) ? (MapItem*)getItem(get_active_map()->items, XY_KEY(x - 1, y)) : NULL;
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 
}

/**
 * Returns the MapItem at current coordinate location
 */
 MapItem* get_here(int x, int y)
 {
    //****************
    // TODO: Implement
    //****************
    return (MapItem*)getItem(get_active_map()->items, XY_KEY(x, y));
    // 1. Get map item 
    // 2. If the item exist and is a clear type, remove item
    // 3. Return the item 
 }

MapItem* detect_near(int x, int y) {
    MapItem* item;

    item = get_north(x, y);
    if (item && (item->type == NPC || item->type == DOOR)) return item;

    item = get_south(x, y);
    if (item && (item->type == NPC || item->type == DOOR)) return item;

    item = get_east(x, y);
    if (item && (item->type == NPC || item->type == DOOR)) return item;

    item = get_west(x, y);
    if (item && (item->type == NPC || item->type == DOOR)) return item;

    return NULL;
}



 MapItem* detect_enemy_near(int x, int y) {
    MapItem* item;

    // Check North
    item = get_north(x, y);
    if ((item && (item->type == ENEMY || item->type == BOSS || item->type == BADGUY1 || item->type == BADGUY2|| item->type == BUZZ))) {
        return item;
    }

    // Check South
    item = get_south(x, y);
    if ((item && (item->type == ENEMY || item->type == BOSS || item->type == BADGUY1 || item->type == BADGUY2|| item->type == BUZZ))) {
        return item;
    }

    // Check East
    item = get_east(x, y);
    if ((item && (item->type == ENEMY || item->type == BOSS || item->type == BADGUY1 || item->type == BADGUY2|| item->type == BUZZ))) {
        return item;
    }

    // Check West
    item = get_west(x, y);
    if ((item && (item->type == ENEMY || item->type == BOSS || item->type == BADGUY1 || item->type == BADGUY2|| item->type == BUZZ))) {
        return item;
    }

    return NULL;
}


 

/**
 * Erases item on a location by replacing it with a clear sentinel
 */
void map_erase(int x, int y)
{
    MapItem* item = (MapItem*)insertItem(get_active_map()->items, XY_KEY(x, y), (void*)&CLEAR_SENTINEL);
    if(item) free(item);
}


////////////////////////////////////
// Adding specific items to the map
////////////////////////////////////


void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_boss(int x, int y) {
    MapItem* boss = (MapItem*) malloc(sizeof(MapItem));
    boss->type = BOSS;
    boss->draw = draw_boss; // You need to define this function
    boss->walkable = false;
    boss->data = NULL;

    // Set any additional boss-specific properties
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), boss);
    if (val) free(val); // If something is already there, free it
}

void add_buzz(int x, int y) {
    MapItem* buzz = (MapItem*) malloc(sizeof(MapItem));
    buzz->type = BUZZ;
    buzz->draw = draw_buzz; // You need to define this function
    buzz->walkable = false;
    buzz->data = NULL;
    // Set any additional boss-specific properties
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), buzz);
    if (val) free(val); // If something is already there, free it
}

void add_npc(int x, int y)
{
    //****************
    // TODO: Implement
    //****************

    MapItem* npc = (MapItem*) malloc(sizeof(MapItem));
    npc->type = NPC;
    npc->draw = draw_npc;
    npc->walkable = false;
    npc->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), npc);
    if (val) free(val);

    // 1. Implement the same way as how we add plant
    //     *Make the NPC NOT walkable

}


void add_water(int x, int y)
{

   //****************
    // TODO: Implement
    //****************
    MapItem* item = (MapItem*)malloc(sizeof(MapItem));
    item->type = WATER;
    item->draw = draw_water; // draw_water should be a function that knows how to draw water
    item->walkable = false;  // Assuming the player cannot walk on water
    item->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), item);
    if (val) free(val); // Free existing item if there is one
    // 1. Implement the same way as how we add plant

}

void add_fire(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    MapItem* item = (MapItem*)malloc(sizeof(MapItem));
    item->type = FIRE;
    item->draw = draw_fire;
    item->walkable = true;
    item->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), item);
    if (val) free(val); // Free existing item if there is one
    // 1. Implement the same way as how we add plant

}

void add_earth(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    MapItem* item = (MapItem*)malloc(sizeof(MapItem));
    item->type = EARTH;
    item->draw = draw_earth; // draw_earth should be a function that knows how to draw earth
    item->walkable = false;  // Assuming the player can walk on earth
    item->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), item);
    if (val) free(val); // Free existing item if there is one
    // 1. Implement the same way as how we add plant

}


void add_slain_enemy(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    MapItem* item = (MapItem*)malloc(sizeof(MapItem));
    item->type = SLAIN_ENEMY;
    item->draw = draw_slain_enemy; // draw_slain_enemy should be a function for drawing defeated enemies
    item->walkable = true;         // Assuming the player can walk over a slain enemy
    item->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), item);
    if (val) free(val); // Free existing enemy item if there is one
    // 1. Implement the same way as how we add plant
    // Note: This function is to ovewrite enemy when it is defeated
    //      You can do the following:
    //      -   Overwrite enemy with any other item (say plant, mud)
    //      -   Make a new drawing for a defeated enemy
    //      -   Erase enemy instead 
}

void add_badguy1(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    MapItem* badguy1 = (MapItem*)malloc(sizeof(MapItem));
    badguy1->type = BADGUY1;
    badguy1->draw = draw_badguy1;
    badguy1->walkable = false;
    badguy1->data = NULL;
    

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), badguy1);
    if (val) free(val); // Free existing enemy item if there is one
    // 1. Implement the same way as how we add plant
    // Note: This function is to ovewrite enemy when it is defeated
    //      You can do the following:
    //      -   Overwrite enemy with any other item (say plant, mud)
    //      -   Make a new drawing for a defeated enemy
    //      -   Erase enemy instead 
}

void add_badguy2(int x, int y)
{
    //****************
    // TODO: Implement
    //****************
    MapItem* badguy2 = (MapItem*)malloc(sizeof(MapItem));
    badguy2->type = BADGUY2;
    badguy2->draw = draw_badguy2;
    badguy2->walkable = false;
    badguy2->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), badguy2);
    if (val) free(val); // Free existing enemy item if there is one
    // 1. Implement the same way as how we add plant
    // Note: This function is to ovewrite enemy when it is defeated
    //      You can do the following:
    //      -   Overwrite enemy with any other item (say plant, mud)
    //      -   Make a new drawing for a defeated enemy
    //      -   Erase enemy instead 
}

void add_chest(int x, int y)
{

   //****************
    // TODO: Implement
    //****************
    MapItem* item = (MapItem*)malloc(sizeof(MapItem));
    item->type = CHEST;
    item->draw = draw_chest; // draw_water should be a function that knows how to draw water
    item->walkable = true;  // Assuming the player cannot walk on water
    item->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), item);
    if (val) free(val); // Free existing item if there is one
    // 1. Implement the same way as how we add plant

}

void add_banyan(int x, int y)
{
    MapItem* item = (MapItem*)malloc(sizeof(MapItem));
    item->type = BANYAN;
    item->draw = draw_banyan;
    item->walkable = true;
    item->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), item);
    if (val) free(val);
}

void add_christmas_tree(int x, int y) {
    MapItem* tree = (MapItem*) malloc(sizeof(MapItem));
    tree->type = CHRISTMAS_TREE;
    tree->draw = draw_christmas_tree;
    tree->walkable = false;
    tree->data = NULL;

    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), tree);
    if (val) free(val); // If something is already there, free it
}

////////////////////////////////////
// Adding environment to the map
////////////////////////////////////


void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_door(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = DOOR;
        w1->draw = draw_door;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}


void add_stairs(int x, int y, int tm, int tx, int ty)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = STAIRS;
    w1->draw = draw_stairs;
    w1->walkable = true;
    StairsData* data = (StairsData*) malloc(sizeof(StairsData));
    data->tm = tm;
    data->tx = tx;
    data->ty = ty;
    w1->data = data;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it    
}


void add_cave(int x, int y, int n, int tm, int tx, int ty)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = CAVE;
    if (n==1){
        w1->draw = draw_cave1;
    }
    if (n==2){
        w1->draw = draw_cave2;
    }
    if (n==3){
        w1->draw = draw_cave3;
    }
    if (n==4){
        w1->draw = draw_cave4;
    }
    w1->walkable = true;
    StairsData* data = (StairsData*) malloc(sizeof(StairsData));
    data->tm = tm;
    data->tx = tx;
    data->ty = ty;
    w1->data = data;
    
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it    
}


void add_mud(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = MUD;
        w1->draw = draw_mud;
        w1->walkable = true;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
} 
