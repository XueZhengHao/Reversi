#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>

#include "Reversi.h"

using std::ostream; using std::flush; using std::endl;
using std::vector; using std::pair;

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

pair<vector<Piece>, vector<vector<Piece>>>Game::get_invaild_index_and_flip_pieces(Piece::PieceType type) {
    vector<Piece> pieces;
    vector<vector<Piece>> flips;
    for (int x = 0; x < X_SIZE; x++) {
        for (int y = 0; y < Y_SIZE; y++) {
            if (ground.get_piece(x, y) == type) {
                try {
                    do {
                        if (ground.get_piece(x + 1, y) == Piece::PieceType::Null) { break; }
                        vector<Piece> tmp;
                        for (int i = x + 1; i < X_SIZE; i++) {
                            tmp.push_back(Piece(i, y, Piece::filp(type)));
                            if (ground.get_piece(i, y) == (type)) {
                                break;
                            }
                            if (ground.get_piece(i, y) == Piece::PieceType::Null) {
                                pieces.push_back(Piece(i, y, type));
                                flips.push_back(tmp);
                                break;
                            }
                        }
                    } while (false);
                } catch (...) {}
                try {

                    do {
                        if (x - 1 < 0 || ground.get_piece(x - 1, y) == Piece::PieceType::Null) { break; }
                        vector<Piece> tmp;
                        for (int i = x - 1; i >= 0; i--) {
                            tmp.push_back(Piece(i, y, Piece::filp(type)));
                            if (ground.get_piece(i, y) == (type)) {
                                break;
                            }
                            if (ground.get_piece(i, y) == (Piece::PieceType::Null)) {
                                pieces.push_back(Piece(i, y, type));
                                flips.push_back(tmp);
                                break;
                            }
                        }
                    } while (false);
                } catch (...) {}
                try {
                    do {
                        if (ground.get_piece(x, y + 1) == Piece::PieceType::Null) { break; }
                        vector<Piece> tmp;
                        for (int i = y + 1; i < Y_SIZE; i++) {
                            tmp.push_back(Piece(x, i, Piece::filp(type)));
                            if (ground.get_piece(x, i) == (type)) {
                                break;
                            }
                            if (ground.get_piece(x, i) == (Piece::PieceType::Null)) {
                                pieces.push_back(Piece(x, i, type));
                                flips.push_back(tmp);
                                break;
                            }
                        }
                    } while (false);
                } catch (...) {}
                try {
                    do {
                        if (y - 1 < 0 || ground.get_piece(x, y - 1) == Piece::PieceType::Null) { break; }
                        vector<Piece> tmp;
                        for (int i = y - 1; i >= 0; i--) {
                            tmp.push_back(Piece(x, i, Piece::filp(type)));
                            if (ground.get_piece(x, i) == (type)) {
                                break;
                            }
                            if (ground.get_piece(x, i) == (Piece::PieceType::Null)) {
                                pieces.push_back(Piece(x, i, type));
                                flips.push_back(tmp);
                                break;
                            }
                        }
                    } while (false);
                } catch (...) {}
                try {
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
                                pieces.push_back(Piece(i, j, type));
                                flips.push_back(tmp);
                                break;

                            }
                        }
                    } while (false);
                } catch (...) {}
                try {
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
                                pieces.push_back(Piece(i, j, type));
                                flips.push_back(tmp);
                                break;

                            }
                        }
                    } while (false);
                } catch (...) {}
                try {
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
                                pieces.push_back(Piece(i, j, type));
                                flips.push_back(tmp);
                                break;

                            }
                        }
                    } while (false);
                } catch (...) {}
                try {
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
                                pieces.push_back(Piece(i, j, type));
                                flips.push_back(tmp);
                                break;

                            }
                        }
                    } while (false);
                } catch (...) {}


            }
        }

    }
    return{ pieces, flips };
}

bool Reversi::Game::add_piece(Piece piece) {
    auto invaild = get_invaild_index_and_flip_pieces(piece.get_type());
    if (invaild.first.size() == 0 || std::find(invaild.first.begin(), invaild.first.end(), piece)== invaild.first.end())
        return false;

    ground.set_piece(piece);

    for (int i = 0; i < invaild.first.size(); i++) {
        if (invaild.first[i]==(piece)) {
            for (const auto& item : invaild.second[i]) {
                ground.set_piece(item.flip());
            }
        }
    }

    return true;
}

