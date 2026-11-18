find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(StickyNotesQt
    src/main.cpp
    src/StickyNote.cpp
    src/StickyNote.h
)

target_link_libraries(StickyNotesQt
    PRIVATE
        Qt6::Widgets
)

set_target_properties(StickyNotesQt PROPERTIES
    WIN32_EXECUTABLE TRUE
)