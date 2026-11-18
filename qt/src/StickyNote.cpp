#include "StickyNote.h"

#include <QMouseEvent>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QPushButton>

StickyNote::StickyNote(QWidget* parent)
    : QWidget(parent)
{
    setFixedSize(320, 320);

    setWindowFlags(
        Qt::Window |
        Qt::FramelessWindowHint
    );

    setObjectName("stickyNote");

    auto* closeButton = new QPushButton("×", this);

    closeButton->setGeometry(width() - 34, 6, 28, 28);

    closeButton->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"
        "    border: none;"
        "    font-size: 20px;"
        "    color: #5A5130;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(0, 0, 0, 25);"
        "    border-radius: 4px;"
        "}"
    );

    connect(closeButton, &QPushButton::clicked,
        this, &QWidget::close);

    setAttribute(Qt::WA_DeleteOnClose);

    auto* layout = new QVBoxLayout(this);

    // Leave a small empty area at the top for dragging the note.
    layout->setContentsMargins(12, 34, 12, 12);

    m_editor = new QPlainTextEdit(this);

    m_editor->setPlaceholderText("Write something...");
    m_editor->setFrameShape(QFrame::NoFrame);

    applyColors();

    layout->addWidget(m_editor);
}

void StickyNote::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton &&
        event->position().y() <= 34)
    {
        m_dragging = true;

        m_dragOffset =
            event->globalPosition().toPoint()
            - frameGeometry().topLeft();

        event->accept();
        return;
    }

    QWidget::mousePressEvent(event);
}

void StickyNote::mouseMoveEvent(QMouseEvent* event)
{
    if (m_dragging &&
        (event->buttons() & Qt::LeftButton))
    {
        move(
            event->globalPosition().toPoint()
            - m_dragOffset
        );

        event->accept();
        return;
    }

    QWidget::mouseMoveEvent(event);
}

void StickyNote::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = false;
    }

    QWidget::mouseReleaseEvent(event);
}

QString StickyNote::text() const
{
    return m_editor->toPlainText();
}

void StickyNote::setText(const QString& text)
{
    m_editor->setPlainText(text);
}

QColor StickyNote::backgroundColor() const
{
    return m_backgroundColor;
}

QColor StickyNote::textColor() const
{
    return m_textColor;
}

void StickyNote::setColors(
    const QColor& backgroundColor,
    const QColor& textColor
)
{
    m_backgroundColor = backgroundColor;
    m_textColor = textColor;

    applyColors();
}

void StickyNote::applyColors()
{
    setStyleSheet(
        QString(
            "QWidget#stickyNote {"
            "    background-color: %1;"
            "}"
        ).arg(m_backgroundColor.name())
    );

    if (m_editor)
    {
        m_editor->setStyleSheet(
            QString(
                "QPlainTextEdit {"
                "    background: transparent;"
                "    border: none;"
                "    font-size: 18px;"
                "    color: %1;"
                "}"
            ).arg(m_textColor.name())
        );
    }
}