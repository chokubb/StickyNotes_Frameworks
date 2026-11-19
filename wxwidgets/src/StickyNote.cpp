#include "StickyNote.h"

#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/utils.h>

StickyNote::StickyNote()
    : wxFrame(
        nullptr,
        wxID_ANY,
        "",
        wxDefaultPosition,
        wxSize(320, 320),
        wxBORDER_NONE
    )
{
    SetBackgroundColour(
        wxColour(255, 242, 168)
    );

    auto* layout = new wxBoxSizer(wxVERTICAL);

    // Empty top strip used for dragging the frameless note.
    layout->AddSpacer(34);

    m_editor = new wxTextCtrl(
        this,
        wxID_ANY,
        "",
        wxDefaultPosition,
        wxDefaultSize,
        wxTE_MULTILINE |
        wxTE_NO_VSCROLL |
        wxBORDER_NONE
    );

    m_editor->SetBackgroundColour(
        wxColour(255, 242, 168)
    );

    m_editor->SetForegroundColour(
        wxColour(43, 43, 43)
    );

    m_editor->SetFont(
        wxFontInfo(12)
    );

    m_editor->SetHint(
        "Write something..."
    );

    layout->Add(
        m_editor,
        1,
        wxEXPAND |
        wxLEFT |
        wxRIGHT |
        wxBOTTOM,
        12
    );

    SetSizer(layout);
    Layout();

    Bind(
        wxEVT_LEFT_DOWN,
        &StickyNote::onLeftDown,
        this
    );

    Bind(
        wxEVT_MOTION,
        &StickyNote::onMouseMove,
        this
    );

    Bind(
        wxEVT_LEFT_UP,
        &StickyNote::onLeftUp,
        this
    );

    Centre();
}

void StickyNote::onLeftDown(wxMouseEvent& event)
{
    if (
        event.LeftDown() &&
        event.GetY() <= 34
        )
    {
        m_dragging = true;

        m_dragOffset =
            wxGetMousePosition()
            - GetPosition();

        if (!HasCapture())
        {
            CaptureMouse();
        }

        return;
    }

    event.Skip();
}

void StickyNote::onMouseMove(wxMouseEvent& event)
{
    if (
        m_dragging &&
        event.Dragging() &&
        event.LeftIsDown()
        )
    {
        Move(
            wxGetMousePosition()
            - m_dragOffset
        );

        return;
    }

    event.Skip();
}

void StickyNote::onLeftUp(wxMouseEvent& event)
{
    if (m_dragging)
    {
        m_dragging = false;

        if (HasCapture())
        {
            ReleaseMouse();
        }

        return;
    }

    event.Skip();
}