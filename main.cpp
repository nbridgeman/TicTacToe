#include <iostream>

using namespace std;

size_t BOARD_DIM = 3;

class Player {
public:
    Player() {
        _piece = '\0';
    }

    Player(char piece) {
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
        cout << "  ";
        for (size_t col = 0; col < BOARD_DIM; col++) {
            cout << col + 1 << " ";
        }
        cout << endl;
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

    short get_status() {
        if (check_rows() || check_cols() || check_diags()) {
            return 1;
        } else if (is_tie()) {
            return -1;
        } else {
            return 0;
        }
    }


private:
    char ** _layout;
};

class TicTacToe {
public:
    TicTacToe() {
        _board = new Board();
        _player_one = Player('X');
        _player_two =  Player('O');
        _current_player = &_player_one;
        _other_player = &_player_two;
    }

    ~TicTacToe() {
        delete _board;
        delete _current_player;
        delete _other_player;
    }

    void swap_players() {
        Player * temp = _current_player;
        _current_player = _other_player;
        _other_player = temp;
        delete temp;
    }

    void take_turn() {
        size_t row = BOARD_DIM;
        size_t col = BOARD_DIM;
        while (row >= BOARD_DIM || col >= BOARD_DIM) {
            cout << _current_player->get_piece() << " player, please input a row and column: ";
            cin >> col >> row;
            row--;
            col--;
        }
        while (_board->get_loc(row, col) != '-') {
            cout << _current_player->get_piece() << " player, please input a row and column: ";
            cin >> row >> col;
        }
        _board->place_piece(_current_player->get_piece(), row, col);
        _board->print_board();
        swap_players();
    }

    void play() {
        _board->print_board();
        while (_board->get_status() == 0) {
            take_turn();
        }
        if (_board->get_status() == 1) {
            cout << _other_player->get_piece() << " player is the winner!" << endl;
        } else {
            cout << "It's a tie!" << endl;
        }
    }

private:
    Board * _board;
    Player _player_one;
    Player _player_two;
    Player * _current_player;
    Player * _other_player;
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}
