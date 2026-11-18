#include "NoteManager.h"
#include "StickyNote.h"

#include <QCursor>

NoteManager::NoteManager(QObject* parent)
    : QObject(parent)
{}

void NoteManager::createNote()
{
    removeDeletedNotes();

    auto* note = new StickyNote();

    const QPoint cursorPosition = QCursor::pos();

    const int offset = (m_noteCounter % 6) * 24;

    note->move(
        cursorPosition.x() + 20 + offset,
        cursorPosition.y() + 20 + offset
    );

    m_notes.append(note);

    note->show();

    ++m_noteCounter;
}

void NoteManager::removeDeletedNotes()
{
    m_notes.removeIf(
        [](const QPointer<StickyNote>& note)
        {
            return note.isNull();
        }
    );
}