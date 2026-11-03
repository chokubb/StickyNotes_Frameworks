\# Sticky Notes — Порівняння кросплатформних фреймворків C++



\[Українська](#українська) | \[English](#english)



\---



\# Українська



\## Про проєкт



Цей репозиторій створено в межах курсової роботи на тему «Порівняльний аналіз фреймворків для розробки кросплатформних додатків мовою C++».



Метою роботи є практичне порівняння фреймворків Qt та wxWidgets шляхом реалізації однакового застосунку за допомогою обох фреймворків.



\## Ідея застосунку



Проєкт являє собою настільний застосунок для створення віртуальних стікерів.



Основна ідея — зробити роботу з нотатками максимально схожою на використання звичайних паперових стікерів: користувач може швидко створити нотатку, розмістити її у потрібному місці на екрані, редагувати текст та видалити її, коли вона більше не потрібна.



\## Фреймворки



У межах роботи порівнюються:



\- Qt

\- wxWidgets



В обох фреймворках буде реалізовано однаковий базовий набір функцій для забезпечення коректного порівняння.



\## Запланована базова функціональність



\- створення стікерів;

\- введення та редагування тексту;

\- переміщення стікерів по екрану;

\- одночасна робота з декількома нотатками;

\- видалення нотаток;

\- кастомний інтерфейс без стандартного оформлення вікна.



\## Структура репозиторію



```text

qt/            — реалізація за допомогою Qt

wxwidgets/     — реалізація за допомогою wxWidgets

docs/          — матеріали порівняння та нотатки щодо розробки

```



\## Основні критерії порівняння



Під час розробки планується порівняти:



\- складність початкового налаштування;

\- структуру та обсяг коду;

\- створення та керування вікнами;

\- обробку взаємодії з користувачем;

\- можливості кастомізації інтерфейсу;

\- підтримку анімацій;

\- кросплатформність;

\- процес збирання та розгортання застосунку.



\---



\# English



\## About the Project



This repository was created as part of a coursework project titled “Comparative Analysis of Frameworks for Cross-Platform Application Development in C++.”



The goal of the project is to provide a practical comparison of Qt and wxWidgets by implementing the same application using both frameworks.



\## Application Idea



The project is a desktop application for creating virtual sticky notes.



The main idea is to make digital notes behave more like physical sticky notes: the user should be able to quickly create a note, place it anywhere on the screen, edit its text, and remove it when it is no longer needed.



\## Frameworks



The following frameworks are compared:



\- Qt

\- wxWidgets



The same basic feature set will be implemented using both frameworks to provide a fair comparison.



\## Planned Core Features



\- creating sticky notes;

\- entering and editing text;

\- moving notes around the screen;

\- working with multiple notes simultaneously;

\- deleting notes;

\- a custom interface without the standard window frame.



\## Repository Structure



```text

qt/            — Qt implementation

wxwidgets/     — wxWidgets implementation

docs/          — comparison materials and development notes

```



\## Main Comparison Criteria



The development process will be used to compare:



\- initial project setup;

\- code structure and complexity;

\- window creation and management;

\- user interaction handling;

\- interface customization;

\- animation capabilities;

\- cross-platform support;

\- application build and deployment.

