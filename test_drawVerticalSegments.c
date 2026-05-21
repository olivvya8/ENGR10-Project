#include <stdio.h>
#include <string.h>
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

void drawVerticalSegments(int segment, int startRow, int endRow, int col){
	if(segment == 1){
		for(int i = startRow; i < endRow; i++){
			set_pixel(i, col, 255, 0, 0);
		}
	}

}

int main(void) {

    // --- Test 1: Segment of red pixels --- Has 5 parameters to be passed
    {
        drawVerticalSegments(1,10,25,5);  // Segment, startRow, endRow, col
        assert_pixel(0, 10, 5, 255, 0, 0); // row, col, r, g, b
    }

    printf("\nSummary: %d passed, %d failed\n", passed, failed);
    return failed == 0 ? 0 : 1;
}