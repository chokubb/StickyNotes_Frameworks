#pragma once

#include <wx/frame.h>
#include <wx/gdicmn.h>

class wxMouseEvent;
class wxStaticText;
class wxTextCtrl;

class StickyNote : public wxFrame
{
public:
    StickyNote();

private:
    void onLeftDown(wxMouseEvent& event);
    void onMouseMove(wxMouseEvent& event);
    void onLeftUp(wxMouseEvent& event);
    void onCloseClicked(wxMouseEvent& event);

    wxTextCtrl* m_editor;
    wxStaticText* m_closeLabel;

    wxPoint m_dragOffset;
    bool m_dragging = false;
};