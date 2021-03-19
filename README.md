# :snake:Crazy_Snake
 Crazy_Snake game is text base game made by C++
 Contributed by 👨__*Huang xinghai*__ and 🧑__*Wong wai chun*__
 1. Group No.: 157
 2. Group members: 2 
 3. Topic: Crazy Snake
 4. Link: https://github.com/Harry556/Crazy_Snake/edit/main/README.md
 
## Game Description
 These are some new feather differ to the tradition console snake game, so that why we name it by Crazy snake.
 You will see new stuff inside the game such as obstacle, toxic food. 

## :dragon_face:Game features
 //What feather about this game, how this different to other snake?
 //Obtacle(Different type of obtacle)/Food🍉🍋
 
 pause game
 load game
 start game
 exit game(save game)
 press key to open menu while gaming
 
 setting
 set speed of snake
 set the different
 
## :seedling:Introduce the game rules
1. These are some stuff will see while the game
2. 1. Obstacle
3. 2. 1. Hard obstacle
4. 3. 2. 1. Random bound to one of the perpendicular direction
5. 4. 3. 2. Deduced one unit length of snake
6. 5. 4. 3. Reduced score by 5
7. 6. 5. Soft obstacle
8. 7. 6. 1. Random bound to one of the perpendicular direction
9. 1. Food
10. 2. 1. Normal food
11. 3. 2. 1. Score by 10
12. 4. 3. Toxic food
13. 4. 4. 1. Reduced score by 5

## :detective:Technique involved
//How to implement an animation in console
1. #include <conio.h> for sleep(), time delay for making animation
2. #include <windows.h> for detected user key press event
3. #include <fstream> for read/write file stream
4. Display clear console and display multi-line text every particular time, to make the animation smoother, it should be refreash the console at least more than or close to 24 times per seconds
5. Calculate the snake tails which will grow by eat something
6. Calculate the time interval between the console display and the speed of snake. 

## :man_in_tuxedo:Game flow
1. Game title and option menu will be displayed in the main page
2. Player can press key [1-5] for choosing the page getting in.
3. 1. [1]Start a new game
4. 2. [2]Load the game
5. 3. [3]How to play
6. 4. [4]Scores records
7. 5. [5]Exit the game 
8. If player start a game, then all the console text will be clear,Then show the game page consist of the text and have the animation
9. Player controls the movement of snake by press direction key.
10. If player press key [p] while gaming, which will pause the game.
11. If player press key [s] while gaming, which will save the game.
12. If player press key [e] while gaming, which will back to the main page.
  
