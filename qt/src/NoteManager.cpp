#include "NoteManager.h"
#include "StickyNote.h"

#include <QCursor>
#include <QRandomGenerator>
#include <QSettings>

#include <algorithm>
#include <cmath>

NoteManager::NoteManager(QObject* parent)
    : QObject(parent)
{}

void NoteManager::createNote()
{
    removeDeletedNotes();

    auto* note = new StickyNote();

    const auto palette = generatePalette();

    note->setColors(
        palette.first,
        palette.second
    );

    const QPoint cursorPosition = QCursor::pos();
    const int offset = (m_noteCounter % 6) * 24;

    note->move(
        cursorPosition.x() + 20 + offset,
        cursorPosition.y() + 20 + offset
    );

    m_notes.append(note);

    note->show();

    ++m_noteCounter;
}

void NoteManager::saveNotes()
{
    removeDeletedNotes();

    QSettings settings;

    settings.remove("notes");

    settings.beginWriteArray("notes");

    int index = 0;

    for (const QPointer<StickyNote>& note : m_notes)
    {
        if (note.isNull())
        {
            continue;
        }

        settings.setArrayIndex(index);

        settings.setValue("text", note->text());

        settings.setValue("x", note->x());
        settings.setValue("y", note->y());

        settings.setValue("width", note->width());
        settings.setValue("height", note->height());

        settings.setValue(
            "backgroundColor",
            note->backgroundColor().name()
        );

        settings.setValue(
            "textColor",
            note->textColor().name()
        );

        ++index;
    }

    settings.endArray();
    settings.sync();
}

void NoteManager::loadNotes()
{
    QSettings settings;

    const int count = settings.beginReadArray("notes");

    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);

        auto* note = new StickyNote();

        const QString text =
            settings.value("text").toString();

        const int x =
            settings.value("x", 100).toInt();

        const int y =
            settings.value("y", 100).toInt();

        const int width =
            settings.value("width", 320).toInt();

        const int height =
            settings.value("height", 320).toInt();

        const QColor backgroundColor(
            settings.value(
                "backgroundColor",
                "#FFF2A8"
            ).toString()
        );

        const QColor textColor(
            settings.value(
                "textColor",
                "#2B2B2B"
            ).toString()
        );

        note->setText(text);

        note->setColors(
            backgroundColor,
            textColor
        );

        note->resize(width, height);
        note->move(x, y);

        m_notes.append(note);

        note->show();

        ++m_noteCounter;

        const int loadedHue =
            backgroundColor.toHsl().hue();

        if (loadedHue >= 0)
        {
            m_lastHue = loadedHue;
        }
    }

    settings.endArray();
}

void NoteManager::removeDeletedNotes()
{
    m_notes.removeIf(
        [](const QPointer<StickyNote>& note)
        {
            return note.isNull();
        }
    );
}

QPair<QColor, QColor> NoteManager::generatePalette()
{
    constexpr int minimumHueDifference = 40;

    int hue = 0;

    do
    {
        hue = QRandomGenerator::global()->bounded(360);

        if (m_lastHue < 0)
        {
            break;
        }

        int difference = std::abs(hue - m_lastHue);

        difference = std::min(
            difference,
            360 - difference
        );

        if (difference >= minimumHueDifference)
        {
            break;
        }

    } while (true);

    m_lastHue = hue;

    const int saturation =
        QRandomGenerator::global()->bounded(90, 141);

    const int lightness =
        QRandomGenerator::global()->bounded(210, 231);

    const QColor background =
        QColor::fromHsl(
            hue,
            saturation,
            lightness
        );

    QColor text =
        QColor::fromHsl(
            hue,
            95,
            55
        );

    if (contrastRatio(background, text) < 4.5)
    {
        text = QColor("#2B2B2B");
    }

    return { background, text };
}

double NoteManager::contrastRatio(
    const QColor& first,
    const QColor& second
) const
{
    auto relativeLuminance =
        [](const QColor& color)
        {
            auto linearize =
                [](double value)
                {
                    value /= 255.0;

                    if (value <= 0.04045)
                    {
                        return value / 12.92;
                    }

                    return std::pow(
                        (value + 0.055) / 1.055,
                        2.4
                    );
                };

            const double red =
                linearize(color.red());

            const double green =
                linearize(color.green());

            const double blue =
                linearize(color.blue());

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