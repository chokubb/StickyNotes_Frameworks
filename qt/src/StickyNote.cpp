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

    setStyleSheet(
        "QWidget#stickyNote {"
        "    background-color: #FFF2A8;"
        "}"
    );

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

    m_editor->setStyleSheet(
        "QPlainTextEdit {"
        "    background: transparent;"
        "    border: none;"
        "    font-size: 18px;"
        "    color: #2B2B2B;"
        "}"
    );

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