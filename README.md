# FreshBoy

FreshBoy is a Game Boy (DMG) emulator written in modern C++.

The project started as a way to explore new features in C++20.  
It turned out to be a great way to combine my passion for embedded
systems programming with a splash of 90s nostalgia.

### Design goals

- Maximize code readability.
- Use modern C++20 features.
- No external dependencies in core library.
- Decoupled audio / video subsystem.
- Cross-platform.

### Features

- Full audio / video emulation with good performance.
- Supports ROM, MBC1, MBC2, MBC3 + RTC and MBC5 cartridges.
- RAM persistence (save data).
- Multiple color palettes.
- Original DMG boot ROM.
- Freestanding core emulator library with its own API.
  - No dependencies on other libraries, only standard C++.
  - Easy to replace SDL2 with another media library.
- Lightweight C++ wrapper library on top of native SDL2.
- Accurate CPU emulation, passes blargg's cpu_instrs tests.
- Accurate PPU emulation, passes dmg-acid2 tests.
- Accurate APU emulation, passes (most of) blargg's dmg_sound tests.

### Build instructions

#### Ubuntu 22.04
```
$ sudo apt install build-essential cmake ninja-build libsdl2-dev
$ ./install.sh
```

#### Visual Studio 2022 (17.8.3)
I've tested the build using version 17.8.3 of Visual Studio 2022 (MVSC 19.38.33133 for x64).
Make sure to enable the C++ CMake tools for Windows in the Visual Studio installer.

1. Download the latest [SDL2](https://github.com/libsdl-org/SDL/releases) development libraries for MSVC.
2. Unpack the archive and add it to the system PATH.
3. Open the Developer PowerShell for VS 2022.

```
> .\install.ps1
```

### Keymap

|  Game Boy   |   FreshBoy   |
|:-----------:|:------------:|
|      A      |      X       |
|      B      |      Z       |
|    Start    |    Return    |
|   Select    |  Backspace   |
|     Up      |      Up      |
|    Down     |     Down     |
|    Left     |     Left     |
|    Right    |    Right     |

#### Color palettes

Press C to cycle between the available color palettes.

### Screenshots

#### Roms

![](img/roms/tetris.png) ![](img/roms/zelda.png)

![](img/roms/donkey.png) ![](img/roms/pokemon.png)

![](img/roms/mario.png) ![](img/roms/mario2.png)

#### Tests

![](img/test/cpu_instrs.png) ![](img/test/instr_timing.png)

![](img/test/dmg-acid2.png) ![](img/test/dmg_sound.png)
