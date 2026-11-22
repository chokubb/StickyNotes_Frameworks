#include "NoteManager.h"
#include "StickyNote.h"

#include <algorithm>
#include <cmath>
#include <random>

#include <wx/config.h>
#include <wx/event.h>
#include <wx/utils.h>

#include <wx/display.h>

void NoteManager::createNote()
{
    const wxPoint cursorPosition =
        wxGetMousePosition();

    const int offset =
        (m_noteCounter % 6) * 24;

    constexpr int noteWidth = 320;
    constexpr int noteHeight = 320;
    constexpr int margin = 20;

    int displayIndex =
        wxDisplay::GetFromPoint(
            cursorPosition
        );

    if (displayIndex == wxNOT_FOUND)
    {
        displayIndex = 0;
    }

    wxDisplay display(
        static_cast<unsigned int>(
            displayIndex
            )
    );

    const wxRect area =
        display.GetClientArea();

    int x =
        cursorPosition.x
        + margin
        + offset;

    int y =
        cursorPosition.y
        + margin
        + offset;

    const int areaRight =
        area.GetLeft()
        + area.GetWidth();

    const int areaBottom =
        area.GetTop()
        + area.GetHeight();

    // If there isn't enough room to the right,
    // place the note to the left of the cursor.
    if (x + noteWidth > areaRight)
    {
        x =
            cursorPosition.x
            - noteWidth
            - margin
            - offset;
    }

    // If there isn't enough room below,
    // place the note above the cursor.
    if (y + noteHeight > areaBottom)
    {
        y =
            cursorPosition.y
            - noteHeight
            - margin
            - offset;
    }

    const int maxX =
        std::max(
            area.GetLeft(),
            areaRight - noteWidth
        );

    const int maxY =
        std::max(
            area.GetTop(),
            areaBottom - noteHeight
        );

    x = std::clamp(
        x,
        area.GetLeft(),
        maxX
    );

    y = std::clamp(
        y,
        area.GetTop(),
        maxY
    );

    createNoteAt(
        wxPoint(x, y)
    );
}

StickyNote* NoteManager::createNoteAt(
    const wxPoint& position
)
{
    const auto palette =
        generatePalette();

    return createNoteAt(
        position,
        wxSize(320, 320),
        "",
        palette.first,
        palette.second
    );
}

StickyNote* NoteManager::createNoteAt(
    const wxPoint& position,
    const wxSize& size,
    const wxString& text,
    const wxColour& backgroundColor,
    const wxColour& textColor
)
{
    auto* note = new StickyNote();

    note->SetSize(size);
    note->Move(position);
    note->setText(text);

    note->setColors(
        backgroundColor,
        textColor
    );

    m_notes.push_back(note);

    note->Bind(
        wxEVT_CLOSE_WINDOW,
        [this, note](wxCloseEvent& event)
        {
            removeNote(note);
            event.Skip();
        }
    );

    note->Show();
    note->Raise();

    ++m_noteCounter;

    return note;
}

void NoteManager::saveNotes()
{
    wxConfig config(
        "StickyNotesWx",
        "StickyNotesFrameworkComparison"
    );

    config.DeleteGroup("notes");

    config.SetPath("/");

    config.Write(
        "lastHue",
        static_cast<long>(m_lastHue)
    );

    config.SetPath("/notes");

    config.Write(
        "count",
        static_cast<long>(m_notes.size())
    );

    for (
        std::size_t i = 0;
        i < m_notes.size();
        ++i
        )
    {
        StickyNote* note = m_notes[i];

        if (note == nullptr)
        {
            continue;
        }

        config.SetPath(
            wxString::Format(
                "/notes/%zu",
                i
            )
        );

        const wxPoint position =
            note->GetPosition();

        const wxSize size =
            note->GetSize();

        const wxColour background =
            note->backgroundColor();

        const wxColour text =
            note->textColor();

        config.Write(
            "text",
            note->text()
        );

        config.Write(
            "x",
            static_cast<long>(position.x)
        );

        config.Write(
            "y",
            static_cast<long>(position.y)
        );

        config.Write(
            "width",
            static_cast<long>(size.x)
        );

        config.Write(
            "height",
            static_cast<long>(size.y)
        );

        config.Write(
            "backgroundRed",
            static_cast<long>(background.Red())
        );

        config.Write(
            "backgroundGreen",
            static_cast<long>(background.Green())
        );

        config.Write(
            "backgroundBlue",
            static_cast<long>(background.Blue())
        );

        config.Write(
            "textRed",
            static_cast<long>(text.Red())
        );

        config.Write(
            "textGreen",
            static_cast<long>(text.Green())
        );

        config.Write(
            "textBlue",
            static_cast<long>(text.Blue())
        );
    }

    config.Flush();
}

