# Building Raptor

The engine currently enjoys a variety of c++17 features, and uses CMake to manage its sprawling core of semi-managed dependencies.  Whilst building Raptor, **no** additional software is installed to any root path on your computer; all software requirements are safely housed within the Raptor root directory.  Thus, it is completely safe to delete the Raptor folder in your file system, and not have to worry about dependencies that haven't been cleaned up.

## Prerequisites

First, make sure that you have a proper C++ development environment set up.  The engine only offers Linux support for the time being (ARM / 32 bit / 64 bit), and installing dependencies on those platforms is quite simple.  In order to begin building and hacking on the engine, you'll need to have:
- CMake 3.5
- gcc / g++ 8.0
- OpenGL 3.3
- GLEW
- X Window Server

We'll provide all the rest at build time.
