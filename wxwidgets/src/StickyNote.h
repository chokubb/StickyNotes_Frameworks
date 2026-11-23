#pragma once

#include <wx/colour.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <wx/string.h>

class wxMouseEvent;
class wxSizeEvent;
class wxStaticText;
class wxTextCtrl;

class StickyNote : public wxFrame
{
public:
    static constexpr int DefaultWidth = 320;
    static constexpr int DefaultHeight = 320;

    static constexpr int MinimumWidth = 220;
    static constexpr int MinimumHeight = 180;

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
    void updateControlPositions();

    void onLeftDown(wxMouseEvent& event);
    void onMouseMove(wxMouseEvent& event);
    void onLeftUp(wxMouseEvent& event);

    void onCloseClicked(wxMouseEvent&);

    void onSize(wxSizeEvent& event);

    void onResizeLeftDown(wxMouseEvent& event);
    void onResizeMouseMove(wxMouseEvent& event);
    void onResizeLeftUp(wxMouseEvent& event);

    wxTextCtrl* m_editor;
    wxStaticText* m_closeLabel;
    wxStaticText* m_resizeGrip;

    wxColour m_backgroundColor{ 255, 242, 168 };
    wxColour m_textColor{ 43, 43, 43 };

    wxPoint m_dragOffset;
    bool m_dragging = false;

    wxPoint m_resizeStartMouse;
    wxSize m_resizeStartSize;
    bool m_resizing = false;
};