#include "utils.cpp"
#include <limits>
#include <stdlib.h>
#include <time.h>

int INFINITY = numeric_limits<int>::max();
int generated;
int expanded;

int negamax(state s, int depth, bool player){
    generated++;
    if (depth == 0 || s.terminal(player)){
        return player ? s.value() : -s.value();
    }
    int alpha = -INFINITY;
    for(int move : s.valid_moves(player)){
        alpha = max(alpha , -negamax(s.apply_move(move,player) , depth - 1, !player));
    }
    expanded++;
    return alpha;
}

int negamax(state s, int depth, int alpha, int beta, bool player){
    generated++;
    if (depth == 0 || s.terminal(player)){
        return player ? s.value() : -s.value();
    }
    int score = -INFINITY;
    int val;
    for(int move : s.valid_moves(player)){
        val = -negamax(s.apply_move(player,move) , depth - 1, -beta, -alpha, !player);
        score = max(score , val);
        alpha = max(alpha , score);
        if (alpha >= beta) break;
    }
    expanded++;
    return score;
}

bool mayorQue(int a, int b){
    return a > b;
}

bool mayorIgual(int a, int b){
    return a >= b;
}

bool test(state s, int depth, bool player, int score, bool (*condition)(int,int)){
    generated++;
    if (depth == 0 || s.terminal(player)){
        return condition(s.value(),score);
    }
    for(int move : s.valid_moves(player)){
        if (player && test(s.apply_move(player,move) , depth - 1, !player, score , condition))
            return true;
        if (!player && !test(s.apply_move(player,move) , depth - 1, !player, score , condition))
            return false;
    }
    expanded++;
    return !(player);
}

int scout(state s, int depth, bool player){
    generated++;
    if (depth == 0 || s.terminal(player)){
        return s.value();
    }
    int score = 0;
    bool first = true;
    for(int move : s.valid_moves(player)){
        state child = s.apply_move(player,move);
        if (first){
            score = scout(child , depth - 1, !player);
            first = false;
        }
        else{
            if (player && test(child , depth, !player, score , mayorQue))
                score = scout(child , depth - 1, !player);
            if (!player && !test(child , depth, !player, score , mayorIgual))
                score = scout(child , depth - 1, !player);
        }
    }
    expanded++;
    return score;
}

int negascout(state s, int depth, int alpha, int beta, bool player){
    if (depth == 0 || s.terminal(player)){
        return player ? s.value() : -s.value();
    }
    bool first = true;
    for(int move : s.valid_moves(player)){
        generated++;
        state child = s.apply_move(player, move);
        int score;
        if (first){
            first = false;
            score = -negascout(child, depth -1, -beta, -alpha, !player);
        }
        else{
            score = -negascout(child, depth -1, -alpha - 1, -alpha, !player);
            if (alpha < score && score < beta){
                score = -negascout(child, depth -1, -beta, -score, !player);
            }
        }
        alpha = max(alpha,score);
        if (alpha >= beta)
            break;
    }
    expanded++;
    return alpha;
}

int calc_move(state s, int depth, bool player, int algorithm){
    vector<int> moves =  s.valid_moves(player);
    int best_h = player ? INFINITY : -INFINITY;
    int best_move = -1;
    for (int i : moves){
        int t;
        switch(algorithm){
            case 1:
                t = negamax(s.apply_move(i, player), depth, player);
                break;
            case 2:
                t = negamax(s.apply_move(i, player), depth, -INFINITY, INFINITY, player);
                break;
            case 3:
                t = scout(s.apply_move(i, player), depth, player);
                t = (player ? t : -t);
                break;
            case 4:
                t = negascout(s.apply_move(i, player), depth, -INFINITY, INFINITY, player);
                break;
            default:
                t = 0;
                break;
        }
        if ((!player && t > best_h) || (player && t < best_h)){
            best_h = t;
            best_move = i;
        }
    }
    return best_move;
}

