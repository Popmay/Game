// need to add a function to check if the user has entered a valid input
// need draw/display logic
// need card logic
// need game win logic
// shop?
// types of enemys and base cards off of them
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
string tileID[99];

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
                                       // vectors for each enemy

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
  for (int i = 0; i < sizeof(enemy); i++) {
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

  for (int i = 0; i < sizeof(object); i++) {
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
  for (int i = 0; i < sizeof(enemy); i++) {
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

  // spawn enemys
  enemySpawner();
  enemyCardSpawner();

  // spawn objects
  objectSpawner();
}

void objectController(int objectTileID) {

  int e = 0;

  for (int i = 0; i < sizeof(object); i++) {
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

  return enemyCards[enemyID][rand() % sizeof(enemyCards[enemyID])]
      .data()
      ->damage;
}

int playerCardController() {

  return playerCards[rand() % sizeof(PlayerCards)].damage;
}

void enemyController(int enemyTileID) {
  // dont know if needed
}

void fightController(int enemyTileID) {

  int e = 0;

  for (int i = 0; i < sizeof(enemy); i++) {
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
    enemy[e].enemyTileID = -1;
  }
  // need logic for player death

  // need win and lose logic and player move after win
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
  }
}

void enemyMover() {

  int test;
  int choice = rand() % 3;

  for (int i = 0; i < sizeof(enemy); i++) {

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
      fightController(test);
    } else {
      i--;
    }
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

int main() {

  makeBoard();

  // on click event
  enemyMover();
  tellPlayerSurroundings(player.playerTileID);

  playerMover(rand() % 99);
  return 0;
}
