#pragma once

#include <wx/frame.h>
#include <wx/gdicmn.h>

class wxMouseEvent;
class wxTextCtrl;

class StickyNote : public wxFrame
{
public:
    StickyNote();

private:
    void onLeftDown(wxMouseEvent& event);
    void onMouseMove(wxMouseEvent& event);
    void onLeftUp(wxMouseEvent& event);

    wxTextCtrl* m_editor;

    wxPoint m_dragOffset;
    bool m_dragging = false;
};