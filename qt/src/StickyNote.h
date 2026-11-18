#pragma once

#include <QPoint>
#include <QString>
#include <QWidget>

class QMouseEvent;
class QPlainTextEdit;

class StickyNote : public QWidget
{
public:
    explicit StickyNote(QWidget* parent = nullptr);

    QString text() const;
    void setText(const QString& text);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QPlainTextEdit* m_editor;

    QPoint m_dragOffset;
    bool m_dragging = false;
};