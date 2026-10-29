#ifndef NON_BLOCKING_LED_H
#define NON_BLOCKING_LED_H

#include <Arduino.h>

class NonBlockingLED {
public:
    // activeLow = true si el LED enciende con nivel bajo (GND / ánodo común)
    NonBlockingLED(uint8_t pin, bool activeLow = false);

    void begin();
    void update(); // Debe llamarse continuamente en el bucle principal

    // Inversión de lógica en tiempo de ejecución
    void setInverted(bool inverted);
    void invert();

    // Control manual directo
    void on();
    void off();
    void toggle();

    // Parpadeos continuos
    void blink(uint32_t intervalMs);
    void blinkPattern(uint32_t onTimeMs, uint32_t offTimeMs);

    // Destellos finitos y disparo único
    void blinkCount(uint8_t count, uint32_t onTimeMs, uint32_t offTimeMs);
    void pulse(uint32_t durationMs);

    // Consulta de estado lógico actual (true = encendido)
    bool getState() const;

private:
    enum LEDMode {
        MODE_SOLID,
        MODE_BLINK,
        MODE_PULSE,
        MODE_BLINK_COUNT
    };

    uint8_t _pin;
    bool _activeLow;
    bool _state;
    LEDMode _mode;

    uint32_t _onTime;
    uint32_t _offTime;
    uint32_t _previousMillis;

    uint8_t _targetCount;
    uint8_t _currentBlinks;

    void setPinState(bool state);
};

#endif