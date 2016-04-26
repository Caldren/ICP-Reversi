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
#include <iostream>
#include "GUI.hpp"
#include "AI.hpp"
#include "Game.hpp"

GUI::GUI() : bg(new QLabel)
{
    setFixedSize(800, 600);
    bg->setBackgroundRole(QPalette::Base);
    bg->setScaledContents(true);

    setCentralWidget(bg);

    createMenus();
}

GUI::~GUI()
{
    delete game;
    game = nullptr;
}

void GUI::createMenus()
{
    QMenu *gameMenu = menuBar()->addMenu(tr("&Game"));
    QAction *newGame = gameMenu->addAction(tr("&New game"), this,
            SLOT(sNewGame()), QKeySequence("n"));
    saveGame = gameMenu->addAction(tr("Sa&ve game"), this,
            SLOT(sSaveGame()), QKeySequence("v"));
    saveGame->setEnabled(true);
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

void GUI::sNewGame()
{
    QDialog dialog;
    QVBoxLayout *mainLayout = new QVBoxLayout;
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
    std::set<int>::iterator it = Board::SIZES.begin();
    std::advance(it, sizesList->currentIndex());
    game = new Game(*it);

    const Player *p;
    for(auto player : pobj) {
        if(player.human->isChecked()) {
            game->addPlayer(player.name->text().toStdString());
        } else {
            p = game->addPlayer(player.name->text().toStdString(), Player::AI);
            ((AI*)p)->setAlgorithm(algoList->currentIndex());
        }
    }
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

}

void GUI::sTurnPrev()
{

}

void GUI::sTurnNext()
{

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
