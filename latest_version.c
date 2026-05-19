#include <stdio.h>
#include "camera_x11.h"
#include <time.h>
#include <stdbool.h>
#include <math.h>

//using namespace std;

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


// =====================================================
// THRESHOLDS
// =====================================================

// --- Dark/noise rejection ---
const double MIN_TOTAL_BRIGHTNESS = 0.10;

// --- White/grey glare rejection ---
const double BRIGHT_GLARE_TOTAL = 2.70;
const double MAX_GLARE_CHROMA = 0.05;

// --- Yellow/orange rejection ---
const double MAX_GREEN_RED_RATIO = 0.78;


// =====================================================
// BRIGHT LIGHT THRESHOLDS
// =====================================================

const double BRIGHT_TOTAL_THRESHOLD = 1.55;

const double BRIGHT_MIN_R_RATIO = 0.40;

const double BRIGHT_MIN_RG_DELTA = 0.16;
const double BRIGHT_MIN_RB_DELTA = 0.16;

const double BRIGHT_MIN_CHROMA = 0.18;


// =====================================================
// NORMAL LIGHT THRESHOLDS
// =====================================================

const double NORMAL_TOTAL_THRESHOLD = 0.60;

const double NORMAL_MIN_R_RATIO = 0.50;

const double NORMAL_MIN_RG_DELTA = 0.12;
const double NORMAL_MIN_RB_DELTA = 0.10;

const double NORMAL_MIN_CHROMA = 0.12;


// =====================================================
// DIM LIGHT THRESHOLDS
// =====================================================

const double DIM_MIN_R_RATIO = 0.62;

const double DIM_MIN_RG_DELTA = 0.06;
const double DIM_MIN_RB_DELTA = 0.06;

const double DIM_MIN_CHROMA = 0.06;

const int highDisplacement = 50;
const int smallDisplacement = 16;



void trackRuby(bool *rubyDetected, bool *rubyMoved, bool *attemptedTheft, int *prevCenterRow, int *prevCenterCol)
{
    static int motionCount = 0;

    int redCount = 0;
    bool valid = false;
    long totalRow = 0;
    long totalCol = 0;
    

    
    for (int row = 0; row < 480; row++) {

        for (int col = 0; col < 640; col++) {

            valid = false;

            uchar r, g, b;

            get_pixel(row, col, &r, &g, &b);

            
				// ---------- Brightness ----------
			double total = ((double)r + (double)g + (double)b) / 255.0;
			double scaledR = (double)r / 255.0;
			double scaledG = (double)g / 255.0;
			double scaledB = (double)b / 255.0;

					// Reject near-black pixels/noise
			if (total <= MIN_TOTAL_BRIGHTNESS){
				continue;
			}
				


			// ---------- Basic colour metrics ----------
			double maxVal = fmax(scaledR, fmax(scaledG, scaledB));
			double minVal = fmin(scaledR, fmin(scaledG, scaledB));

			double chroma = maxVal - minVal;

			double rRatio = scaledR / (total + 0.000001);

			double rgDifference = scaledR - scaledG;
			double rbDifference = scaledR - scaledB;


			// ---------- Reject white/grey glare ----------
			if (total > BRIGHT_GLARE_TOTAL && chroma < MAX_GLARE_CHROMA){

				continue;
				
			}


			// ---------- Red must dominate ----------
			if (scaledR <= scaledG || scaledR <= scaledB)
				continue;


			// ---------- Reject yellow/orange ----------
			if (scaledG > scaledR * MAX_GREEN_RED_RATIO)
				continue;


			// =================================================
			// BRIGHT LIGHTING
			// =================================================
			
            if (total >= BRIGHT_TOTAL_THRESHOLD && rRatio >= BRIGHT_MIN_R_RATIO &&	rgDifference >= BRIGHT_MIN_RG_DELTA &&
                rbDifference >= BRIGHT_MIN_RB_DELTA &&
                chroma >= BRIGHT_MIN_CHROMA)
            {
                valid = true;
            }
			

			// =================================================
			// NORMAL LIGHTING
			// =================================================
			
            else if (total >= NORMAL_TOTAL_THRESHOLD && rRatio >= NORMAL_MIN_R_RATIO &&
                rgDifference >= NORMAL_MIN_RG_DELTA &&
                rbDifference >= NORMAL_MIN_RB_DELTA &&
                chroma >= NORMAL_MIN_CHROMA)
            {
                valid = true;
            }
			

			// =================================================
			// DIM LIGHTING
			// =================================================
			
            else if (rRatio >= DIM_MIN_R_RATIO &&
                rgDifference >= DIM_MIN_RG_DELTA &&
                rbDifference >= DIM_MIN_RB_DELTA &&
                chroma >= DIM_MIN_CHROMA)
            {
                valid = true;
            }
			

            if(valid){
                redCount ++;
                totalRow += row;
                totalCol += col;
            }


		}

		
	

    }

	



    // -------- Ruby detection --------
    if (redCount > 2000) {

        *rubyDetected = true;
        *attemptedTheft = false;

        // -------- Find center --------
        int centerRow = totalRow / redCount;
        int centerCol = totalCol / redCount;

       
        // -------- Motion detection --------
        if (*prevCenterRow != -1) {

			start = false;
            int dx = centerRow - *prevCenterRow;
            int dy = centerCol - *prevCenterCol;

            long disp = dx*dx + dy*dy;

            
            if(disp > highDisplacement){
                *rubyMoved = true;
                *attemptedTheft = true;
            }
			else if(disp > smallDisplacement){
				motionCount ++;
				
			}
			else{
				motionCount = 0; //ruby is still/center has hardly changed
			}
        }


        if(motionCount >= 3){
            *rubyMoved = true;
            *attemptedTheft = true;
        }

        *prevCenterRow = centerRow;
        *prevCenterCol = centerCol;

        

    }

    else {

        *rubyDetected = false;
        *attemptedTheft = true;

        

        printf("Attempted theft\n");
    }
}

//const char *time_str_display
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
	display_picture();
}



int main() {

	bool rubyDetected = false;
    bool rubyMoved = false;
    bool attemptedTheft = false;
	int prevCenterRow = -1;
	int prevCenterCol = -1;
	long prevBrightness = 0;
	bool rubyPresent = false;
	
	
	 if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }

	time_t raw_time;
	struct tm *info;
   
    (for int i = 0; i < 10; i++){
        take_picture();
    }

	take_picture();
	

	display_picture();
	trackRuby(&rubyDetected, &rubyMoved, &attemptedTheft, &prevCenterRow, &prevCenterCol);
	if(attemptedTheft){
		changeStartDisplay(true);
		rubyPresent = true;
	}
	else{
		changeStartDisplay(false); //turn screen red
		//exit(0); //ruby not present at start, terminate
		
	}

// make 1000 runs/program continues to run if ruby is present  //do we want a while loop instead?

  while(rubyPresent) {
	take_picture();
	trackRuby(&rubyDetected, &rubyMoved, &attemptedTheft, &prevCenterRow, &prevCenterCol);
	if(attemptedTheft){
		changeStartDisplay(true);
	}
	else{
		time(&raw_time);
		rubyPresent = false;
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
  display_picture();
  sleep(1000);
  //close_screen_stream();
  return 0;

}