# redis-clone

A simple Redis clone written in C++. This is just a fun project for me to learn C++ and Redis, though I do have some plans for this project.

## Roadmap

(this is not in order of when I plan to implement it)

- [ ] Add support for [RESP](https://redis.io/docs/reference/protocol-spec/)
- [ ] Add support for other types (for now it only supports strings)
- [ ] Add support for other commands (for now it only supports `SET`, `GET`, `DEL`, and `PING`)

## Build Instructions

### Windows

**Prerequisites**

- Visual Studio 2022 (Community Edition is fine)
- CMake 3.8 or higher

**Build Steps**

1. Clone this repository

```bash
git clone https://github.com/frolleks/redis-clone.git
```

2. cd into the cloned repository

```bash
cd redis-clone
```

3. Create a build directory

```bash
mkdir build
```

4. cd into the build directory

```bash
cd build
```

5. Run CMake to generate the build files

```bash
cmake ..
```

6. Build the project

```bash
cmake --build .
```

7. Run the project

```bash
./Debug/redis.exe
```

### Linux

**Prerequisites**

- A C++ compiler (GCC or Clang)
- CMake 3.8 or higher

**Build Steps**

1. Clone this repository

```bash
git clone https://github.com/frolleks/redis-clone.git
```

2. cd into the cloned repository

```bash
cd redis-clone
```

3. Create a build directory

```bash
mkdir build
```

4. cd into the build directory

```bash
cd build
```

5. Run CMake to generate the build files

```bash
cmake ..
```

6. Build the project

```bash
cmake --build .
```

7. Run the project

```bash
./redis
```

## License

MIT License