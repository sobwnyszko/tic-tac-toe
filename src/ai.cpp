#include "ai.h"

#include <algorithm>  // max(),min()
#include <limits>
#include <cmath>
int int_max = std::numeric_limits<int>::max();

int ai::minimax(board _board, int depth, int mn, int mx, int alpha, int beta, bool maximizing) const {
    int game_state = _board.gameState();

    if (game_state != 0 || _board.isFull() || depth == 0)
        return game_state;

    if (maximizing) {
        int max = -int_max;
        for (int i = mn; i < mx; ++i){
            for (int j = mn; j < mx; ++j){
                if (!_board.isOccupied(i, j)) {
                    _board.changeTurn(1);
                    _board.set(i, j);
                    max = std::max(max, minimax(_board, depth - 1, mn, mx, alpha, beta, false));
                    _board.remove(i, j);
                    alpha = std::max(alpha, max);
                    if (alpha >= beta){
                        return alpha;
                    }
                }
            }
        }
        return max;
    }

    else {
        int min = int_max;
        for (int i = mn; i < mx; ++i){
            for (int j = mn; j < mx; ++j){
                if (!_board.isOccupied(i, j)) {
                    _board.changeTurn(0);
                    _board.set(i, j);
                    min = std::min(min, minimax(_board, depth - 1, mn, mx, alpha, beta, true));
                    _board.remove(i, j);
                    beta = std::min(beta, min);
                    if (beta <= alpha)
                        return beta;
                }
            }
        }
        return min;
    }
}

void ai::move(board _board, int a) {
    int current, best = int_max;
    if (a == 0 && _board.getSize() > 4){
        double s = (_board.getSize()+1)/2;
        double ps = s/2;
        for (int i = ceil(s-ps); i < floor(s+ps); i++){
            for (int j = ceil(s-ps); j < floor(s+ps); j++){
                if (!_board.isOccupied(i, j)) {
                    _board.changeTurn(0);
                    _board.set(i, j);
                    current = minimax(_board, glebokosc, ceil(s-ps), floor(s+ps), -int_max, int_max, true);
                    _board.remove(i, j);
                    if (current < best) {
                        x = i;
                        y = j;
                        best = current;
                    }
                }
            }
        }
    }
    else{
        for (int i = 1; i < _board.getSize() + 1; i++){
            for (int j = 1; j < _board.getSize() + 1; j++){
                if (!_board.isOccupied(i, j)) {
                    _board.changeTurn(0);
                    _board.set(i, j);
                    current = minimax(_board, glebokosc, 1, _board.getSize() + 1, -int_max, int_max, true);
                    _board.remove(i, j);
                    if (current < best) {
                        x = i;
                        y = j;
                        best = current;
                    }
                }
            }
        }
    }
}
