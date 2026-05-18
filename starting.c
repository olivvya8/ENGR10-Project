// /*
//  * The code below is meant to detect whether the Red Ruby
//  * is present. The starategy implemented by the code is not very effective. 
//  * Study the code so that you understand what the strategy is and how 
//  * it is implemented. Then design and implement a better startegy.
//  * 
//  * */



// #include <stdio.h>
// #include "camera_x11.h"
// #include <time.h>

// //using namespace std;

// const int values_segments[10][7] = {
//     {1, 1, 1, 1, 1, 1, 0},
//     {0, 1, 1, 0, 0, 0, 0},
//     {1, 1, 0, 1, 1, 0, 1},
// 	{1, 1, 1, 1, 0, 0, 1},
// 	{0, 1, 1, 0, 0, 1, 1},
// 	{1, 0, 1, 1, 0, 1, 1},
// 	{1, 0, 1, 1, 1, 1, 1},
// 	{1, 1, 1, 0, 0, 0, 0};
// 	{1, 1, 1, 1, 1, 1, 1},
// 	{1, 1, 1, 1, 0, 1, 1}
// };

// //Function to count the number of red pixels present/determine whether or not ruby is present
// boolean detectRuby(){
// 	int totalRedPixels = 0;
// 	for(int row = 0; row < 480; row++){
// 		for(int col = 0; col < 640; col++){
// 			uchar r, g, b;
// 			get_pixel(row, col, &r, &g, &b);
// 			if((r >= 125 && r <= 255) && (g >= 0 && g <= 100) && (b >= 0 && b <= 100)){
// 				totalRedPixels++;
// 			}
// 		}
// 	}
	
// 	if(totalRedPixels > 0){
// 		return true;
// 	}
// 	return false;
// }

// void logTheft(const char *time_str){
// 	FILE *fptr = fopen("ruby_theft.log", "a");

// 	if(fptr == NULL){
// 		perror("Failed to open log file");
// 		return;
// 	}

// 	fprintf(fptr, "Time of theft: %s", time_str);
	
// 	fclose(fptr);

// }

// void displayTime(str time_str){
// 	int size = 20;
// 	int startRow = 40;
// 	int startCol = 40;
// 	int spacing = 5;
// 	int row = startRow;
// 	int col = startCol;
// 	for(int i = 0; i < strlen(time_str); i++){
// 		int digit = time_str[i] - '0';
// 		drawHorizontalSegments(values_segments[digit][0], row, col, (col+size));
// 		drawHorizontalSegments(values_segments[digit][3], (row+2*size), col, (col+size));
// 		drawHorizontalSegments(values_segments[digit][6], (row+size), col, (col+size));

// 		drawVerticalSegments(values_segments[digit][1], row, (row+size), col);
// 		drawVerticalSegments(values_segments[digit][2], (row+size), (row+2*size), col);
// 		drawVerticalSegments(values_segments[digit][4], row, (row+size), (col+size));
// 		drawVerticalSegments(values_segments[digit][5], (row+size), (row+2*size), (col+size));

// 		col = col + size + spacing;

// 		if(i == 1 || i == 3){
// 			drawHorizontalSegment(1, (row+size), col, (col+size));
// 			col = col + size + spacing;
// 		}




		
// 	}
	
// 	display_picture();
// }

// void drawHorizontalSegments(int segment, int row, int startColumn, int endColumn){
// 	if(segment == 1){
// 		for(int i = startColumn; i < endColumn; i++){
// 			set_pixel(row, i, 255, 0, 0);
// 		}
// 	}
// }

// void drawVerticalSegments(int segment, int startRow, int endRow, int col){
// 	if(segment == 1){
// 		for(int i = startRow; i < endRow; i++){
// 			set_pixel(i, col, 255, 0, 0);
// 		}
// 	}

// }


// void changeStartDisplay(boolean present){
// 	if(present){
// 		for(int row = 0; row < 30; row ++){
// 			for(int col = 0; col < 50; col ++){
// 				set_pixel(row, col, 0, 255, 0);
// 			}
// 		}
// 	}
// 	else{
// 		for(int r = 0; r < 480; r ++){
// 			for(int c = 0; c < 640; c ++){
// 				set_pixel(row, col, 255, 0, 0);
// 			}
// 		}
// 	}
// 	display_picture();
// }



// int main() {

// 	boolean rubyPresent = false;
	
// 	 if (start_camera() != 0) {
//         printf("Failed to start camera\n");
//         return 1;
//     }

// 	time_t raw_time;
// 	struct tm *info;
   


// 	take_picture();
	

// 	display_picture();
// 	if(detectRuby()){
// 		changeStartDisplay(true);
// 		rubyPresent = true;
// 	}
// 	else{
// 		changeStartDisplay(false); //turn screen red
// 		exit(0); //ruby not present at start, terminate
// 	}

// // make 1000 runs/program continues to run if ruby is present  //do we want a while loop instead?
//   for (int countrun = 0; countrun < 10000; countrun++) {
// 	take_picture();
	
