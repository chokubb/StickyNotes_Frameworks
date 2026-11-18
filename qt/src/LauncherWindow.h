#pragma once

#include <QWidget>

class NoteManager;

class LauncherWindow : public QWidget
{
public:
    explicit LauncherWindow(
        NoteManager* noteManager,
        QWidget* parent = nullptr
    );

private:
    NoteManager* m_noteManager;
};