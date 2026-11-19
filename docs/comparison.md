Framework Comparison

This document records observations collected during the practical implementation of the same sticky-notes application using Qt and wxWidgets.

The comparison is based on equivalent functional requirements wherever possible.

Comparison Criteria

The following aspects are evaluated:

initial project setup;

dependency integration;

code structure and complexity;

creation and management of independent windows;

frameless-window support;

mouse-event handling;

text editing controls;

creation of multiple windows at runtime;

resizing;

custom interface styling;

custom drawing;

persistence of application state;

animation capabilities;

cross-platform support;

build and deployment workflow.

Functional Baseline

The common baseline for both implementations includes:

creation of sticky notes;

editable text;

independent note movement;

multiple notes;

note deletion;

resizable notes;

persistent text;

persistent position;

persistent dimensions;

persistent colors;

random pastel note palettes;

readable text colors;

a compact paper-stack launcher;

creation of notes by dragging from the launcher.

Additional visual effects will be considered after the two implementations reach functional parity.

Qt

Project Setup

The Qt implementation uses:

Qt 6.12;

Qt Widgets;

C++20;

CMake;

MSVC v143;

Visual Studio 2026.

Qt is located by CMake using find_package(Qt6 REQUIRED COMPONENTS Widgets).

A project-wide CMake preset stores the selected generator, architecture, compiler toolset, and Qt installation path.

Window Creation

Individual sticky notes are implemented as custom QWidget windows.

Standard window decorations are removed using Qt::FramelessWindowHint.

Each note operates as an independent top-level window.

User Interaction

Mouse events are overridden to implement note dragging.

The upper part of the note acts as a custom drag region while the main area remains available for text editing.

Text input is implemented using QPlainTextEdit.

Multiple Notes

A separate NoteManager component creates and tracks active StickyNote instances.

Notes can be created dynamically during program execution and operate independently.

Resizing

Notes can be resized through QSizeGrip.

A minimum note size prevents the interface from becoming unusable when a note is reduced too far.

Persistence

Persistent application state is implemented using QSettings.

The following properties are stored between sessions:

note text;

x and y coordinates;

width and height;

background color;

text color.

Saved notes are automatically recreated during application startup.

Color Generation

New notes receive a randomly generated pastel background color.

The color is generated in the HSL color space with restricted saturation and lightness values to keep the palette within a soft pastel range.

A darker text color is generated from the same hue.

The foreground/background contrast ratio is calculated before the palette is accepted. A neutral dark-gray text color is used as a fallback if the generated color does not provide sufficient contrast.

To increase visual variety, consecutive generated notes are required to have a minimum hue difference.

Generated colors are stored with the note and therefore remain unchanged after restarting the application.

Custom Launcher

The Qt implementation includes a small frameless launcher positioned near the bottom-right area of the desktop.

Its temporary paper-stack appearance is drawn directly using QPainter.

The launcher supports:

click-to-create;

drag-to-create.

During drag-to-create, a new note is created and follows the pointer until it is released.

Current Qt Assessment

Qt has provided direct high-level solutions for most of the required functionality.

Particularly useful components so far include:

QWidget;

QPlainTextEdit;

QSizeGrip;

QSettings;

QPainter;

Qt mouse events;

Qt style sheets.

The final comparative assessment will be completed only after the equivalent wxWidgets implementation is developed.

wxWidgets

Implementation pending.

Equivalent functionality will be reproduced as closely as possible before final conclusions are made.