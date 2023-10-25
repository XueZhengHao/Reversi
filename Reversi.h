#pragma once

#ifndef REVERSI_H
#define REVERSI_H "Why do you use it? It's invaild."

#include <vector>
#include <memory>
#include <iostream>
#include <utility>

namespace Reversi {
    class Piece {
    public:
        enum class PieceType {
            Null,
            Black,
            White,
        };

        int get_x() const { return x; }
        int get_y() const { return y; }

        PieceType get_type() const { return this->type; }

        Piece(int x, int y, PieceType type) :x(x), y(y), type(type) {}
        
        Piece flip() const {
            return Piece(x, y, filp(type));
        }

        static PieceType filp(PieceType piece) {
            return piece == PieceType::Black ? PieceType::White : PieceType::Black;
        }
    private:
        int x;
        int y;

        PieceType type;        
    };

    inline std::ostream& operator <<(std::ostream& os, Piece p) {
        return os <<
            (p.get_type() == Piece::PieceType::Null ? " "
                : (p.get_type() == Piece::PieceType::Black ? "X" : "O"));
    }

    bool operator == (const Piece& lhs, const Piece& rhs);

    class Ground {
        friend  std::ostream& operator<<(std::ostream& os, Ground g);
    public:
        Ground(int x_size, int y_size) :x_size(x_size), y_size(y_size), pieces() {
            init_pieces();
        }

        Piece::PieceType get_piece(int x, int y) {
            return pieces.at(y).at(x).get_type();
        }

        void set_piece(const Piece& piece) {
            pieces.at(piece.get_y()).at(piece.get_x()) = piece;
        }

        void set_piece(int x,int y,Piece::PieceType type) {
            set_piece(Piece(x, y, type));
        }
    private:
        int x_size;
        int y_size;

        std::vector<std::vector<Piece >> pieces;

        void init_pieces() {
            for (int i = 0; i < x_size; i++) {
                pieces.push_back(std::vector<Piece>());
                for (int j = 0; j < y_size; j++) {
                    pieces[i].push_back(Piece(i, j, Piece::PieceType::Null));
                }
            }
        }
    };
    std::ostream& operator <<(std::ostream& os, Ground g);
    class Game {
    public:
        static const int X_SIZE = 10, Y_SIZE = 10;

        int black_score() { return blackScore; }
        int white_score() { return whiteScore; }

        Ground get_ground() { return ground; }

        Game();

        bool add_piece(Piece piece);

        void calculate_score() {
            blackScore = whiteScore = 0;
            for (int i = 0; i < X_SIZE; i++) {
                for (int j = 0; j < Y_SIZE; j++) {
                    if (ground.get_piece(i, j) == Piece::PieceType::Black)
                        blackScore++;
                    else if (ground.get_piece(i, j) == Piece::PieceType::White)
                        whiteScore++;
                }
            }
        }

        std::vector<Piece> invaild(Piece::PieceType piece) { return get_invaild_index_and_flip_pieces(piece).first; }

        bool game_over() {
            for (int i = 0; i < X_SIZE; i++) {
                for (int j = 0; j < Y_SIZE; j++) {
                    if (ground.get_piece(i, j) ==Piece::PieceType::Null)
                        return false;
                }
            }
            return true;
        }
    private:
        Ground ground = Ground(X_SIZE, Y_SIZE);
        int blackScore = 0, whiteScore = 0;

        std::pair<std::vector<Piece>, std::vector<std::vector<Piece>>>
            get_invaild_index_and_flip_pieces(Piece::PieceType type);
    };
}
#endif // !REVERSI_H
