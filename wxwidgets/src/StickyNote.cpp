#include "StickyNote.h"

#include <algorithm>

#include <wx/font.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
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
    SetMinSize(
        wxSize(220, 180)
    );

    auto* layout =
        new wxBoxSizer(wxVERTICAL);

    // Empty top strip used for dragging.
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
        wxRIGHT,
        12
    );

    // Leave some room for the resize grip.
    layout->AddSpacer(20);

    SetSizer(layout);

    m_closeLabel = new wxStaticText(
        this,
        wxID_ANY,
        wxString(L"\u00D7"),
        wxDefaultPosition,
        wxSize(30, 30),
        wxALIGN_CENTER_HORIZONTAL
    );

    m_closeLabel->SetFont(
        wxFontInfo(16)
    );

    m_closeLabel->SetCursor(
        wxCursor(wxCURSOR_HAND)
    );

    m_resizeGrip = new wxStaticText(
        this,
        wxID_ANY,
        "///",
        wxDefaultPosition,
        wxSize(24, 20),
        wxALIGN_CENTER_HORIZONTAL
    );

    m_resizeGrip->SetFont(
        wxFontInfo(8)
    );

    m_resizeGrip->SetCursor(
        wxCursor(wxCURSOR_SIZENWSE)
    );

    m_closeLabel->Bind(
        wxEVT_LEFT_UP,
        &StickyNote::onCloseClicked,
        this
    );

    m_resizeGrip->Bind(
        wxEVT_LEFT_DOWN,
        &StickyNote::onResizeLeftDown,
        this
    );

    m_resizeGrip->Bind(
        wxEVT_MOTION,
        &StickyNote::onResizeMouseMove,
        this
    );

    m_resizeGrip->Bind(
        wxEVT_LEFT_UP,
        &StickyNote::onResizeLeftUp,
        this
    );

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

    Bind(
        wxEVT_SIZE,
        &StickyNote::onSize,
        this
    );

    applyColors();

    Layout();
    updateControlPositions();
}

wxString StickyNote::text() const
{
    return m_editor->GetValue();
}

void StickyNote::setText(
    const wxString& text
)
{
    m_editor->SetValue(text);
}

wxColour StickyNote::backgroundColor() const
{
    return m_backgroundColor;
}

wxColour StickyNote::textColor() const
{
    return m_textColor;
}

void StickyNote::setColors(
    const wxColour& backgroundColor,
    const wxColour& textColor
)
{
    m_backgroundColor = backgroundColor;
    m_textColor = textColor;

    applyColors();
}

void StickyNote::applyColors()
{
    SetBackgroundColour(
        m_backgroundColor
    );

    if (m_editor != nullptr)
    {
        m_editor->SetBackgroundColour(
            m_backgroundColor
        );

        m_editor->SetForegroundColour(
            m_textColor
        );

        m_editor->Refresh();
    }

    if (m_closeLabel != nullptr)
    {
        m_closeLabel->SetBackgroundColour(
            m_backgroundColor
        );

        m_closeLabel->SetForegroundColour(
            m_textColor
        );

        m_closeLabel->Refresh();
    }

    if (m_resizeGrip != nullptr)
    {
        m_resizeGrip->SetBackgroundColour(
            m_backgroundColor
        );

        m_resizeGrip->SetForegroundColour(
            m_textColor
        );

        m_resizeGrip->Refresh();
    }

    Refresh();
}

void StickyNote::updateControlPositions()
{
    const wxSize clientSize =
        GetClientSize();

    if (m_closeLabel != nullptr)
    {
        m_closeLabel->Move(
            clientSize.x
            - m_closeLabel->GetSize().x
            - 6,
            3
        );
    }

    if (m_resizeGrip != nullptr)
    {
        m_resizeGrip->Move(
            clientSize.x
            - m_resizeGrip->GetSize().x
            - 3,
            clientSize.y
            - m_resizeGrip->GetSize().y
            - 3
        );
    }
}

void StickyNote::onLeftDown(
    wxMouseEvent& event
)
{
    if (event.GetY() <= 34)
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

void StickyNote::onMouseMove(
    wxMouseEvent& event
)
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

void StickyNote::onLeftUp(
    wxMouseEvent& event
)
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

void StickyNote::onCloseClicked(
    wxMouseEvent&
)
{
    Close();
}

void StickyNote::onSize(
    wxSizeEvent& event
)
{
    Layout();
    updateControlPositions();

    event.Skip();
}

void StickyNote::onResizeLeftDown(
    wxMouseEvent&
)
{
    m_resizing = true;

    m_resizeStartMouse =
        wxGetMousePosition();

    m_resizeStartSize =
        GetSize();

    if (!m_resizeGrip->HasCapture())
    {
        m_resizeGrip->CaptureMouse();
    }
}

void StickyNote::onResizeMouseMove(
    wxMouseEvent& event
)
{
    if (
        !m_resizing ||
        !event.Dragging() ||
        !event.LeftIsDown()
        )
    {
        event.Skip();
        return;
    }

    const wxPoint currentMouse =
        wxGetMousePosition();

    const wxPoint difference =
        currentMouse
        - m_resizeStartMouse;

    const wxSize minimumSize =
        GetMinSize();

    const int width =
        std::max(
            minimumSize.x,
            m_resizeStartSize.x
            + difference.x
        );

    const int height =
        std::max(
            minimumSize.y,
            m_resizeStartSize.y
            + difference.y
        );

    SetSize(
        wxSize(width, height)
    );
}

void StickyNote::onResizeLeftUp(
    wxMouseEvent&
)
{
    if (!m_resizing)
    {
        return;
    }

    m_resizing = false;

    if (m_resizeGrip->HasCapture())
    {
        m_resizeGrip->ReleaseMouse();
    }
}