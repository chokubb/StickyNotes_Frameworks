Development Notes

This document records implementation decisions, milestones, problems, fixes, and observations that may later be used in the coursework report.

Shared Project Setup

The project uses:

C++20;

Visual Studio 2026;

MSVC v143;

CMake;

one Git repository for both implementations.

The root CMake project contains separate subdirectories for Qt and wxWidgets so that both applications can be developed under the same project structure.

Qt

Initial Setup

Qt 6.12 MSVC 2022 64-bit was installed separately.

The first milestone was a minimal frameless yellow QWidget.

This verified:

Qt installation;

compiler compatibility;

CMake configuration;

successful compilation;

successful application launch.

Visual Studio initially generated its own CMake cache without the Qt installation path.

The issue was resolved by adding CMakePresets.json.

Editable and Draggable Note

The initial window was replaced by a dedicated StickyNote class.

QPlainTextEdit provides editable content.

A custom top region is used for dragging so that note movement does not interfere with text editing.

Multiple Notes

A NoteManager class was introduced to create and track independent notes.

Active notes are stored using QPointer.

Persistence

QSettings stores:

text;

position;

dimensions;

background color;

text color.

State is restored automatically at application startup.

Deleted notes do not return after restart.

Random Pastel Palettes

New notes receive randomly generated pastel backgrounds.

The algorithm uses:

random HSL hue;

restricted saturation;

restricted lightness;

minimum hue separation;

matching darker text;

contrast-ratio validation;

dark-gray fallback.

QColor::fromHsl() provides the required color conversion directly.

Generated colors persist between sessions.

Resizing

QSizeGrip provides interactive resizing.

The note has a defined minimum size.

The close button and resize grip are automatically repositioned after resizing.

Dimensions are included in persistence.

Paper-Stack Launcher

The temporary button launcher was replaced with a custom frameless paper-stack launcher drawn using QPainter.

The launcher supports:

click-to-create;

drag-to-create.

During drag-to-create, a newly created note follows the mouse until release.

Qt Core Milestone

The Qt version reached the complete baseline functionality required for the framework comparison.

Additional visual work was intentionally deferred while the wxWidgets implementation was developed.

wxWidgets

Initial Setup

wxWidgets 3.2.12 is integrated using CMake FetchContent.

The framework source archive is downloaded and built inside the project build directory.

The first milestone was a minimal frameless yellow wxFrame.

Successful configuration, compilation, and execution were captured in screenshots.

Editable and Draggable Note

The first functional note used wxTextCtrl.

The initial implementation exposed an unwanted vertical scrollbar and the text control did not expand into the expected layout.

The final control uses:

wxTE_MULTILINE |
wxTE_NO_VSCROLL |
wxBORDER_NONE

and the frame explicitly performs layout after attaching the sizer.

A custom top strip handles dragging through bound mouse events.

This became one of the first practical differences observed between Qt and wxWidgets.

Multiple Notes and Launcher

A NoteManager class was introduced to create and track notes.

A temporary native launcher button was initially used to create multiple notes.

The native appearance reinforced the observation that wxWidgets controls follow platform styling more strongly than the Qt widgets used in this project.

Individual close controls were also added to each note.

Close-Control Unicode Issue

The close symbol initially rendered incorrectly.

Increasing the control size did not resolve the problem.

The issue was traced to interpretation of the non-ASCII source literal.

The final implementation explicitly uses:

wxString(L"\u00D7")

for the multiplication-sign close glyph.

This guarantees the intended Unicode code point.

Persistence

Persistence is implemented with wxConfig.

Each note stores:

text;

x/y position;

width/height;

background RGB channels;

text RGB channels.

Unlike the Qt implementation, the wx version manually maintains hierarchical paths and a stored note count.

Random Pastel Palettes

The same conceptual palette algorithm used in Qt was reproduced in wxWidgets.

Because wxColour does not provide the same HSL construction API used by QColor, an explicit HSL-to-RGB conversion function was implemented.

The resulting colors visually match the Qt pastel approach.

Color persistence was tested successfully.

Resizing

To preserve the frameless visual design, the implementation does not use a normal native resizable window border.

Instead, a custom bottom-right resize grip handles:

mouse-down state;

mouse capture;

cursor movement;

size calculation;

minimum dimensions;

release of mouse capture.

The grip also follows the note's dynamically generated text color.

Persistent width and height were added to wxConfig.

Paper-Stack Launcher

The temporary launcher button was replaced with a frameless shaped launcher.

The paper stack is drawn programmatically.

The launcher supports:

click-to-create;

drag-to-create.

During drag-to-create, a real note is created after the drag threshold is reached and then follows the pointer.

A demonstration video is stored in docs/videos.

Launcher UX Fixes

Two issues were found during normal desktop use.

Click-created notes near the screen edge

Because the launcher sits near the bottom-right corner, creating a note based only on the cursor position could place most of the note outside the usable display area.

The final implementation:

finds the display containing the pointer;

checks the usable client area;

chooses a position on the opposite side of the pointer when necessary;

clamps the final position inside the display.

Always-on-top launcher

The launcher initially used wxSTAY_ON_TOP.

This caused the paper stack to remain above unrelated applications even when the sticky-note application was not active.

The flag was removed so the launcher now follows normal desktop z-order behavior.

These issues are considered implementation-level UX bugs rather than framework limitations.

wxWidgets Core Milestone

The wxWidgets version now implements the same functional baseline as the Qt version:

frameless notes;

editable text;

independent dragging;

multiple notes;

deletion;

persistence;

random pastel colors;

readable text colors;

resizing;

paper-stack launcher;

click-to-create;

drag-to-create.

Functional Parity Milestone

Qt and wxWidgets have now reached core functional parity.

This creates a stable coursework baseline even if additional visual-polish work is not completed.

The current project already provides:

two working implementations of the same application;

comparable feature sets;

incremental Git history;

implementation screenshots;

persistence testing;

documented framework-specific development issues;

material for the practical comparison chapter.

Planned Cross-Framework Improvements

The next visual-development stage may include:

previewing the next note color directly in the paper stack;

displaying the next three generated colors;

treating the visible stack as a queue;

shifting colors upward when the top note is removed;

generating a new random color only for the new bottom sheet;

stronger visual feedback while pulling a note from the stack;

replaceable custom artwork;

user-created sprites;

paper-crumpling deletion animation;

final visual polish.

Before continuing visual work, the Qt launcher should also be tested for the same edge-placement and z-order issues that were identified and fixed in wxWidgets.