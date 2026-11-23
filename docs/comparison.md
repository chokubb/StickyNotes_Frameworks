Framework Comparison

This document records observations collected while implementing the same sticky-notes application using Qt and wxWidgets.

Both implementations have reached the same core functional baseline, allowing direct comparison of the development experience.

Functional Baseline

Both versions currently support:

frameless sticky-note windows;

editable text;

independent window movement;

multiple simultaneous notes;

deletion;

resizing;

persistent text;

persistent position;

persistent dimensions;

persistent colors;

random pastel palettes;

readable text colors;

paper-stack launcher;

click-to-create interaction;

drag-to-create interaction.

Custom artwork and deletion animations are intentionally outside the current baseline.

Development Environment

Both implementations use:

C++20;

CMake;

Visual Studio 2026;

MSVC v143;

Windows x64.

This keeps the development environment consistent while changing the GUI framework.

Initial Setup

Qt

Qt 6.12 was installed separately using the MSVC 2022 64-bit package.

The project locates Qt using:

find_package(Qt6 REQUIRED COMPONENTS Widgets)

An initial issue occurred because Visual Studio created a CMake cache without the required Qt installation path.

This was resolved by introducing CMakePresets.json, which stores the selected generator, architecture, compiler toolset, and Qt path.

wxWidgets

wxWidgets 3.2.12 is integrated through CMake FetchContent.

The source archive is downloaded automatically and wxWidgets is built as part of the CMake project.

This avoids a separate manual framework installation but makes the initial configuration/build process significantly heavier because the framework libraries are compiled locally.

Window Creation

Qt

Sticky notes are custom QWidget top-level windows.

Window decorations are removed with:

Qt::FramelessWindowHint

wxWidgets

Sticky notes are custom wxFrame windows created with:

wxBORDER_NONE

Both frameworks support the required frameless top-level windows.

Text Editing

Qt

Editable content is implemented using QPlainTextEdit.

The control integrated into the custom note layout without requiring significant framework-specific correction.

wxWidgets

Editable content is implemented using wxTextCtrl.

During the first implementation, the multiline control retained an unwanted native vertical scrollbar and did not initially occupy the expected area of the frame.

The final implementation explicitly uses:

wxTE_MULTILINE | wxTE_NO_VSCROLL | wxBORDER_NONE

and explicitly performs layout after attaching the sizer.

This required more adjustment than the equivalent Qt implementation.

Mouse Interaction and Dragging

Qt

The custom StickyNote class overrides virtual mouse-event handlers:

mousePressEvent;

mouseMoveEvent;

mouseReleaseEvent.

wxWidgets

The implementation binds event types to dedicated handlers using Bind():

wxEVT_LEFT_DOWN;

wxEVT_MOTION;

wxEVT_LEFT_UP.

Both approaches provide the required behavior, but their event models differ structurally.

Multiple Notes and Object Management

Qt

Active notes are stored in:

QList<QPointer<StickyNote>>

QPointer automatically becomes null when the corresponding QObject is destroyed.

wxWidgets

Active notes are stored in:

std::vector<StickyNote*>

Close events explicitly remove destroyed note pointers from the collection.

Both approaches work correctly, but Qt provides an additional framework-level guarded pointer abstraction.

Resizing

Qt

Qt provides QSizeGrip, which can be inserted directly into the custom frameless note.

The grip handles the resizing interaction itself.

wxWidgets

Using a normal resizable frame border would conflict with the custom frameless design.

For this reason, the wxWidgets version uses a custom bottom-right resize grip and manually handles:

mouse capture;

initial cursor position;

initial note dimensions;

drag distance;

minimum width and height;

release of mouse capture.

For this application, Qt required substantially less custom resize logic.

Persistence

Qt

Persistence is implemented with QSettings.

Qt provides array-oriented methods:

beginWriteArray;

setArrayIndex;

beginReadArray.

Each note stores:

text;

x/y position;

width/height;

background color;

text color.

wxWidgets

Persistence is implemented with wxConfig.

The implementation manually creates hierarchical paths such as:

/notes/0
/notes/1
/notes/2

and stores the number of notes separately.

Equivalent data is stored for each note.

Both frameworks provide built-in persistence APIs, but QSettings offered a more convenient abstraction for this particular collection-based data structure.

Color Generation

Qt

Qt's QColor provides HSL support directly through methods such as:

QColor::fromHsl(...)

This allows pastel background and matching text colors to be generated with relatively little custom code.

wxWidgets

wxColour represents RGB colors but does not provide the same high-level HSL conversion used by the Qt implementation.

The wxWidgets version therefore contains its own HSL-to-RGB conversion function.

Both versions use the same general algorithm:

random hue across the color wheel;

restricted pastel saturation;

restricted high lightness;

darker text based on the same hue;

minimum contrast ratio of 4.5;

dark-gray fallback when required;

minimum difference between consecutive hues.

The final visual result is similar, but the wxWidgets implementation requires more supporting code.

Interface Customization

Qt

Qt style sheets are used to customize:

note backgrounds;

text colors;

transparent editor appearance;

close controls;

hover behavior.

This made it relatively easy to move away from the native Windows visual style.

wxWidgets

wxWidgets generally exposes controls that follow native platform behavior and appearance more closely.

During development this produced several small additional issues for the custom visual design:

native scrollbar behavior;

more explicit control sizing;

explicit layout management;

more manual visual handling.

The close symbol also required an explicit wide Unicode string:

wxString(L"\u00D7")

to guarantee correct rendering in the selected Windows/MSVC environment.

For a conventional native-looking desktop application this behavior can be beneficial, but for this highly customized interface it required more manual work.

Custom Drawing and Launcher

Qt

The paper-stack launcher is drawn using QPainter.

The launcher uses a translucent frameless window.

wxWidgets

The equivalent stack is drawn using wxWidgets drawing APIs and a shaped frameless frame.

A wxRegion is used to define the launcher shape.

Both frameworks successfully implement the custom launcher and drag-to-create interaction.

Launcher and Note Placement Fixes

During testing of the wxWidgets launcher, two UX issues were identified:

click-created notes could appear partially outside the usable screen area when the launcher was near the bottom-right corner;

the launcher initially used an always-on-top window flag and therefore remained above unrelated applications.

The first issue was fixed by checking the display containing the pointer and clamping the new note position to the display client area.

The second was fixed by removing the explicit always-on-top flag.

Equivalent behavior in the Qt launcher will be verified separately before final testing.

These are treated as implementation-level UX issues rather than intrinsic framework limitations.

Preliminary Comparison

At the current stage, both frameworks are capable of implementing the complete baseline application.

Qt generally required less custom supporting code for this particular project, especially in:

color conversion;

resizing;

style customization;

guarded object references;

array-based settings storage.

wxWidgets successfully reproduced the same functionality, but several areas required more explicit platform-oriented or manual handling.

At the same time, wxWidgets' stronger reliance on native controls can be an advantage for applications that intentionally seek a traditional platform-native interface.

The final coursework conclusions should also consider:

final visual-polish work;

deployment/package size;

build output;

cross-platform testing where practical;

any additional issues identified during final testing.