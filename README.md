# Minishell

Este proyecto consiste en la creación de un **intérprete de comandos UNIX** desde cero, implementado en lenguaje **C** como parte del currículo de la Escuela 42. Reproduce funcionalidades esenciales de una shell, gestionando procesos, señales, redirecciones, piping, variables de entorno y más.

## 🎯 Objetivos del Proyecto

- Comprender el funcionamiento interno de una **shell POSIX**.
- Implementar control de procesos, **pipe**, redirecciones, y ejecución de comandos.
- Manejar señales y variables de entorno como en bash.
- Aplicar buenas prácticas de desarrollo en C, incluyendo gestión robusta de memoria y errores.

## 🛠️ Funcionalidades Principales

- Lectura y ejecución de comandos interactivos.
- Soporte para:
  - Comandos encadenados con `|`
  - Redirecciones `<`, `>`, `>>`, `<<` (heredoc)
  - Variables de entorno (`$VAR`)
  - Expansión de tildes y comillas (`'`, `"`)
  - Señales (Ctrl+C, Ctrl+D)
- Implementación de comandos **built-in** como:
  - `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`

## 📚 Conceptos de Ingeniería de Software

Minishell permite afianzar conceptos avanzados en ingeniería de software:

- **Sistemas operativos**: control de procesos, pipes, duplicación de descriptores.
- **Manejo de señales y errores** en un entorno interactivo.
- **Parsing recursivo**: interpretación de sintaxis compleja y evaluación de expresiones.
- **Gestión de memoria dinámica y estructuras de datos robustas**.
- Diseño modular, testing manual intensivo, y debugging a bajo nivel.
