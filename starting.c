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

//Function to count the number of red pixels present/determine whether or not ruby is present
bool detectRuby(){
	int totalRedPixels = 0;
	for(int row = 0; row < 480; row++){
		for(int col = 0; col < 640; col++){
			uchar r, g, b;
			get_pixel(row, col, &r, &g, &b);
			if((r >= 125 && r <= 255) && (g >= 0 && g <= 100) && (b >= 0 && b <= 100)){
				totalRedPixels++;
			}
		}
	}
	
	if(totalRedPixels > 0){
		return true;
	}
	return false;
}

void logTheft(const char *time_str){
	FILE *fptr = fopen("ruby_theft.log", "a");

	if(fptr == NULL){
		perror("Failed to open log file");
		return;
	}

	fprintf(fptr, "Time of theft: %s", time_str);
	
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
		drawHorizontalSegments(values_segments[digit][3], (row+size), col, (col+size));
		drawHorizontalSegments(values_segments[digit][6], (row+2*size), col, (col+size));

		drawVerticalSegments(values_segments[digit][1], row, (row+size), col);
		drawVerticalSegments(values_segments[digit][2], (row+size), (row+2*size), col);
		drawVerticalSegments(values_segments[digit][4], row, (row+size), (col+size));
		drawVerticalSegments(values_segments[digit][5], (row+size), (row+2*size), (col+size));

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

	bool rubyPresent = false;
	
	 if (start_camera() != 0) {
        printf("Failed to start camera\n");
        return 1;
    }

	time_t raw_time;
	struct tm *info;
   


	take_picture();
	

	display_picture();
	if(detectRuby()){
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
	
	if(detectRuby()){
		changeStartDisplay(true);
	}
	else{
		time(&raw_time);
		rubyPresent = false;
		info = localtime(&raw_time);
		int hours = info->tm_hour;
		int minutes = info->tm_min;
		int seconds = info->tm_sec;
		char time_str[6];
		char time_str_display[9];
		snprintf(time_str, sizeof(time_str), "%02d%02d%02d", hours, minutes, seconds);
		snprintf(time_str_display, sizeof(time_str_display), "%02d-%02d-%02d", hours, minutes, seconds);
		
		displayTime(time_str);
		logTheft(time_str_display);
		//exit(0);

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