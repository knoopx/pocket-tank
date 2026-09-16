/* notice.h - the announcement modals (docs/AUDIO.md section 4a, 2026-09-15):
 * a milestone the moment it is earned, a stage reached.
 *
 * Milestones are set in several places (progression.c, tank.c), so the
 * queue does not need hooks: notice_tick diffs each fish's ms_bits, the
 * tank's tank_ms_bits and each fish's stage against what it announced
 * last frame. notice_sync adopts the current state silently (boot, a
 * restored save, a reset) so nothing old is announced. A fish that
 * appears (an arrival) is adopted silently too - the birth flow is its
 * announcement - but the population milestone it brings is queued.
 *
 * One notice is up at a time for NOTICE_UP_S, or until a tap; the next
 * waits NOTICE_GAP_S. Nothing shows while `blocked` (setup / birth flow /
 * reset prompt up): the queue holds. Each notice carries the cue to play
 * when it comes up; the platform takes it with notice_take_cue. */
#ifndef NOTICE_H
#define NOTICE_H
#include <stdbool.h>
#include <stdint.h>
#include "tank.h"

enum { NOTICE_MILESTONE, NOTICE_TANK_MILESTONE, NOTICE_STAGE };
typedef struct { int kind; int fish; uint32_t bit; float age; } notice_t;

#define NOTICE_UP_S   6.0f
#define NOTICE_GAP_S  1.0f
#define NOTICE_QUEUE  8

void notice_sync(const tank_t *t);
void notice_tick(const tank_t *t, float dt, bool blocked);
const notice_t *notice_current(void);      /* NULL = none up */
void notice_dismiss(void);                 /* a tap */
int  notice_take_cue(void);                /* SND_* for a notice that just came up, else -1 */
int  notice_pending(void);                 /* queued, not counting the one up */

#endif
