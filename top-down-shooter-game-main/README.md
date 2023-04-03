# top-down-shooter-game
By using C++ and OpenGL (including glfw libraries),this a program that simulates a 2D top
down shooter game. Imagine a simplified version of “Space Asteroids Arcade".
We represented the ship and the bullet with triangles.
The asteroids are represented by squares that rotate towards the ship by increasing the position on Oy axis.
After creating the vao,vbo,ibo for all of our objects we can start the game.
The movement of the ship is made with W to go up,S to go down,A to move left and D to move right by increasing  each values on the axis it moves.
If we press click left(keyboard input in a callback using boolean)we shoot a bullet.
To exit the game we use ESC key. 
For creating a matrice to transform and rotatate for the asteroids we are using a for loop.In the same for loop we attributed a color(a different one for each of our object).
To increase the difficulty we used gllfwGetTime and if it goes past our limit the asteroids will start moving faster and turning red to signal the difficulty increase.
In order to make a collision we had to calculate a distance between the asteroids and the bullet and when the distance is shorter than our limit the asteroids will dissapear.
Almost the same with our ship with another distance but now for the collision we will get 100% damage(like the asteroids receive when they are shot)and we will get another change to destroy 
them by respawning in our initial ship's position.
In the console we will get messages like "Ship destroyed!/Try again!" when the ship hits the asteroids and also for the damage of the bullet.
Asteroids are spawning in waves after some time.
The ship can't get out of our screen bounds and when the bullet does it comes back to the initial position ready to shoot again.
Almost all of these steps are commented in our program.
