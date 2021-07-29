#include "utils.hpp"
#include <iterator>
#include <algorithm>

state::state(const state &s) {
    n = s.n;
    p_pos = s.p_pos;
    e_pos = s.e_pos;
    board = unique_ptr<bool[]>(new bool[s.n*s.n]);
    for(int i=0; i<s.n*s.n; i++){
        board[i] = s.board[i];
    }
}

state::state(int pn) : n(pn), board(new bool[pn*pn]){
    for(int i = 0; i < n*n; i++){
        board[i] = false;
    }
}

int state::coordToPos(pair<int,int> c){
    return c.first * n + c.second;
}

pair<int,int> state::posToCoord(int p){
    return make_pair(p/n, p%n);
}

vector<int> state::valid_moves(bool player){
    vector<int> moves;
    pair<int,int> coord;

    // first move
    if ((player && p_pos == -1) || (!player && e_pos == -1)){
        for (int i = 0; i < n*n; i++)
            if (!board[i])
                moves.push_back(i);
        return moves;
    }

    if (player)
        coord = posToCoord(p_pos);
    else
        coord = posToCoord(e_pos);

    for(int i = coord.first -1; i <= coord.first +1; i++){
        if (i < 0 || i >= n)
            continue;
        for(int j = coord.second -1; j <= coord.second +1; j++){
            if ((j < 0 || j >= n) || (j == coord.second && i == coord.first))
                continue;
            int move = coordToPos(make_pair(i,j));
            if (!board[move])
                moves.push_back(move);
        }
    }
    return moves;
}
inline state state::apply_move(int move, bool player){
    state result = *this;
    result.board[move] = 1;
    if (player)
        result.p_pos = move;
    else
        result.e_pos = move;
    return result;
}

void state::printarray(bool player){
    
    vector<int> vm = valid_moves(player);
    
    for(int i = 0; i < n; i++){
        int row = i*n;
        for(int j = 0; j < n; j++){
            if (e_pos == row + j )
                cout << "\033[1m \033[91mE \033[0m";
            else if (p_pos == row + j )
                cout << "\033[1m \033[94mP \033[0m";
            else{
                if (board[row + j])
                    cout <<"\033[30m";
                else if (find(vm.begin(), vm.end(), row + j) != vm.end())
                    cout <<"\033[92m";
                if (row + j < 10)
                    cout << "0" << row + j << " ";
                else
                    cout << row + j << " ";
                cout << "\033[0m";
            }
        }
        cout << endl;
    }
}