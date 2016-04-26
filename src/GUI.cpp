#include <QMainWindow>
#include <QApplication>
#include <QMenuBar>
#include <QLabel>
#include <QObject>
#include <QMessageBox>

#include "GUI.hpp"

GUI::GUI() : bg(new QLabel)
{
    setFixedSize(800, 600);
    bg->setBackgroundRole(QPalette::Base);
    bg->setScaledContents(true);

    setCentralWidget(bg);

    createMenus();
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

}

void GUI::sSaveGame()
{
    QFileDialog dialog(this, tr("Save game"));
    dialog.setDefaultSuffix("sav");

    if(dialog.exec() != QDialog::Accepted)
        return;

    QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
            dialog.selectedFiles().first());

    // TODO: Save game
}

void GUI::sLoadGame()
{
    QFileDialog dialog(this, tr("Load saved game"));

    if(dialog.exec() != QDialog::Accepted)
        return;

    QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
            dialog.selectedFiles().first());

    // TODO: Load game
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
