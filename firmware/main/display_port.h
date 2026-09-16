/* display_port.h — the ONLY platform-specific seam for the renderer.
 * The tank renders into an RGB565 buffer (common/render.c); this port ships
 * it to the panel: the 4B's ST7703 720x720 MIPI-DSI panel (the BSP's DPI
 * path), with a stub port for QEMU / compile-only builds. */
#ifndef DISPLAY_PORT_H
#define DISPLAY_PORT_H
#include <stdint.h>
#include <stdbool.h>
#define PANEL_W 720
#define PANEL_H 720
#define SCALED_W   PANEL_W    /* full glass width  */
#define SCALED_H   PANEL_H    /* full glass height */
#define GLASS_X_OFF 0
#define GLASS_Y_OFF 0

bool display_port_init(void);
/* push a full TANK_W x TANK_H RGB565 frame; may return before DMA completes */
void display_port_flush(const uint16_t *fb);
/* power the panel down for device sleep; display_port_wake (or a boot's
 * display_port_init) re-sequences it */
void display_port_sleep(void);
/* re-power and re-init the panel after display_port_sleep, without reboot */
void display_port_wake(void);
/* true = present the frame rotated 180 degrees (device held upside down) */
void display_port_set_inverted(bool inverted);
/* panel brightness 0..255 (DCS 0x51; the init sequence starts at 255). Kept
 * across display_port_wake, which re-inits the panel. */
void    display_port_set_brightness(uint8_t level);
uint8_t display_port_brightness(void);
#endif
