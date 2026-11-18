#pragma once

#include <QColor>
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

    QColor backgroundColor() const;
    QColor textColor() const;

    void setColors(
        const QColor& backgroundColor,
        const QColor& textColor
    );

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    void applyColors();

    QPlainTextEdit* m_editor;

    QColor m_backgroundColor = QColor("#FFF2A8");
    QColor m_textColor = QColor("#2B2B2B");

    QPoint m_dragOffset;
    bool m_dragging = false;
};