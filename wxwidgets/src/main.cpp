#include <wx/wx.h>

#include "StickyNote.h"

class StickyNotesApp : public wxApp
{
public:
    bool OnInit() override
    {
        auto* note = new StickyNote();

        note->Show();

        return true;
    }
};

wxIMPLEMENT_APP(StickyNotesApp);