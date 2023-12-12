# C++ Maze Game

## Description

Pottery, the main character, is trapped into the Maze. In order to escape, he must get the magic diamond.       
This diamond has been enchanted by Malfoy, the wizard. Whenever Pottery gets close, it might teleport to    
another location of the Maze. He has to grab the magic diamond and escape the Maze, before Malfoy does it.    
From the beginning ot the game, Malfoy has the advantage of knowing exactly the path to the magic diamond.    
Pottery should be very careful about his steps.  

## Set up

### Step 1)
Clone the repository
```
git clone https://github.com/amplifier19/Cpp.git
```

### Step 2)
Compile the project
```
cd ./Cpp-main/BFS-Maze-Game
g++ Game.cpp -lncurses -o Game
```

### Step 3)
Execute, using as command line argument one of the maps: `map1.txt`, `map2.txt` 
```
./Game map1.txt
```

### Gameplay
- Move Pottery using ⬅️⬆️⬇️➡️    
- Let Malfoy make a move with `Space`
- Exit game with `Esc`
