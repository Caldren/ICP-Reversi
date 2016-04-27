#include <QMainWindow>
#include <QApplication>
#include <QMenuBar>
#include <QLabel>
#include <QObject>
#include <QMessageBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QRadioButton>
#include <QComboBox>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QStatusBar>
#include <iostream>
#include "GUI.hpp"
#include "AI.hpp"
#include "Game.hpp"

GUI::GUI() : statusLeft(new QLabel), statusMiddle(new QLabel),
    statusRight(new QLabel)
{
    qscene = nullptr;
    statusBar()->setSizeGripEnabled(false);
    statusMiddle->setAlignment(Qt::AlignCenter);
    statusBar()->addWidget(statusLeft);
    statusBar()->addWidget(statusMiddle, 1);
    statusBar()->addWidget(statusRight);
    setFixedSize(800, 600);

    initView();
    createMenus();
}

GUI::~GUI()
{
    delete game;
    delete qscene;
}

void GUI::createMenus()
{
    QMenu *gameMenu = menuBar()->addMenu(tr("&Game"));
    QAction *newGame = gameMenu->addAction(tr("&New game"), this,
            SLOT(sNewGame()), QKeySequence("n"));
    saveGame = gameMenu->addAction(tr("Sa&ve game"), this,
            SLOT(sSaveGame()), QKeySequence("v"));
    saveGame->setEnabled(false);
    QAction *loadGame = gameMenu->addAction(tr("&Load game"), this,
            SLOT(sLoadGame()), QKeySequence("l"));
    gameMenu->addSeparator();
    QAction *quitGame = gameMenu->addAction(tr("&Quit"), this,
            SLOT(sQuit()), QKeySequence::Quit);

    QMenu *turnMenu = menuBar()->addMenu(tr("&Turn"));
    turnSkip = turnMenu->addAction(tr("&Skip turn"), this,
            SLOT(sTurnSkip()), QKeySequence("s"));
    turnSkip->setEnabled(false);
    turnPrev = turnMenu->addAction(tr("&Previous turn"), this,
            SLOT(sTurnPrev()), QKeySequence("b"));
    turnPrev->setEnabled(false);
    turnNext = turnMenu->addAction(tr("Nex&t turn"), this,
            SLOT(sTurnNext()), QKeySequence("f"));
    turnNext->setEnabled(false);
}

void GUI::initView()
{
    if(qscene != nullptr) {
        delete qscene;
        qscene = nullptr;
    }

    qscene = new QGraphicsScene(this);
    qview = new QGraphicsView(qscene);
    qview->setRenderHint(QPainter::Antialiasing, false);
    qview->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    qview->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);

    setCentralWidget(qview);
}

void GUI::drawBoard()
{
    if(game == nullptr)
        return;

    const Board *b = game->getBoard();
    int boardSize = b->getSize();

    setFixedSize(boardSize * sqSize + 10, boardSize * sqSize + 60);
    initView();
    bitems.clear();

    QColor c(Qt::green);
    for(int i = 0; i < boardSize; i++) {
        for(int j = 0; j < boardSize; j++) {
            BoardSquare *it = new BoardSquare(c, sqSize, i, j);
            it->setPos(QPointF(j * sqSize, i * sqSize));
            qscene->addItem(it);
            bitems.push_back(it);

            int fcolor = b->getField(i, j);
            if(fcolor != Color::EMPTY) {
                BoardCircle *c = new BoardCircle(fcolor, sqSize - 20);
                c->setPos(QPointF(10, 10));
                c->setParentItem(it);
            }
            connect(it, SIGNAL(mousePressed(int, int)), this,
                    SLOT(sHandleBoardEvent(int, int)));
        }
    }

    updateStatusBar();
}

void GUI::updateBoard()
{
    const Board *b = game->getBoard();
    int boardSize = b->getSize();

    for(int i = 0; i < boardSize; i++) {
        for(int j = 0; j < boardSize; j++) {
            BoardSquare *it = bitems[i * boardSize + j];
            int fcolor = b->getField(i, j);

            for(auto c : it->childItems()) {
               c->setParentItem(0);
               delete c;
            }

            if(fcolor != Color::EMPTY) {
                if(it->childItems().size() != 0) {
                    for(auto c : it->childItems()) {
                        c->setParentItem(0);
                        delete c;
                    }
                }

                BoardCircle *c = new BoardCircle(fcolor, sqSize - 20);
                c->setPos(QPointF(10, 10));
                c->setParentItem(it);
            }
        }
    }
}

void GUI::enableHistory()
{
    turnPrev->setEnabled(true);
    turnNext->setEnabled(true);
    turnSkip->setEnabled(true);
    saveGame->setEnabled(true);
}

void GUI::updateStatusBar()
{
    if(game == nullptr)
        return;

    const Player *p1 = game->getP1();
    const Player *p2 = game->getP2();

    if(p1 == nullptr || p2 == nullptr)
        return;

    statusLeft->setText(tr("%1: %2").arg(p1->getName().c_str()).arg(
                p1->getScore()));
    statusRight->setText(tr("%1: %2").arg(p2->getName().c_str()).arg(
                p2->getScore()));
    statusMiddle->setText(game->getCurrentPlayer()->getName().c_str());

}

void GUI::sHandleBoardEvent(int x, int y)
{
    std::cout << "Handling event for " << x << ";" << y << std::endl;
    game->playerTurn(x, y);
    updateBoard();
    updateStatusBar();
}

