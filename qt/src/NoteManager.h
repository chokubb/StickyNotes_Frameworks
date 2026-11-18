#pragma once

#include <QColor>
#include <QList>
#include <QObject>
#include <QPointer>
#include <QPair>
#include <QPoint>

class StickyNote;

class NoteManager : public QObject
{
public:
    explicit NoteManager(QObject* parent = nullptr);

    void createNote();
    StickyNote* createNoteAt(const QPoint& position);
    void loadNotes();
    void saveNotes();

private:
    QList<QPointer<StickyNote>> m_notes;

    int m_noteCounter = 0;
    int m_lastHue = -1;

    void removeDeletedNotes();

    QPair<QColor, QColor> generatePalette();
    double contrastRatio(
        const QColor& first,
        const QColor& second
    ) const;
};