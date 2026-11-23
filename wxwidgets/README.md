wxWidgets Implementation

wxWidgets implementation of the cross-platform sticky-notes application used in the framework comparison.

Status

Core functionality complete.

The wxWidgets implementation has reached functional parity with the Qt baseline.

Implemented Features

frameless independent sticky-note windows;

direct text editing;

note dragging;

multiple simultaneous notes;

individual deletion;

resizing;

persistence of text, position, dimensions, and colors;

random pastel palette generation;

automatic readable text colors;

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

editable content using wxTextCtrl;

frameless-window appearance;

custom dragging;

custom resizing;

note colors;

close control.

Because the application intentionally avoids a native window border, resizing is implemented with a custom bottom-right grip.

NoteManager

Handles:

creation and tracking of notes;

safe initial note placement;

random pastel palette generation;

HSL-to-RGB conversion;

contrast checking;

persistence;

restoration of saved notes.

Persistent state is implemented with wxConfig.

LauncherWindow

Provides the custom paper-stack interface.

The temporary stack appearance is drawn with wxWidgets drawing APIs and a shaped frameless window.

The launcher supports:

click-to-create;

drag-to-create.

Implementation Observations

The wxWidgets version required several additional explicit adjustments during development, including:

suppressing the native multiline text-control scrollbar;

forcing the initial layout after constructing the sizer;

explicit Unicode handling for the × close symbol;

custom resize-grip behavior;

manual HSL color conversion;

manual hierarchical storage of note data with wxConfig;

additional control over native widget appearance.

These differences are documented in docs/comparison.md.

Planned Improvements

custom paper-stack artwork;

visible preview of upcoming note colors;

three-color stack queue;

improved drag feedback;

custom visual assets;

paper-crumpling deletion animation;

final visual polish.