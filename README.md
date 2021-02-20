# ncurses-pathfinding
A demonstration of Dijkstra's Pathfinding Algorithm with ncurses visuals. The terrain used in pathfinding is procedurally generated using Perlin Noise.

## Usage
1. Install the ncurses development library
2. Clone the git repository and navigate into its directory
```console
git clone https://github.com/JosCla/ncurses-pathfinding && cd ncurses-pathfinding
```
3. Build the program
```console
make
```
4. Run the program
```console
./ncpath
```

## How to use the tool
Upon entering the program, press 'c' to display the controls menu. The controls menu lists the keyboard controls used to operate the tool:
```console
arrow keys: move cursor
s: set start point (cost zero)
p: mark optimal path from start to cursor
d: delete all marked paths
```
You can also press 'q' to quit at any time.
