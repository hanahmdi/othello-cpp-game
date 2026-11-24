#include "Othello.hpp"

#include <iostream>
#include <sstream>
#include <string>

using othello::Cell;
using othello::Game;

void show(const Game& game) {
    std::cout << "\n     1 2 3 4 5 6 7 8\n";
    for (int r = 0; r < Game::size; ++r) {
        std::cout << "  " << r + 1 << "  ";
        for (int c = 0; c < Game::size; ++c)
            std::cout << static_cast<char>(game.board()[r][c]) << ' ';
        std::cout << '\n';
    }
    std::cout << "Black: " << game.count(Cell::Black)
              << " | White: " << game.count(Cell::White) << "\n";
}

int main() {
    Game game;
    std::cout << "Othello / Reversi - Two-player C++ Console Edition\n";
    std::cout << "Enter: row col (1..8), or q to exit.\n";
    while (!game.is_over()) {
        show(game);
        const Cell active = game.current_player();
        const auto moves = game.legal_moves(active);
        std::cout << (active == Cell::Black ? "Black" : "White") << " to move. ";
        if (moves.empty()) {
            std::cout << "No legal move: turn passes automatically.\n";
            game.pass();
            continue;
        }
        std::cout << "Enter row col: ";
        std::string line;
        if (!std::getline(std::cin, line) || line == "q" || line == "Q") {
            std::cout << "Session ended.\n";
            return 0;
        }
        int row, col;
        std::istringstream input(line);
        std::string extra;
        if (!(input >> row >> col) || (input >> extra) ||
            !game.play(row - 1, col - 1)) {
            std::cout << "Invalid move. Select an empty cell that brackets opposing discs.\n";
        }
    }
    show(game);
    std::cout << "Game over: ";
    switch (game.outcome()) {
    case othello::Outcome::BlackWins: std::cout << "Black wins!\n"; break;
    case othello::Outcome::WhiteWins: std::cout << "White wins!\n"; break;
    case othello::Outcome::Draw: std::cout << "Draw.\n"; break;
    default: break;
    }
}
