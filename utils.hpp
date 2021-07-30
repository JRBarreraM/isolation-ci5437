#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

class state{
    public:
        int n;
        int h;
        unique_ptr<bool[]> board;
        int p_pos = -1;
        int e_pos = -1;
        int turn  = 1;
        state(int n, int h);
        state(const state &s);
        void printarray(bool player);
        int coordToPos(pair<int,int> c);
        pair<int,int> posToCoord(int p);
        vector<int> valid_moves(bool player);
        state apply_move(int move, bool player);
        bool terminal(bool player);
        int offensive();
        int defensive();
        int defensiveToOffensive();
        int offensiveToDefensive();
        int value();
        const state& operator=(const state &s) {
            n = s.n;
            h = s.h;
            p_pos = s.p_pos;
            e_pos = s.e_pos;
            turn = s.turn;
            board = unique_ptr<bool[]>(new bool[s.n*s.n]);
            for(int i=0; i<s.n*s.n; i++){
                board[i] = s.board[i];
            }
            return *this;
        }
};