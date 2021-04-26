# :snake:Crazy_Snake (By Wong wai chun)
 Crazy_Snake game is text base game made by C++
 Contributed by 👨__*Huang xinghai 3035757145*__ and 🧑__*Wong wai chun 3035756919*__
 1. Group No.: 157
 2. Group members: 2 
 3. Topic: Crazy Snake
 4. Link: https://github.com/Harry556/Crazy_Snake/edit/main/README.md
 
## Game Description (By Wong wai chun)
 In this game, the player will act as a moving snake that is composed by digital characters. The snake is very hungry and it needs eating foods continuously to survive.  
 Although the concept of this game has a long history, our game is called **Crazy Snake** for some reasons.   
 There are many new features that make this game differ from the traditional console snake game. For example, this game provides a large diversity of obstacles and foods to maximize the playfulness.  
 The full features will be introduced in the next section.  

## :dragon_face:Game features (By Wong wai chun)
 
 ### Gameplay
  Using the keys (W, A, S, D) on the keyboard to control the movement of the snake.
 ### Foods and Obstacles
  The following types of foods and obstacles will be appeared in **Crazy Snake**:  
  * Normal food
  * Toxic food
  * Hard obstacle
  * Soft obstacle
  
  As the score increase and time goes on, the probability of appearing obstacles and toxic food will be increased.  
  The details of rewards and penalties will be introduced in the **Introduction to game rules** section.
 ### Difficulty
  **Crazy Snake** provides four difficulties for selection: *Beginner*, *Intermediate*, *Pro*, *Master*.  
  *Beginner* is the easiest while *Master* is the most difficult.  
  The parametes such as initial moving speed of the snake, the appearance proportion of toxic food to normal food, the appearance frequency of hard and fatal obstacles, will increase with increasing difficulties.  
  Players are allowed to choose their favored difficulty before starting the game to maximize the gaming experience.
 ### Save and Load
  **Crazy Snake** allows player to save and load the game progress.
 
 
## :seedling: Introduction to Game rules (by Huang xinghai)
1. These are some stuff will see while the game
2. 1. Obstacle
3. 2. 1. Hard obstacle
4. 3. 2. 1. Random bound to one of the perpendicular direction
5. 4. 3. 2. Deduced one unit length of the snake
6. 5. 4. 3. Reduced score by 5
7. 5. 4. 4. Decrease tails length by 1
8. 6. 5. Soft obstacle
9. 7. 6. 1. Random bound to one of the perpendicular direction
10. 1. Food
11. 2. 1. Normal food
12. 3. 2. 1. Score by 10
13. 3. 2. 2. Increase tails length by 1
14. 4. 3. Toxic food
15. 4. 4. 1. Reduced score by 5
16. 4. 4. 2. Decrease tails length by 1

The snake eats different stuff will gain the score or change the states in the game.
The player should avoid colliding with the fatal obstacle event the hard obstacle and toxic food, it will lose the game or deduce the score.

#####   
How to win the game
1. If the player attain the particular scores and length of tail, then win the game (each difficulty will have different winning goals, players can check on the "Game Rules" page within the game.
2. It can continue to the game to break the records if the player won the game
3. If the player collides with a fatal obstacle, then lose the game

## :detective: Technique involved (by Huang xinghai)
1. #include <conio.h> for sleep(), time delay for making animation
2. #include <windows.h> for detected user key press event
3. #include <fstream> for read/write file stream
4. Display clear console and display multi-line text every particular time, to make the animation smoother, it should be refreshed the console at least more than or close to 24 times per seconds
5. Calculate the snake tails which will grow by eat something
6. Calculate the time interval between the console display and the speed of the snake. 
7. Data structure: the location of tail, foods, obstacles will be stored in 1D arrays.

## :man_in_tuxedo:Game flow (by Huang xinghai)
1. Game title and options menu will be displayed on the main page
2. Player can press key [1-6], it will go to the following page.
3. 1. [1]Start a new game
4. 2. [2]Load the game
5. 3. [3]How to play
6. 4. [4]Change difficulty
7. 5. [5]Exit the game 
8. If the player start a game, then all the console text will be clear, Then show the game page consist of the text and have the animation
9. Player controls the movement of the snake by press the direction key.
10. If the player press key [p] while gaming, which will pause the game.
11. If the player press key [x] while gaming, which will save the game and back to the menu page.
12. If the player press key [e] while gaming, which will back to the main page.
