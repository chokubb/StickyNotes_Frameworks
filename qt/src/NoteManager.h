#pragma once

#include <QObject>
#include <QPointer>
#include <QList>

class StickyNote;

class NoteManager : public QObject
{
public:
    explicit NoteManager(QObject* parent = nullptr);

    void createNote();

private:
    QList<QPointer<StickyNote>> m_notes;
    int m_noteCounter = 0;

    void removeDeletedNotes();
};