# Lab 2: 4x4 Keypad to 7-Segment Display

## Objective

Interface a 4x4 matrix keypad with a 7-segment display (common anode). Display the currently pressed key, and when multiple keys are pressed, cycle through them every 500 ms.

## Learning Outcomes

By completing this lab, you will practice:

- Reading matrix keypad input with the `Keypad` library
- Handling multiple simultaneous key presses
- Mapping alphanumeric input to 7-segment patterns
- Time-based switching with `millis()`

## File

- Sketch: `task2.ino`

## Library Dependency

Install Arduino `Keypad` library before uploading.

In Arduino IDE:

1. Open Library Manager.
2. Search for `Keypad`.
3. Install the maintained `Keypad` library.

## Hardware Required

- Arduino Uno (or compatible)
- 4x4 matrix keypad
- 1-digit 7-segment display (common anode)
- 7 current-limiting resistors (typically 220 ohm to 330 ohm)
- Breadboard and jumper wires

## Pin Mapping

### Keypad Wiring

- Row pins: 9, 10, 11, 12
- Column pins: 13, A0, A1, A2

### 7-Segment Wiring

Segment pin assignments in code:

- Pin 2 -> segment a
- Pin 3 -> segment b
- Pin 4 -> segment c
- Pin 5 -> segment d
- Pin 6 -> segment e
- Pin 7 -> segment f
- Pin 8 -> segment g

Important:

- This sketch is written for common anode logic.
- Segment ON = write `LOW`
- Segment OFF = write `HIGH`

## Supported Display Characters

The sketch maps:

- `0` to `9`
- `A` to `D`

For `*` or `#`, the sketch clears the display and turns ON only the middle segment (`g`) to show a dash-like indicator.

## Program Logic Summary

1. Initialize all 7-segment pins as outputs and set them `HIGH` (display OFF).
2. Continuously read keypad state with `keypad.getKeys()`.
3. Build a string of currently active keys (`PRESSED` or `HOLD`).
4. If at least one key is active:
	 - Display one key.
	 - If multiple keys are active, rotate between them every 500 ms.
5. If no key is active, clear the display.

## Multi-Key Cycling Behavior

When multiple keys are held, the display index increments every 500 ms:

$$
\\text{currentIdx} = (\\text{currentIdx} + 1) \\bmod \\text{active.length()}
$$

This creates a simple round-robin visual scan of all active keys.

## How To Run

1. Open `task2.ino` in Arduino IDE.
2. Install `Keypad` library if not already installed.
3. Wire keypad and 7-segment display according to pin map.
4. Select board and COM port.
5. Upload sketch.
6. Press keypad buttons and observe display output.

## Test Checklist

- Press one numeric key -> matching digit appears.
- Press `A`, `B`, `C`, or `D` -> matching character pattern appears.
- Press `*` or `#` -> dash-like output appears (middle segment).
- Hold two or more keys -> display alternates every ~500 ms.
- Release all keys -> display turns off.

## Common Issues and Fixes

- Nothing displays:
	- Confirm display type is common anode.
	- Confirm shared anode pin(s) are connected correctly.
	- Verify segment resistor connections.
- Wrong segments light up:
	- Re-check segment-to-pin mapping (a-g).
- Key presses not detected:
	- Verify keypad row/column wiring order matches code arrays.
	- Confirm `Keypad` library is installed correctly.
- Display appears inverted:
	- Common cathode display will not work correctly with current bitmasks/logic.

## Extension Ideas

- Add support for lowercase letters or custom symbols.
- Add decimal point handling if your display supports it.
- Show key press count or last key timestamp via serial monitor.

