#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <algorithm>
#include <iterator>

#include "Reversi.h"

using std::ostream; using std::flush; using std::endl;
using std::vector; using std::pair; using std::set;

using namespace Reversi;


std::ostream& Reversi::operator<<(std::ostream& os, Ground g) {
    os << " 0123456789\n";
    int i = 0;
    for (const auto& item : g.pieces) {
        os << i;
        for (const auto& piece : item) {
            os << piece;
        }
        os << endl;
        i++;
    }
    return os;
}

bool Reversi::operator==(const Piece& lhs, const Piece& rhs) {
    return lhs.get_x()==rhs.get_x()&& lhs.get_y() == rhs.get_y()&& lhs.get_type() == rhs.get_type();
}

Reversi::Game::Game() {
    ground.set_piece(5, 5, Piece::PieceType::Black);
    ground.set_piece(6, 6, Piece::PieceType::Black);
    ground.set_piece(5, 6, Piece::PieceType::White);
    ground.set_piece(6, 5, Piece::PieceType::White);
}

std::map<Piece, vector<Piece>> Game::get_invaild(Piece::PieceType type) {
    std::map<Piece, std::vector<Piece>> ret;
    std::pair<int, int> directions[8] = {
        std::make_pair(0,1),
        std::make_pair(1,0),
        std::make_pair(0,-1),
        std::make_pair(-1,0),
        std::make_pair(1,1),
        std::make_pair(1,-1),
        std::make_pair(-1,1),
        std::make_pair(-1,-1),
    };
    for (int x = 0; x < X_SIZE; x++) {
        for (int y = 0; y < Y_SIZE; y++) {
            if (ground.get_piece(x, y) == type) {
                for (std::pair<int, int> d : directions) {
                    if (!(x + d.first <0 || x + d.first >X_SIZE ||
                        y + d.second <0 || y + d.second >Y_SIZE ||
                        ground.get_piece(x + d.first, y + d.second) == Piece::PieceType::Null||
                        ground.get_piece(x + d.first, y + d.second) == type)) {
                        vector<Piece> flips;
                        if (find(x, y, d, type, flips)) {
                            ret[flips.back()] = flips;
                        }
                    }
                }
            }

        }
    }
    
    return ret;
}/*auto add_ret = [&](Piece p, vector<Piece> f) {
        std::copy(f.begin(), f.end(), std::back_inserter(ret[p]));
        };
    for (int x = 0; x < X_SIZE; x++) {
        for (int y = 0; y < Y_SIZE; y++) {
            if (ground.get_piece(x, y) == type) {
                do {
                    if (ground.get_piece(x + 1, y) == Piece::PieceType::Null) { break; }
                    vector<Piece> tmp;
                    for (int i = x + 1; i < X_SIZE; i++) {
                        tmp.push_back(Piece(i, y, Piece::filp(type)));
                        if (ground.get_piece(i, y) == (type)) {
                            break;
                        }
                        if (ground.get_piece(i, y) == Piece::PieceType::Null) {
                            add_ret(Piece(i, y, type), tmp);
                            break;
                        }
                    }
                } while (false);
                do {
                    if (x - 1 < 0 || ground.get_piece(x - 1, y) == Piece::PieceType::Null) { break; }
                    vector<Piece> tmp;
                    for (int i = x - 1; i >= 0; i--) {
                        tmp.push_back(Piece(i, y, Piece::filp(type)));
                        if (ground.get_piece(i, y) == (type)) {
                            break;
                        }
                        if (ground.get_piece(i, y) == (Piece::PieceType::Null)) {
                            add_ret(Piece(i, y, type), tmp);
                            break;
                        }
                    }
                } while (false);
                do {
                    if (ground.get_piece(x, y + 1) == Piece::PieceType::Null) { break; }
                    vector<Piece> tmp;
                    for (int i = y + 1; i < Y_SIZE; i++) {
                        tmp.push_back(Piece(x, i, Piece::filp(type)));
                        if (ground.get_piece(x, i) == (type)) {
                            break;
                        }
                        if (ground.get_piece(x, i) == (Piece::PieceType::Null)) {
                            add_ret(Piece(x, i, type), tmp);
                            break;
                        }
                    }
                } while (false);
                do {
                    if (y - 1 < 0 || ground.get_piece(x, y - 1) == Piece::PieceType::Null) { break; }
                    vector<Piece> tmp;
                    for (int i = y - 1; i >= 0; i--) {
                        tmp.push_back(Piece(x, i, Piece::filp(type)));
                        if (ground.get_piece(x, i) == (type)) {
                            break;
                        }
                        if (ground.get_piece(x, i) == (Piece::PieceType::Null)) {
                            add_ret(Piece(x, i, type), tmp);
                            break;
                        }
                    }
                } while (false);
                do {
                    if (ground.get_piece(x + 1, y + 1) == Piece::PieceType::Null) { break; }
                    vector<Piece> tmp;
                    int i = x + 1;
                    int j = y + 1;
                    for (; i < X_SIZE && j < Y_SIZE; i++, j++) {
                        tmp.push_back(Piece(i, j, Piece::filp(type)));
                        if (ground.get_piece(i, j) == (type)) {
                            break;
                        }
                        if (ground.get_piece(i, j) == (Piece::PieceType::Null)) {
                            add_ret(Piece(i, j, type), tmp);
                            break;

                        }
                    }
                } while (false);
                do {
                    if (y - 1 < 0 || ground.get_piece(x + 1, y - 1) == Piece::PieceType::Null) { break; }
                    vector<Piece> tmp;
                    int i = x + 1;
                    int j = y - 1;
                    for (; i < X_SIZE && j >= 0; i++, j--) {
                        tmp.push_back(Piece(i, j, Piece::filp(type)));
                        if (ground.get_piece(i, j) == (type)) {
                            break;
                        }
                        if (ground.get_piece(i, j) == (Piece::PieceType::Null)) {
                            add_ret(Piece(i, j, type), tmp);
                            break;

                        }
                    }
                } while (false);
                do {
                    if (x - 1 < 0 || ground.get_piece(x - 1, y + 1) == Piece::PieceType::Null) { break; }
                    vector<Piece> tmp;
                    int i = x - 1;
                    int j = y + 1;
                    for (; i >= 0 && j < Y_SIZE; i--, j++) {
                        tmp.push_back(Piece(i, j, Piece::filp(type)));
                        if (ground.get_piece(i, j) == (type)) {
                            break;
                        }
                        if (ground.get_piece(i, j) == (Piece::PieceType::Null)) {
                            add_ret(Piece(i, j, type), tmp);
                            break;

                        }
                    }
                } while (false);
                    do {
                        if (x - 1 < 0 || y - 1 < 0 ||
                            ground.get_piece(x - 1, y - 1) == Piece::PieceType::Null) {
                            break;
                        }
                        vector<Piece> tmp;
                        int i = x - 1;
                        int j = y - 1;
                        for (; i >= 0 && j >= 0; i--, j--) {
                            tmp.push_back(Piece(i, j, Piece::filp(type)));
                            if (ground.get_piece(i, j) == (type)) {
                                break;
                            }
                            if (ground.get_piece(i, j) == (Piece::PieceType::Null)) {
                                add_ret(Piece(i, j, type), tmp);
                                break;

                            }
                        }
                    } while (false);


            }
        }

    }
    */

void Reversi::Game::add_piece(std::pair< Piece, vector<Piece>> piece) {
    ground.set_piece(piece.first);
    for (auto p : piece.second) {
        ground.set_piece(p);
    }
}

