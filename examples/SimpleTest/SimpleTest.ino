#include <NonBlockingLED.h>

// Instancia para el LED integrado o en cualquier pin digital
NonBlockingLED led(13);

void setup() {
    led.begin();

    // Si los estudiantes conectaron el LED al revés (ánodo a VCC o módulo activo en LOW),
    // pueden corregirlo sin recablear usando cualquiera de estas dos opciones:
    // led.invert();
    // led.setInverted(true);

    // Arranca con 3 destellos rápidos de confirmación (100 ms ON, 100 ms OFF)
    led.blinkCount(3, 100, 100);
}

void loop() {
    // Motor de tiempos continuo (no bloqueante)
    led.update();

    // Aquí corre libremente el control de motores, lectura de línea o botones
}