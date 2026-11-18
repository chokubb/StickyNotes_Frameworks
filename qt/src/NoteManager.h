#pragma once

#include <QList>
#include <QObject>
#include <QPointer>

class StickyNote;

class NoteManager : public QObject
{
public:
    explicit NoteManager(QObject* parent = nullptr);

    void createNote();
    void loadNotes();
    void saveNotes();

private:
    QList<QPointer<StickyNote>> m_notes;
    int m_noteCounter = 0;

    void removeDeletedNotes();
};