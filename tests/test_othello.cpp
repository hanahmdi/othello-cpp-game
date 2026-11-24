#include "Othello.hpp"
#include <cassert>
#include <iostream>
#include <random>

using namespace othello;

int main() {
    { // Initialization and legal move generation.
        Game g;
        assert(g.count(Cell::Black) == 2);
        assert(g.count(Cell::White) == 2);
        assert(g.legal_moves(Cell::Black).size() == 4);
        assert(g.legal_moves(Cell::White).size() == 4);
        assert(!g.is_legal(-1, 4, Cell::Black));
        assert(!g.is_legal(8, 0, Cell::Black));
        assert(!g.is_legal(3, 3, Cell::Black));
        assert(!g.play(-1, 2));
        assert(g.current_player() == Cell::Black);
        assert(!g.pass());
        assert(g.outcome() == Outcome::InProgress);
    }
    { // Opening move and disc flipping.
        Game g;
        assert(g.is_legal(2, 4, Cell::Black));
        assert(g.play(2, 4));
        assert(g.board()[2][4] == Cell::Black);
        assert(g.board()[3][4] == Cell::Black);
        assert(g.count(Cell::Black) == 4);
        assert(g.count(Cell::White) == 1);
        assert(g.current_player() == Cell::White);
        assert(!g.play(2, 4));
    }
    { // Deterministic complete-game simulations and score invariant.
        std::mt19937 rng(20261124);
        for (int trial = 0; trial < 25; ++trial) {
            Game g;
            int turns = 0;
            while (!g.is_over() && turns < 120) {
                Cell active = g.current_player();
                auto moves = g.legal_moves(active);
                if (moves.empty()) assert(g.pass());
                else {
                    auto move = moves[rng() % moves.size()];
                    assert(g.play(move.row, move.col));
                }
                const int occupied = g.count(Cell::Black) + g.count(Cell::White);
                assert(occupied >= 4 && occupied <= 64);
                ++turns;
            }
            assert(g.is_over());
            assert(turns <= 120);
            assert(g.outcome() != Outcome::InProgress);
        }
    }
    std::cout << "PASS: initialization, legality, flipping, pass guard, and 25 complete games\n";
}