// 	if(detectRuby()){
// 		changeStartDisplay(true);
// 	}
// 	else{
// 		time(&raw_time);
// 		rubyPresent = false;
// 		info = localtime(&raw_time);
// 		int hours = info->tm_hour;
// 		int minutes = info->tm_min;
// 		int seconds = info->tm_sec;
// 		char time_str[9];
// 		snprintf(time_str, sizeof(time_str), "%02d%02d%02d", hours, minutes, seconds);
// 		snprintf(time_str_dislay, sizeof(time_str), "%02d-%02d-%02d", hours, minutes, seconds);
// 		displayTime(time_str);
// 		logTheft(time_str_display);
// 		exit(0);

// 	}

	
	

// 	// //perform initial check and output accordingly (core)

// 	// int totRed = 0;
// 	// int totInt = 0;
// 	// double redness = 0.0;
//     // // for all pixels in latest image
//     // for (int row = 0 ; row < 480 ; row++) {	
// 	// 	for (int col = 0; col < 640; col++) {
// 	// 		uchar r, g ,b ;
// 	// 		get_pixel(row, col, &r, &g ,&b);
// 	// 		totRed = totRed + r;
// 	// 		totInt = totInt + (r+g+b)/3;
// 	// 		redness = (double)totRed/(3.0*(double)totInt);
// 	// 	}
// 	// }

// 	// printf(" countrun: %d\n",countrun);
// 	// printf(" Total red:%d\n",totRed);
// 	// printf(" Total intensity: %d\n",totInt);
// 	// printf("  redness : %f\n", redness);
// 	//sleep1(1000); // slow down a bit to make display easier
	
//   }  
//   //close_screen_stream();
//   return 0;

// }


// /*
//  * The code below is meant to detect whether the Red Ruby
//  * is present. The starategy implemented by the code is not very effective. 
//  * Study the code so that you understand what the strategy is and how 
//  * it is implemented. Then design and implement a better startegy.
//  * 
//  * */



// #include <stdio.h>
// #include "camera_x11.h"

// //using namespace std;

// int main() {
	
// 	 if (start_camera() != 0) {
//         printf("Failed to start camera\n");
//         return 1;
//     }
   
//   // make 1000 runs  
//   for (int countrun = 0; countrun < 10000; countrun++) {
// 	take_picture();
// 	display_picture();
// 	// int totRed = 0;
// 	// int totInt = 0;
// 	// double redness = 0.0;
//     // // for all pixels in latest image
//     // for (int row = 0 ; row < 480 ; row++) {	
// 	// 	for (int col = 0; col < 640; col++) {
// 	// 		uchar r, g ,b ;
// 	// 		get_pixel(row, col, &r, &g ,&b);
// 	// 		totRed = totRed + r;
// 	// 		totInt = totInt + (r+g+b)/3;
// 	// 		redness = (double)totRed/(3.0*(double)totInt);
// 	// 	}
// 	// }

// 	int totalRedPixels = 0;

// 	for(int row = 0; row < 480; row++){
// 		for(int col = 0; col < 640; col++){
// 			uchar r, g, b;
// 			get_pixel(row, col, &r, &g, &b);
// 			if((r >= 128 && r <= 255) && (g >= 0 && g <= 100) && (b >= 0 && b <= 100)){
// 				totalRedPixels ++;
// 			}

// 		}
// 	}

// 	// printf(" countrun: %d\n",countrun);
// 	// printf(" Total red:%d\n",totRed);
// 	// printf(" Total intensity: %d\n",totInt);
// 	// printf("  redness : %f\n", redness);
// 	printf("Number of red: %d\n", totalRedPixels);
// 	//sleep1(1000); // slow down a bit to make display easier
	
//   }  
//   //close_screen_stream();
//   return 0;
// }





/*
 * The code below is meant to detect whether the Red Ruby
 * is present. The starategy implemented by the code is not very effective. 
 * Study the code so that you understand what the strategy is and how 
 * it is implemented. Then design and implement a better startegy.
 * 
 * */



#include <stdio.h>
#include "camera_x11.h"
#include <time.h>
#include <stdbool.h>

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

//Function to count the number of red pixels present/determine whether or not ruby is present
// int detectRuby(){
// 	int totalRedPixels = 0;
// 	*totalRow = 0;
//     *totalCol = 0;
//     *totalBrightness = 0;

// 	for(int row = 0; row < 480; row++){
// 		for(int col = 0; col < 640; col++){
// 			uchar r, g, b;
// 			get_pixel(row, col, &r, &g, &b);
// 			if((r >= 125 && r <= 255) && (g >= 0 && g <= 100) && (b >= 0 && b <= 100) && (r - g) > 40 && (r - b) > 40){ //&& (r - g) > 40 && (r - b) > 40
// 				totalRedPixels++;
// 				*totalRow += row;
//                 *totalCol += col;

//                 // brightness measure (lighting tracker)
//                 *totalBrightness += (r + g + b) / 3;
// 			}
// 		}
// 	}

// 	*prevCenterRow = centerRow;
//     *prevCenterCol = centerCol;
//     *prevBrightness = avgBrightness;

// 	return totalRedPixels;
// }


// bool detectMovement(bool *rubyDetected, int redCount, long *totalRow, long *totalCol, int *prevCenterRow, int *prevCenterCol) {
	
  
  	//int redCount = detectRuby();

