#pragma once
#include <vector>

class board {
  private:
    int size;                                // rozmiar pola (kwadratowej)
    int win;                                 // ilosc znakow w rzedzie do wygranej
    bool turn;                               // kolej, 1-gracz, 0-ai
    char player_symbol, ai_symbol;           // x/o
    std::vector<std::vector<char>> entries;  // pola (x lub o)

  public:
    board(){};
    board(int size, int to_win, char player);
    int getSize() const { return size; }
    void changeTurn(bool player) { player ? turn = 1 : turn = 0; }
    void print() const;                   // wyswietlenie pola
    void set(int x, int y);               // ustawianie pola
    void remove(int x, int y);            // usuniecie pola
    void reset();                         // czyszczenie pola
    char check(int x, int y) const;       // sprawdzanie znaku w polu
    bool isOccupied(int x, int y) const;  // sprawdzanie czy pole jest zajete
    bool isFull() const;                  // sprawdzanie czy plansza jest zapelniona
    bool isPlayerTurn() const;            // sprawdzenie czy teraz jest ruch gracza
    int gameState() const;                // sprawdzanie stanu gry
};
