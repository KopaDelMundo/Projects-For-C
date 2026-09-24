# Projects-For-C

Aaron's C learning roadmap. Each `Phase 1/weekN/` directory is a self-contained
exercise building toward game-engine-style systems programming. Worked through
week by week; week 7 is the current edge.

Last updated: 2026-09-24

## Layout and conventions

- One `main.c` per week, self-contained. No headers, no multi-file builds yet.
- Prototypes at the top of the file, `main` next, definitions after. Keep this.
- `Makefile` per week. Standard flags: `-Wall -Wextra -g -Wstrict-prototypes`.
  `-Wstrict-prototypes` was added deliberately after week 1 — do not drop it.
- `notes.txt` is scratch: design sketches, draft functions, test-case lists.
  Not documentation. Sometimes holds an *earlier, wrong* version of a function.
- `week7/tests.c` is the established test pattern: `#include "main.c"` with
  `#define main demo_main` to rename the demo out of the way, a `CHECK` macro
  counting pass/fail, one `test_*` function per behavior, `return failed != 0`.
  Reuse this shape for new test suites.
- Weeks are split `_a`/`_b` (or `week7`/`week7b`) when the exercise has two
  parts. `week5_revised` is a rework, not a separate exercise.

## How Aaron wants to work

- **Feedback before fixes.** He asks for a review, fixes things himself, then
  asks for another pass. Don't silently apply changes he hasn't asked for.
- **Ranked by severity, with reasoning.** Say *why* something is wrong and what
  it breaks later, not just what to type. Name the general principle.
- **Honest calibration over encouragement.** He has directly asked whether he's
  improving or whether mistakes are "par for the course." Answer from evidence
  in the code and git history, and state the caveats that cut against the
  flattering read.
- Ask before changing files when the request is "show me" or "give feedback."

## Recurring mistake patterns

These repeat across weeks. Worth checking for in any new code:

1. **Named constant defined, then bypassed.** `#define BASE_CAP 10` but
   `da_init` hardcodes `10` (week 7). `Proj_Flag` enum but `active_state == 1`
   (week 7b). Harmless until the constant changes.
2. **Partially-initialized structs.** `init_pool` sets 1 of 4 fields (week 7b).
   Week 6's `e2` omits `.type_of_entity`, so `kind` zero-inits to
   `KIND_PROJECTILE` and an NPC prints as a projectile.
3. **Boundary expressions.** `count + 1 >= capacity` grows a cycle early
   (week 7). `index > POOL_SIZE` should be `>=` (week 7b). Most persistent one.
4. **Meta-pattern: rules applied inconsistently across sibling functions.**
   `da_remove_swap` had its `num < 0` guard from the first commit;
   `da_get` didn't get `i < 0` until the test suite forced it. The knowledge is
   there — the sweep across every call site is what's missing.

Mistake *class* has shifted over time: week 1 was language-level (empty
prototypes, float equality), weeks 5-7 were memory/lifetime, week 7b is
semantic — compiles clean, runs clean, plausible output, wrong. Bugs are fewer
and less severe but harder to detect, which is why the test suites now matter.

## Already mastered — don't re-teach

- The `realloc` idiom: assign to `tmp`, NULL-check, then commit. `notes.txt` in
  week 7 preserves the naive leaking version he started with and corrected.
- `da_free` NULLing the pointer and zeroing count/capacity; double-free safety.
- Fixing categories with compiler flags rather than vigilance.
- Passing large structs by pointer and small ones (`Vector2`) by value.
- Lookup tables for state machines (week 6 `can_transition`).

## Known open issues

Found in review, left unfixed. Not a task list — context so they aren't
re-reported as new.

- **week6/main.c** — `e2` declared without `.type_of_entity`, prints
  "Projectile speed: 0 mph" four times for an NPC. Leftover `DEBUG:` printfs in
  `can_transition` and `set_state`. `legal[from][to]` indexed with no bounds
  validation. `%.f` vs `%.1f` format mismatch in `print_entity`.
- **week7/main.c** — `da_clear` touches `items[0]` unconditionally, so calling
  it on a freed array is a NULL deref (`./tests --probe` triggers it).
  `da_init` hardcodes `10` instead of `BASE_CAP` and skips the malloc NULL
  check that `da_push` does. `da_get` prints to stdout from an accessor.
- **week7b/main.c** — `spawnResult1 == INACTIVE` should be `== -1`; `INACTIVE`
  is 0, which is now a valid slot index, so the branch fires on the first spawn
  and never on actual overflow (output looks correct either way).
  `print_projectile` bounds check uses `> POOL_SIZE`, should be `>=`.
  `init_pool` still sets only `active_state`.

## Gaps deliberately not implemented

- **week7b** has no `pool_despawn(pool, index)`. Lifetime expiry is the only
  route back to `INACTIVE`, but projectiles mostly die on impact. Natural
  companion to `pool_spawn` returning an index.
- `pool_spawn` is an O(n) scan per call. Fine at `POOL_SIZE 256`. The next step
  would be a `first_free` hint or a free list threaded through inactive slots.
