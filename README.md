# 🕹️ cub3D - Raycast Maze Adventure  

*A 42 School project recreating Wolfenstein 3D-style graphics using ray-casting techniques*  

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)  
[![42 Norm](https://img.shields.io/badge/Codestyle-42_Norm-green.svg)](https://github.com/42School/norminette)  
![Success Rate](https://img.shields.io/badge/Success_Rate-66%25-brightgreen)  

## 🚀 Features  
- **Ray-casting Engine**:  
  - 3D projection from 2D maps  
  - Wall collision detection  
  - Floor/ceiling rendering  

- **Game Controls**:  
  - WASD movement  
  - Mouse/camera rotation  
  - Minimap toggle  

- **Map System**:  
  - `.cub` file parsing  
  - Custom texture support  
  - Color configuration  

## 📊 Project Stats  
- **Team Size**: 2 developers  
- **Development Time**: ~280 hours  
- **Success Rate**: 66.7% (832 completions)  
- **Key Challenges**:  
  - 3D math implementation  
  - Texture mapping optimization  
  - Edge case handling (1.4% leak rate)  

## 🛠️ Installation  
```bash  
git clone https://github.com/<your-username>/cub3D.git  
cd cub3D  
make  
```
Requires MiniLibX (included)

## 🎮 Usage

```bash
./cub3D maps/example.cub  
```
Gameplay Demo ← Add gameplay screenshot/GIF

## 📚 Technical Deep Dive

* **Ray-casting Math:**
```c
void cast_rays(t_game *game) {  
  // Ray direction calculation  
  // Wall distance projection  
  // Texture coordinate mapping  
}
```
**Performance:** 60 FPS target

**Memory:** Zero leaks enforced

## 🌟 Learning Outcomes
* **Graphics Programming:** Learned low-level rendering techniques

* **Team Collaboration:** Git workflow and task division

* **Optimization:** Balanced accuracy vs performance
