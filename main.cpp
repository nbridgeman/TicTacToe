#include <iostream>

using namespace std;

size_t BOARD_DIM = 3;

class Player {
public:
    Player() {
        _piece = '\0';
    }

    void set_piece(char piece) {
        _piece = piece;
    }

    char get_piece() {
        return _piece;
    }

private:
    char _piece;
};

class Board {
public:
    Board() {
        _layout = new char * [BOARD_DIM];
        for (size_t row = 0; row < BOARD_DIM; row++) {
            _layout[row] = new char[BOARD_DIM];
        }
        for (size_t row = 0; row < BOARD_DIM; row++) {
            for (size_t col = 0; col < BOARD_DIM; col++) {
                _layout[row][col] = '-';
            }
        }
    }

    ~Board() {
        for (size_t i = 0; i < BOARD_DIM; i++) {
            delete[] _layout[i];
        }
        delete _layout;
    }

    void print_board() const {
        for (size_t row = 0; row < BOARD_DIM; row++) {
            cout << row + 1 << " ";
            for (size_t col = 0; col < BOARD_DIM; col++) {
                cout << _layout[row][col] << " ";
            }
            cout << endl;
        }
        cout << "  1 2 3" << endl << endl;
    }

    void place_piece(char piece, size_t row, size_t col) {
        _layout[row][col] = piece;
    }

    char get_loc(size_t row, size_t col) {
        return _layout[row][col];
    }

    bool check_rows() {
        for (size_t row = 0; row < BOARD_DIM; row++) {
            size_t col = 0;
            while (col < BOARD_DIM) {
                if (_layout[row][col] == '-') {
                    break;
                } else if (col == BOARD_DIM - 1 && _layout[row][col] == _layout[row][0]) {
                    return true;
                } else if (_layout[row][col] == _layout[row][0]) {
                    col++;
                } else {
                    break;
                }
            }
        }
        return false;
    }

    bool check_cols() {
        for (size_t col = 0; col < BOARD_DIM; col++) {
            size_t row = 0;
            while (row < BOARD_DIM) {
                if (_layout[row][col] == '-') {
                    break;
                } else if (row == BOARD_DIM - 1 && _layout[row][col] == _layout[0][col]) {
                    return true;
                } else if (_layout[row][col] == _layout[0][col]) {
                    row++;
                } else {
                    break;
                }
            }
        }
        return false;
    }

    bool check_diags() {
        size_t index = 0;
        while (index < BOARD_DIM) {
            if (_layout[index][index] == '-') {
                break;
            } else if (index == BOARD_DIM - 1 && _layout[index][index] == _layout[0][0]) {
                return true;
            } else if (_layout[index][index] == _layout[0][0]) {
                index++;
            } else {
                break;
            }
        }
        index = 0;
        while (index < BOARD_DIM) {
            if (_layout[index][BOARD_DIM - 1 - index] == '-') {
                break;
            } else if (index == BOARD_DIM - 1 && _layout[index][BOARD_DIM - 1 - index] == _layout[0][BOARD_DIM - 1]) {
                return true;
            } else if (_layout[_layout[index][BOARD_DIM - 1 - index] == _layout[0][BOARD_DIM - 1]]) {
                index++;
            } else {
                break;
            }
        }
        return false;
    }

    bool is_winner() {
        if (check_rows() || check_cols() || check_diags()) {
            return true;
        } else {
            return false;
        }
    }

    bool is_tie() {
        for (size_t row = 0; row < BOARD_DIM; row++) {
            for (size_t col = 0; col < BOARD_DIM; col++) {
                if (_layout[row][col] == '-') {
                    return false;
                }
            }
        }
        return true;
    }

private:
    char ** _layout;
};

class TicTacToe {
public:
    TicTacToe() {
        _board = new Board();
        _player_one = Player();
        _player_two =  Player();
        _player_one.set_piece('X');
        _player_two.set_piece('O');
        player_one_turn = true;
    }

    ~TicTacToe() {
        delete _board;
    }

    void take_turn() {
        size_t row = BOARD_DIM;
        size_t col = BOARD_DIM;
        while (row >= BOARD_DIM || col >= BOARD_DIM) {
            cin >> col >> row;
            row--;
            col--;
        }
        while (_board->get_loc(row, col) != '-') {
            cin >> row >> col;
        }
        if (player_one_turn) {
            _board->place_piece(_player_one.get_piece(), row, col);
            player_one_turn = false;
        } else {
            _board->place_piece(_player_two.get_piece(), row, col);
            player_one_turn = true;
        }
        _board->print_board();
    }

    void print_board() {
        _board->print_board();
    }

    bool is_winner() {
        return _board->is_winner();
    }

    bool is_tie() {
        return _board->is_tie();
    }

private:
    Board * _board;
    Player _player_one;
    Player _player_two;
    bool player_one_turn;
};

class Game {
public:
    Game() {
        _TicTacToe = new TicTacToe();
    }

    ~Game() {
        delete _TicTacToe;
    }

    void play() {
        _TicTacToe->print_board();
        _TicTacToe->take_turn();
        while (!_TicTacToe->is_winner()) {
            if (_TicTacToe->is_tie()) {
                break;
            }
            _TicTacToe->take_turn();
        }
    }

private:
    TicTacToe * _TicTacToe;
};

int main() {
    Game test = Game();
    test.play();
    return 0;
}
