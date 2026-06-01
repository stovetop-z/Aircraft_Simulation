# Bare-Metal Aerospace Flight Engine

A strictly deterministic, zero-allocation 3D flight physics engine and machine learning testbed. Written in modern C++, this engine bypasses traditional object-oriented overhead in favor of Data-Oriented Design (DOD) to guarantee microsecond-level execution within a strict 100Hz real-time scheduling budget.

Designed specifically as an environment for Reinforcement Learning (RL) agents, the engine features a non-blocking UDP telemetry bridge to pipe continuous 13D state vectors directly into Python/PyTorch environments.

## Core Features

* **Runge-Kutta 4 (RK4) Integration:** A custom, highly stable numerical integrator operating on flat memory arrays to eliminate function-call overhead.
* **Quaternion Kinematics:** Fully 3D rotational math using quaternions to prevent gimbal lock and floating-point drift, complete with Earth-Frame to Body-Frame rotation matrices.
* **Aerodynamic Engine:** Calculates lift, induced/parasitic drag, and rotational damping coefficients across all control surfaces (ailerons, elevator, rudder).
* **SIMD Matrix Math:** Includes an untyped Memory Arena and hardware-specific intrinsics (ARM NEON / Intel AVX) for vectorized tensor mathematics.
* **Zero-Allocation IPC:** A fire-and-forget UDP telemetry layer that casts structs to raw bytes, ensuring network I/O never blocks the physics thread.

## Architecture

```text
flight_sim_project/
├── CMakeLists.txt              # Build configuration
├── include/                    # PUBLIC API
│   ├── math/                   # SIMD Tensors, Quaternions, RK4 Template
│   ├── physics/                # 13D State Vector, Control Inputs, Aero Constants
│   └── *ipc/                    # Non-blocking POSIX UDP socket definitions
├── src/                        # PRIVATE IMPLEMENTATION
│   ├── math/                   # Tensor operations and memory allocation
│   ├── physics/                # Aerodynamic force and moment equations
│   ├── *ipc/                    # OS-level networking
│   └── main.cpp                # 100Hz Main Executive Loop
├── scripts/                    # PYTHON ML BRIDGE
│   └── *udp_listener.py         # PyTorch RL integration (WIP)
└── tests/                      # VERIFICATION
    ├── test_math.cpp           # Asserts quaternion normalization & integration
    └── test_physics.cpp        # Asserts static drop and control deflections

    * indicates anything to be added.