#ifndef CATCH_H
#define CATCH_H

#include <QMainWindow>

#include "Cell.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class Catch;
}
QT_END_NAMESPACE

class Player;

class Catch : public QMainWindow {
    Q_OBJECT

public:
    Catch(QWidget *parent = nullptr);
    virtual ~Catch();

signals:
    void turnEnded();
    void gameOver();

private:
    Ui::Catch *ui;
    Player* m_player;
    Cell* m_board[8][8];
    Cell* neighboor_ex(Cell* cell);
    void foiPonto();

private slots:
    void play(int id);
    void switchPlayer();
    void reset();
    void showGameOver();

    void showAbout();

    void updateSelectables(bool over);
    void updateStatusBar();

};

#endif // CATCH_H
