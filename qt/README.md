# Qt Implementation

Qt implementation of the cross-platform sticky-notes application used in the framework comparison.

## Status

**Core functionality complete.**

The implementation currently supports:

- frameless independent sticky-note windows;
- direct text editing;
- dragging notes around the desktop;
- multiple simultaneous notes;
- individual deletion;
- resizing;
- persistence of text, position, dimensions, and colors between sessions;
- random pastel color generation;
- automatically generated contrasting text colors;
- a compact paper-stack launcher;
- creation of notes by clicking or dragging from the launcher.

## Structure

```text
src/
├── main.cpp
├── StickyNote.h
├── StickyNote.cpp
├── NoteManager.h
├── NoteManager.cpp
├── LauncherWindow.h
└── LauncherWindow.cpp
```

### `StickyNote`

Represents an individual sticky note and is responsible for:

- displaying and editing text;
- custom frameless-window appearance;
- note movement;
- resizing;
- applying note colors;
- deletion controls.

### `NoteManager`

Manages note creation and application state, including:

- tracking active notes;
- generating random pastel palettes;
- calculating readable text colors;
- saving note data;
- restoring notes between application sessions.

Persistent state is implemented using `QSettings`.

### `LauncherWindow`

Provides the compact paper-stack interface used to create new notes.

The launcher supports both:

- click-to-create;
- drag-to-create interaction.

Its current appearance is rendered programmatically using `QPainter` and is intended to be replaceable by custom visual assets later.

## Planned Improvements

The core Qt feature set is considered complete for the initial framework comparison.

Future visual improvements may include:

- custom paper-stack artwork;
- a visible queue showing the colors of upcoming notes;
- improved visual feedback during drag-to-create;
- custom paper textures;
- a paper-crumpling deletion animation.