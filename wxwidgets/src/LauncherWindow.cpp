#include "LauncherWindow.h"

#include "NoteManager.h"
#include "StickyNote.h"

#include <cmath>

#include <wx/dcbuffer.h>
#include <wx/display.h>
#include <wx/region.h>
#include <wx/utils.h>

LauncherWindow::LauncherWindow(
    NoteManager* noteManager
)
    : wxFrame(
        nullptr,
        wxID_ANY,
        "",
        wxDefaultPosition,
        wxSize(160, 130),
        wxBORDER_NONE |
        wxFRAME_NO_TASKBAR |
        wxFRAME_SHAPED
    ),
    m_noteManager(noteManager)
{
    SetBackgroundStyle(
        wxBG_STYLE_PAINT
    );

    // Shape the launcher roughly like overlapping sheets
    // instead of leaving a normal rectangular window.
    wxRegion shape;

    shape.Union(
        wxRect(30, 34, 110, 82)
    );

    shape.Union(
        wxRect(25, 29, 110, 82)
    );

    shape.Union(
        wxRect(20, 24, 110, 82)
    );

    SetShape(shape);

    Bind(
        wxEVT_PAINT,
        &LauncherWindow::onPaint,
        this
    );

    Bind(
        wxEVT_LEFT_DOWN,
        &LauncherWindow::onLeftDown,
        this
    );

    Bind(
        wxEVT_MOTION,
        &LauncherWindow::onMouseMove,
        this
    );

    Bind(
        wxEVT_LEFT_UP,
        &LauncherWindow::onLeftUp,
        this
    );

    Bind(
        wxEVT_CLOSE_WINDOW,
        &LauncherWindow::onClose,
        this
    );

    wxDisplay display(0u);

    const wxRect area =
        display.GetClientArea();

    Move(
        area.GetRight()
        - GetSize().x
        - 20,
        area.GetBottom()
        - GetSize().y
        - 20
    );

    SetCursor(
        wxCursor(wxCURSOR_HAND)
    );
}

wxRect LauncherWindow::stackRect() const
{
    return wxRect(
        20,
        24,
        120,
        92
    );
}

wxRect LauncherWindow::closeRect() const
{
    return wxRect(
        108,
        27,
        20,
        20
    );
}

void LauncherWindow::onPaint(
    wxPaintEvent&
)
{
    wxAutoBufferedPaintDC dc(this);

    dc.SetBackground(
        wxBrush(
            wxColour(255, 255, 255)
        )
    );

    dc.Clear();

    dc.SetPen(*wxTRANSPARENT_PEN);

    // Back sheet
    dc.SetBrush(
        wxBrush(
            wxColour(217, 206, 244)
        )
    );

    dc.DrawRoundedRectangle(
        30,
        34,
        110,
        82,
        8
    );

    // Middle sheet
    dc.SetBrush(
        wxBrush(
            wxColour(221, 235, 197)
        )
    );

    dc.DrawRoundedRectangle(
        25,
        29,
        110,
        82,
        8
    );

    // Top sheet
    dc.SetBrush(
        wxBrush(
            wxColour(255, 242, 168)
        )
    );

    dc.DrawRoundedRectangle(
        20,
        24,
        110,
        82,
        8
    );

    dc.SetTextForeground(
        wxColour(81, 74, 64)
    );

    dc.SetFont(
        wxFontInfo(24)
    );

    dc.DrawLabel(
        "+",
        wxRect(
            20,
            38,
            110,
            32
        ),
        wxALIGN_CENTER
    );

    dc.SetFont(
        wxFontInfo(9)
    );

    dc.DrawLabel(
        "drag a note",
        wxRect(
            20,
            72,
            110,
            22
        ),
        wxALIGN_CENTER
    );

    dc.SetFont(
        wxFontInfo(14)
    );

    dc.DrawLabel(
        wxString(L"\u00D7"),
        closeRect(),
        wxALIGN_CENTER
    );
}

void LauncherWindow::onLeftDown(
    wxMouseEvent& event
)
{
    const wxPoint position =
        event.GetPosition();

    if (
        closeRect().Contains(position)
        )
    {
        Close();
        return;
    }

    if (
        stackRect().Contains(position)
        )
    {
        m_pressedOnStack = true;

        m_pressPosition =
            position;

        m_draggedNote = nullptr;

        if (!HasCapture())
        {
            CaptureMouse();
        }

        SetCursor(
            wxCursor(wxCURSOR_HAND)
        );

        return;
    }

    event.Skip();
}

void LauncherWindow::onMouseMove(
    wxMouseEvent& event
)
{
    if (
        !m_pressedOnStack ||
        !event.LeftIsDown()
        )
    {
        event.Skip();
        return;
    }

    const wxPoint movement =
        event.GetPosition()
        - m_pressPosition;

    const int dragDistance =
        std::abs(movement.x)
        + std::abs(movement.y);

    if (
        m_draggedNote == nullptr &&
        dragDistance >= 8
        )
    {
        const wxPoint mousePosition =
            wxGetMousePosition();

        m_draggedNote =
            m_noteManager->createNoteAt(
                mousePosition
                - wxPoint(40, 20)
            );
    }

    if (m_draggedNote != nullptr)
    {
        m_draggedNote->Move(
            wxGetMousePosition()
            - wxPoint(40, 20)
        );
    }
}

void LauncherWindow::onLeftUp(
    wxMouseEvent&
)
{
    if (!m_pressedOnStack)
    {
        return;
    }

    if (m_draggedNote == nullptr)
    {
        m_noteManager->createNote();
    }

    m_draggedNote = nullptr;
    m_pressedOnStack = false;

    if (HasCapture())
    {
        ReleaseMouse();
    }

    SetCursor(
        wxCursor(wxCURSOR_HAND)
    );
}

void LauncherWindow::onClose(
    wxCloseEvent&
)
{
    if (HasCapture())
    {
        ReleaseMouse();
    }

    m_noteManager->saveNotes();

    m_noteManager->closeAllNotes();

    Destroy();
}