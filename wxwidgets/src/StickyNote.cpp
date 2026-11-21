#include "StickyNote.h"

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
    auto* layout = new wxBoxSizer(wxVERTICAL);

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

    m_editor->SetFont(wxFontInfo(12));
    m_editor->SetHint("Write something...");

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

    m_closeLabel = new wxStaticText(
        this,
        wxID_ANY,
        wxString(L"\u00D7"),
        wxPoint(284, 3),
        wxSize(30, 30),
        wxALIGN_CENTER_HORIZONTAL
    );

    m_closeLabel->SetFont(wxFontInfo(16));
    m_closeLabel->SetCursor(
        wxCursor(wxCURSOR_HAND)
    );

    m_closeLabel->Bind(
        wxEVT_LEFT_UP,
        &StickyNote::onCloseClicked,
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

    applyColors();
    Layout();
}

wxString StickyNote::text() const
{
    return m_editor->GetValue();
}

void StickyNote::setText(const wxString& text)
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
    SetBackgroundColour(m_backgroundColor);

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

    Refresh();
}

void StickyNote::onLeftDown(wxMouseEvent& event)
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

void StickyNote::onCloseClicked(wxMouseEvent&)
{
    Close();
}