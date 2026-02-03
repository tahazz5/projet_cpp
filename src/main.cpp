#ifdef USE_QT_GUI
#include "gui/qt/QtChessWindow.h"
#include <QApplication>
#else
#include "gui/ChessWindow.h"
#endif

int main(int argc, char **argv) {
#ifdef USE_QT_GUI
    QApplication app(argc, argv);
    chess::QtChessWindow window;
    window.show();
    return app.exec();
#else
    (void)argc;
    (void)argv;
    chess::ChessWindow window;
    window.show();
    return 0;
#endif
}
