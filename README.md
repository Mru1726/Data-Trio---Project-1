# Team Members
# Mrunali PArmar - 202401122
# Manya Rana - 202401115
# Maharshi Soni - 202401108

# **Snake Game (C++ Console Application) 🐍**

A classic **Snake Game** built in **C++** using the **Windows Console API**. The game includes **boundary detection**, **self-collision detection**, and a **score system**.  

## **📜 How to Play**
- Use **W, A, S, D** keys to control the snake:  
  - `W` → Move **Up**  
  - `A` → Move **Left**  
  - `S` → Move **Down**  
  - `D` → Move **Right**  
- Eat the food (`o`) to grow the snake.  
- Avoid **hitting the walls** or **your own body**—otherwise, it's **Game Over**!  

## **⚙️ Features**
✔️ **Boundary Handling**: The game ends if the snake hits the wall.  
✔️ **Self-Collision Detection**: If the snake runs into itself, the game ends.  
✔️ **Random Food Placement**: Food spawns at random positions within the console.  
✔️ **Score System**: The score increases each time the snake eats food.  
✔️ **Smooth Movement**: Uses the `Sleep(100)` function to control movement speed.  
✔️ **Real-Time Input Handling**: Uses `_kbhit()` to capture user input without waiting.  

## **📥 Installation & Setup**
1. **Clone this repository**  
   ```sh
   git clone https://github.com/your-username/snake-game.git
   cd snake-game
   ```
2. **Compile the code using g++ (MinGW recommended)**
   ```sh
   g++ snake.cpp -o snake.exe
   ```
3. **Run the game**
   ```sh
   ./snake.exe
   ```

## **🖥️ System Requirements**
- **Operating System**: Windows (due to `windows.h` dependency)  
- **Compiler**: MinGW (g++) or MSVC  

## **📸 Screenshot**
(You can add an image here by uploading it to your repository and linking it)

```
####################
#                  #
#        O         #
#       O O        #
#     o            #
#                  #
####################
Current Score: 5
```

## **🛠️ Future Improvements**
🔹 Add **pause and resume** functionality.  
🔹 Add **difficulty levels** (speed increase over time).  
🔹 Support for **Linux & macOS** (replace `windows.h` with cross-platform alternatives). 
🔹 Implement a **high score system** to track and display the best score across multiple game sessions.  
🔹 **Enhance graphics** by using a more advanced rendering method for a smoother and visually appealing experience.  
---

### **Enjoy the game!**
