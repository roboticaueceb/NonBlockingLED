# NonBlockingLED

Librería ligera y no bloqueante para el control de LEDs en microcontroladores compatibles con el ecosistema Arduino (AVR, ESP32, ESP8266, SAMD, STM32, etc.).

Diseñada específicamente para robótica educativa y sistemas embebidos donde el uso de `delay()` degrada o congela bucles críticos como lecturas analógicas, filtros de orientación o algoritmos de control PID.

---

## Características

- **Cero bloqueos:** Toda la temporización se gestiona internamente mediante marcas de tiempo con `millis()`.
- **Inversión lógica en caliente:** Compatible con configuraciones *Active-High* (cátodo a GND) y *Active-Low* (ánodo a VCC o módulos con pull-up) configurable desde el constructor o en tiempo de ejecución con `invert()`.
- **Patrones flexibles:**
  - Parpadeo simétrico continuo (`blink`).
  - Parpadeo asimétrico continuo (`blinkPattern`).
  - Destello único de confirmación (`pulse`).
  - Ráfagas finitas para códigos de estado o errores (`blinkCount`).
- **Bajo consumo de memoria:** Sin dependencias externas ni estructuras pesadas.

---

## Estructura de la Librería

```text
NonBlockingLED/
├── examples/
│   └── EjemploLEDs/
│       └── EjemploLEDs.ino
├── keywords.txt
├── library.properties
├── NonBlockingLED.cpp
├── NonBlockingLED.h
└── README.md