#pragma once

#include <utility>
#include <vector>

#include <wx/colour.h>
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
    int m_lastHue = -1;

    StickyNote* createNoteAt(
        const wxPoint& position,
        const wxString& text,
        const wxColour& backgroundColor,
        const wxColour& textColor
    );

    void removeNote(StickyNote* note);

    std::pair<wxColour, wxColour>
        generatePalette();

    wxColour hslToColour(
        int hue,
        double saturation,
        double lightness
    ) const;

    double contrastRatio(
        const wxColour& first,
        const wxColour& second
    ) const;
};