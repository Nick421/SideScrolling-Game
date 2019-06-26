# SideScrolling-Game
A side scroller platform game written in C++ using QT library

# Design patterns used
## Stage 1

### Factory method

The game dialog is created by a factory to allow for easy extension. The separation of object construction from object use allows new game dialogs to be created without tight coupling of the start dialog and the game dialog.

### Singleton

The Config class is a singleton to make sure no more than one instance is ever created.

## Stage 2

### Composite pattern (This is implemented wrong) 

The GameState class stores information about the current game's state. This includes a pointer to an  Entity object, the root of the game state hierarchy. The Entity class is an abstract class that defines pure virtual methods for updating, rendering and retrieving components (such as Colliders) for an object in the game (e.g. an Obstacle). There are two abstract subclasses of Entity: LeafEntity and CompositeEntity. LeafEntity currently does not add any additional functionality to the Entity class, but CompositeEntity allows for the updating and rendering of children Entities. There are three main concrete classes in the scene that have CompositeEntity as an ancestor: StickmanPlayer, Obstacle and EmptyEntity.

### Object adapter

There are two object adapters present in the code.
  1. Configuration is an abstract class, the target. ExtendedConfig (the adapter) accesses the Config singleton (adaptee) to extend the functionality of the Config class.
  2. Player is an abstract class, the target. StickmanPlayer (the adapter) accesses the Stickman object (adaptee) from the config singleton to allow for physics and collision operations.

### Factory method

The GameState class is the product (however instances of it can be created), produced by the createGameState() method in the abstract factory GameStateFactory. Stage2GameStateFactory is a concrete factory that produces Stage2GameState objects, which are concrete products inheriting from GameState. This allows for the customisation of GameState objects, and the easy creation of GameState instances in both the Stage2Game class and the Tester class.

## stage 3 (This is the stage I worked on)

### Mediator pattern
Use for communicating between Stage3Game class to background, stickman, obstacle and power-ups. The GameState class from stage 2 was effectively a pseudo mediator already so the mediator class is a subclass of GameState with additional functionalities.

The mediator handles all interaction between Stickman, obstacle,power ups and checkpoint. The Stage3game simply calls the mediator to perform or check any of these interaction in the game.

Additional info is in comments in each files. 

# Commands
  1. Left & Right key to move 
  2. Backspace to jump
  3. P to pause the game
  4. Konami code for super secret powerup

# TestMode
In main.cpp, change the boolean on line 18,19 to true in order to use stage 3 test.
The tests are unit tests which mainly focus on mediator functionality with Powerups and checkpoint and winning/losing. 

# Demo video

[![Watch the video](https://img.youtube.com/vi/pA8xT22hvmE/maxresdefault.jpg)](https://youtu.be/pA8xT22hvmE)

# Future work
It is unlikely I will touch this project again but I will go back and make my own stage 1 game into stage 3 in another repositry and any additional work will be done on that project instead.
