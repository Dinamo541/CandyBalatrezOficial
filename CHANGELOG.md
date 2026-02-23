# Changelog

Todas las notas importantes de los cambios en este proyecto se documentarán en este archivo.

## [1.0.0] - 2025-10-24
### Añadido
- Implementación inicial del juego "Candy Balatrez".
- Sistema de niveles progresivos con tres niveles únicos.
- Animaciones dinámicas para gemas (caída, desaparición, intercambio).
- Elementos especiales: bloques inmóviles y bombas explosivas.
- Interfaz gráfica con SFML para mostrar puntajes, movimientos y objetivos.

### Cambiado
- Ajustes en la lógica de gravedad para manejar bloques y gemas de manera eficiente.
- Mejoras en las animaciones para suavizar las transiciones entre movimientos.

### Corregido
- Corrección de errores en la detección de combinaciones de gemas.
- Solución a problemas de memoria relacionados con la eliminación de gemas.

---

## [0.1.0] - 2025-10-01
### Añadido
- Configuración inicial del proyecto.
- Integración de SFML para gráficos y manejo de eventos.
- Clases base para gemas (`Gems`), bloques (`Block`) y bombas (`Bombs`).
- Sistema de tablero (`Board`) y lógica de juego (`Game`).