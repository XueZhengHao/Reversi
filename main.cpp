#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>
#include <initializer_list>
#include <string>
#include <algorithm>

#include "Reversi.h"
using namespace Reversi;

using std::cout; using std::cin;
using std::vector;

constexpr Piece::PieceType AI = Piece::PieceType::White;

auto best(std::map<Piece, vector<Piece>> invaild) -> std::shared_ptr<std::pair<Piece, vector<Piece>>> {
    return std::make_shared<std::pair<Piece, vector<Piece>>>(*invaild.begin());
}

int main() {
    Game game;
    Piece::PieceType nextType = Piece::PieceType::Black;
    while (!game.game_over()) {
        std::system("cls");
        cout << game.get_ground() << "\n";
        do {
            auto invaild = game.get_invaild(nextType);
            if (invaild.empty())
                break;
            if (nextType == AI) {
                cout << "This round for AI!\n";
                auto b = best(invaild);
                if (b == nullptr)break;
                game.add_piece(*b);
            } else {
                cout << "This round for you!\n";
                cout << "Now is " << (nextType == Piece::PieceType::Black ? "black." : "white.")
                    << "\nInvaild:\n";
                size_t index = 1;
                for (auto& piece : invaild) {
                    cout << index << ": " << piece.first.get_x() << ", " << piece.first.get_y() << ".\n";
                    index++;
                }
                cout << "Please enter the index: ";
                cin >> index;
                while (index < 1 || index > invaild.size()) {
                    cout << "F**k! Try again! ";
                    cin >> index;
                }
                --index;
                size_t i = 0;
                for (auto& p : invaild) {
                    if (i == index) {
                        print("added");
                        game.add_piece(p);
                    }
                    i += 1;
                }
                cout << std::endl;
            }
            
        } while (false);

        nextType = Piece::filp(nextType);
    }
    cout << game.get_ground() << "\n";
    game.calculate_score();
    cout << (game.white_score() < game.black_score() ? "Black" : "White") << " is winner" << std::endl;
    return 0;
}