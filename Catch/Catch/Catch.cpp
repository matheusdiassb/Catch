#include "Catch.h"
#include "ui_Catch.h"
#include "Player.h"

#include <QDebug>
#include <QList>
#include <QQueue>
#include <QMessageBox>
#include <QActionGroup>
#include <QSignalMapper>

Catch::Catch(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Catch),
      m_player(Player::player(Player::Red)) {

    ui->setupUi(this);

    QObject::connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(reset()));
    QObject::connect(ui->actionQuit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    QObject::connect(ui->actionAbout, SIGNAL(triggered(bool)), this, SLOT(showAbout()));

    QSignalMapper* map = new QSignalMapper(this);
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QString cellName = QString("cell%1%2").arg(row).arg(col);
            Cell* cell = this->findChild<Cell*>(cellName);
            Q_ASSERT(cell != nullptr);
            Q_ASSERT(cell->row() == row && cell->col() == col);

            m_board[row][col] = cell;

            int id = row * 8 + col;
            map->setMapping(cell, id);
            QObject::connect(cell, SIGNAL(clicked(bool)), map, SLOT(map()));
            QObject::connect(cell, SIGNAL(mouseOver(bool)), this, SLOT(updateSelectables(bool)));
        }
    }
#if QT_VERSION < QT_VERSION_CHECK(6,0,0)
    QObject::connect(map, SIGNAL(mapped(int)), this, SLOT(play(int)));
#else
    QObject::connect(map, SIGNAL(mappedInt(int)), this, SLOT(play(int)));
#endif

    // When the turn ends, switch the player.
    QObject::connect(this, SIGNAL(turnEnded()), this, SLOT(switchPlayer()));

    // Fim das jogadas disponíveis
    QObject::connect(this, SIGNAL(gameOver()), this, SLOT(showGameOver()));

    this->reset();

    this->adjustSize();
    this->setFixedSize(this->size());
}

Catch::~Catch() {
    delete ui;
}

void Catch::play(int id) {
    Cell* cell = m_board[id / 8][id % 8];
    if (cell == nullptr || !cell->isSelectable())
        return;

    Cell* neighboor = neighboor_ex(cell);

    if (neighboor != nullptr){
        cell->setState(Cell::Blocked);
        neighboor->setState(Cell::Blocked);

        foiPonto();
    }

    emit turnEnded();
}

void Catch::switchPlayer() {
    bool gameEnded = true;
    // Switch the player.
    m_player = m_player->other();

    // Aqui vai ocorrer a chegacagem de game over
    if (m_player->orientation() == Player::Horizontal){
        //checa se tem jogada na horizontal disponível
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 7; ++j) {
                if(m_board[i][j + 1]->isEmpty() && m_board[i][j]->isEmpty()){
                    gameEnded = false;
                }
            }
        }

    } else {
        //testa se tem jogada na vertical disponível
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 8; ++j) {
                if(m_board[i][j]->isEmpty() && m_board[i + 1][j]->isEmpty()){
                    gameEnded = false;
                }
            }
        }
    }

    if (gameEnded)
           emit gameOver();

    // Finally, update the status bar.
    this->updateStatusBar();
}

void Catch::reset() {
    // Reset board.
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Cell* cell = m_board[row][col];
            cell->reset();
        }
    }

    // Reset the players.
    Player* red = Player::player(Player::Red);
    red->reset();

    Player* blue = Player::player(Player::Blue);
    blue->reset();

    m_player = red;

    // Finally, update the status bar.
    this->updateStatusBar();
}

void Catch::showAbout() {
    QMessageBox::information(this, tr("Sobre"), tr("Catch\n"
                                                   "Matheus Barros - matheusdias.souza@protonmail.com\n"));
}

void Catch::updateSelectables(bool over) {
    Cell* cell = qobject_cast<Cell*>(QObject::sender());
    Q_ASSERT(cell != nullptr);

    Cell* n = neighboor_ex(cell);

    if (over) {
        if (n != nullptr) {
            if (cell->isEmpty() && n->isEmpty()) {
                cell->setState(Cell::Selectable);
                n->setState(Cell::Selectable);
            }
        }
    } else {
        if (n != nullptr) {
            if (cell->isSelectable() && n->isSelectable()) {
                cell->setState(Cell::Empty);
                n->setState(Cell::Empty);
            }
        }
    }
}

