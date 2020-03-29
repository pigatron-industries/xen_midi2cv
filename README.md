# MIDI - CV

MIDI to control voltage converter.

Uses [PJRC Teensy 4.0](https://www.pjrc.com/teensy-4-0/) and [MikroElektronika PIXI Click](https://www.mikroe.com/pixi-click) for IO.



## Hardware

Hardware functions are split into various PCBs.

* PGTNX05 Mainboard - Contains the Teensy 4 CPU, 2x MIDI Inputs and Outputs, 1x PIXI Click for 20 CV Outputs (12-bit).
* PGTNX06 IO Expander - Space for another 2x PIXI Click boards for up to 40 CV inputs or outputs.
* PGTNX07 Gate Output - 32x Gate/Trigger outputs.
* PGTNX08 Pitch Output - 8x 16-bit CV outputs for 1v/oct pitch control.
