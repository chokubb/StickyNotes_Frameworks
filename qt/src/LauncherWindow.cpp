#include "LauncherWindow.h"
#include "NoteManager.h"

#include <QPushButton>
#include <QVBoxLayout>

#include <QApplication>
#include <QCloseEvent>

LauncherWindow::LauncherWindow(
    NoteManager* noteManager,
    QWidget* parent
)
    : QWidget(parent),
    m_noteManager(noteManager)
{
    setWindowTitle("Sticky Notes");
    setFixedSize(220, 100);

    auto* layout = new QVBoxLayout(this);

    auto* newNoteButton =
        new QPushButton("+  New sticky note", this);

    newNoteButton->setMinimumHeight(50);

    newNoteButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #FFF2A8;"
        "    border: 1px solid #D6C875;"
        "    border-radius: 8px;"
        "    font-size: 16px;"
        "    color: #2B2B2B;"
        "}"
        "QPushButton:hover {"
        "    background-color: #FFED8A;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #F2DF75;"
        "}"
    );

    layout->addWidget(newNoteButton);

    connect(
        newNoteButton,
        &QPushButton::clicked,
        m_noteManager,
        &NoteManager::createNote
    );
}

void LauncherWindow::closeEvent(QCloseEvent* event)
{
    event->accept();

    QApplication::quit();
}