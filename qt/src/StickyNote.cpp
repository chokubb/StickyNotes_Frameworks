#include "StickyNote.h"

#include <QMouseEvent>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QSizeGrip>
#include <QVBoxLayout>

StickyNote::StickyNote(QWidget* parent)
    : QWidget(parent)
{
    setMinimumSize(220, 180);
    resize(320, 320);

    setWindowFlags(
        Qt::Window |
        Qt::FramelessWindowHint
    );

    setObjectName("stickyNote");

    m_closeButton = new QPushButton("×", this);
    m_closeButton->setFixedSize(28, 28);

    connect(
        m_closeButton,
        &QPushButton::clicked,
        this,
        &QWidget::close
    );

    setAttribute(Qt::WA_DeleteOnClose);

    auto* layout = new QVBoxLayout(this);

    // Top area is used for dragging.
    // Extra space at the bottom/right leaves room for the resize grip.
    layout->setContentsMargins(12, 34, 20, 20);

    m_editor = new QPlainTextEdit(this);

    m_editor->setPlaceholderText("Write something...");
    m_editor->setFrameShape(QFrame::NoFrame);

    layout->addWidget(m_editor);

    m_sizeGrip = new QSizeGrip(this);
    m_sizeGrip->setFixedSize(20, 20);
    m_sizeGrip->setToolTip("Resize note");

    applyColors();
    updateControlPositions();

    m_closeButton->raise();
    m_sizeGrip->raise();
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

    if (m_closeButton)
    {
        m_closeButton->setStyleSheet(
            QString(
                "QPushButton {"
                "    background: transparent;"
                "    border: none;"
                "    font-size: 20px;"
                "    color: %1;"
                "}"
                "QPushButton:hover {"
                "    background-color: rgba(0, 0, 0, 25);"
                "    border-radius: 4px;"
                "}"
            ).arg(m_textColor.name())
        );
    }
}

void StickyNote::updateControlPositions()
{
    if (m_closeButton)
    {
        m_closeButton->move(
            width() - m_closeButton->width() - 6,
            6
        );
    }

    if (m_sizeGrip)
    {
        m_sizeGrip->move(
            width() - m_sizeGrip->width() - 3,
            height() - m_sizeGrip->height() - 3
        );
    }
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

void StickyNote::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    updateControlPositions();
}