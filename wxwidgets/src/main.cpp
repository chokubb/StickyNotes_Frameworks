#include <memory>

#include <wx/wx.h>

#include "LauncherWindow.h"
#include "NoteManager.h"

class StickyNotesApp : public wxApp
{
public:
    bool OnInit() override
    {
        m_noteManager =
            std::make_unique<NoteManager>();

        auto* launcher =
            new LauncherWindow(
                m_noteManager.get()
            );

        SetTopWindow(launcher);

        launcher->Show();

        return true;
    }

private:
    std::unique_ptr<NoteManager> m_noteManager;
};

wxIMPLEMENT_APP(StickyNotesApp);