#pragma once

#include <wx/colour.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/string.h>

class wxMouseEvent;
class wxStaticText;
class wxTextCtrl;

class StickyNote : public wxFrame
{
public:
    StickyNote();

    wxString text() const;
    void setText(const wxString& text);

    wxColour backgroundColor() const;
    wxColour textColor() const;

    void setColors(
        const wxColour& backgroundColor,
        const wxColour& textColor
    );

private:
    void applyColors();

    void onLeftDown(wxMouseEvent& event);
    void onMouseMove(wxMouseEvent& event);
    void onLeftUp(wxMouseEvent& event);
    void onCloseClicked(wxMouseEvent&);

    wxTextCtrl* m_editor;
    wxStaticText* m_closeLabel;

    wxColour m_backgroundColor{ 255, 242, 168 };
    wxColour m_textColor{ 43, 43, 43 };

    wxPoint m_dragOffset;
    bool m_dragging = false;
};