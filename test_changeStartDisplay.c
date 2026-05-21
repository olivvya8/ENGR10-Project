#include <stdio.h>
#include <string.h>
#include <stdbool.h>
//#include "horiz_seg_test.h"   // contains: void drawHorizontalSegments(int segment, int row, int startColumn, int endColumn);

static int passed = 0;
static int failed = 0;

static int actual_calls = 0;
static int actual_row[256];
static int actual_col[256];
static int actual_r[256];
static int actual_g[256];
static int actual_b[256];


void set_pixel(int row, int col, int r, int g, int b) {
    if (actual_calls < 256) {
        actual_row[actual_calls] = row;
        actual_col[actual_calls] = col;
        actual_r[actual_calls] = r;
        actual_g[actual_calls] = g;
        actual_b[actual_calls] = b;
    }
    actual_calls++;
}

static void assert_int_equal(const char *label, int expected, int actual) {
    if (expected != actual) {
        fprintf(stderr,
                "FAIL: %s: expected %d, got %d\n", label, expected, actual);
        failed++;
        return;
    }
    passed++;
    return;
}

static void assert_pixel(int index, int expected_row, int expected_col, int expected_r, int expected_g, int expected_b) {
    assert_int_equal("pixel row",
                     expected_row,
                     actual_row[index]);

    assert_int_equal("pixel col",
                     expected_col,
                     actual_col[index]);

    assert_int_equal("pixel r",
                     expected_r,
                     actual_r[index]);

    assert_int_equal("pixel g",
                     expected_g,
                     actual_g[index]);

    assert_int_equal("pixel b",
                     expected_b,
                     actual_b[index]);
}

void changeStartDisplay(bool present){
	if(present){
		for(int row = 0; row < 30; row ++){
			for(int col = 0; col < 50; col ++){
				set_pixel(row, col, 0, 255, 0);
			}
		}
	}
	else{
		for(int r = 0; r < 480; r ++){
			for(int c = 0; c < 640; c ++){
				set_pixel(r, c, 255, 0, 0);
			}
		}
	}
}

int main(void) {

    // --- Test 1: Ruby is present ---
    {
        changeStartDisplay(true);  // present
        assert_pixel(0, 0, 0, 0, 255, 0); 
    }

    // --- Test 2: Ruby not present ---
    {
        changeStartDisplay(false);  // not present
        assert_pixel(0, 0, 0, 255, 0, 0); 
    }

    printf("\nSummary: %d passed, %d failed\n", passed, failed);
    return failed == 0 ? 0 : 1;
}
