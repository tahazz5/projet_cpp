#include "QtChessWindow.h"

#include "../../engine/MoveGenerator.h"
#include <QGridLayout>
#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

namespace {

int squareIndexFromInput(const QString &input, int offset) {
    if (input.size() < offset + 2) {
        return -1;
    }
    const QChar file = input[offset];
    const QChar rank = input[offset + 1];
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') {
        return -1;
    }
    const int fileIndex = file.unicode() - 'a';
    const int rankIndex = rank.unicode() - '1';
    return rankIndex * 8 + fileIndex;
}

PieceType promotionFromInput(const QChar &promo) {
    switch (promo.toLower().toLatin1()) {
    case 'q':
        return PieceType::QUEEN;
    case 'r':
        return PieceType::ROOK;
    case 'b':
        return PieceType::BISHOP;
    case 'n':
        return PieceType::KNIGHT;
    default:
        return PieceType::NONE;
    }
}

bool parseMoveInput(const QString &input, Move &move) {
    if (input.size() < 4) {
        return false;
    }
    const int from = squareIndexFromInput(input, 0);
    const int to = squareIndexFromInput(input, 2);
    if (from < 0 || to < 0) {
        return false;
    }
    PieceType promo = PieceType::NONE;
    if (input.size() >= 5) {
        promo = promotionFromInput(input[4]);
    }
    move = Move(Square(from), Square(to), promo);
    return true;
}

bool isMoveInList(const Move &move, const std::vector<Move> &moves) {
    for (const auto &candidate : moves) {
        if (candidate.get_from().get_index() == move.get_from().get_index() &&
            candidate.get_to().get_index() == move.get_to().get_index() &&
            candidate.get_promotion() == move.get_promotion()) {
            return true;
        }
    }
    return false;
}

QString pieceLabel(const Piece *piece) {
    if (!piece) {
        return ".";
    }
    const char symbol = piece->to_string().front();
    return QString(QChar(symbol));
}

} // namespace

namespace chess {

QtChessWindow::QtChessWindow(QWidget *parent)
    : QWidget(parent), ai(2), humanColor(0), statusLabel(nullptr),
      moveInput(nullptr), submitButton(nullptr), newGameButton(nullptr) {
    setupUi();
    refreshBoard();
    updateStatus("Nouveau jeu. Entrez un coup (ex: e2e4).");
}

void QtChessWindow::setupUi() {
    setWindowTitle("Chess Qt GUI");
    auto *layout = new QVBoxLayout(this);
    statusLabel = new QLabel(this);
    layout->addWidget(statusLabel);

    auto *boardLayout = new QGridLayout();
    QFont boardFont;
    boardFont.setFamily("monospace");
    boardFont.setPointSize(14);
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            auto *label = new QLabel(this);
            label->setAlignment(Qt::AlignCenter);
            label->setMinimumSize(30, 30);
            label->setFont(boardFont);
            const bool dark = ((rank + file) % 2 == 1);
            label->setStyleSheet(dark ? "background:#b58863;color:white;"
                                      : "background:#f0d9b5;color:black;");
            boardLabels[rank][file] = label;
            boardLayout->addWidget(label, 7 - rank, file);
        }
    }
    layout->addLayout(boardLayout);

    auto *controlsLayout = new QHBoxLayout();
    moveInput = new QLineEdit(this);
    moveInput->setPlaceholderText("e2e4 / e7e8q");
    submitButton = new QPushButton("Jouer", this);
    newGameButton = new QPushButton("Nouvelle partie", this);
    controlsLayout->addWidget(moveInput);
    controlsLayout->addWidget(submitButton);
    controlsLayout->addWidget(newGameButton);
    layout->addLayout(controlsLayout);

    connect(submitButton, &QPushButton::clicked, this, [this]() { handleSubmitMove(); });
    connect(newGameButton, &QPushButton::clicked, this, [this]() { handleNewGame(); });
}

void QtChessWindow::refreshBoard() {
    const Board board = position.getBoard();
    for (int rank = 7; rank >= 0; --rank) {
        for (int file = 0; file < 8; ++file) {
            int index = rank * 8 + file;
            boardLabels[rank][file]->setText(pieceLabel(board.getPiece(index)));
        }
    }
}

void QtChessWindow::updateStatus(const QString &message) {
    statusLabel->setText(message);
}

bool QtChessWindow::applyHumanMove(const QString &input) {
    Move chosenMove(Square(0), Square(0), PieceType::NONE);
    if (!parseMoveInput(input.trimmed().toLower(), chosenMove)) {
        updateStatus("Coup invalide. Format attendu: e2e4 ou e7e8q.");
        return false;
    }

    auto moves = MoveGenerator::generateMoves(position);
    if (!isMoveInList(chosenMove, moves)) {
        updateStatus("Coup illégal pour la position actuelle.");
        return false;
    }
    position.makeMove(chosenMove);
    updateStatus(QString("Vous avez joué %1.").arg(QString::fromStdString(chosenMove.to_string())));
    return true;
}

void QtChessWindow::maybePlayAiMove() {
    auto moves = MoveGenerator::generateMoves(position);
    if (moves.empty()) {
        updateStatus("Aucun coup disponible. Fin de partie.");
        return;
    }
    if (position.getSideToMove() != humanColor) {
        Move aiMove = ai.chooseMove(position);
        position.makeMove(aiMove);
        updateStatus(QString("IA joue %1.").arg(QString::fromStdString(aiMove.to_string())));
    }
}

void QtChessWindow::handleSubmitMove() {
    if (position.getSideToMove() != humanColor) {
        updateStatus("Attendez le coup de l'IA.");
        return;
    }
    if (applyHumanMove(moveInput->text())) {
        maybePlayAiMove();
    }
    refreshBoard();
    moveInput->clear();
}

void QtChessWindow::handleNewGame() {
    position = Position();
    refreshBoard();
    updateStatus("Nouvelle partie. Entrez un coup.");
    if (position.getSideToMove() != humanColor) {
        maybePlayAiMove();
        refreshBoard();
    }
}

} // namespace chess
