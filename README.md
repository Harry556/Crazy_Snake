# :snake:Crazy_Snake (By Wong wai chun)
 Crazy_Snake game is text base game made by C++
 Contributed by 👨__*Huang xinghai 3035757145*__ and 🧑__*Wong wai chun 3035756919*__
 1. Group No.: 157
 2. Group members: 2 
 3. Topic: Crazy Snake
 4. Link: https://github.com/Harry556/Crazy_Snake/edit/main/README.md
 
## Game Description (By Wong wai chun)
 These are some new feather differ to the tradition console snake game, so that why we name it by Crazy snake.
 You will see new stuff inside the game such as obstacle, toxic food. 

## :dragon_face:Game features (By Wong wai chun)
 //What feather about this game, how this different to other snake?
 //Obtacle(Different type of obtacle)/Food🍉🍋
 //Obtacle and food may not occupy one location maybe consist of 3-5
 //Output input - >Can save game
 //Random event
 //Data structure for storing game-> 1D Array store for each the tail location/food/toxic food/obstacle
 //Program code seperate to multi-files
 //pause game
 //load game
 //start game
 //exit game(save game)
// press key to open menu while gaming
/// setting
 //set speed of snake
 //set the different
 
# My part was done la and i need to have work tonight, cant do with the remain part,
 
## :seedling: Introduce the game rules (by Huang xinghai)
1. These are some stuff will see while the game
2. 1. Obstacle
3. 2. 1. Hard obstacle
4. 3. 2. 1. Random bound to one of the perpendicular direction
5. 4. 3. 2. Deduced one unit length of the snake
6. 5. 4. 3. Reduced score by 5
7. 6. 5. Soft obstacle
8. 7. 6. 1. Random bound to one of the perpendicular direction
9. 8. 7. Fatal obstacle
10. 9. 8. 1. Lose the game
11. 1. Food
12. 2. 1. Normal food
13. 3. 2. 1. Score by 10
14. 4. 3. Toxic food
15. 4. 4. 1. Reduced score by 5

The snake eats different stuff will gain the score or change the states in the game.
The player should avoid colliding with the fatal obstacle event the hard obstacle and toxic food, it will lose the game or deduce the score.

#####   
How to win the game
1. If the player attain the score 300 and 15 length tail, then win the game
2. It can continue to the game to break the records if the player won the game
3. If the player collides with a fatal obstacle, then lose the game

## :detective: Technique involved (by Huang xinghai)
1. #include <conio.h> for sleep(), time delay for making animation
2. #include <windows.h> for detected user key press event
3. #include <fstream> for read/write file stream
4. Display clear console and display multi-line text every particular time, to make the animation smoother, it should be refreshed the console at least more than or close to 24 times per seconds
5. Calculate the snake tails which will grow by eat something
6. Calculate the time interval between the console display and the speed of the snake. 

## :man_in_tuxedo:Game flow (by Huang xinghai)
1. Game title and options menu will be displayed on the main page
2. Player can press key [1-6], it will go to the following page.
3. 1. [1]Start a new game
4. 2. [2]Load the game
5. 3. [3]How to play
6. 4. [4]Scores records
7. 5. [5]Change difficulty
8. 5. [6]Exit the game 
9. If the player start a game, then all the console text will be clear, Then show the game page consist of the text and have the animation
10. Player controls the movement of the snake by press the direction key.
11. If the player press key [p] while gaming, which will pause the game.
12. If the player press key [s] while gaming, which will save the game.
13. If the player press key [e] while gaming, which will back to the main page.
