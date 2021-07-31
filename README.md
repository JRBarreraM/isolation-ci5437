# IsolationMinMax

## Como correr

Ubicado en la carpeta raiz del proyecto, compilar el programa con 

```
make
```

Para ejecutar utilice el comando

```
./main <n> <depth> <h> <a> <m> <r>
```
Donde:
- n: especifica el orden del tablero nxn.
- depth: especifica la profundidad a la que los algoritmos llegaran en cada turno.
- h: especifica la heuristica utilizada por el algoritmo seleccionado, donde 1) offensive, 2) defensive, 3) defensiveToOffensive y 4) offensiveToDefensive.
- a: especifica el algoritmo utilizado para la IA, donde 1) Negamax, 2) Negamax alpha-beta, 3) Scout y 4) Negascout.
- m: especifica el modo de juego, donde 1) IA vs IA, 2) Jugador vs IA y 3) Jugador vs Jugador.
- r: especifica si el primer movimiento para la IA es aleatorio o no, donde 0) No y 1) Si.

Del mismo modo puede ejecutarse el programa simplemente con:

```
./main
```
De esta forma se inicia el programa con un menu interactivo que te permite seleccionar las opciones de la partida.

Una vez comenzada la partida el juego mostrara los turnos validos a jugar, para seleccionar una jugada introduzca el numero de la casilla correspondiente.

## Representacion Utilizada
Para representar cada estado del juego se utilizo:
- Un arreglo `board` de tamaño NxN de booleanos que indica si una casilla esta ocupada o no
- Dos entero `p_pos` y `e_pos` que indican la posicion del jugador y el oponente en dicho turno
- Un entero `turn` que indica el numero del turno
- Un entero `h` que especifica la heuristica a utlizar en ese turno

## Heuristicas
Las heuristicas implementadas son bastante sencillas, estas se basan en la cantidad de movimientos disponibles que tendran el jugador y el oponente despues de realizar el movimiento.

### Offensive
La ofensiva le otorga mayor importancia a que el jugador tenga una menor cantidad de casillas disponibles.
```
playerMoves - (enemyMoves * 2)
```

### Defensive
La defensiva le otorga mayor importancia a que el oponente tenga una mayor cantidad de casillas disponibles.
```
(playerMoves * 2) - enemyMoves
```

### Defensive to Offensive
Esta heuristica utiliza la heuristica defensiva durante la primera mitad de la partida y luego comienza aplicar la heuristica defensiva

### Offensive to Defensive
Esta funciona igual que la anterior, pero comienza con la heuristica ofensiva en la primera mitad de la partida y la segunda aplica la heuristica defensiva
