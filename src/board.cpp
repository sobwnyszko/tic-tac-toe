#include "board.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

board::board(int size, int win, char player_symbol) : size(size), win(win), player_symbol(player_symbol), entries(size, vector<char>(size)) {
    // przekroczenia
    if (size < 3) {
        size = 3;
        entries.resize(size);
    }

    if (win < 2)
        win = 2;
    if (win > size)
        win = size;

    // inicjalizacja pol
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            entries[i][j] = 0;

    if (player_symbol == 'x')
        ai_symbol = 'o';
    else if (player_symbol == 'o')
        ai_symbol = 'x';
    else {
        player_symbol = 'x';
        ai_symbol = 'o';
    }

    turn = 1;  // gracz zaczyna
}

void board::print() const {
    system("cls");  // windows, czyszczenie konsoli

    // oznaczenia kolumn
    cout << string(5, ' ');
    for (int i = 0; i < size; ++i) {
        if (i < 9)
            cout << setw(1) << i + 1 << "   ";
        else
            cout << setw(2) << i + 1 << "  ";
    }
    cout << endl;

    // linia pozioma gorna
    cout << string(3, ' ') << '.' << string(4 * size - 1, '-') << "." << endl;

    for (int i = 0; i < size; ++i) {
        // oznaczenia wierszy, linie pionowe i znaki
        cout << setw(2) << i + 1 << " | ";
        for (int j = 0; j < size; ++j) {
            if (entries[j][i] == 0)
                cout << ' ';
            else
                cout << entries[j][i];
            if (j < size - 1)
                cout << " | ";
        }
        cout << " | " << i + 1;

        // linie poziome
        if (i < size - 1) {
            cout << "\n   |";
            for (int j = 0; j < size - 1; ++j){

                cout << string(3, '-') << '+';}
                cout << string(3, '-') << "|";
        }
        cout << endl;
    }

    // linia pozioma dolna
    cout << string(3, ' ') << '\'' << string(4 * size - 1, '-') << "\'" << endl;

    // oznaczenia kolumn
    cout << string(5, ' ');
    for (int i = 0; i < size; ++i) {
        if (i < 9)
            cout << setw(1) << i + 1 << "   ";
        else
            cout << setw(2) << i + 1 << "  ";
    }
    cout << endl << endl;
}

void board::set(int x, int y) {
    if (x >= 1 && x <= size && y >= 1 && y <= size) {
        if (isPlayerTurn())
            entries[x - 1][y - 1] = player_symbol;
        else
            entries[x - 1][y - 1] = ai_symbol;
    }
}

void board::reset() {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            entries[i][j] = 0;
    turn = 1;  // gracz zaczyna
}

void board::remove(int x, int y) {
    entries[x - 1][y - 1] = 0;
}

char board::check(int x, int y) const {
    if (x >= 1 && x <= size && y >= 1 && y <= size)
        return entries[x - 1][y - 1];
    else
        return 0;
}

bool board::isOccupied(int x, int y) const {
    return check(x, y);
}

bool board::isFull() const {
    for (int i = 1; i < size + 1; ++i) {
        for (int j = 1; j < size + 1; ++j)
            if (!isOccupied(i, j))
                return false;
    }
    return true;
}

bool board::isPlayerTurn() const {
    return turn;
}

int board::gameState() const {
    // 1 - gracz
    // 0 - nic/remis
    // -1 - AI

    int player_counter, ai_counter;

    // poziomo
    for (int x = 0; x < size; x++) {
        player_counter = ai_counter = 1;
        for (int y = 0; y < size - 1; y++) {
            if (entries[x][y] == entries[x][y + 1]) {
                if (entries[x][y] == player_symbol)
                    player_counter++;
                else if (entries[x][y] == ai_symbol)
                    ai_counter++;
                if (player_counter == win)
                    return 1;
                if (ai_counter == win)
                    return -1;
            }
        }
    }

    // pionowo
    for (int y = 0; y < size; y++) {
        player_counter = ai_counter = 1;
        for (int x = 0; x < size - 1; x++) {
            if (entries[x][y] == entries[x + 1][y]) {
                if (entries[x][y] == player_symbol)
                    player_counter++;
                else if (entries[x][y] == ai_symbol)
                    ai_counter++;
                if (player_counter == win)
                    return 1;
                if (ai_counter == win)
                    return -1;
            }
        }
    }

    // po przekatnych
    for (int x = 1; x < size - win + 1; x++) {
        player_counter = ai_counter = 1;
        for (int y = 0; y < (size - x - 1); y++) {
            if (entries[y][x + y] == entries[y + 1][x + y + 1]) {
                if (entries[y][x + y] == player_symbol)
                    player_counter++;
                else if (entries[y][x + y] == ai_symbol)
                    ai_counter++;
                if (player_counter == win)
                    return 1;
                if (ai_counter == win)
                    return -1;
            }
        }
    }
    for (int x = 0; x < size - win + 1; x++) {
        player_counter = ai_counter = 1;
        for (int y = 0; y < (size - x - 1); y++) {
            if (entries[x + y][y] == entries[x + y + 1][y + 1]) {
                if (entries[x + y][y] == player_symbol)
                    player_counter++;
                else if (entries[x + y][y] == ai_symbol)
                    ai_counter++;
                if (player_counter == win)
                    return 1;
                if (ai_counter == win)
                    return -1;
            }
        }
    }
    for (int x = 0; x < size - win + 1; x++) {
        player_counter = ai_counter = 1;
        for (int y = 0; y < (size - x - 1); y++) {
            if (entries[size - 1 - y][x + y] == entries[size - 1 - (y + 1)][x + y + 1]) {
                if (entries[size - 1 - y][x + y] == player_symbol)
                    player_counter++;
                else if (entries[size - 1 - y][x + y] == ai_symbol)
                    ai_counter++;
                if (player_counter == win)
                    return 1;
                if (ai_counter == win)
                    return -1;
            }
        }
    }
    for (int x = 1; x < size - win + 1; x++) {
        player_counter = ai_counter = 1;
        for (int y = 0; y < (size - x - 1); y++) {
            if (entries[size - 1 - x - y][y] == entries[size - x - y - 2][y + 1]) {
                if (entries[size - 1 - x - y][y] == player_symbol)
                    player_counter++;
                else if (entries[size - 1 - x - y][y] == ai_symbol)
                    ai_counter++;
                if (player_counter == win)
                    return 1;
                if (ai_counter == win)
                    return -1;
            }
        }
    }

    return 0;
}
