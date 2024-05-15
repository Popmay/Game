#include <iostream>

#include <SDL2/SDL.h>

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
string tileID[99];

const int WIDTH = 1000, HEIGHT = 1000;


    SDL_Window *window;
    SDL_Renderer *renderer;
    int grid_cell_size = 100;
    int grid_width = 10;
    int grid_height = 10;
    int window_width = (grid_width * grid_cell_size) + 1;
    int window_height = (grid_height * grid_cell_size) + 101;
    SDL_Color grid_background = {22, 22, 22, 255}; // Barely Black
    SDL_Color grid_line_color = {44, 44, 44, 255}; // Dark grey
    SDL_Color grid_cursor_color = {255, 255, 255, 255}; // White

// need draw/display logic for shop and differnt colors for diffent enemys
// need card logic
// need game win logic
//disply cards
//fight logic and enemy mover crash game


int tileControler(string occupantID) {
  for (int i = 0; i < 99; i++) {
    if (tileID[i] == occupantID) {
      return i;
    }
  }
  return -1;
}

class EnemyCards {
public:
  int damage;
  string effect;
  string color;
  int ownerTileID;
};

vector<EnemyCards> enemyCards[10][10]; // Two-dimensional array of enemy card

class PlayerCards {
public:
  int damage;
  string effect;
  string color;
};

PlayerCards playerCards[10];

class Object {
public:
  int value;
  string type;
  int objectTileID;
};

Object object[10];

class Enemy {
public:
  int health;
  int enemyTileID;
  string type;
};

Enemy enemy[10];

class Player {
public:
  int health;
  int gold;
  int playerTileID;
};

Player player; // Create an instance of the Player class

void enemySpawner() {

  // set the position of the 10 ememys to random emtpy tiles
  for (int i = 0; i < 10; i++) {
    int test = rand() % 99;

    if (tileID[test] == "empty") { // check if tile is empty
      enemy[i].enemyTileID = test;
      tileID[test] = "enemy";

      if (test >= 0 && test < 33) { // set enemy type based on position
        enemy[i].type = "Slime";
      } else if (test >= 33 && test < 66) {
        enemy[i].type = "Goblin";
      } else {
        enemy[i].type = "Dark Wizard";
      }

    } else {
      i--;
    }
  }
}

void objectSpawner() {

  // set the position of the 10 object of two random types to random empty tiles

  for (int i = 0; i < 10; i++) {
    int test = rand() % 99;
    if (tileID[test] == "empty") {
      object[i].objectTileID = test;
      if (rand() % 2 == 0) {
        object[i].type = "coin";
        tileID[test] = "coin";
        object[i].value = rand() % 10;
      } else {
        object[i].type = "apple";
        tileID[test] = "apple";
        object[i].value = rand() % 5;
      }
    } else {
      i--;
    }
  }
}

void enemyCardSpawner() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {

      if (enemy[i].type == "Slime") { // set card atibutes based on enemy type
        EnemyCards enemyCard;
        enemyCard.damage = rand() % 4 + 1;
        enemyCard.effect = "Heal 1 Health";
        enemyCard.color = "Blue";
        enemyCard.ownerTileID = enemy[i].enemyTileID;
        enemyCards[i][j].push_back(enemyCard);
      } else if (enemy[i].type == "Goblin") {
        EnemyCards enemyCard;
        enemyCard.damage = rand() % 7 + 1;
        enemyCard.effect = "Steal 1 Gold";
        enemyCard.color = "Green";
        enemyCard.ownerTileID = enemy[i].enemyTileID;
        enemyCards[i][j].push_back(enemyCard);
      } else if (enemy[i].type == "Dark Wizard") {
        EnemyCards enemyCard;
        enemyCard.damage = rand() % 10 + 1;
        enemyCard.effect = "+1 Damage on Win";
        enemyCard.color = "Red";
        enemyCard.ownerTileID = enemy[i].enemyTileID;
        enemyCards[i][j].push_back(enemyCard);
      }
    }
  }
}

void makeBoard() {

  // clear board
  for (int i = 0; i < 99; i++) {
    tileID[i] = "empty";
  }

  // spawn player
  player.playerTileID = 0;
  tileID[0] = "player";

//   spawn enemys
  enemySpawner();
  enemyCardSpawner();

//   spawn objects
  objectSpawner();

  
    // Place the grid cursor in the middle of the screen.
    SDL_Rect grid_cursor = {
        .x = 100*(player.playerTileID % 10),
        .y = 10*(player.playerTileID - player.playerTileID % 10),
        .w = grid_cell_size,
        .h = grid_cell_size,
    };
  
    SDL_Color grid_background = {22, 22, 22, 255}; // Barely Black
    SDL_Color grid_line_color = {44, 44, 44, 255}; // Dark grey
    SDL_Color grid_cursor_color = {255, 255, 255, 255}; // White

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
       
    }

    if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window,
                                    &renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer: %s", SDL_GetError());
       
    }

    SDL_SetWindowTitle(window, "SDL Grid");

    SDL_bool quit = SDL_FALSE;
    SDL_bool mouse_active = SDL_FALSE;
    SDL_bool mouse_hover = SDL_FALSE;

}