state enemy_move(state s, int depth, bool player, int algorithm){
    return s.apply_move(calc_move(s, depth, player, algorithm), player);
}

int main(int argc, const char **argv) {
    int n = 0;
    int depth = 0;
    int h = 0;
    int a = 0;
    int m = 0;
    int r = 0;
    bool player = true;
    generated = 0;
    expanded = 0;

    srand (time(NULL));

    if( argc > 6 ){
        n = atoi(argv[1]);
        depth = atoi(argv[2]);
        h = atoi(argv[3]);
        a = atoi(argv[4]);
        m = atoi(argv[5]);
        r = atoi(argv[6]);
    }
    else{
        while (true){
            cout << "Ingrese el numero de filas del tablero: ";
            cin >> n;
            cout << endl;
            if (n > 0)
                break;
            cout << "Ingrese un numero de lados mayor a 0"<<endl <<endl;
        }

        while (true){
            cout << "Modos de juego: 1) IA vs IA, 2) Jugador vs IA, 3) Jugador vs Jugador" << endl;
            cout << "Ingrese un modo de juego: ";
            cin >> m;
            cout << endl;
            if (0 < m && m < 4)
                break;
            cout << "Ingrese un modo de juego valido"<<endl <<endl;
        }

        if (m != 3){

            while (true){
                cout << "Desea que el primer movimiento sea aleatorio: 0 para NO, 1 para SI ";
                cin >> r;
                cout << endl;
                if (r < 0 || r > 1)
                    break;
                cout << "Ingrese 1 o 0"<<endl <<endl;
            }

            while (true){
                cout << "Ingrese un valor para depth: ";
                cin >> depth;
                cout << endl;
                if (depth > 1)
                    break;
                cout << "Ingrese un valor mayor a 1"<<endl <<endl;
            }

            while (true){
                cout << "Heuristicas: 1) offensive, 2) defensive, 3) defensiveToOffensive, 4) offensiveToDefensive" << endl;
                cout << "Ingrese un numero de heuristica: ";
                cin >> h;
                cout << endl;
                if (0 < h && h < 5)
                    break;
                cout << "Ingrese un numero de heuristica valido"<<endl <<endl;
            }

            while (true){
                cout << "Algoritmos: 1) negamax, 2) negamax alpha-beta, 3) scout, 4) negascout" << endl;
                cout << "Ingrese un numero de algoritmo: ";
                cin >> a;
                cout << endl;
                if (0 < a && a < 5)
                    break;
                cout << "Ingrese un numero de algoritmo valido"<<endl <<endl;
            }
        }
    }

    state game = state(n,h);
    while(!game.terminal(player)){
        game.printarray(player);
        int input;
        if ((player && m > 1) || (!player && m == 3)){
            while (true){
                cout << "Ingrese el numero de la casilla: ";
                cin >> input;
                vector<int> vm = game.valid_moves(player);
                if (find(vm.begin(), vm.end(), input) != vm.end()) {
                    cout << endl;
                    break;
                }
                cout << "No se puede mover a la casilla "<< input <<endl <<endl;
            }
            game = game.apply_move(input, player);
        }
        else if ((r && game.turn == 2) || (r && game.turn == 1 && m == 1)){
            vector<int> vm = game.valid_moves(player);
            int v1 = rand() % (vm.size() -1);
            game = game.apply_move(vm[v1], player);
        }
        else{
            game = enemy_move(game, depth, player, a);
            cout << "generated: " << generated << endl;
            cout << "expanded: " << expanded << endl << endl;
            generated = 0;
            expanded = 0;
        }
        player = !player;
        cout << "Turn: " << game.turn << endl;
    }
    game.printarray(player);
    if (!player)
        cout << "\033[1m\033[94mFelicidades Player \033[0m" << endl;
    else
        cout << "\033[1m\033[91mFelicidades Enemy \033[0m" << endl;
}