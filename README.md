# Sticky Notes — Порівняння кросплатформних фреймворків C++

[Українська](#українська) | [English](#english)

![Qt implementation](docs/screenshots/qt/12-paper-stack-launcher.png)

---

# Українська

## Про проєкт

Цей репозиторій створено в межах курсової роботи на тему **«Порівняльний аналіз фреймворків для розробки кросплатформних додатків мовою C++»**.

Метою роботи є практичне порівняння фреймворків **Qt** та **wxWidgets** шляхом реалізації одного й того самого настільного застосунку за допомогою обох технологій.

Для порівняння розробляється застосунок віртуальних стікерів, орієнтований на швидку та інтуїтивну роботу з нотатками без необхідності відкривати окреме повноцінне вікно менеджера нотаток.

## Ідея застосунку

Основна концепція полягає у відтворенні взаємодії зі звичайними паперовими стікерами.

Користувач може створити новий стікер через компактний лаунчер у вигляді стопки паперу, витягнути нову нотатку з цієї стопки, розмістити її в будь-якому місці екрана та одразу вводити текст.

Створені нотатки працюють як окремі безрамкові вікна та можуть незалежно переміщуватися, змінювати розмір і видалятися.

## Фреймворки

У межах роботи порівнюються:

- **Qt 6.12**
- **wxWidgets 3.2.12**

Для забезпечення коректного практичного порівняння в обох реалізаціях передбачається однаковий базовий набір функціональних можливостей.

## Поточний стан

| Функціональність | Qt | wxWidgets |
| --- | :---: | :---: |
| Створення стікерів | ✅ | ⏳ |
| Редагування тексту | ✅ | ⏳ |
| Переміщення стікерів | ✅ | ⏳ |
| Робота з декількома нотатками | ✅ | ⏳ |
| Видалення нотаток | ✅ | ⏳ |
| Збереження тексту та позиції | ✅ | ⏳ |
| Збереження розміру | ✅ | ⏳ |
| Зміна розміру стікерів | ✅ | ⏳ |
| Випадкові пастельні кольори | ✅ | ⏳ |
| Автоматичний контрастний колір тексту | ✅ | ⏳ |
| Збереження кольорів між запусками | ✅ | ⏳ |
| Лаунчер у вигляді стопки стікерів | ✅ | ⏳ |
| Створення нотатки перетягуванням зі стопки | ✅ | ⏳ |
| Користувацька графіка та фінальне візуальне оформлення | Заплановано | Заплановано |
| Анімація видалення / зминання паперу | Заплановано | Заплановано |

Базова функціональність реалізації на **Qt** завершена. Наступним етапом є реалізація аналогічних можливостей за допомогою **wxWidgets** і подальше практичне порівняння двох фреймворків.

## Реалізована функціональність Qt

Поточна Qt-версія підтримує:

- безрамкові стікери у вигляді окремих вікон;
- безпосереднє введення та редагування тексту;
- переміщення нотаток по робочому столу;
- одночасну роботу з декількома стікерами;
- зміну розмірів;
- видалення окремих нотаток;
- збереження тексту, позиції, розміру та кольорів між запусками;
- випадкову генерацію пастельної палітри;
- автоматичне формування контрастного кольору тексту;
- компактний безрамковий лаунчер;
- створення нового стікера звичайним натисканням або перетягуванням зі стопки.

## Заплановані візуальні покращення

Після досягнення функціонального паритету між Qt та wxWidgets планується подальше візуальне вдосконалення застосунку:

- власна графіка для лаунчера;
- відображення кольорів наступних стікерів безпосередньо у стопці;
- черга з трьох видимих кольорів майбутніх нотаток;
- візуальний ефект витягування стікера зі стопки;
- користувацька анімація зминання паперу під час видалення;
- додаткове стилістичне оформлення без зміни основної логіки застосунку.

## Структура репозиторію

```text
StickyNotes_Frameworks/
├── qt/                 — реалізація за допомогою Qt
├── wxwidgets/          — реалізація за допомогою wxWidgets
├── docs/               — матеріали порівняння та нотатки щодо розробки
├── CMakeLists.txt      — коренева конфігурація CMake
├── CMakePresets.json   — конфігурація середовища збирання
└── README.md
```

## Основні критерії порівняння

Під час розробки аналізуються:

- складність початкового налаштування;
- структура та обсяг коду;
- створення та керування вікнами;
- обробка подій миші та взаємодії з користувачем;
- робота з текстовими елементами;
- можливості кастомізації інтерфейсу;
- робота з власним малюванням елементів;
- збереження стану застосунку;
- підтримка анімацій;
- кросплатформність;
- процес збирання та розгортання.

## Середовище розробки

Поточна конфігурація проєкту:

- C++20;
- Visual Studio 2026;
- MSVC v143;
- CMake;
- Qt 6.12 MSVC 2022 64-bit;
- Windows x64.

Поточний `CMakePresets.json` передбачає встановлення Qt у:

```text
C:/Qt/6.12.0/msvc2022_64
```

## Збирання Qt-версії

Конфігурація проєкту:

```powershell
cmake --preset windows-vs2026-v143
```

Збирання:

```powershell
cmake --build --preset debug
```

Запуск:

```powershell
.\build\qt\Debug\StickyNotesQt.exe
```

---

# English

## About the Project

This repository was created as part of a coursework project titled **“Comparative Analysis of Frameworks for Cross-Platform Application Development in C++.”**

The goal is to provide a practical comparison of **Qt** and **wxWidgets** by implementing the same desktop application using both technologies.

The application used for the comparison is a virtual sticky-note system designed for quick and direct note-taking without requiring the user to work through a conventional full-size notes manager.

## Application Idea

The main concept is to reproduce the interaction of physical sticky notes.

The user can create a new note through a compact paper-stack launcher, pull a note out of the stack, place it anywhere on the screen, and immediately enter text.

Created notes operate as independent frameless windows and can be moved, resized, and deleted separately.

## Frameworks

The coursework compares:

- **Qt 6.12**
- **wxWidgets 3.2.12**

The same core feature set is intended to be implemented with both frameworks to provide a fair practical comparison.

## Current Status

| Feature | Qt | wxWidgets |
| --- | :---: | :---: |
| Sticky-note creation | ✅ | ⏳ |
| Text editing | ✅ | ⏳ |
| Window dragging | ✅ | ⏳ |
| Multiple notes | ✅ | ⏳ |
| Note deletion | ✅ | ⏳ |
| Persistent text and position | ✅ | ⏳ |
| Persistent dimensions | ✅ | ⏳ |
| Note resizing | ✅ | ⏳ |
| Random pastel colors | ✅ | ⏳ |
| Automatic contrasting text color | ✅ | ⏳ |
| Persistent colors | ✅ | ⏳ |
| Paper-stack launcher | ✅ | ⏳ |
| Drag-to-create interaction | ✅ | ⏳ |
| Custom artwork and final visual design | Planned | Planned |
| Paper-crumpling deletion animation | Planned | Planned |

The **core Qt implementation is complete**. The next stage is to reproduce the same functionality with **wxWidgets** and use the two implementations for the practical framework comparison.

## Implemented Qt Features

The current Qt implementation supports:

- independent frameless sticky-note windows;
- direct text entry and editing;
- moving notes around the desktop;
- multiple notes simultaneously;
- note resizing;
- individual note deletion;
- persistence of text, position, dimensions, and colors;
- random pastel palette generation;
- automatic contrasting text colors;
- a compact frameless launcher;
- note creation through either clicking or dragging from the paper stack.

## Planned Visual Improvements

After functional parity is reached between Qt and wxWidgets, further visual development is planned:

- custom launcher artwork;
- displaying the colors of upcoming notes directly in the stack;
- a visible three-color queue of future notes;
- visual feedback while pulling a note from the stack;
- a custom paper-crumpling deletion animation;
- additional visual polish without changing the underlying note-management logic.

## Repository Structure

```text
StickyNotes_Frameworks/
├── qt/                 — Qt implementation
├── wxwidgets/          — wxWidgets implementation
├── docs/               — comparison materials and development notes
├── CMakeLists.txt      — root CMake configuration
├── CMakePresets.json   — build environment configuration
└── README.md
```

## Main Comparison Criteria

The development process is used to compare:

- initial project setup;
- code structure and complexity;
- window creation and management;
- mouse-event and user-interaction handling;
- text controls;
- interface customization;
- custom drawing capabilities;
- application-state persistence;
- animation support;
- cross-platform capabilities;
- build and deployment processes.

## Development Environment

The current project configuration uses:

- C++20;
- Visual Studio 2026;
- MSVC v143;
- CMake;
- Qt 6.12 MSVC 2022 64-bit;
- Windows x64.

The current `CMakePresets.json` expects Qt to be installed at:

```text
C:/Qt/6.12.0/msvc2022_64
```

## Building the Qt Version

Configure the project:

```powershell
cmake --preset windows-vs2026-v143
```

Build:

```powershell
cmake --build --preset debug
```

Run:

```powershell
.\build\qt\Debug\StickyNotesQt.exe
```