void NoteManager::loadNotes()
{
    wxConfig config(
        "StickyNotesWx",
        "StickyNotesFrameworkComparison"
    );

    config.SetPath("/");

    long lastHue = -1;

    config.Read(
        "lastHue",
        &lastHue,
        -1L
    );

    m_lastHue =
        static_cast<int>(lastHue);

    config.SetPath("/notes");

    long count = 0;

    config.Read(
        "count",
        &count,
        0L
    );

    for (long i = 0; i < count; ++i)
    {
        config.SetPath(
            wxString::Format(
                "/notes/%ld",
                i
            )
        );

        wxString text;

        long x = 100;
        long y = 100;

        long width = 320;
        long height = 320;

        long backgroundRed = 255;
        long backgroundGreen = 242;
        long backgroundBlue = 168;

        long textRed = 43;
        long textGreen = 43;
        long textBlue = 43;

        config.Read(
            "text",
            &text,
            ""
        );

        config.Read(
            "x",
            &x,
            100L
        );

        config.Read(
            "y",
            &y,
            100L
        );

        config.Read(
            "width",
            &width,
            320L
        );

        config.Read(
            "height",
            &height,
            320L
        );

        config.Read(
            "backgroundRed",
            &backgroundRed,
            255L
        );

        config.Read(
            "backgroundGreen",
            &backgroundGreen,
            242L
        );

        config.Read(
            "backgroundBlue",
            &backgroundBlue,
            168L
        );

        config.Read(
            "textRed",
            &textRed,
            43L
        );

        config.Read(
            "textGreen",
            &textGreen,
            43L
        );

        config.Read(
            "textBlue",
            &textBlue,
            43L
        );

        const auto channel =
            [](long value)
            {
                return static_cast<unsigned char>(
                    std::clamp(
                        value,
                        0L,
                        255L
                    )
                    );
            };

        const wxColour backgroundColor(
            channel(backgroundRed),
            channel(backgroundGreen),
            channel(backgroundBlue)
        );

        const wxColour textColor(
            channel(textRed),
            channel(textGreen),
            channel(textBlue)
        );

        createNoteAt(
            wxPoint(
                static_cast<int>(x),
                static_cast<int>(y)
            ),
            wxSize(
                std::max(
                    220,
                    static_cast<int>(width)
                ),
                std::max(
                    180,
                    static_cast<int>(height)
                )
            ),
            text,
            backgroundColor,
            textColor
        );
    }
}

void NoteManager::removeNote(
    StickyNote* note
)
{
    m_notes.erase(
        std::remove(
            m_notes.begin(),
            m_notes.end(),
            note
        ),
        m_notes.end()
    );
}

void NoteManager::closeAllNotes()
{
    const auto notes = m_notes;

    for (StickyNote* note : notes)
    {
        if (note != nullptr)
        {
            note->Close(true);
        }
    }
}

