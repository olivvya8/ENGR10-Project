#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

static const char *days[] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
static const char *months[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};

void logTheft(struct tm *current){
	FILE *fptr = fopen("ruby_theft.log", "a");

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

/* Unit tests for logTheft */
static int tests_passed = 0;
static int tests_failed = 0;

static void expect_contains(const char *content, const char *needle, const char *testname){
	if(strstr(content, needle) != NULL){
		tests_passed++;
		printf("%s: passed\n", testname);
	} else {
		tests_failed++;
		printf("%s: failed\n", testname);
	}
}

int main(void){
	/* Test 1: standard date/time */
	remove("ruby_theft.log");
	struct tm t1 = {0};
	t1.tm_hour = 13; t1.tm_min = 5; t1.tm_sec = 9;
	t1.tm_wday = 1; /* Monday */
	t1.tm_mday = 15; t1.tm_mon = 4; /* May */
	t1.tm_year = 2023 - 1900;
	logTheft(&t1);

	FILE *f = fopen("ruby_theft.log","r");
	if(!f){ perror("open"); return 1; }
	fseek(f,0,SEEK_END); long len = ftell(f); fseek(f,0,SEEK_SET);
	char *buf = malloc(len+1); fread(buf,1,len,f); buf[len]=0; fclose(f);

	expect_contains(buf, "Monday 15 May 2023", "Test 1 date line");
	expect_contains(buf, "13 hours - 05 minutes - 09 seconds", "Test 1 time line");
	free(buf);

	/* Test 2: midnight and Sunday */
	remove("ruby_theft.log");
	struct tm t2 = {0};
	t2.tm_hour = 0; t2.tm_min = 0; t2.tm_sec = 0;
	t2.tm_wday = 0; /* Sunday */
	t2.tm_mday = 1; t2.tm_mon = 0; /* January */
	t2.tm_year = 2000 - 1900;
	logTheft(&t2);

	f = fopen("ruby_theft.log","r"); if(!f){ perror("open"); return 1; }
	fseek(f,0,SEEK_END); len = ftell(f); fseek(f,0,SEEK_SET);
	buf = malloc(len+1); fread(buf,1,len,f); buf[len]=0; fclose(f);

	expect_contains(buf, "Sunday 1 January 2000", "Test 2 date line");
	expect_contains(buf, "00 hours - 00 minutes - 00 seconds", "Test 2 time line");
	free(buf);

	printf("\nSummary: %d passed, %d failed\n", tests_passed, tests_failed);
	return tests_failed == 0 ? 0 : 2;
}