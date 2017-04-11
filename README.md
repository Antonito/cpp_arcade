# cpp_arcade
## An arcade game simulator

### Installation

```bash
make init    # Init the dependencies
make update  # Update all the dependencies
make link    # Install the dependencies
make         # Install the game
```

You can compile the full project in debug mode with
``` bash
make re DEBUG=yes
```

You can start a multiplayer game (when supported) with this command:
```bash
echo -ne "serverAddress\nserverPort\n" | ./arcade pathToTheGFXLibrary
```

### Games
We currently support a few games.
- Snake
- Nibbler
- Blockade
- Centipede
- SolarFox
- Pacman
- Pong (multiplayer, network)
- Space Invaders

### Libs
We currently support those libraries
- Allegro5
- SDL2
- SFML
- XLib
- Ncurses
- Libcaca
- LibLapin

You can switch to another library at any moment.

