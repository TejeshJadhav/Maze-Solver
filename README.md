#About The Library
This Library if for Robot which will be capable of finding the end of a non-cyclic line maze, calculating the shortest path from the start point to the end point, and then driving that shortest path.  
The robot needs to be programmed with an algorithm that lets it navigate the entire maze or until it finds the end.  
This technique says that when at an intersection turn left if you can, else go straight if you can, else turn right if you can, else turn around because you are at a dead end. This algorithm will allow the robot to navigate a maze and find the end of it.  
The second part of maze solving is taking the path the robot traveled and shortening it to the correct path to the end of the maze without traveling down any dead ends. This part of maze solving is a bit trickier. The robot has to memorize the path it travels using the left hand on the wall technique and then shorten that path. The robot memorizes the path by storing each turn as a letter.  

Using This Library  
Place The Header File In the Library Folder Of Arduino Ide.  
Include the maze_solver.h in the Sketch.  
1.Call the _initialize() function.
2.Use insert("<turn direction>") fucntion on Each Turning.
3.Call run() function in a loop to Solve the Maze.
