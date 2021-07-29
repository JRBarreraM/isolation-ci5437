#include "utils.cpp"
int main() {
    state game = state(5);
    game.apply_move(3,true).apply_move(7,false).apply_move(8,true).printarray(true);
    // game.printarray();
    // for (auto i :game.valid_moves(true)){
    //     cout << i << " ";
    // }
    // cout << endl;
}