#pragma once

#include <array>
#include <utility>
#include <vector>

namespace othello {

enum class Cell : char { Empty = '.', Black = 'B', White = 'W' };
enum class Outcome { InProgress, BlackWins, WhiteWins, Draw };

struct Move {
    int row;
    int col;
};

class Game {
public:
    static constexpr int size = 8;
    using Board = std::array<std::array<Cell, size>, size>;

    Game();
    const Board& board() const { return board_; }
    Cell current_player() const { return current_; }
    static Cell other(Cell color);

    bool is_legal(int row, int col, Cell color) const;
    std::vector<Move> legal_moves(Cell color) const;
    bool play(int row, int col);
    bool pass();
    bool is_over() const;
    int count(Cell color) const;
    Outcome outcome() const;

private:
    Board board_{};
    Cell current_ = Cell::Black;
    std::vector<Move> flips_for(int row, int col, Cell color) const;
    static bool inside(int row, int col);
};

}  // namespace othello