// 	//printf("Red Count: %d\n", redCount);
	
// 	if (redCount > 2000) {
// 		*rubyDetected = true;
// 		// ----------- Find centre -----------
// 		int centerRow = *totalRow / redCount;
//     	int centerCol = *totalCol / redCount;
		

// 		if (prevCenterRow != -1) {
// 			int xChange = centerRow - *prevCenterRow;
// 			int yChange = centerCol - *prevCenterCol;

// 			// Find change in center pos
// 			long disp = xChange * xChange + yChange * yChange;

// 			//printf("Displacement: %ld\n", disp);
// 			if (disp > 10) {
// 				printf("Ruby moved\n");
// 			} else {
// 				printf("Ruby still there\n");
// 			}
// 		}

// 		// Update prev row and col
// 		*prevCenterRow = centerRow;
// 		*prevCenterCol = centerCol;
// 	} else {
// 		*rubyDetected = false;
// 		printf("No ruby detected\n");
// 	}

// 	return 0;
// }

void trackRuby(bool *rubyDetected, int *prevCenterRow, int *prevCenterCol, long *prevBrightness)
{
    static int motionCount = 0;

    int redCount = 0;

    long totalRow = 0;
    long totalCol = 0;
    long totalBrightness = 0;

	bool start = true;

    
    for (int row = 0; row < 480; row++) {

        for (int col = 0; col < 640; col++) {

            uchar r, g, b;

            get_pixel(row, col, &r, &g, &b);

            // Detect red pixels
            if (r > 125 &&
                (r - g) > 40 &&
                (r - b) > 40)
            {
                redCount++;

                totalRow += row;
                totalCol += col;

                totalBrightness += (r + g + b) / 3;
            }
        }
    }

    // -------- Ruby detection --------
    if (redCount > 2000) {

        *rubyDetected = true;

        // -------- Find center --------
        int centerRow = totalRow / redCount;
        int centerCol = totalCol / redCount;

        // -------- Average brightness --------
        long avgBrightness = totalBrightness / redCount;

       
        // -------- Motion detection --------
        if (*prevCenterRow != -1) {

			start = false;
            int dx = centerRow - *prevCenterRow;
            int dy = centerCol - *prevCenterCol;

            long disp = dx*dx + dy*dy;

            long brightnessChange = labs(avgBrightness - *prevBrightness);

            // // Motion persistence
            // if (disp > 9) {
            //     motionCount++;
            // }
            // else {
            //     motionCount = 0;
            // }

            // -------- Classification --------
            // if (motionCount >= 3) {

            //     if (brightnessChange < 30) {
            //         printf("Ruby moving\n");
			// 		*rubyDetected = true;
            //     }
            //     else {
            //         printf("Ruby moving with lighting change\n");
			// 		*rubyDetected = true;
            //     }

            // }
            // else {

            //     if (brightnessChange < 30) {
            //         printf("Ruby still\n");
            //     }
            //     else {
            //         printf("Ruby still, lighting changed\n");
            //     }
            // }

			if(disp > 9){
				if(disp <= 16 && brightnessChange > 30){
					*rubyDetected = true; //center changes due to change in lighting but ruby is probably still
				}
				else{
					*rubyDetected = false; //brightness is similar so ruby has probably moved
				}
			}
			else{
				*rubyDetected = true; //ruby is still/center has hardly changed
			}
        }


        
        *prevCenterRow = centerRow;
        *prevCenterCol = centerCol;
        *prevBrightness = avgBrightness;
    }

    else {

        *rubyDetected = false;

        //motionCount = 0;

        printf("No ruby detected\n");
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
	int prevCenterRow = -1;
	int prevCenterCol = -1;
	long prevBrightness = 0;
	
	
	 if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }

	time_t raw_time;
	struct tm *info;
   


	take_picture();
	

	display_picture();
	trackRuby(&rubyDetected, &prevCenterRow, &prevCenterCol, &prevBrightness);
	if(rubyDetected){
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
	trackRuby(&rubyDetected, &prevCenterRow, &prevCenterCol, &prevBrightness);
	if(rubyDetected){
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

	//display_picture();

	
	

	// //perform initial check and output accordingly (core)

	// int totRed = 0;
	// int totInt = 0;
	// double redness = 0.0;
    // // for all pixels in latest image
    // for (int row = 0 ; row < 480 ; row++) {	
	// 	for (int col = 0; col < 640; col++) {
	// 		uchar r, g ,b ;
	// 		get_pixel(row, col, &r, &g ,&b);
	// 		totRed = totRed + r;
	// 		totInt = totInt + (r+g+b)/3;
	// 		redness = (double)totRed/(3.0*(double)totInt);
	// 	}
	// }

	// printf(" countrun: %d\n",countrun);
	// printf(" Total red:%d\n",totRed);
	// printf(" Total intensity: %d\n",totInt);
	// printf("  redness : %f\n", redness);
	//sleep1(1000); // slow down a bit to make display easier
	
  }  
  display_picture();
  sleep(1000);
  //close_screen_stream();
  return 0;

}