Development Notes

This document records implementation decisions, development progress, encountered issues, and observations that may later be used in the coursework report and framework comparison.

Qt

Development Environment

The Qt implementation was developed using:

C++20;

Qt 6.12;

Qt Widgets;

Visual Studio 2026;

MSVC v143;

CMake;

Windows x64.

Qt was installed using the MSVC 2022 64-bit package.

The project uses a CMake preset so that the command-line build and Visual Studio use the same compiler and Qt configuration.

Initial Setup

The first Qt milestone was a minimal frameless yellow QWidget.

This was used to verify:

Qt installation;

CMake configuration;

MSVC toolset compatibility;

successful compilation;

successful application launch.

A CMake configuration issue occurred when Visual Studio initially attempted to create its own cache without the Qt installation path.

This was resolved by adding CMakePresets.json, which stores the project configuration and Qt path.

Editable and Draggable Notes

The original test window was replaced with a dedicated StickyNote class.

QPlainTextEdit is used for editable note content.

Because the note is frameless, custom mouse-event handling was added to allow the window to be dragged from an empty region at the top of the note without interfering with text selection and editing.

Multiple Notes

A separate NoteManager class was introduced to manage note creation and active note instances.

This removed note-management responsibility from main.cpp and allowed multiple independent sticky-note windows to exist simultaneously.

Persistence

Application state is stored using QSettings.

The Qt version currently preserves:

text;

screen position;

note dimensions;

background color;

text color.

State is saved when the application closes and restored during the next launch.

Testing confirmed that deleted notes do not reappear after restarting the application.

Random Pastel Palettes

Each newly created note receives a random pastel color.

Colors are generated using HSL values restricted to a pastel saturation and lightness range.

The text color is based on the same hue but uses a much darker lightness value.

A contrast-ratio check is performed to maintain readability. If the calculated contrast is insufficient, a neutral dark-gray text color is used.

A minimum hue difference is enforced between consecutive generated notes to reduce repeated or visually similar colors.

The generated palette is stored persistently and does not change when the application restarts.

Resizing

Notes use QSizeGrip for interactive resizing.

The initial size is 320 × 320 pixels, while a minimum size prevents notes from becoming impractically small.

The close button and resize grip are repositioned automatically when the note dimensions change.

Width and height are stored through the existing persistence system.

Paper-Stack Launcher

The original temporary launcher window was replaced by a compact frameless launcher.

The current launcher is drawn programmatically using QPainter and visually represents a small stack of sticky notes.

It supports two creation methods:

clicking the stack;

dragging a new note from the stack and placing it directly on the desktop.

The launcher remains separate from the note-management logic so that its visual representation can later be replaced without redesigning the underlying application.

Current Qt Milestone

The core Qt functionality is considered complete for the first stage of the coursework.

Implemented functionality includes:

frameless notes;

text editing;

independent dragging;

multiple notes;

deletion;

persistent state;

random pastel colors;

automatic readable text colors;

resizing;

a compact paper-stack launcher;

drag-to-create interaction.

The next major development stage is the implementation of equivalent functionality using wxWidgets.

Planned Visual Improvements

The following improvements are intentionally deferred until functional parity with wxWidgets is reached:

replace the temporary launcher drawing with custom artwork;

display the colors of the next three notes directly in the paper stack;

treat the visible stack as a queue, where removing the top note shifts the remaining colors upward and generates a new color for the bottom note;

provide stronger visual feedback while a note is being pulled from the stack;

support replaceable custom visual assets;

add a custom paper-crumpling deletion animation;

improve final visual polish.

wxWidgets

Development has not started yet.

The wxWidgets implementation will reproduce the same core requirements as the Qt version so that differences between the frameworks can be evaluated under comparable conditions.