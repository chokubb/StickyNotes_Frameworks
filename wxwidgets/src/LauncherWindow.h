#pragma once

#include <wx/frame.h>

class NoteManager;
class wxCloseEvent;
class wxCommandEvent;

class LauncherWindow : public wxFrame
{
public:
    explicit LauncherWindow(
        NoteManager* noteManager
    );

private:
    void onNewNote(wxCommandEvent& event);
    void onClose(wxCloseEvent& event);

    NoteManager* m_noteManager;
};