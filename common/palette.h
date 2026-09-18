/* palette.h — the tank's colour constants (2026-09-22: the vivid
 * photo-reference look). One home for every hard-coded colour: the water
 * gradient, the floor, the vegetation, the fish, and the UI chrome.
 * render.c, tank.c and setup.c all draw from this table, so a recolour
 * is a change to one file. The castle and the snail keep their own tone
 * tables (CASTLE_RGB / SNAIL_RGB in render.c) - per-element shading, not
 * palette. */
#ifndef POCKET_TANK_PALETTE_H
#define POCKET_TANK_PALETTE_H

/* water: bright cyan at the surface, deepening to azure at the floor */
#define WATER_TOP    0x50c4e8
#define WATER_MID    0x24a0da
#define WATER_DEEP   0x1578b5

/* the floor: sand tones light -> dark (2026-09-19: the keeper wants sand, not
 * green pebbles - the plants already carry the green), and the reef rock */
#define PEBBLE_LT    0xe0c084
#define PEBBLE_MD    0xc2a066
#define PEBBLE_DK    0xa3824c
#define PEBBLE_DARK  0x84663a
#define REEF_ROCK    0x1e4a3c

/* vegetation: the frond greens (the grass pair, then the sword plant's
 * yellow-green pair) */
#define FROND_A      0x4fae62
#define FROND_B      0x38a05a
#define FROND_C      0x9ed458
#define FROND_D      0x82c244

/* the algae film on the glass: two greens, dappled */
#define ALGAE_A      0x4a9a52
#define ALGAE_B      0x3d8448

/* the airstone's stones (light -> dark) and the glint */
#define STONE_A      0x3a4a44
#define STONE_B      0x2e3e38
#define STONE_C      0x4a5a56
#define STONE_GLINT  0x6a7a76

/* the food pellets and their glint */
#define FOOD_PELLET  0xffbd59
#define FOOD_GLINT   0xffe9bd

/* the fish palette (tank.c's roster + the keeper's swatches): the six
 * roster bodies and their darker fins, plus the extra blue and silver */
#define FISH_TEAL        0x00e0c0
#define FISH_ORANGE      0xff5a2e
#define FISH_GREEN       0x4cd64c
#define FISH_VIOLET      0x8f7bff
#define FISH_YELLOW      0xffc512
#define FISH_PINK        0xff5c8a
#define FISH_BLUE        0x35b6ff
#define FISH_SILVER      0xeef4f6
#define FISH_TEAL_FIN    0x009e8c
#define FISH_ORANGE_FIN  0xc23a14
#define FISH_GREEN_FIN   0x2ea832
#define FISH_VIOLET_FIN  0x5f4fd0
#define FISH_YELLOW_FIN  0xd09012
#define FISH_PINK_FIN    0xc43a68

/* the fish accents: stripe colours, the stress red, and a dark ink */
#define FISH_ACCENT_AMBER  0xffa53d
#define FISH_ACCENT_GOLD   0xffd54f
#define FISH_ACCENT_VIOLET 0x9a86ff
#define FISH_ACCENT_WHITE  0xffffff
#define FISH_ACCENT_RED    0xf25b65
#define FISH_ACCENT_INK    0x0e1c24

/* a hungry fish washes out toward these (render.c's pale mix) */
#define FISH_HUNGRY       0x7a8a8e
#define FISH_HUNGRY_FIN   0x5a6a6e

/* UI chrome over the tank: panels, cards and buttons (opaque, drawn over
 * the scene - the night dim is the water's, never the UI's) */
#define UI_WHITE   0xffffff
#define UI_PANEL   0x04141a
#define UI_EDGE    0x9fd8e2
#define UI_INNER   0x1c2f36
#define UI_DIM     0x2a3f45
#define UI_CAPTION 0x3f6a72
#define UI_STEEL   0x9fb4b8
#define UI_INK     0x031015
#define UI_KEY     0x0e2229
#define UI_GO      0x155e58
#define UI_FILL    0x5f8a92
#define UI_DANGER  0x7a2028

#endif
