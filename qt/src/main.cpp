#include <QApplication>

#include "LauncherWindow.h"
#include "NoteManager.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    NoteManager noteManager;

    LauncherWindow launcher(&noteManager);
    launcher.show();

    return app.exec();
}