void Catch::updateStatusBar() {
    ui->statusbar->showMessage(tr("Vez do %1 (%2 a %3)")
        .arg(m_player->name()).arg(m_player->count()).arg(m_player->other()->count()));
}

Cell* Catch::neighboor_ex(Cell* cell){
    Cell* neighboor = nullptr;

    if (m_player->orientation() == Player::Horizontal) {
        if(cell->col()+1 < 8)
            neighboor = m_board[cell->row()][cell->col()+1];
    } else {
        if(cell->row()+1 < 8)
            neighboor = m_board[cell->row()+1][cell->col()];
    }

    return neighboor;
}

void Catch::foiPonto(){
    QQueue <Cell*> worklist;
    QList <Cell*> cluster;
    int linha_atual;
    int coluna_atual;
    Cell* var_atual;
    Cell* aux;

    /* criar lista todos -
     *  Vai conter todos as celulas vazias
     */
    QList <Cell*> todos;

    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if (m_board[i][j]->isEmpty()) {
                todos.append(m_board[i][j]);
            }
        }
    }

    // LOOP ENQUANTO TODOS ESTIVER CHEIA

    while (!todos.isEmpty()){
        //qDebug() << "Tamanho todos: " << todos.length();
         /* criar um worklist -
         *  Uma fila com o primeiro elemento da lista todos
         */
           worklist.enqueue(todos.takeFirst());

           while (!worklist.isEmpty()){
                       //qDebug() << "Tamanho worklist: " << worklist.length();
                 /* e uma variavel atual -
                 *  Pesquisa no atual se tem vizinhos e se eles são vazios, caso sejam eles entram entram na worklist e saem
                 *  da lista "todos"
                 *
                 *  Depois que terminar de olhar os vizinhos a variavel atual entra no cluster.
                 */

                 var_atual = worklist.dequeue();

                 linha_atual = var_atual->row();
                 coluna_atual = var_atual->col();

                 if ((linha_atual + 1) < 8){
                     Cell* c = m_board[linha_atual + 1][coluna_atual];
                     if (todos.contains(c)) {
                         worklist.enqueue(c);
                         todos.removeOne(c);
                     }
                 }

                 if ((coluna_atual + 1) < 8){
                     Cell* c = m_board[linha_atual][coluna_atual+1];
                     if (todos.contains(c)){
                         worklist.enqueue(c);
                         todos.removeOne(c);
                     }
                 }

                 if ((linha_atual - 1) >= 0){
                     Cell* c = m_board[linha_atual - 1][coluna_atual];
                     if (todos.contains(c)) {
                         worklist.enqueue(c);
                         todos.removeOne(c);
                     }
                 }

                 if ((coluna_atual - 1) >= 0){
                     Cell* c = m_board[linha_atual][coluna_atual-1];
                     if (todos.contains(c)) {
                         worklist.enqueue(c);
                         todos.removeOne(c);
                     }
                 }

                 /* criar um cluster -
                 *  Vai receber as variaveis que já foram pesquisadas,
                 */
                cluster.append(var_atual);
            }

           /*Teste se o número de itens no cluster é maior que 3, se ignora o cluster e passa pra frente
           *      Se for menor pega a quantidade de item no cluster e soma nos pontos, e colore os itens selecionados
           *      com a cor do jogador que terminou a jogada.
          */

           if(cluster.size() < 4){
               foreach(aux, cluster){
                   aux->setPlayer(m_player);
                   m_player->incrementCount();
               }
           }

           //limpa o cluster
           cluster.clear();
     }
}

void Catch::showGameOver(){
    //atualiza a barra de status com a ultima jogada
    this->updateStatusBar();

    Player* atual = m_player;
    Player* other = m_player->other();

    if (atual->count() > other->count())
        QMessageBox::information(this, tr("Vencedor"), tr("Parábens, o %1 venceu por %2 a %3.")
                                 .arg(atual->name()).arg(atual->count()).arg(other->count()));

    else if (atual->count() < other->count())
        QMessageBox::information(this, tr("Vencedor"), tr("Parábens, o %1 venceu por %2 a %3.")
                                 .arg(other->name()).arg(other->count()).arg(atual->count()));
    else
        QMessageBox::information(this, tr("Empate"), tr("O jogo empatou em %1 a %2.").arg(atual->count()).arg(other->count()));
}
