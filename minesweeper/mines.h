#include<iostream>
#include <cstdlib>
#include <ctime>


class Board {
    private:
        const int size;
        int** board;
        char** playing_board;

    public:
        Board(int board_size) : size(board_size) {
            
            this->create_board();

            this->plant_mines();

            this->update_neighbours();

        }

        void create_board() {

            board = new int*[size];
            playing_board = new char*[size];

            for (int i=0; i<size; i++) {
                board[i] = new int[size];
                playing_board[i] = new char[size];
            }

            for (int i=0; i<size; i++) {
                for (int j=0; j<size; j++) {
                    // 0 indicates clean board
                    board[i][j] = 0;
                    playing_board[i][j] = '_';
                }
            }

            std:: cout << "Created new board of size " << size;
        }

        void plant_mines() {
            int loc = 0;

            srand(time(0));
            // number of mines = board_size * board_size/8
            for (int i=0; i<size*(size/8); i++) {
                loc = this->generate_random_number(size*size);
                board[loc/size][loc%size] = -1;
            }

            std:: cout << "\nMines Planted";
        }

        int generate_random_number(int max) {
            return rand() % max;
        }

        void update_neighbours() {

            for (int i=0; i<this->size; i++) {
                for (int j=0; j<this->size; j++) {
                    
                    if (board[i][j] == -1) {
                        this->increment_neighbours(i,j);
                    }
                }
            }

            std:: cout << "\nUpdated Neighbours";
        }

        void increment_neighbours(int row, int col) {
            
            for (int i=row-1; i<row+2; i++) {
                for (int j=col-1; j<col+2; j++) {
                    if (i>=0 && i<size && j>=0 && j<size) {
                        if (board[i][j] == -1) {
                            continue;
                        }
                        else {
                            board[i][j] += 1;
                        }
                    }
                }
            }
        }
        
        bool right_guess(int row, int col) {
            if (board[row][col] == -1) {
                playing_board[row][col] = 'm';
                return false;
            }
            else if (board[row][col] == 0) {
                reveal_batch(row,col);
                return true;
            }
            playing_board[row][col] = board[row][col] + '0'; // convert to char
            return true;
        }

        void reveal_batch(int row, int col) {
            for (int i=row-1; i<row+2; i++) {
                for (int j=col-1; j<col+2; j++) {
                    if (i>=0 && i<size && j>=0 && j<size && playing_board[i][j] == '_') {
                        if (board[i][j] == 0) {
                            playing_board[i][j] = board[i][j] + '0'; // convert to char
                            this->reveal_batch(i,j);
                        }
                        else {
                            if (board[i][j] != -1) {
                                playing_board[i][j] = board[i][j] + '0'; // convert to char
                            }
                        }
                    }
                }
            }
            return;
        }

        void print_board() {

            std:: cout << "\n    ";
            for (int j=1; j<size+1; j++) {
                std:: cout << j << " ";
            }
            std:: cout << "\n    ";
            for (int j=1; j<size+1; j++) {
                std:: cout << "--";
            }

            std:: cout << "\n";

            for (int i=0; i<size; i++) {
                std:: cout << i+1 << " | ";
                for (int j=0; j<size; j++) {
                    std:: cout << playing_board[i][j] << " ";
                }
                std:: cout << "\n";
            }
        }

        void reveal_board() {

            std:: cout << "\n    ";
            for (int j=1; j<size+1; j++) {
                std:: cout << j << " ";
            }
            std:: cout << "\n    ";
            for (int j=1; j<size+1; j++) {
                std:: cout << "--";
            }

            std:: cout << "\n";

            for (int i=0; i<size; i++) {
                std:: cout << i+1 << " | ";
                for (int j=0; j<size; j++) {
                    std:: cout << board[i][j] << " ";
                }
                std:: cout << "\n";
            }
        }

        ~Board() {
            for (int i=0; i<size; i++) {
                    delete board[i];
                    delete playing_board[i];
            }

            delete board;
            delete playing_board;
        }

};
