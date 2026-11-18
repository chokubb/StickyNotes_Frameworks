#pragma once

#include <QPoint>
#include <QPointer>
#include <QWidget>

class QCloseEvent;
class QMouseEvent;
class QPaintEvent;
class NoteManager;
class StickyNote;

class LauncherWindow : public QWidget
{
public:
    explicit LauncherWindow(
        NoteManager* noteManager,
        QWidget* parent = nullptr
    );

protected:
    void paintEvent(QPaintEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

    void closeEvent(QCloseEvent* event) override;

private:
    QRect stackRect() const;

    NoteManager* m_noteManager;

    QPoint m_pressPosition;
    bool m_pressedOnStack = false;

    QPointer<StickyNote> m_draggedNote;
};