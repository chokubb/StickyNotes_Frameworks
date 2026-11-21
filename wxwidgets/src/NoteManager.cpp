#include "NoteManager.h"
#include "StickyNote.h"

#include <algorithm>

#include <wx/config.h>
#include <wx/event.h>
#include <wx/utils.h>

void NoteManager::createNote()
{
    const wxPoint cursorPosition =
        wxGetMousePosition();

    const int offset =
        (m_noteCounter % 6) * 24;

    createNoteAt(
        wxPoint(
            cursorPosition.x + 20 + offset,
            cursorPosition.y + 20 + offset
        )
    );
}

StickyNote* NoteManager::createNoteAt(
    const wxPoint& position,
    const wxString& text
)
{
    auto* note = new StickyNote();

    note->Move(position);
    note->setText(text);

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

    return note;
}

void NoteManager::saveNotes()
{
    wxConfig config(
        "StickyNotesWx",
        "StickyNotesFrameworkComparison"
    );

    config.DeleteGroup("notes");

    config.SetPath("/notes");

    config.Write(
        "count",
        static_cast<long>(m_notes.size())
    );

    for (
        std::size_t i = 0;
        i < m_notes.size();
        ++i
        )
    {
        StickyNote* note = m_notes[i];

        if (note == nullptr)
        {
            continue;
        }

        config.SetPath(
            wxString::Format(
                "/notes/%zu",
                i
            )
        );

        const wxPoint position =
            note->GetPosition();

        config.Write(
            "text",
            note->text()
        );

        config.Write(
            "x",
            static_cast<long>(position.x)
        );

        config.Write(
            "y",
            static_cast<long>(position.y)
        );
    }

    config.Flush();
}

void NoteManager::loadNotes()
{
    wxConfig config(
        "StickyNotesWx",
        "StickyNotesFrameworkComparison"
    );

    config.SetPath("/notes");

    long count = 0;

    config.Read(
        "count",
        &count,
        0L
    );

    for (long i = 0; i < count; ++i)
    {
        config.SetPath(
            wxString::Format(
                "/notes/%ld",
                i
            )
        );

        wxString text;

        long x = 100;
        long y = 100;

        config.Read(
            "text",
            &text,
            ""
        );

        config.Read(
            "x",
            &x,
            100L
        );

        config.Read(
            "y",
            &y,
            100L
        );

        createNoteAt(
            wxPoint(
                static_cast<int>(x),
                static_cast<int>(y)
            ),
            text
        );
    }
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
    const auto notes = m_notes;

    for (StickyNote* note : notes)
    {
        if (note != nullptr)
        {
            note->Close(true);
        }
    }
}