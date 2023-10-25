#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

#include "Reversi.h"
using namespace Reversi;

using std::cout; using std::cin;

int main() {
    Game game;

    Piece::PieceType nextType = Piece::PieceType::Black;
    while (!game.game_over()) {
        std::system("cls");
        cout << game.get_ground() << "\n";
        do {
            auto invaild = game.invaild(nextType);
            if (invaild.empty())
                break;
            cout << "Now is " << (nextType == Piece::PieceType::Black ? "black.\n" : "white.\n");
            for (auto& piece : invaild) {
                cout << "Invaild piece pos: " << piece.get_x() << ", "<< piece.get_y() << ".\n";
            }
            cout << ("Please enter the index: ");
            int index;
            cin >> index;
            game.add_piece(invaild[index]);
            cout << std::endl;
        } while (false);

        nextType = Piece::filp(nextType);
    }
    cout << game.get_ground() << "\n";
    game.calculate_score();
    cout << (game.white_score() < game.black_score() ? "Black" : "White") << " is winner" << std::endl;
    return 0;
}