#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

class state{
    public:
        int n;
        unique_ptr<bool[]> board;
        int p_pos = -1;
        int e_pos = -1;
        state(int pn);
        state(const state &s);
        void printarray(bool player);
        int coordToPos(pair<int,int> c);
        pair<int,int> posToCoord(int p);
        vector<int> valid_moves(bool player);
        state apply_move(int move, bool player);
};