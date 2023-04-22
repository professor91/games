#include"mines.h"

#include<limits>


class Game {

    private:
        int board_size;
        int difficulty[3] = {8,16,32};

    public:
            Game() {
                this->choose_difficulty();
                
            }

            void choose_difficulty() {
                int choice;
                bool flag = false;
                
                do {
                    flag = false;
                    
                    std:: cout  << "\nChoose difficulty: \n1. Easy\n2. Medium\n3. Hard"
                                << "\nEnter your choice: ";
                    
                    try {
                        std:: cin >> choice;
                        if (std::cin.fail()) {
                            throw std::invalid_argument("\nInvalid input: not a number");
                        }
                    }
                    catch (std::invalid_argument& e) {
                        flag = true;
                        std:: cerr << e.what() << std:: endl;
                        std:: cin.clear();
                        std:: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    if (choice<0 || choice>3) {
                        flag = true;
                        std:: cerr << "\nWrong Choice";
                    }
                    else {
                        board_size = difficulty[choice-1];
                    }

                }while(flag);  

            }

            void start_game() {
                Board board(board_size);

                int pos;
                bool flag = true;

                while (flag) {
                    std:: cout << "\n\nEnter Coordinate (no space): ";
                    try {
                        std:: cin >> pos;
                        if (std::cin.fail()) {
                            throw std::invalid_argument("\nInvalid input: not a number");
                        }
                    }
                    catch (std::invalid_argument& e) {
                        flag = true;
                        std:: cerr << e.what() << std:: endl;
                        std:: cin.clear();
                        std:: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    if (wrong_coordinates(pos)) {
                        std:: cout << "Wrong coordinates";
                    }
                    else {
                        int x = (pos/10) - 1;
                        int y = (pos%10) - 1;

                        if (board.right_guess(x,y)) {
                            board.print_board();
                        }
                        else {
                            board.print_board();
                            std:: cout << "\n\nBooom!! Game Over";
                            flag = false;
                        }
                    }
                }
            }

            bool wrong_coordinates(int pos) {
                if (pos/10 == 0 || pos/1000 != 0) {
                    return true;
                }
                else {
                    return false;
                }
            }

            ~Game() {
                // no memory leaks
            }

};
