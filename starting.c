
#include <stdio.h>
#include "camera_x11.h"

#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

//#define TESTING
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int frameCount = 0;		// Global frame count variable for detect

const int values_segments[10][7] = {
    {1, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 1},
	{0, 1, 1, 0, 0, 1, 1},
	{1, 0, 1, 1, 0, 1, 1},
	{1, 0, 1, 1, 1, 1, 1},
	{1, 1, 1, 0, 0, 0, 0},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 0, 1, 1}
};

char *days[] = {
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

char *months[] = {
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

//using namespace std;

int checkForRuby(int redCount) {
	//if (rubyDetected == false) {
	if (redCount < 1000) {
		for (int row = 0 ; row < 300; row++) {		// Loop through all X pixels
			for (int col = 0; col < 200; col++) {	// Loop through all Y pixels
				set_pixel(row, col, 250, 0, 0); // Set every pixel to red (screen alert)
				display_picture();
				sleep(2);
				printf("Ruby not detected :( \n");
				exit(0);
			}
		}
		
	} else {
		for (int row = 10 ; row < 40 ; row++) {		// Loop through rectangle X pixels
			for (int col = 10; col < 40; col++) {	// Loop through rectangle Y pixels
				set_pixel(row, col, 0, 255, 0); 	// Draw green rectangle
			}
		}
	}
	display_picture();
	return 0;
}

int detect(bool *rubyDetected, int redCount, long *totalRow, long *totalCol, int *prevCenterRow, int *prevCenterCol, bool *rubyMoved) {

	printf("Red Count: %d\n", redCount);
	
	if (redCount > 1000) {
		*rubyDetected = true;
		// ----------- Find centre -----------
		int centerRow = *totalRow / redCount;
    	int centerCol = *totalCol / redCount;

		if (*prevCenterRow != -1) {
			int xChange = centerRow - *prevCenterRow;
			int yChange = centerCol - *prevCenterCol;


			// Find change in center pos
			long disp = xChange * xChange + yChange * yChange;
			if (disp > 30) {    		// Some number between 10 and 20
				frameCount++;   
			

				if (frameCount >= 5) {
					printf("Ruby moved\n");
					*rubyMoved = true;
				}
			} else {
				//printf("Ruby still\n");
				frameCount = 0;
				*rubyMoved = false;
			}
		}

		// Update prev row and col
		*prevCenterRow = centerRow;
		*prevCenterCol = centerCol;
	} 
	// else {
	// 	*rubyDetected = false;
	// 	printf("No ruby detected\n");
	// }

	return *rubyMoved;
}

void logTheft(struct tm *current){
	FILE *fptr = fopen("ruby_theft.log", "a"); //error - need to create a new file, currently outputs time several times

	if(fptr == NULL){
		perror("Failed to open log file");
		return;
	}

	int hours = current->tm_hour;
	int minutes = current->tm_min;
	int seconds = current->tm_sec;
	int wday = current->tm_wday;
	int mday = current->tm_mday;
	int month = current->tm_mon + 1;
	int year = current->tm_year + 1900;

	char *dayName = days[current->tm_wday];
	char *monthName = months[current->tm_mon];


	fprintf(fptr, "Date and time of attempted theft: \n");
	fprintf(fptr, "%s %d %s %d\n", dayName, mday, monthName, year);
	fprintf(fptr, "%02d hours - %02d minutes - %02d seconds\n\n", hours, minutes, seconds);
	
	fclose(fptr);

}

void drawHorizontalSegments(int segment, int row, int startColumn, int endColumn){
	if(segment == 1){
		for(int i = startColumn; i < endColumn; i++){
			set_pixel(row, i, 255, 0, 0);
		}
	}
}

void drawVerticalSegments(int segment, int startRow, int endRow, int col){
	if(segment == 1){
		for(int i = startRow; i < endRow; i++){
			set_pixel(i, col, 255, 0, 0);
		}
	}

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
	
	display_picture();
}

int main() {
	
	 if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }
	
	for (int i=0;i<=10;i++) {
		take_picture();
	}

	bool rubyDetected = false;
	bool rubyMoved = false;
	int prevCenterRow = -1;
  	int prevCenterCol = -1;

	time_t raw_time;
	struct tm *info;

  // make 1000 runs  
  for (int countrun = 0; countrun < 1000; countrun++) {
	while (!rubyMoved) {
		take_picture();
		display_picture();

		int redCount = 0;

		// -------- Find centre of ruby -------------------
		long totalRow = 0;
		long totalCol = 0;


		// orginal redCount on start up
		// for all pixels in latest image
		for (int row = 0 ; row < 1200 ; row++) {	
			for (int col = 0; col < 420; col++) {
				uchar r, g ,b ;
				get_pixel(row, col, &r, &g ,&b);
				
				double bRatio = b/(r+g+b + 0.00001);
				double gRatio = g/(r+g+b + 0.00001);
	
				
				if (gRatio < 0.3 && bRatio < 0.3) {
					redCount ++;		// Increment counter for red px
					totalRow += row;	// Add row
					totalCol += col;	// Add col
					
				}
			}
		}
		//printf("Red Count: %d\n", redCount);
		detect(&rubyDetected, redCount, &totalRow, &totalCol, &prevCenterRow, &prevCenterCol, &rubyMoved);

		checkForRuby(redCount);

		if (rubyMoved) {
			time(&raw_time);
		//rubyPresent = false;
		info = localtime(&raw_time);

		int hours = info->tm_hour;
		int minutes = info->tm_min;
		int seconds = info->tm_sec;
		int wday = info->tm_wday;
		int mday = info->tm_mday;
		int month = info->tm_mon + 1;
		int year = info->tm_year + 1900;

		char time_str[7];
		char time_str_display[9];
		snprintf(time_str, sizeof(time_str), "%02d%02d%02d", hours, minutes, seconds);
		snprintf(time_str_display, sizeof(time_str_display), "%02d-%02d-%02d", hours, minutes, seconds);
		
		displayTime(time_str);
		logTheft(info);
		//exit(0);

		printf("%s", time_str);
		printf("%s", time_str_display);
		printf("%d", hours);
		printf("%d", minutes);
		printf("%d", seconds);
		}
		
	}
	
}
  //close_screen_stream();
  return 0;
}