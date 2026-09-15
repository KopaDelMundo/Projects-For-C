/*
 * Edge-case tests for the week 7 dynamic array.
 *
 * main.c is #included directly so the tests can see Entity, DynArray and the
 * da_* functions without splitting the exercise into a separate header. The
 * demo main() in main.c is renamed out of the way so this file can define its
 * own.
 */
#define main demo_main
#include "main.c"
#undef main

#include <string.h>

static int checks_run;
static int checks_failed;

#define CHECK(cond, ...)                                                      \
    do {                                                                      \
        checks_run++;                                                         \
        if (cond) {                                                           \
            printf("  pass: ");                                               \
        } else {                                                              \
            checks_failed++;                                                  \
            printf("  FAIL: ");                                               \
        }                                                                     \
        printf(__VA_ARGS__);                                                  \
        printf("\n");                                                         \
    } while (0)

static void banner(const char *name)
{
    printf("\n== %s ==\n", name);
}

/* Fill an array with itemNum 0..n-1 so contents are easy to verify. */
static void fill(DynArray *a, int n)
{
    for (int i = 0; i < n; i++) {
        Entity e = { i };
        da_push(a, &e);
    }
}

static void test_init(void)
{
    DynArray a;

    banner("da_init");
    da_init(&a);
    CHECK(a.count == 0, "count starts at 0 (got %d)", a.count);
    CHECK(a.capacity > 0, "capacity starts positive (got %d)", a.capacity);
    CHECK(a.items != NULL, "items buffer allocated");
    da_free(&a);
}

static void test_push_growth(void)
{
    DynArray a;
    int grew_ok = 1;

    banner("da_push growth");
    da_init(&a);

    /* 100 pushes forces several realloc rounds past the initial capacity. */
    fill(&a, 100);
    CHECK(a.count == 100, "count is 100 after 100 pushes (got %d)", a.count);
    CHECK(a.capacity >= a.count, "capacity >= count (cap %d, count %d)",
          a.capacity, a.count);

    /* Every element must survive the reallocs intact. */
    for (int i = 0; i < a.count; i++) {
        if (a.items[i].itemNum != i) {
            grew_ok = 0;
            printf("  (slot %d holds %d)\n", i, a.items[i].itemNum);
        }
    }
    CHECK(grew_ok, "all 100 elements survived reallocation in order");

    da_free(&a);
}

static void test_get_bounds(void)
{
    DynArray a;
    Entity *p;

    banner("da_get bounds");
    da_init(&a);
    fill(&a, 5);

    p = da_get(&a, 0);
    CHECK(p != NULL && p->itemNum == 0, "index 0 returns first element");

    p = da_get(&a, 4);
    CHECK(p != NULL && p->itemNum == 4, "index count-1 returns last element");

    p = da_get(&a, 5);
    CHECK(p == NULL, "index == count returns NULL");

    p = da_get(&a, 999);
    CHECK(p == NULL, "index far past the end returns NULL");

    /*
     * A negative index is the interesting case: the guard only tests
     * i > count - 1, so a negative i slips through and indexes before the
     * buffer. Expected to fail until da_get also rejects i < 0.
     */
    p = da_get(&a, -1);
    CHECK(p == NULL, "negative index returns NULL");

    da_free(&a);
}

static void test_remove_swap(void)
{
    DynArray a;

    banner("da_remove_swap");
    da_init(&a);
    fill(&a, 5);                     /* 0 1 2 3 4 */

    /* Removing the middle should pull the last element into the hole. */
    da_remove_swap(&a, 1);
    CHECK(a.count == 4, "count drops to 4 (got %d)", a.count);
    CHECK(a.items[1].itemNum == 4, "last element swapped into slot 1 (got %d)",
          a.items[1].itemNum);

    /* Removing the final slot is the edge case flagged in the prototypes. */
    da_remove_swap(&a, a.count - 1);
    CHECK(a.count == 3, "removing the last element leaves count 3 (got %d)",
          a.count);
    CHECK(a.items[0].itemNum == 0, "slot 0 untouched by last-element removal");

    /* Out-of-range indices must be rejected without touching count. */
    da_remove_swap(&a, -1);
    CHECK(a.count == 3, "negative index rejected, count still 3 (got %d)",
          a.count);

    da_remove_swap(&a, a.count);
    CHECK(a.count == 3, "index == count rejected, count still 3 (got %d)",
          a.count);

    /* Drain it completely: the last removal must leave an empty array. */
    while (a.count > 0) {
        da_remove_swap(&a, a.count - 1);
    }
    CHECK(a.count == 0, "draining leaves count 0 (got %d)", a.count);
    CHECK(a.capacity >= BASE_CAP, "capacity never shrinks below BASE_CAP "
          "(cap %d)", a.capacity);

    da_free(&a);
}

static void test_shrink_keeps_data(void)
{
    DynArray a;
    int kept_ok = 1;

    banner("shrink preserves data");
    da_init(&a);
    fill(&a, 100);

    /* Remove from the tail until the shrink path has run several times. */
    while (a.count > 8) {
        da_remove_swap(&a, a.count - 1);
    }
    CHECK(a.count == 8, "count is 8 after draining (got %d)", a.count);
    CHECK(a.capacity >= a.count, "capacity still >= count (cap %d, count %d)",
          a.capacity, a.count);

    /* Tail removals only, so the survivors are still 0..7 in order. */
    for (int i = 0; i < a.count; i++) {
        if (a.items[i].itemNum != i) {
            kept_ok = 0;
        }
    }
    CHECK(kept_ok, "survivors intact after repeated shrinking");

    /* The buffer must still be usable for writing after shrinking. */
    fill(&a, 20);
    CHECK(a.count == 28, "can push again after shrinking (got %d)", a.count);

    da_free(&a);
}

static void test_free(void)
{
    DynArray a;

    banner("da_free");
    da_init(&a);
    fill(&a, 30);
    da_free(&a);

    CHECK(a.items == NULL, "items is NULL after free");
    CHECK(a.count == 0, "count is 0 after free (got %d)", a.count);
    CHECK(a.capacity == 0, "capacity is 0 after free (got %d)", a.capacity);

    /* Freeing twice must be safe now that da_free NULLs the pointer. */
    da_free(&a);
    CHECK(a.items == NULL, "second da_free is a harmless no-op");
}

static void test_empty_array_prints(void)
{
    DynArray a;

    banner("empty array");
    da_init(&a);
    CHECK(da_get(&a, 0) == NULL, "da_get on an empty array returns NULL");

    /* Must not read items[0] when count is 0. */
    print_DynArray(&a);
    CHECK(a.count == 0, "printing an empty array leaves count 0");

    da_remove_swap(&a, 0);
    CHECK(a.count == 0, "removing from an empty array is rejected");

    da_free(&a);
}

int main(int argc, char **argv)
{
    (void)argv;

    test_init();
    test_push_growth();
    test_get_bounds();
    test_remove_swap();
    test_shrink_keeps_data();
    test_free();
    test_empty_array_prints();

    printf("\n========================================\n");
    printf("%d checks, %d failed\n", checks_run, checks_failed);
    printf("========================================\n");

    /*
     * da_clear touches items[0] unconditionally, so calling it on a freed
     * array dereferences NULL. Opt in with ./tests --probe to let the
     * sanitizer report it; it is off by default so the suite above can finish.
     */
    if (argc > 1) {
        DynArray a;
        da_init(&a);
        da_free(&a);
        printf("\nprobe: da_clear on a freed array\n");
        da_clear(&a);
    }

    return checks_failed != 0;
}