std::pair<wxColour, wxColour>
NoteManager::generatePalette()
{
    constexpr int minimumHueDifference = 40;

    static std::mt19937 generator(
        std::random_device{}()
    );

    std::uniform_int_distribution<int>
        hueDistribution(0, 359);

    std::uniform_int_distribution<int>
        saturationDistribution(35, 55);

    std::uniform_int_distribution<int>
        lightnessDistribution(82, 90);

    int hue = 0;

    while (true)
    {
        hue =
            hueDistribution(generator);

        if (m_lastHue < 0)
        {
            break;
        }

        int difference =
            std::abs(
                hue - m_lastHue
            );

        difference =
            std::min(
                difference,
                360 - difference
            );

        if (
            difference >=
            minimumHueDifference
            )
        {
            break;
        }
    }

    m_lastHue = hue;

    const double saturation =
        saturationDistribution(generator)
        / 100.0;

    const double lightness =
        lightnessDistribution(generator)
        / 100.0;

    const wxColour background =
        hslToColour(
            hue,
            saturation,
            lightness
        );

    wxColour text =
        hslToColour(
            hue,
            0.37,
            0.22
        );

    if (
        contrastRatio(
            background,
            text
        ) < 4.5
        )
    {
        text =
            wxColour(
                43,
                43,
                43
            );
    }

    return {
        background,
        text
    };
}

wxColour NoteManager::hslToColour(
    int hue,
    double saturation,
    double lightness
) const
{
    const double h =
        hue / 360.0;

    double red = lightness;
    double green = lightness;
    double blue = lightness;

    if (saturation > 0.0)
    {
        const double q =
            lightness < 0.5
            ? lightness *
            (1.0 + saturation)
            : lightness +
            saturation -
            lightness * saturation;

        const double p =
            2.0 * lightness - q;

        auto hueToRgb =
            [](double pValue,
                double qValue,
                double t)
            {
                if (t < 0.0)
                {
                    t += 1.0;
                }

                if (t > 1.0)
                {
                    t -= 1.0;
                }

                if (t < 1.0 / 6.0)
                {
                    return pValue +
                        (qValue - pValue) *
                        6.0 * t;
                }

                if (t < 1.0 / 2.0)
                {
                    return qValue;
                }

                if (t < 2.0 / 3.0)
                {
                    return pValue +
                        (qValue - pValue) *
                        (2.0 / 3.0 - t) *
                        6.0;
                }

                return pValue;
            };

        red =
            hueToRgb(
                p,
                q,
                h + 1.0 / 3.0
            );

        green =
            hueToRgb(
                p,
                q,
                h
            );

        blue =
            hueToRgb(
                p,
                q,
                h - 1.0 / 3.0
            );
    }

    return wxColour(
        static_cast<unsigned char>(
            std::round(red * 255.0)
            ),
        static_cast<unsigned char>(
            std::round(green * 255.0)
            ),
        static_cast<unsigned char>(
            std::round(blue * 255.0)
            )
    );
}

double NoteManager::contrastRatio(
    const wxColour& first,
    const wxColour& second
) const
{
    auto relativeLuminance =
        [](const wxColour& colour)
        {
            auto linearize =
                [](double value)
                {
                    value /= 255.0;

                    if (
                        value <=
                        0.04045
                        )
                    {
                        return
                            value / 12.92;
                    }

                    return std::pow(
                        (value + 0.055)
                        / 1.055,
                        2.4
                    );
                };

            const double red =
                linearize(colour.Red());

            const double green =
                linearize(colour.Green());

            const double blue =
                linearize(colour.Blue());

            return
                0.2126 * red +
                0.7152 * green +
                0.0722 * blue;
        };

    const double firstLuminance =
        relativeLuminance(first);

    const double secondLuminance =
        relativeLuminance(second);

    const double lighter =
        std::max(
            firstLuminance,
            secondLuminance
        );

    const double darker =
        std::min(
            firstLuminance,
            secondLuminance
        );

    return
        (lighter + 0.05) /
        (darker + 0.05);
}