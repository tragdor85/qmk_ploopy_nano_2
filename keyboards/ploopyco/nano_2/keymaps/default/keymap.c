/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT( QK_MOUSE_BUTTON_1 )
};

bool scrolling_mode = false;

int16_t scroll_accum_horizontal = 0;
int16_t scroll_accum_vertical = 0;

int wiggle_count = 0;
bool last_wiggle_direction = false;
uint16_t last_wiggle_time = 0;
uint16_t last_mode_switch_time = 0;

static void reset_wiggle_if_stale(void) {
    if (timer_read() - last_wiggle_time > 150) {
        wiggle_count = 0;
    }
}

static void detect_right_wiggle(int16_t mouse_x_raw, int16_t mouse_y_raw) {
    if (mouse_x_raw > 1 && mouse_y_raw < 3 && !last_wiggle_direction) {
        wiggle_count++;
        last_wiggle_time = timer_read();
        last_wiggle_direction = !last_wiggle_direction;
    }
}

static void detect_left_wiggle(int16_t mouse_x_raw, int16_t mouse_y_raw) {
    if (mouse_x_raw < -1 && mouse_y_raw < 3 && last_wiggle_direction) {
        wiggle_count++;
        last_wiggle_time = timer_read();
        last_wiggle_direction = !last_wiggle_direction;
    }
}

static void check_and_toggle_scroll(void) {
    if (wiggle_count > 3) {
        scrolling_mode = !scrolling_mode;
        wiggle_count = 0;
        last_wiggle_time = 0;
        last_mode_switch_time = 0;
    }
}

static void accumulate_scroll(int16_t mouse_x_raw, int16_t mouse_y_raw) {
    scroll_accum_horizontal += mouse_x_raw;
    scroll_accum_vertical += mouse_y_raw;
}

static void process_horizontal_scroll(int16_t* scroll_value) {
    if (scroll_accum_horizontal > 150) {
         *scroll_value = 1;
        scroll_accum_horizontal = 0;
     } else if (scroll_accum_horizontal < -150) {
         *scroll_value = -1;
        scroll_accum_horizontal = 0;
    }
}

static void process_vertical_scroll(int16_t* scroll_value) {
    if (scroll_accum_vertical > 150) {
         *scroll_value = -1;
        scroll_accum_vertical = 0;
     } else if (scroll_accum_vertical < -150) {
         *scroll_value = 1;
        scroll_accum_vertical = 0;
    }
}

static void set_scrolling_mode_output(report_mouse_t* mouse_report) {
    mouse_report->x = 0;
    mouse_report->y = 0;
}

static void set_mouse_mode_output(report_mouse_t* mouse_report) {
    mouse_report->h = 0;
    mouse_report->v = 0;
}

static void set_scroll_output(report_mouse_t* mouse_report, int16_t h_scroll, int16_t v_scroll) {
    mouse_report->h = h_scroll;
    mouse_report->v = v_scroll;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    int16_t mouse_x_raw = mouse_report.x;
    int16_t mouse_y_raw = mouse_report.y;

    if (timer_read() - last_mode_switch_time > 250) {
        reset_wiggle_if_stale();
        detect_right_wiggle(mouse_x_raw, mouse_y_raw);
        detect_left_wiggle(mouse_x_raw, mouse_y_raw);
        check_and_toggle_scroll();
    }

    if (scrolling_mode) {
        accumulate_scroll(mouse_x_raw, mouse_y_raw);

        int16_t h_scroll = 0;
        int16_t v_scroll = 0;

        process_horizontal_scroll(&h_scroll);
        process_vertical_scroll(&v_scroll);

        set_scroll_output(&mouse_report, h_scroll, v_scroll);
        set_scrolling_mode_output(&mouse_report);
    } else {
        set_mouse_mode_output(&mouse_report);
    }

    return mouse_report;
}


