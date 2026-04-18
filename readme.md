# QMK Firmware - Ploopy Nano Fork

This is a fork of [qmk_firmware](https://github.com/qmk/qmk_firmware) that only supports the Ploopy Nano 2 trackball.

## Build Instructions

Run this command to compile the firmware:

```bash
make ploopyco/nano_2/rev2_003:default
```

When successful, this creates `ploopyco_nano_2_rev2_003_default.uf2` in the `.build/` directory. To flash the firmware:

1. Unplug the Ploopy Nano 2
2. Hold the button on the device
3. Plug it back in (the device will mount as storage)
4. Copy the `.uf2` file to the mounted drive

See the [official programming instructions](https://ploopyco.github.io/nano-2-trackball/appendices/programming/) for more details.

## Custom Trackball Functionality

This fork adds specialized trackball controls for the Ploopy Nano 2:

- **Left Button Click**: Standard click functionality
- **Left Button Hold**: Extended hold detection for special actions
- **Wiggle Toggle**: Toggle between mouse movement mode and scrolling mode

## Credits

Wiggle toggle implementation adapted from [pandrr/wiggleball](https://github.com/pandrr/wiggleball). Ploopy Nano 2 trackball information from [ploopyco/nano-2-trackball](https://github.com/ploopyco/nano-2-trackball).

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

## Supported Keyboards

* [Ploopy Nano 2](keyboards/ploopyco/nano_2/)

