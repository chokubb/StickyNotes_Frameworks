#pragma once

#include <wx/frame.h>
#include <wx/gdicmn.h>

class NoteManager;
class StickyNote;

class wxCloseEvent;
class wxMouseEvent;
class wxPaintEvent;

class LauncherWindow : public wxFrame
{
public:
    explicit LauncherWindow(
        NoteManager* noteManager
    );

private:
    wxRect stackRect() const;
    wxRect closeRect() const;

    void onPaint(wxPaintEvent& event);

    void onLeftDown(wxMouseEvent& event);
    void onMouseMove(wxMouseEvent& event);
    void onLeftUp(wxMouseEvent& event);

    void onClose(wxCloseEvent& event);

    NoteManager* m_noteManager;

    wxPoint m_pressPosition;

    bool m_pressedOnStack = false;

    StickyNote* m_draggedNote = nullptr;
};