#include "Othello.hpp"

namespace othello {

Game::Game() {
    for (auto& row : board_) row.fill(Cell::Empty);
    board_[3][3] = Cell::Black;
    board_[3][4] = Cell::White;
    board_[4][3] = Cell::White;
    board_[4][4] = Cell::Black;
}

Cell Game::other(Cell color) {
    return color == Cell::Black ? Cell::White : Cell::Black;
}

bool Game::inside(int row, int col) {
    return row >= 0 && row < size && col >= 0 && col < size;
}

std::vector<Move> Game::flips_for(int row, int col, Cell color) const {
    std::vector<Move> all;
    if (!inside(row, col) || color == Cell::Empty || board_[row][col] != Cell::Empty)
        return all;

    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            int r = row + dr, c = col + dc;
            std::vector<Move> line;
            while (inside(r, c) && board_[r][c] == other(color)) {
                line.push_back({r, c});
                r += dr;
                c += dc;
            }
            // Only a nonempty chain of opposite discs terminated by our disc can flip.
            if (!line.empty() && inside(r, c) && board_[r][c] == color)
                all.insert(all.end(), line.begin(), line.end());
        }
    }
    return all;
}

bool Game::is_legal(int row, int col, Cell color) const {
    return !flips_for(row, col, color).empty();
}

std::vector<Move> Game::legal_moves(Cell color) const {
    std::vector<Move> moves;
    for (int r = 0; r < size; ++r)
        for (int c = 0; c < size; ++c)
            if (is_legal(r, c, color)) moves.push_back({r, c});
    return moves;
}

bool Game::play(int row, int col) {
    if (is_over()) return false;
    auto flips = flips_for(row, col, current_);
    if (flips.empty()) return false;
    board_[row][col] = current_;
    for (auto move : flips) board_[move.row][move.col] = current_;
    current_ = other(current_);
    return true;
}

bool Game::pass() {
    if (is_over() || !legal_moves(current_).empty()) return false;
    current_ = other(current_);
    return true;
}

bool Game::is_over() const {
    for (const auto& row : board_)
        for (Cell cell : row)
            if (cell == Cell::Empty)
                return legal_moves(Cell::Black).empty() && legal_moves(Cell::White).empty();
    return true;
}

int Game::count(Cell color) const {
    int n = 0;
    for (const auto& row : board_)
        for (Cell cell : row) if (cell == color) ++n;
    return n;
}

Outcome Game::outcome() const {
    if (!is_over()) return Outcome::InProgress;
    if (count(Cell::Black) > count(Cell::White)) return Outcome::BlackWins;
    if (count(Cell::Black) < count(Cell::White)) return Outcome::WhiteWins;
    return Outcome::Draw;
}

}  // namespace othello
