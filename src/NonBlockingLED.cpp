#include "NonBlockingLED.h"

NonBlockingLED::NonBlockingLED(uint8_t pin, bool activeLow)
    : _pin(pin),
      _activeLow(activeLow),
      _state(false),
      _mode(MODE_SOLID),
      _onTime(500),
      _offTime(500),
      _previousMillis(0),
      _targetCount(0),
      _currentBlinks(0) {}

void NonBlockingLED::begin() {
    pinMode(_pin, OUTPUT);
    setPinState(false);
}

void NonBlockingLED::setPinState(bool state) {
    _state = state;
    // Si activeLow es true: true -> LOW, false -> HIGH
    digitalWrite(_pin, _activeLow ? !_state : _state);
}

void NonBlockingLED::setInverted(bool inverted) {
    _activeLow = inverted;
    setPinState(_state);
}

void NonBlockingLED::invert() {
    setInverted(!_activeLow);
}

bool NonBlockingLED::getState() const {
    return _state;
}

void NonBlockingLED::on() {
    _mode = MODE_SOLID;
    setPinState(true);
}

void NonBlockingLED::off() {
    _mode = MODE_SOLID;
    setPinState(false);
}

void NonBlockingLED::toggle() {
    _mode = MODE_SOLID;
    setPinState(!_state);
}

void NonBlockingLED::blink(uint32_t intervalMs) {
    blinkPattern(intervalMs, intervalMs);
}

void NonBlockingLED::blinkPattern(uint32_t onTimeMs, uint32_t offTimeMs) {
    _mode = MODE_BLINK;
    _onTime = onTimeMs;
    _offTime = offTimeMs;
    _previousMillis = millis();
    setPinState(true);
}

void NonBlockingLED::pulse(uint32_t durationMs) {
    _mode = MODE_PULSE;
    _onTime = durationMs;
    _previousMillis = millis();
    setPinState(true);
}

void NonBlockingLED::blinkCount(uint8_t count, uint32_t onTimeMs, uint32_t offTimeMs) {
    if (count == 0) {
        off();
        return;
    }
    _mode = MODE_BLINK_COUNT;
    _targetCount = count;
    _currentBlinks = 0;
    _onTime = onTimeMs;
    _offTime = offTimeMs;
    _previousMillis = millis();
    setPinState(true);
}

void NonBlockingLED::update() {
    if (_mode == MODE_SOLID) return;

    uint32_t currentMillis = millis();

    switch (_mode) {
        case MODE_BLINK: {
            uint32_t targetDuration = _state ? _onTime : _offTime;
            if (currentMillis - _previousMillis >= targetDuration) {
                _previousMillis = currentMillis;
                setPinState(!_state);
            }
            break;
        }

        case MODE_PULSE: {
            if (_state && (currentMillis - _previousMillis >= _onTime)) {
                setPinState(false);
                _mode = MODE_SOLID;
            }
            break;
        }

        case MODE_BLINK_COUNT: {
            uint32_t targetDuration = _state ? _onTime : _offTime;
            if (currentMillis - _previousMillis >= targetDuration) {
                _previousMillis = currentMillis;

                if (_state) {
                    setPinState(false);
                    _currentBlinks++;
                    if (_currentBlinks >= _targetCount) {
                        _mode = MODE_SOLID;
                    }
                } else {
                    setPinState(true);
                }
            }
            break;
        }

        default:
            break;
    }
}