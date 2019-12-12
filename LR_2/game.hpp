#pragma once
#include <iostream>

class Game {
    private:
        char field[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
        int winCoord[8][3] = {
            { 0, 1, 2 },
            { 3, 4, 5 },
            { 6, 7, 8 },
            { 0, 3, 6 },
            { 1, 4, 7 },
            { 2, 5, 8 },
            { 0, 4, 8 },
            { 2, 4, 6 }
        };

        void drawGameField() {
            for (int i = 0; i < 3; i++) {
                std::cout << field[0 + i * 3] << " " << field[1 + i * 3] << " " << field[2 + i * 3] << std::endl;
            }
        };

        void processInput(char name) {
            bool valid = false;

            while (!valid) {
                try {
                    int move;
                    std::cout << "MOVE " << name << " TO: " << std::endl;

                    std::cin >> move;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        throw std::invalid_argument("Input must be integer!");
                    }

                    if (move > 0 && move < 10) {
                        if (field[move - 1] != 'x' && field[move - 1] != 'o') {
                            field[move - 1] = name;
                            valid = true;
                        } else throw std::invalid_argument("Already busy!");
                    } else throw std::invalid_argument("Invalid Input.");
                } catch (std::invalid_argument exc) {
                    std::cout << exc.what() << std::endl;
                    std::string str;
                    std::getline(std::cin, str);
                }
            }
        };

        char checkWinner() {
            for (int i = 0; i < 8; i++) {
                if (
                    field[winCoord[i][0]] == field[winCoord[i][1]] &&
                    field[winCoord[i][0]] == field[winCoord[i][2]] &&
                    field[winCoord[i][1]] == field[winCoord[i][2]]
                ) {
                    return field[winCoord[i][0]];
                }
            }
            return '\0';
        };

    public:
        Game() {};

        void start() {
            int counter = 0;
            bool hasWinner = false;

            while (!hasWinner) {
                system("clear");
                counter++;
                drawGameField();
                processInput((counter % 2 == 0) ? 'x' : 'o');

                if (counter > 4) {
                    char winner = checkWinner();

                    if (winner != '\0') {
                        hasWinner = true;
                        system("clear");
                        drawGameField();
                        std::cout << "WINNER: " << winner << std::endl;
                        break;
                    }
                }

                if (counter == 9) {
                    system("clear");;
                    std::cout << "DRAW!" << std::endl;
                    break;
                }
            }
        };
};
