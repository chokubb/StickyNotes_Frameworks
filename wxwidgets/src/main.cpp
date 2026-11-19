#include <wx/wx.h>

class StickyNoteFrame : public wxFrame
{
public:
    StickyNoteFrame()
        : wxFrame(
            nullptr,
            wxID_ANY,
            "",
            wxDefaultPosition,
            wxSize(320, 320),
            wxBORDER_NONE
        )
    {
        SetBackgroundColour(
            wxColour(255, 242, 168)
        );

        auto* label = new wxStaticText(
            this,
            wxID_ANY,
            "My first wxWidgets sticky note",
            wxPoint(20, 20)
        );

        label->SetForegroundColour(
            wxColour(43, 43, 43)
        );

        Centre();
    }
};

class StickyNotesApp : public wxApp
{
public:
    bool OnInit() override
    {
        auto* note = new StickyNoteFrame();

        note->Show();

        return true;
    }
};

wxIMPLEMENT_APP(StickyNotesApp);