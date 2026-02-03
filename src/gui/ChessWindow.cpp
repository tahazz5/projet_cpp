#include "ChessWindow.h"
#include "BoardRenderer.h"
#include "../core/Position.h"
#include "../engine/MoveGenerator.h"
#include "../engine/SimpleAI.h"
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

using namespace chess;

namespace {

int squareIndexFromInput(const std::string &input, size_t offset) {
    if (offset + 1 >= input.size()) {
        return -1;
    }
    char file = input[offset];
    char rank = input[offset + 1];
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        return -1;
    }
    int fileIndex = file - 'a';
    int rankIndex = rank - '1';
    return rankIndex * 8 + fileIndex;
}

::PieceType promotionFromInput(char promo) {
    switch (promo) {
    case 'q':
        return ::PieceType::QUEEN;
    case 'r':
        return ::PieceType::ROOK;
    case 'b':
        return ::PieceType::BISHOP;
    case 'n':
        return ::PieceType::KNIGHT;
    default:
        return ::PieceType::NONE;
    }
}

bool parseMoveInput(const std::string &input, ::Move &move) {
    if (input.size() < 4) {
        return false;
    }
    int from = squareIndexFromInput(input, 0);
    int to = squareIndexFromInput(input, 2);
    if (from < 0 || to < 0) {
        return false;
    }
    ::PieceType promo = ::PieceType::NONE;
    if (input.size() >= 5) {
        promo = promotionFromInput(static_cast<char>(std::tolower(input[4])));
    }
    move = ::Move(::Square(from), ::Square(to), promo);
    return true;
}

bool isMoveInList(const ::Move &move, const std::vector<::Move> &moves) {
    for (const auto &candidate : moves) {
        if (candidate.get_from().get_index() == move.get_from().get_index() &&
            candidate.get_to().get_index() == move.get_to().get_index() &&
            candidate.get_promotion() == move.get_promotion()) {
            return true;
        }
    }
    return false;
}

} // namespace

ChessWindow::ChessWindow() {}

void ChessWindow::printHelp() {
    std::cout << "Commandes disponibles:\n"
              << "  - Entrez un coup au format e2e4 ou e7e8q (promotion).\n"
              << "  - tapez 'help' pour afficher cette aide.\n"
              << "  - tapez 'quit' pour quitter.\n";
}

void ChessWindow::show() {
    ::Position position;
    ::SimpleAI ai(2);
    int humanColor = 0;

    std::cout << "=== Interface texte Chess GUI ===\n";
    std::cout << "Choisissez votre couleur (0 = blanc, 1 = noir): ";
    if (!(std::cin >> humanColor) || (humanColor != 0 && humanColor != 1)) {
        std::cout << "Choix invalide. Blanc par defaut.\n";
        humanColor = 0;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    printHelp();

    while (true) {
        std::cout << "\n";
        BoardRenderer::render(position.getBoard());
        std::cout << (position.getSideToMove() == 0 ? "Trait: Blanc\n" : "Trait: Noir\n");

        auto moves = ::MoveGenerator::generateMoves(position);
        if (moves.empty()) {
            std::cout << "Aucun coup disponible. Fin de partie.\n";
            break;
        }

        if (position.getSideToMove() == humanColor) {
            std::string input;
            std::cout << "Votre coup: ";
            std::getline(std::cin, input);
            if (input == "quit") {
                std::cout << "Fin de la partie.\n";
                break;
            }
            if (input == "help") {
                printHelp();
                continue;
            }

            ::Move chosenMove(::Square(0), ::Square(0), ::PieceType::NONE);
            if (!parseMoveInput(input, chosenMove) || !isMoveInList(chosenMove, moves)) {
                std::cout << "Coup invalide. Essayez a nouveau.\n";
                continue;
            }
            position.makeMove(chosenMove);
        } else {
            ::Move aiMove = ai.chooseMove(position);
            std::cout << "IA joue: " << aiMove.to_string() << "\n";
            position.makeMove(aiMove);
        }
    }
}
