#pragma once

#include "../../core/Position.h"
#include "../../engine/SimpleAI.h"

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;

namespace chess {

class QtChessWindow : public QWidget {
public:
    explicit QtChessWindow(QWidget *parent = nullptr);

private:
    void handleSubmitMove();
    void handleNewGame();
    void setupUi();
    void refreshBoard();
    void updateStatus(const QString &message);
    bool applyHumanMove(const QString &input);
    void maybePlayAiMove();

    Position position;
    SimpleAI ai;
    int humanColor;

    QLabel *statusLabel;
    QLineEdit *moveInput;
    QPushButton *submitButton;
    QPushButton *newGameButton;
    QLabel *boardLabels[8][8];
};

} // namespace chess
