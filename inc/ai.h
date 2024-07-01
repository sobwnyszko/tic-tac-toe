#pragma once
#include "board.h"

class ai : public board {
  private:
    int x, y;
    int glebokosc;  // maksymalna glebokosc rekursji

  public:
    ai(int glebokosc) : glebokosc(glebokosc) {};
    int minimax(board _board, int depth, int mn, int mx, int alpha, int beta, bool maximizing) const; // gracz - max, ai - min
    void move(board _board, int a);
    int getx() const { return x; }
    int gety() const { return y; }


};
