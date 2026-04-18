# Ploopyco

* [Mouse](mouse/)
* [Trackball](trackball/)
* [Trackball Mini](trackball_mini/)
* [Trackball Nano](trackball_nano/)
* [Trackball Thumb](trackball_thumb/)
* [Adept/Madromys](madromys/)

# Customizing your PloopyCo Device

There are a number of behavioral settings that you can use to help customize your experience
|Define                         |Default Value|Description                                              |
|-------------------------------|-------------|---------------------------------------------------------|
|`PLOOPY_IGNORE_SCROLL_CLICK`   |*Not defined*|Ignores scroll wheel if it is pressed down.              |
|`PLOOPY_SCROLL_DEBOUNCE`       |`5`          |Number of milliseconds between scroll events.            |
|`PLOOPY_SCROLL_BUTTON_DEBOUNCE`|`100`        |Time to ignore scroll events after pressing scroll wheel.|

## DPI

The default DPI is set to `1600`. If your device has a button mapped to `DPI_CONFIG`, you can cycle through the available DPI options. To change the DPI values, define `PLOOPY_DPI_OPTIONS` and `PLOOPY_DPI_DEFAULT` in your keymap's `config.h` before including the keyboard:

```c
#define PLOOPY_DPI_OPTIONS { 1600 }
#define PLOOPY_DPI_DEFAULT 0
```

The `PLOOPY_DPI_OPTIONS` array sets the DPI values you can cycle through and their order. The `PLOOPY_DPI_DEFAULT` defines which index (0-based) is used on first boot. If your keyboard lacks a `DPI_CONFIG` button, you must change the DPI by updating this code and reflashing the firmware.

## Drag Scroll

Drag Sroll is a custom keycode for the Ploopy devices that allow you to hold or tap a button and have the mouse movement translate into scrolling instead.

Nothing needs to be enabled to use this functionality.  Just add the `DRAG_SCROLL` to your keymap.

### Drag Scroll Configuration

* `#define PLOOPY_DRAGSCROLL_MOMENTARY` - Makes the key into a momentary key, rather than a toggle.
* `#define PLOOPY_DRAGSCROLL_DIVISOR_H 8.0` - Sets the horizontal movement divisor to use when drag scroll is enabled.
* `#define PLOOPY_DRAGSCROLL_DIVISOR_V 8.0` - Sets the vertical movement divisor to use when drag scroll is enabled.
* `#define PLOOPY_DRAGSCROLL_INVERT` - This reverses the direction that the scroll is performed.
