
/*
This Program will take values of daily temperatures as integers 
and will print out the number of hot, pleasant, and cold days. It will 
also print the average values of each range of temperatures and the total average
temperature.

Written By Alex Ludwig
CS108
10-24-2025
*/

# include <stdio.h>

/*Global Variables Declarations*/
int hot_days_ct = 0;
int total_hot_temp = 0;
int pleasant_days_ct = 0;
int total_pleasant_temp = 0;
int cold_days_ct = 0;
int total_cold_temp = 0;
int total_days_ct = 0;

/*Prototypes*/
void check_temp(int);


/*Main*/
int main (void){

/*Local Variable Decalarations*/
double hot_avg;
double pleasant_avg;
double cold_avg;
int total_temp;
double overall_avg;
int daily_temp;

/*User Input & Call to check_temp() for each temperature w/Sentinel 999*/
printf("\n\nPlease enter the daily high temperature or enter 999 to exit\n");
scanf("%d", &daily_temp);

while(daily_temp!=999){

	check_temp(daily_temp);
	printf("Please enter the daily high temperature or enter 999 to exit\n");
	scanf("%d", &daily_temp);
}

/*Initialize total_temp & all average variables*/
total_temp = (total_hot_temp+total_pleasant_temp+total_cold_temp);
total_days_ct = (hot_days_ct+pleasant_days_ct+cold_days_ct);
overall_avg = (total_temp/total_days_ct);

hot_avg = (total_hot_temp/hot_days_ct);
pleasant_avg = (total_pleasant_temp/pleasant_days_ct);
cold_avg = (total_cold_temp/cold_days_ct);

/*Final Output*/
printf("The total number of hot days (85+) is %d\n", hot_days_ct);
printf("The average temperature of hot days is %3.2f\n", hot_avg);

printf("The total number of pleasant days (60-84) is %d\n", pleasant_days_ct);
printf("The average temperature of pleasant days is %3.2f\n", pleasant_avg);

printf("The total number of cold days (<60) is %d\n", cold_days_ct);
printf("The average temperature of cold days is %3.2f\n", cold_avg);

printf("The overall average temperature for the entire set of temperatures is %3.2f\n", overall_avg);

return 0;
}

/*Checks to see if temp if hot, plesant, or cold
 and prints that category.Then increments its 
respective ct variable and adds to the respective total temp*/
void check_temp(int temp){

//Checks for hot temp
if(temp>=85){
	printf("%d is a hot day\n", temp);
	total_hot_temp+=temp;
	hot_days_ct++;
}
//Checks for cold temp
else if(temp<60){
	printf("%d is a cold day\n", temp);
	total_cold_temp+=temp;
	cold_days_ct++;
}
//Checks for pleasant temp
else{
	printf("%d is a pleasant day\n", temp);
	total_pleasant_temp+=temp;
	pleasant_days_ct++;
}

}



