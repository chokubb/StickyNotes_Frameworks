#include "LauncherWindow.h"

#include "NoteManager.h"
#include "StickyNote.h"

#include <QApplication>
#include <QCloseEvent>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QScreen>

LauncherWindow::LauncherWindow(
    NoteManager* noteManager,
    QWidget* parent
)
    : QWidget(parent),
    m_noteManager(noteManager)
{
    setFixedSize(160, 130);

    setWindowFlags(
        Qt::Tool |
        Qt::FramelessWindowHint |
        Qt::WindowStaysOnTopHint
    );

    setAttribute(Qt::WA_TranslucentBackground);

    auto* closeButton = new QPushButton("×", this);

    closeButton->setGeometry(
        width() - 27,
        3,
        24,
        24
    );

    closeButton->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"
        "    border: none;"
        "    color: #514A40;"
        "    font-size: 18px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(0, 0, 0, 20);"
        "    border-radius: 5px;"
        "}"
    );

    connect(
        closeButton,
        &QPushButton::clicked,
        this,
        &QWidget::close
    );

    setCursor(Qt::OpenHandCursor);

    if (QScreen* screen = QGuiApplication::primaryScreen())
    {
        const QRect area = screen->availableGeometry();

        move(
            area.right() - width() - 20,
            area.bottom() - height() - 20
        );
    }
}

QRect LauncherWindow::stackRect() const
{
    return QRect(
        20,
        25,
        115,
        90
    );
}

void LauncherWindow::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);

    painter.setRenderHint(
        QPainter::Antialiasing
    );

    painter.setPen(Qt::NoPen);

    // Back sheet
    painter.setBrush(
        QColor("#D9CEF4")
    );

    painter.drawRoundedRect(
        QRectF(30, 34, 110, 82),
        8,
        8
    );

    // Middle sheet
    painter.setBrush(
        QColor("#DDEBC5")
    );

    painter.drawRoundedRect(
        QRectF(25, 29, 110, 82),
        8,
        8
    );

    // Top sheet
    painter.setBrush(
        QColor("#FFF2A8")
    );

    painter.drawRoundedRect(
        QRectF(20, 24, 110, 82),
        8,
        8
    );

    painter.setPen(
        QColor("#514A40")
    );

    QFont plusFont = painter.font();
    plusFont.setPointSize(24);
    plusFont.setBold(false);

    painter.setFont(plusFont);

    painter.drawText(
        QRect(20, 38, 110, 35),
        Qt::AlignCenter,
        "+"
    );

    QFont textFont = painter.font();
    textFont.setPointSize(9);

    painter.setFont(textFont);

    painter.drawText(
        QRect(20, 72, 110, 22),
        Qt::AlignCenter,
        "drag a note"
    );
}

void LauncherWindow::mousePressEvent(QMouseEvent* event)
{
    if (
        event->button() == Qt::LeftButton &&
        stackRect().contains(
            event->position().toPoint()
        )
        )
    {
        m_pressedOnStack = true;

        m_pressPosition =
            event->position().toPoint();

        setCursor(Qt::ClosedHandCursor);

        event->accept();
        return;
    }

    QWidget::mousePressEvent(event);
}

void LauncherWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (
        m_pressedOnStack &&
        (event->buttons() & Qt::LeftButton)
        )
    {
        const QPoint movement =
            event->position().toPoint()
            - m_pressPosition;

        if (
            m_draggedNote.isNull() &&
            movement.manhattanLength() >=
            QApplication::startDragDistance()
            )
        {
            const QPoint notePosition =
                event->globalPosition().toPoint()
                - QPoint(40, 20);

            m_draggedNote =
                m_noteManager->createNoteAt(
                    notePosition
                );
        }

        if (!m_draggedNote.isNull())
        {
            m_draggedNote->move(
                event->globalPosition().toPoint()
                - QPoint(40, 20)
            );
        }

        event->accept();
        return;
    }

    QWidget::mouseMoveEvent(event);
}

void LauncherWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (
        event->button() == Qt::LeftButton &&
        m_pressedOnStack
        )
    {
        // A normal click still creates a note.
        if (m_draggedNote.isNull())
        {
            m_noteManager->createNote();
        }

        m_draggedNote.clear();
        m_pressedOnStack = false;

        setCursor(Qt::OpenHandCursor);

        event->accept();
        return;
    }

    QWidget::mouseReleaseEvent(event);
}

void LauncherWindow::closeEvent(QCloseEvent* event)
{
    event->accept();

    QApplication::quit();
}