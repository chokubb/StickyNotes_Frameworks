#pragma once

#include <QColor>
#include <QPoint>
#include <QString>
#include <QWidget>

class QMouseEvent;
class QPlainTextEdit;
class QPushButton;
class QResizeEvent;
class QSizeGrip;

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
    void resizeEvent(QResizeEvent* event) override;

private:
    void applyColors();
    void updateControlPositions();

    QPlainTextEdit* m_editor;
    QPushButton* m_closeButton;
    QSizeGrip* m_sizeGrip;

    QColor m_backgroundColor = QColor("#FFF2A8");
    QColor m_textColor = QColor("#2B2B2B");

    QPoint m_dragOffset;
    bool m_dragging = false;
};