void objectController(int objectTileID) {

  int e = 0;

  for (int i = 0; i < 10; i++) {
    if (object[i].objectTileID == objectTileID) {
      e = i;
      break;
    }
  }

  if (object[e].type == "coin") {
    player.gold += object[e].value;
    object[e].objectTileID = -1;
  } else if (object[e].type == "apple") {
    player.health += object[e].value;
    object[e].objectTileID = -1;
  }
}

int enemyCardController(int enemyID) {

  // return enemyCards[enemyID][rand() % (int) sizeof(enemyCards[enemyID])].data()->damage;
  return 10;
}

int playerCardController() {

  return playerCards[rand() % (int) sizeof(PlayerCards)].damage;
}

void fightController(int enemyTileID) {

  int e = 0;

  for (int i = 0; i < 10; i++) {
    if (enemy[i].enemyTileID == enemyTileID) {
      e = i;
      break;
    }
  }

  if (enemyCardController(e) > playerCardController()) {
    // need logic for effects
    player.health -= enemyCardController(e);
  } else if (enemyCardController(e) < playerCardController()) {
    // need logic for effects
    enemy[e].health -= playerCardController();
  } else if (enemyCardController(e) == playerCardController()) {
    // tie logic
    // need logic for effects
  }

  if (enemy[e].health <= 0) {
    player.gold += 10; // update gold based on enemy type
    player.playerTileID = enemy[e].enemyTileID;
    tileID[enemy[e].enemyTileID] = "empty";
    enemy[e].enemyTileID = -1;
  }
  // need logic for player death

  // need win and lose logic and player move after win
}

void enemyMover() {

  int test;
  int choice = rand() % 3;

  for (int i = 0; i < 10; i++) {

    if (choice == 0) {
      test = enemy[i].enemyTileID + 10;
    } else if (choice == 1) {
      test = enemy[i].enemyTileID - 10;
    } else if (choice == 2) {
      test = enemy[i].enemyTileID + 1;
    } else {
      test = enemy[i].enemyTileID - 1;
    }

    if (tileID[test] == "empty") {
      enemy[i].enemyTileID = test;
      tileID[test] = "enemy";
    } else if (tileID[test] == "player") {
      i--;
    } else {
      i--;
    }
  }
}

void playerMover(int newTileID) {
  bool isFree;
  bool isAdjacent;
  bool isEnemy;

  if (newTileID == player.playerTileID + 10 ||
      newTileID == player.playerTileID - 10 ||
      newTileID == player.playerTileID + 1 ||
      newTileID == player.playerTileID - 1) {
    isAdjacent = true;
  } else {
    isAdjacent = false;
  }

  if (tileID[newTileID] == "empty") {
    isFree = true;
  } else {
    isFree = false;
  }

  if (tileID[newTileID] == "enemy") {
    isEnemy = true;
  } else {
    isEnemy = false;
  }

  if (isFree == true && isAdjacent == true) {
    // move player
    player.playerTileID = newTileID;
    tileID[newTileID] = "player";
    tileID[player.playerTileID] = "empty";
  } else if (isEnemy == true && isAdjacent == true) {
    // fight start
    fightController(newTileID);
  } else if (isFree == false && isAdjacent == true && isEnemy == false) {
    // claim item
    objectController(newTileID);
    player.playerTileID = newTileID;
    tileID[newTileID] = "player";
    tileID[player.playerTileID] = "empty";
  }else{
    
  }
}


void tellPlayerSurroundings(int playerTileID) {
  int topTileID = playerTileID - 10;
  int bottomTileID = playerTileID + 10;
  int leftTileID = playerTileID - 1;
  int rightTileID = playerTileID + 1;
  cout << "You have the following around you:" << endl;
  if (topTileID >= 0) {
    cout << "Top tile: " << tileID[topTileID] << endl;
  }
  if (bottomTileID < 99) {
    cout << "Bottom tile: " << tileID[bottomTileID] << endl;
  }
  if (leftTileID % 10 != 9 && leftTileID >= 0) {
    cout << "Left tile: " << tileID[leftTileID] << endl;
  }
  if (rightTileID % 10 != 0 && rightTileID < 99) {
    cout << "Right tile: " << tileID[rightTileID] << endl;
  }
}