void GUI::sNewGame()
{
    QDialog dialog;
    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    int AIalgorithmCount = 2; // TODO

    pobj.clear();

    QGroupBox *sizes = new QGroupBox(tr("Board size"));
    QGridLayout *sizesLayout = new QGridLayout;
    QComboBox *sizesList = new QComboBox;
    for(auto s : Board::SIZES) {
        QString ss = QString::number(s);
        sizesList->addItem(ss + " x " + ss);
    }

    sizesLayout->addWidget(sizesList);
    sizes->setLayout(sizesLayout);
    mainLayout->addWidget(sizes);

    QGroupBox *algo = new QGroupBox(tr("AI algorithms"));
    QGridLayout *algoLayout = new QGridLayout;
    algoList = new QComboBox;
    for(int i = 0; i < AIalgorithmCount; i++) {
        algoList->addItem("Algorithm " + QString::number(i));
    }

    algoList->setEnabled(false);
    algoLayout->addWidget(algoList);
    algo->setLayout(algoLayout);
    mainLayout->addWidget(algo);

    for(int i = 0; i < 2; i++) {
        QGridLayout *innerLayout = new QGridLayout;
        QGroupBox *gb = new QGroupBox(tr("Player %1").arg(i + 1));
        QLabel *nameLabel = new QLabel(tr("Name:"));
        QLineEdit *nameEdit = new QLineEdit;
        nameEdit->setMaxLength(12);
        innerLayout->addWidget(nameLabel, 0, 0);
        innerLayout->addWidget(nameEdit, 0, 1, 1, 2);
        QLabel *typeLabel = new QLabel(tr("Type:"));
        QRadioButton *human = new QRadioButton(tr("Human"));
        QRadioButton *ai = new QRadioButton(tr("AI"));
        connect(ai, SIGNAL(toggled(bool)), this,
                SLOT(sCheckAIButtons(bool)));
        human->setChecked(true);
        innerLayout->addWidget(typeLabel, 1, 0);
        innerLayout->addWidget(human, 1, 1);
        innerLayout->addWidget(ai, 1, 2);

        pobj.push_back(PlayerObjects(nameEdit, human, ai));
        gb->setLayout(innerLayout);
        mainLayout->addWidget(gb);
    }

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok|
                                                     QDialogButtonBox::Cancel);
    connect(buttons, SIGNAL(accepted()), &dialog, SLOT(accept()));
    connect(buttons, SIGNAL(rejected()), &dialog, SLOT(reject()));
    mainLayout->addWidget(buttons);

    dialog.setLayout(mainLayout);
    dialog.setModal(true);
    if(dialog.exec() != QDialog::Accepted || pobj.size() != 2)
        return;

    if(game != nullptr) {
        delete game;
        game = nullptr;
    }

    // Get board size from list index
    try {
        std::set<int>::iterator it = Board::SIZES.begin();
        std::advance(it, sizesList->currentIndex());
        game = new Game(*it);
    } catch(const std::exception &e) {
        QMessageBox::critical(this, QGuiApplication::applicationDisplayName(),
                tr("Couldn't create game board: ").arg(e.what()));
        return;
    }

    const Player *p;
    for(auto player : pobj) {
        if(player.human->isChecked()) {
            game->addPlayer(player.name->text().toStdString());
        } else {
            p = game->addPlayer(player.name->text().toStdString(), Player::AI);
            ((AI*)p)->setAlgorithm(algoList->currentIndex());
        }
    }

    game->initGame();

    enableHistory();
    drawBoard();
}

void GUI::sSaveGame()
{
    QFileDialog dialog(this, tr("Save game"));
    dialog.setDefaultSuffix("sav");

    if(dialog.exec() != QDialog::Accepted)
        return;

    std::string error;
    if(!game->save(dialog.selectedFiles().first().toStdString(), error)) {
        QMessageBox::critical(this, QGuiApplication::applicationDisplayName(),
                tr("Couldn't save current game to %1\nReason: %2").arg(
                    dialog.selectedFiles().first()).arg(error.c_str()));
    }
}

void GUI::sLoadGame()
{
    QFileDialog dialog(this, tr("Load saved game"));

    if(dialog.exec() != QDialog::Accepted)
        return;

    if(game != nullptr) {
        delete game;
        game = nullptr;
    }

    try {
        game = new Game(dialog.selectedFiles().first().toStdString());
        enableHistory();
        drawBoard();
    } catch(std::exception &e) {
        QMessageBox::critical(this, QGuiApplication::applicationDisplayName(),
                tr("Couldn't load saved game from %1\nReason: %2").arg(
                    dialog.selectedFiles().first()).arg(e.what()));
    }
}

void GUI::sQuit()
{
    qApp->quit();
}

void GUI::sTurnSkip()
{
    if(game == nullptr)
        return;

    if(!game->skipTurn()) {
        QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
                "Can't skip current turn - at least one valid move is "
                "available");
    }
}

void GUI::sTurnPrev()
{
    if(game == nullptr)
        return;

    if(!game->prevTurn()) {
        QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
                "No previous turn available in history buffer");
    } else {
        updateBoard();
    }
}

void GUI::sTurnNext()
{
    if(game == nullptr)
        return;

    if(!game->nextTurn()) {
        QMessageBox::warning(this, QGuiApplication::applicationDisplayName(),
                "No next turn available in history buffer");
    } else {
        updateBoard();
    }
}

void GUI::sCheckAIButtons(bool checked)
{
    if(pobj.size() != 2)
        return;

    if(checked)
        algoList->setEnabled(true);

    if(pobj[0].ai->isChecked()) {
        pobj[1].ai->setEnabled(false);
    } else if(pobj[1].ai->isChecked()) {
        pobj[0].ai->setEnabled(false);
    } else {
        pobj[0].ai->setEnabled(true);
        pobj[1].ai->setEnabled(true);
        algoList->setEnabled(false);
    }
}
