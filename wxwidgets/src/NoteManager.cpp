#include "NoteManager.h"
#include "StickyNote.h"

#include <algorithm>

#include <wx/event.h>
#include <wx/utils.h>

void NoteManager::createNote()
{
    auto* note = new StickyNote();

    const wxPoint cursorPosition =
        wxGetMousePosition();

    const int offset =
        (m_noteCounter % 6) * 24;

    note->Move(
        cursorPosition.x + 20 + offset,
        cursorPosition.y + 20 + offset
    );

    m_notes.push_back(note);

    note->Bind(
        wxEVT_CLOSE_WINDOW,
        [this, note](wxCloseEvent& event)
        {
            removeNote(note);
            event.Skip();
        }
    );

    note->Show();
    note->Raise();

    ++m_noteCounter;
}

void NoteManager::removeNote(StickyNote* note)
{
    m_notes.erase(
        std::remove(
            m_notes.begin(),
            m_notes.end(),
            note
        ),
        m_notes.end()
    );
}

void NoteManager::closeAllNotes()
{
    // Work on a copy because closing a note removes it
    // from the original collection.
    const auto notes = m_notes;

    for (StickyNote* note : notes)
    {
        if (note != nullptr)
        {
            note->Close(true);
        }
    }
}