void shop(string buttonClicked) {
  int cardRand = rand() % 10 + 1;
  if (buttonClicked == "upgrade") {
    playerCards[cardRand].damage += rand() % 3 + 1;
  } else if (buttonClicked == "duplicate") {
    // need logic for dupicate
  }
}
  
void drawBoard(){

   SDL_Rect grid_cursor = {
        .x = 100*(player.playerTileID % 10),
        .y = 10*(player.playerTileID - player.playerTileID % 10),
        .w = grid_cell_size,
        .h = grid_cell_size,
    };

  SDL_Rect enemy_cursor[10];
for (int i = 0; i < 10; i++) {
    enemy_cursor[i].x = 100 * (enemy[i].enemyTileID % 10);
    enemy_cursor[i].y = 10 * (enemy[i].enemyTileID - enemy[i].enemyTileID % 10);
    enemy_cursor[i].w = grid_cell_size;
    enemy_cursor[i].h = grid_cell_size;
}

SDL_Rect object_cursor[10];
for (int i = 0; i < 10; i++) {
    object_cursor[i].x = 100 * (object[i].objectTileID % 10);
    object_cursor[i].y = 10 * (object[i].objectTileID - object[i].objectTileID % 10);
    object_cursor[i].w = grid_cell_size;
    object_cursor[i].h = grid_cell_size;
}
    
SDL_Rect player_card_cursor[10];
for (int i = 0; i < 10; i++) {
    player_card_cursor[i].x = 100 * i;
    player_card_cursor[i].y = 1001;
    player_card_cursor[i].w = grid_cell_size;
    player_card_cursor[i].h = grid_cell_size;
}

  // Draw grid background.
        SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g,
                               grid_background.b, grid_background.a);
        SDL_RenderClear(renderer);

        // Draw grid lines.
        SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g,
                               grid_line_color.b, grid_line_color.a);

        for (int x = 0; x < 1 + grid_width * grid_cell_size;
             x += grid_cell_size) {
            SDL_RenderDrawLine(renderer, x, 0, x, window_height);
        }

        for (int y = 0; y < 1 + grid_height * grid_cell_size;
             y += grid_cell_size) {
            SDL_RenderDrawLine(renderer, 0, y, window_width, y);
        }

        
        // Draw grid cursor.
        SDL_SetRenderDrawColor(renderer, grid_cursor_color.r,
                               grid_cursor_color.g, grid_cursor_color.b,
                               grid_cursor_color.a);
        SDL_RenderFillRect(renderer, &grid_cursor);

for (int i = 0; i < 10; i++) {
  if(object[i].type == "apple"){
     SDL_SetRenderDrawColor(renderer, 200,
                               0, 0,
                               grid_cursor_color.a);
  }else{
    SDL_SetRenderDrawColor(renderer, 200,
                               100, 0,
                               grid_cursor_color.a);
  }

    SDL_RenderFillRect(renderer, &object_cursor[i]);
}

for (int i = 0; i < 10; i++) {
    
    SDL_SetRenderDrawColor(renderer, 10,
                               10, 10,
                               255);

    SDL_RenderFillRect(renderer, &player_card_cursor[i]);
}

for (int i = 0; i < 10; i++) {
  if(enemy[i].type == "Slime"){
     SDL_SetRenderDrawColor(renderer, 0,
                               100, 200,
                               grid_cursor_color.a);
  }else if(enemy[i].type == "Goblin"){
    SDL_SetRenderDrawColor(renderer, 0,
                               200, 0,
                               grid_cursor_color.a);
  }else if(enemy[i].type == "Dark Wizard"){
    SDL_SetRenderDrawColor(renderer, 0,
                               0, 0,
                               grid_cursor_color.a);
  }

    SDL_RenderFillRect(renderer, &enemy_cursor[i]);
}

        SDL_RenderPresent(renderer);
}


int main( int argc, char *argv[] )
{
    SDL_Init( SDL_INIT_EVERYTHING );
    
    makeBoard();

  tellPlayerSurroundings(player.playerTileID);

 while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
           
            case SDL_MOUSEBUTTONDOWN:

if(event.motion.y <= 1000){
                playerMover((event.motion.x / 100) + (10 * round(event.motion.y/100)));
                tellPlayerSurroundings(player.playerTileID);
                cout << (event.motion.x / 100) << " " << 10 * round(event.motion.y/100);
                drawBoard();
                break;
}else{
  //card logic
}
            }
        }
}

    SDL_Event windowEvent;
    
    while ( true )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if ( SDL_QUIT == windowEvent.type )
            {
                break;
            }
        }
    }
    
    SDL_Quit( );
    
    return EXIT_SUCCESS;
}
