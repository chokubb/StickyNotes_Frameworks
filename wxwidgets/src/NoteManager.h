#pragma once

#include <vector>

#include <wx/gdicmn.h>
#include <wx/string.h>

class StickyNote;

class NoteManager
{
public:
    void createNote();

    void loadNotes();
    void saveNotes();

    void closeAllNotes();

private:
    std::vector<StickyNote*> m_notes;

    int m_noteCounter = 0;

    StickyNote* createNoteAt(
        const wxPoint& position,
        const wxString& text = ""
    );

    void removeNote(StickyNote* note);
};