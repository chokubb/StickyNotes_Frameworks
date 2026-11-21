#include "LauncherWindow.h"
#include "NoteManager.h"

#include <wx/button.h>
#include <wx/sizer.h>

LauncherWindow::LauncherWindow(
    NoteManager* noteManager
)
    : wxFrame(
        nullptr,
        wxID_ANY,
        "Sticky Notes - wxWidgets",
        wxDefaultPosition,
        wxSize(240, 120)
    ),
    m_noteManager(noteManager)
{
    auto* layout = new wxBoxSizer(wxVERTICAL);

    auto* newNoteButton = new wxButton(
        this,
        wxID_ANY,
        "+  New sticky note"
    );

    layout->Add(
        newNoteButton,
        1,
        wxEXPAND |
        wxALL,
        16
    );

    SetSizer(layout);

    newNoteButton->Bind(
        wxEVT_BUTTON,
        &LauncherWindow::onNewNote,
        this
    );

    Bind(
        wxEVT_CLOSE_WINDOW,
        &LauncherWindow::onClose,
        this
    );

    Centre();
}

void LauncherWindow::onNewNote(
    wxCommandEvent&
)
{
    m_noteManager->createNote();
}

void LauncherWindow::onClose(
    wxCloseEvent&
)
{
    m_noteManager->saveNotes();

    m_noteManager->closeAllNotes();

    Destroy();
}