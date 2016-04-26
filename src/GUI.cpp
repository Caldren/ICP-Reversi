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
    QDialog dialog;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    int AIalgorithmCount = 2; // TODO

    pobj.clear();
    QGroupBox *algo = new QGroupBox(tr("AI algorithms"));
    QGridLayout *algoLayout = new QGridLayout;
    QComboBox *algoList = new QComboBox;
    for(int i = 0; i < AIalgorithmCount; i++) {
        algoList->addItem("Algorithm " + QString::number(i));
    }

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

    for(auto p : pobj) {
        std::cout << p.name->text().toStdString() << std::endl;
    }
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
