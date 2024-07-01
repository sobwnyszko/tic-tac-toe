#include <iostream>
#include <string>

#include "ai.h"
#include "board.h"

using namespace std;

int main() {

    int a=0;
    int size, win, glebokosc;
    char player_symbol = 0, ai_symbol = 0;
    char answer = 't';  // potwierdzenie wyboru (t/n)

    while (answer == 't') {
        // wybor planszy
        cout << "ustawienia gry:" << endl << endl;

        // rozmiar
        do {
            cout << "rozmiar pola: ";
            cin >> size;
            cin.clear();
            cin.ignore(1024, '\n');
            if (size < 3){
                cout << "# minimalne wymiary  to 3x3" << endl;
            }
        } while (size < 3);

        // znaki w rzedzie do wygranej
        do {
            cout << "ilosc znakow do wygrania: ";
            cin >> win;
            cin.clear();
            cin.ignore(1024, '\n');
            if (win < 2 || win > size){
                cout << "# wartosc powinna znajdowac sie w przedziale [2 - " << size << ']' << endl;
            }
        } while (win < 2 || win > size);

        // wybor AI
        cout << endl << "ustawienia graczy:" << endl;

        // znak gracza
        do {
            cout << "znak gracza (x/o): ";
            cin >> player_symbol;
            cin.clear();
            cin.ignore(1024, '\n');
            if (!(player_symbol == 'x' || player_symbol == 'o')){
                cout << "# znak moze byc tylko 'x' lub 'o'" << endl;
            }
        } while (!(player_symbol == 'x' || player_symbol == 'o'));

        if (player_symbol == 'x'){
            ai_symbol = 'o';
        }
        else{
            ai_symbol = 'x';
        }

        // glebokosc rekursji minimax
        do {
            cout << "glebokosc rekursji AI: ";
            cin >> glebokosc;
            cin.clear();
            cin.ignore(1024, '\n');
            if (glebokosc <= 0){
                cout << "# glebokosc powinna byc weksza od 0" << endl;
            }
        } while (glebokosc <= 0);

        // potwierdzenie wyboru
        cout << endl;
        do {
            cout << "rozpoczac gre? (t/n): ";
            cin >> answer;
            cin.clear();
            cin.ignore(1024, '\n');
            if (answer != 't' && answer != 'n'){
                cout << "# znak moze byc tylko 't' lub 'n'" << endl;
            }
        } while (answer != 't' && answer != 'n');
        if(answer == 'n'){
            return 0;
        }

    board _board(size, win, player_symbol);
    ai _ai(glebokosc);

    // gra
        _board.reset();
        _board.print();

        if (player_symbol == 'x'){
            _board.changeTurn(1);
        }
        else{
            _board.changeTurn(0);
        }

        while (_board.gameState() == 0 && !_board.isFull()) {  // dopoki wygrana lub remis
            // ruch gracza
            if (_board.isPlayerTurn()) {
                int x, y;
                cout << "twoj ruch!" << endl;
                do {
                    // wczytywanie x
                    do {
                        x = 0;
                        cout << "x = ";
                        cin >> x;
                        cin.clear();
                        cin.ignore(1024, '\n');
                        if (x < 1 || x > size)
                            cout << "# x wybierz z przedzialu [1," << size << "]" << endl;
                    } while (x < 1 || x > size);

                    // wczytywanie y
                    do {
                        y = 0;
                        cout << "y = ";
                        cin >> y;
                        cin.clear();
                        cin.ignore(1024, '\n');
                        if (y < 1 || y > size)
                            cout << "# y wybierz z przedzialu [1," << size << "]" << endl;
                    } while (y < 1 || y > size);

                    // zajete pole
                    if (_board.isOccupied(x, y)) {
                        cout << "pole (" << x << ", " << y << ") jest zajete przez ";
                        if (_board.check(x, y) == player_symbol)
                            cout << "gracza (" << player_symbol << ")";
                        else
                            cout << "komputer (" << ai_symbol << ")";

                        cout << endl;
                    }
                } while (_board.isOccupied(x, y) || x < 1 || x > size || y < 1 || y > size);
                _board.set(x, y);
                _board.changeTurn(0);
            }
            // ruch ai
            else {
                cout << "komputer wykonuje ruch... ";
                    _ai.move(_board, a);
                    _board.set(_ai.getx(), _ai.gety());
                    _board.changeTurn(1);
                    ++a;
            }

            _board.print();

            // sprawdzenie stanu gry
            if (_board.isFull() && _board.gameState() == 0)
                cout << "remis!";
            else if (_board.gameState() != 0) {
                cout << "koniec gry! wygrywa ";
                if (!_board.isPlayerTurn())
                    cout << "gracz (" << player_symbol << ")";
                else
                    cout << "komputer (" << ai_symbol << ")";
            }
            cout << endl;
        }
        // potwierdzenie zakonczenia gry
        do {
            cout << "rozpoczac nowa gre? (t/n): ";
            cin >> answer;
            cin.clear();
            cin.ignore(1024, '\n');
            if (answer != 't' && answer != 'n'){
                cout << "# znak moze byc tylko 't' lub 'n'" << endl;
            }
        } while (answer != 't' && answer != 'n');
    }
}
