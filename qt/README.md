Qt Implementation

Qt implementation of the cross-platform sticky-notes application used in the framework comparison.

Status

Core functionality complete.

The Qt implementation has reached the common functional baseline used for comparison with wxWidgets.

Implemented Features

frameless independent sticky-note windows;

direct text editing;

note dragging;

multiple simultaneous notes;

individual deletion;

resizing;

persistence of text, position, dimensions, and colors;

random pastel palette generation;

automatic contrasting text colors;

paper-stack launcher;

click-to-create interaction;

drag-to-create interaction.

Structure

src/
├── main.cpp
├── StickyNote.h
├── StickyNote.cpp
├── NoteManager.h
├── NoteManager.cpp
├── LauncherWindow.h
└── LauncherWindow.cpp

StickyNote

Represents an individual note and handles:

editable content;

frameless-window appearance;

window dragging;

resizing through QSizeGrip;

note colors;

deletion controls.

NoteManager

Handles:

creation and tracking of notes;

random pastel palette generation;

contrast checking;

persistence;

restoration of saved notes.

Persistent state is implemented with QSettings.

Qt's QColor API is used for HSL color generation and conversion.

LauncherWindow

Provides the custom paper-stack interface.

Its current appearance is drawn programmatically with QPainter.

The launcher supports:

click-to-create;

drag-to-create.

Current Assessment

Qt provided relatively direct high-level APIs for most of the application requirements.

Particularly useful components include:

QWidget;

QPlainTextEdit;

QSizeGrip;

QSettings;

QColor;

QPainter;

Qt style sheets;

virtual mouse-event handlers.

Further visual development is intentionally deferred until the common baseline has been fully reviewed.

Planned Improvements

custom paper-stack artwork;

visible preview of upcoming note colors;

three-color stack queue;

improved drag feedback;

custom visual assets;

paper-crumpling deletion animation;

final visual polish.