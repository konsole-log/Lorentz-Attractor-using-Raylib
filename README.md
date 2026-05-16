# Lorenz Attractor Visualizer

A real-time 3D visualization of the Lorenz attractor built with C++ and [raylib](https://www.raylib.com/). Explore the famous chaotic system interactively by tweaking its parameters live with on-screen sliders.

## What is the Lorenz Attractor?

The Lorenz system is a set of three coupled differential equations originally derived by Edward Lorenz in 1963 while modeling atmospheric convection:

```
dx/dt = σ(y − x)
dy/dt = x(ρ − z) − y
dz/dt = xy − βz
```

Despite its simple form, the system exhibits chaotic behavior — tiny differences in initial conditions lead to vastly different trajectories. The resulting shape, known as the Lorenz attractor, resembles a butterfly and is a hallmark of chaos theory.

---

## Features

- Real-time 3D rendering of the Lorenz trajectory
- Color-coded trail (green → red) showing the evolution over time
- Interactive sliders for live adjustment of **σ (Sigma)**, **ρ (Rho)**, and **β (Beta)**
- Orbital camera — click and drag to rotate the view
- Trail automatically resets when parameters change

---

## Dependencies

- [raylib](https://www.raylib.com/) — graphics and windowing
- [raymath](https://github.com/raysan5/raylib/blob/master/src/raymath.h) — vector math (included with raylib)
- A C++ compiler (g++, clang++, or MSVC)

### Installing raylib

**Ubuntu/Debian:**

```bash
sudo apt install libraylib-dev
```

**macOS (Homebrew):**

```bash
brew install raylib
```

**Windows:**  
Download prebuilt binaries from the [raylib releases page](https://github.com/raysan5/raylib/releases) or build from source.

---

## Building

### Linux / macOS

```bash
g++ main.cpp slider.cpp lorenz.cpp draw.cpp -o lorenz -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

Or with clang:

```bash
clang++ main.cpp slider.cpp lorenz.cpp draw.cpp -o lorenz -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

### macOS (framework-style)

```bash
clang++ main.cpp slider.cpp lorenz.cpp draw.cpp -o lorenz -framework OpenGL -framework Cocoa -framework IOKit -lraylib
```

### Windows (MinGW)

```bash
g++ main.cpp slider.cpp lorenz.cpp draw.cpp -o lorenz.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

### Using Make (recommended)

A `Makefile` is included for convenience:

```bash
make        # build
make clean  # remove binary
```

Then run:

```bash
./lorenz        # Linux/macOS
lorenz.exe      # Windows
```

---

## Controls

| Input             | Action                            |
| ----------------- | --------------------------------- |
| Left-click + drag | Rotate camera (orbital)           |
| Scroll wheel      | Zoom in/out                       |
| Sigma slider      | Adjust σ — rate of convection     |
| Rho slider        | Adjust ρ — temperature difference |
| Beta slider       | Adjust β — geometric factor       |

---

## Parameters

| Parameter | Default    | Description                                                       |
| --------- | ---------- | ----------------------------------------------------------------- |
| σ (Sigma) | 10.0       | Controls how quickly x responds to the difference between x and y |
| ρ (Rho)   | 28.0       | The Rayleigh number; values above ~24.74 produce chaotic behavior |
| β (Beta)  | 8/3 ≈ 2.67 | Related to the physical dimensions of the system                  |

The classic chaotic attractor appears at the default values (σ=10, ρ=28, β=8/3). Try lowering ρ below 24 to see the system settle into a fixed point instead of oscillating chaotically.

---

## Project Structure

```
lorenz/
├── main.cpp        # Entry point, camera setup, main loop
├── slider.h        # Slider struct declaration and function signatures
├── slider.cpp      # Slider draw and update logic
├── lorenz.h        # lorenz() function declaration
├── lorenz.cpp      # Lorenz ODE integration
├── draw.h          # drawBox() declaration
├── draw.cpp        # 3D bounding box rendering
└── Makefile        # Build automation
```

Each module is self-contained: `.h` files declare the interface, `.cpp` files contain the implementation. Include only what you need in each file.

---

## License

MIT — free to use, modify, and distribute.
