#pragma once

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