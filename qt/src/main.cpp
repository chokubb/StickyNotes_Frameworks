#include <QApplication>
#include <QCoreApplication>

#include "LauncherWindow.h"
#include "NoteManager.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName(
        "StickyNotesFrameworkComparison"
    );

    QCoreApplication::setApplicationName(
        "StickyNotesQt"
    );

    NoteManager noteManager;

    noteManager.loadNotes();

    QObject::connect(
        &app,
        &QCoreApplication::aboutToQuit,
        &noteManager,
        &NoteManager::saveNotes
    );

    LauncherWindow launcher(&noteManager);
    launcher.show();

    return app.exec();
}