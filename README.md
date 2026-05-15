# Lorenz Attractor

A real-time visualization of the Lorenz Attractor system built with C++ and raylib, rendered in 2D by projecting the three-dimensional chaotic system onto the XZ plane.

---

## Table of Contents

- [Overview](#overview)
- [The Mathematics](#the-mathematics)
- [Features](#features)
- [Dependencies](#dependencies)
- [Building](#building)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Parameters](#parameters)
- [References](#references)

---

## Overview

The Lorenz Attractor is a set of chaotic solutions to the Lorenz system — a simplified mathematical model originally developed by Edward Lorenz in 1963 to describe atmospheric convection. Despite being governed by only three deterministic differential equations, the system exhibits extreme sensitivity to initial conditions, a hallmark of chaotic behavior popularly known as the **butterfly effect**.

This project numerically integrates the Lorenz system using Euler's method and renders the resulting trajectory in real time using the raylib graphics library.

---

## The Mathematics

The Lorenz system is defined by three coupled ordinary differential equations:

```
dx/dt = σ(y - x)
dy/dt = x(ρ - z) - y
dz/dt = xy - βz
```

Where:

- `x`, `y`, `z` — the state of the system at time `t`
- `σ` (sigma) — the Prandtl number, relates to fluid viscosity
- `ρ` (rho) — the Rayleigh number, relates to temperature difference
- `β` (beta) — a geometric factor of the system

### Classic Parameters

| Parameter | Symbol | Value       |
| --------- | ------ | ----------- |
| Sigma     | σ      | 10.0        |
| Rho       | ρ      | 28.0        |
| Beta      | β      | 8/3 ≈ 2.667 |

These values produce the iconic double-lobe butterfly attractor. Changing them yields qualitatively different attractors or even non-chaotic behavior.

### Numerical Integration — Euler's Method

Since the Lorenz system has no closed-form analytical solution, it is solved numerically. At each time step `dt`, the next state is approximated as:

```
x_new = x + (dx/dt) * dt
y_new = y + (dy/dt) * dt
z_new = z + (dz/dt) * dt
```

A fixed time step of `dt = 0.005` is used for simulation stability and visual consistency, independent of the render frame rate.

### 2D Projection

The three-dimensional trajectory is projected onto the **XZ plane** to produce the classic butterfly wing shape:

```
screen_x =  (x * scale) + screen_width  / 2
screen_y = -(z * scale) + screen_height / 2
```

The Y axis is negated because raylib's screen Y axis increases downward, while the attractor's Z axis increases upward.

### Initial Conditions

```
x =  0.1
y =  0.0
z =  0.0
```

The system is highly sensitive to these values — any small perturbation leads to an entirely different long-term trajectory, despite the overall shape of the attractor remaining the same.

---

## Features

- Real-time numerical simulation of the Lorenz system
- Smooth trail rendering using consecutive line segments
- Configurable simulation parameters (dt, scale, history length)
- Interactive zoom and pan controls
- Color gradient across the trail based on point index or speed

---

## Dependencies

| Dependency                        | Version | Purpose                                  |
| --------------------------------- | ------- | ---------------------------------------- |
| [raylib](https://www.raylib.com/) | 5.x     | Window creation, input, and 2D rendering |
| C++ Standard Library              | C++17   | `std::vector`, `std::string`             |

---

## Building

### Linux / macOS

Make sure raylib is installed on your system, then:

```bash
g++ main.cpp -o lorenz -lraylib -lm -lpthread -ldl -std=c++17
./lorenz
```

### Windows (MinGW)

```bash
g++ main.cpp -o lorenz.exe -lraylib -lopengl32 -lgdi32 -lwinmm -std=c++17
lorenz.exe
```

### Using CMake

```cmake
cmake_minimum_required(VERSION 3.15)
project(LorenzAttractor)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib REQUIRED)

add_executable(lorenz main.cpp)
target_link_libraries(lorenz raylib)
```

```bash
mkdir build && cd build
cmake ..
make
./lorenz
```

---

## Controls

| Key / Input       | Action           |
| ----------------- | ---------------- |
| Mouse Wheel Up    | Zoom in          |
| Mouse Wheel Down  | Zoom out         |
| Middle Mouse Drag | Pan view         |
| `R`               | Reset simulation |
| `ESC`             | Quit             |

---

## Project Structure

```
lorenz-attractor/
├── main.cpp        # Entry point, simulation loop, rendering
└── README.md       # This file
```

---

## Parameters

These constants at the top of `main.cpp` can be adjusted to change the visual and simulation behavior:

| Constant     | Default | Description                                    |
| ------------ | ------- | ---------------------------------------------- |
| `SIGMA`      | 10.0    | Lorenz sigma parameter                         |
| `RHO`        | 28.0    | Lorenz rho parameter                           |
| `BETA`       | 2.667   | Lorenz beta parameter                          |
| `DT`         | 0.005   | Simulation time step — smaller = more accurate |
| `SCALE`      | 10.0    | Pixels per unit — controls zoom level          |
| `MAX_POINTS` | 100000  | Maximum trail length before oldest points drop |

---

## References

- Lorenz, E. N. (1963). _Deterministic Nonperiodic Flow_. Journal of Atmospheric Sciences, 20(2), 130–141.
- [raylib official documentation](https://www.raylib.com/)
- [Lorenz system — Wikipedia](https://en.wikipedia.org/wiki/Lorenz_system)
