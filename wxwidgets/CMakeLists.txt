include(FetchContent)

set(wxBUILD_SHARED OFF CACHE BOOL "" FORCE)
set(wxBUILD_SAMPLES "OFF" CACHE STRING "" FORCE)
set(wxBUILD_TESTS "OFF" CACHE STRING "" FORCE)
set(wxBUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(wxBUILD_BENCHMARKS OFF CACHE BOOL "" FORCE)
set(wxBUILD_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    wxwidgets_source
    URL
        https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.12/wxWidgets-3.2.12.zip
    URL_HASH
        SHA1=c2ffa5941f23162782c009d838ddb71d344070e1
)

FetchContent_MakeAvailable(wxwidgets_source)

add_executable(
    StickyNotesWx
    WIN32

    src/main.cpp

    src/StickyNote.cpp
    src/StickyNote.h

    src/NoteManager.cpp
    src/NoteManager.h

    src/LauncherWindow.cpp
    src/LauncherWindow.h
)

target_link_libraries(
    StickyNotesWx
    PRIVATE
        wx::core
        wx::base
)