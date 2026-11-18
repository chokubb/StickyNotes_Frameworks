#pragma once

#include <QWidget>

class QCloseEvent;
class NoteManager;

class LauncherWindow : public QWidget
{
public:
    explicit LauncherWindow(
        NoteManager* noteManager,
        QWidget* parent = nullptr
    );

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    NoteManager* m_noteManager;
};