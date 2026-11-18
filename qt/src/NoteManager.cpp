#include "NoteManager.h"
#include "StickyNote.h"

#include <QCursor>
#include <QSettings>

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

void NoteManager::saveNotes()
{
    removeDeletedNotes();

    QSettings settings;

    settings.remove("notes");

    settings.beginWriteArray("notes");

    int index = 0;

    for (const QPointer<StickyNote>& note : m_notes)
    {
        if (note.isNull())
        {
            continue;
        }

        settings.setArrayIndex(index);

        settings.setValue("text", note->text());
        settings.setValue("x", note->x());
        settings.setValue("y", note->y());
        settings.setValue("width", note->width());
        settings.setValue("height", note->height());

        ++index;
    }

    settings.endArray();
    settings.sync();
}

void NoteManager::loadNotes()
{
    QSettings settings;

    const int count = settings.beginReadArray("notes");

    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);

        auto* note = new StickyNote();

        const QString text =
            settings.value("text").toString();

        const int x =
            settings.value("x", 100).toInt();

        const int y =
            settings.value("y", 100).toInt();

        note->setText(text);
        note->move(x, y);

        m_notes.append(note);

        note->show();

        ++m_noteCounter;
    }

    settings.endArray();
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