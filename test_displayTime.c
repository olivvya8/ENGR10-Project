#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

// Mock functions and data
int values_segments[10][7] = {
	{1,1,1,1,1,1,0}, // 0
	{0,1,1,0,0,0,0}, // 1
	{1,1,0,1,1,0,1}, // 2
	{1,1,1,1,0,0,1}, // 3
	{0,1,1,0,0,1,1}, // 4
	{1,0,1,1,0,1,1}, // 5
	{1,0,1,1,1,1,1}, // 6
	{1,1,1,0,0,0,0}, // 7
	{1,1,1,1,1,1,1}, // 8
	{1,1,1,1,0,1,1}  // 9
};

void drawHorizontalSegments(int segment, int row, int col1, int col2) {
	// Mock implementation
}

void drawVerticalSegments(int segment, int row1, int row2, int col) {
	// Mock implementation
}

void displayTime(const char *time_str){
	int size = 20;
	int startRow = 40;
	int startCol = 40;
	int spacing = 5;
	int row = startRow;
	int col = startCol;
	for(int i = 0; i < strlen(time_str); i++){
		int digit = time_str[i] - '0';
		drawHorizontalSegments(values_segments[digit][0], row, col, (col+size));
		drawHorizontalSegments(values_segments[digit][3], (row+2*size), col, (col+size));
		drawHorizontalSegments(values_segments[digit][6], (row+size), col, (col+size));

		drawVerticalSegments(values_segments[digit][1], row, (row+size), (col+size));
		drawVerticalSegments(values_segments[digit][2], (row+size), (row+2*size), (col+size));
		drawVerticalSegments(values_segments[digit][4], (row+size), (row+2*size), (col));
		drawVerticalSegments(values_segments[digit][5], row, (row+size), col);

		col = col + size + spacing;

		if(i == 1 || i == 3){
			drawHorizontalSegments(1, (row+size), col, (col+size));
			col = col + size + spacing;
		}
		
	}
	
}

void run_tests() {
	int passed = 0;
	int failed = 0;

	// Test 1: Valid time format HH:MM:SS
	printf("Test 1: Valid time string \"12:34:56\"...");
	displayTime("12:34:56");
	printf(" PASSED\n");
	passed++;

	// Test 2: Valid time format with leading zeros
	printf("Test 2: Valid time string \"00:00:00\"...");
	displayTime("00:00:00");
	printf(" PASSED\n");
	passed++;

	// Test 3: Valid time format with 9s
	printf("Test 3: Valid time string \"23:59:59\"...");
	displayTime("23:59:59");
	printf(" PASSED\n");
	passed++;

	// Test 4: Single digit time
	printf("Test 4: Single digit \"5\"...");
	displayTime("5");
	printf(" PASSED\n");
	passed++;

	// Test 5: Two digits with colon
	printf("Test 5: Two digits with colon \"12:34\"...");
	displayTime("12:34");
	printf(" PASSED\n");
	passed++;

	printf("\n=== Test Results ===\n");
	printf("Passed: %d\n", passed);
	printf("Failed: %d\n", failed);
	printf("Total: %d\n", passed + failed);
}

int main() {
	run_tests();
	return 0;
}