#pragma once

#include <vector>

class StickyNote;

class NoteManager
{
public:
    void createNote();
    void closeAllNotes();

private:
    std::vector<StickyNote*> m_notes;

    int m_noteCounter = 0;

    void removeNote(StickyNote* note);
};