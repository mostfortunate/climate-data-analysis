#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define true 1
#define false 0
#define MAX_YEARS 3193
#define MAX_CHARACTERS 1000

struct date_data {
  float land_average_temperature;
  float land_average_temperature_uncertainty;
  float land_max_temperature;
  float land_max_temperature_uncertainty;
  float land_min_temperature;
  float land_min_temperature_uncertainty;
  float land_and_ocean_average_temperature;
  float land_and_ocean_average_temperature_uncertainty;
};

struct date_entry {
  char date[11];
  struct date_data data;
};

struct column_data {
  int dt;
  int land_average_temperature;
  int land_average_temperature_uncertainty;
  int land_max_temperature;
  int land_max_temperature_uncertainty;
  int land_min_temperature;
  int land_min_temperature_uncertainty;
  int land_and_ocean_average_temperature;
  int land_and_ocean_average_temperature_uncertainty;
};

// Q1
void getYearlyAverages(int *dates_index, struct date_entry dates[MAX_YEARS]) {
  FILE *out = fopen("YearlyLandAvgTemperatures.txt", "w");

  float sum = 0.0;
  float avg = 0.0;

  int lastYear = 1760;
  int count = 0;
  
  for (int i = 0; i < *dates_index; i++) {
    int currentYear = atoi(dates[i].date);

    if (currentYear < 1760) {
      continue;
    }
	
    if (lastYear != currentYear) {
      avg = sum / count;
      
      fprintf(out, "%d %f\n", lastYear, avg);
      printf("%d %.1f\n", lastYear, avg);
      
      lastYear = currentYear;
      sum = 0.0;
      avg = 0.0;
      count = 0; 
    }
    sum += dates[i].data.land_average_temperature;   
    count++;  
  }

   avg = sum / count;
   fprintf(out, "%d %f\n", lastYear, avg);
   printf("%d %.1f\n", lastYear, avg);

  fclose(out);
}

// Q2
void getCenturyAverages(int *dates_index, struct date_entry dates[MAX_YEARS]) {			
	FILE *out = fopen("CenturyLandAvgTemperatures.txt", "w");
	
	float firstCenturySum = 0.0;
	float secondCenturySum = 0.0;
	float thirdCenturySum = 0.0;
	float fourthCenturySum = 0.0;		
	
	float firstCenturyAvg = 0.0;
	float secondCenturyAvg = 0.0;
	float thirdCenturyAvg = 0.0;
	float fourthCenturyAvg = 0.0;
	
	// Getting the temperature sums
	for (int i = 0; i < *dates_index; i++) {
		int currentYear = atoi(dates[i].date);
		if (currentYear < 1760) {
			continue;
		}
		
		if (currentYear >= 1760 && currentYear <= 1799) { // 1st century		
			firstCenturySum += dates[i].data.land_average_temperature;
		} else if (currentYear >= 1800 && currentYear <= 1899) { // 2nd century
			secondCenturySum += dates[i].data.land_average_temperature;
		} else if (currentYear >= 1900 && currentYear <= 1999) { // 3rd century
			thirdCenturySum += dates[i].data.land_average_temperature;
		} else if (currentYear >= 2000 && currentYear <= 2015) { // 4th century
			fourthCenturySum += dates[i].data.land_average_temperature;
		}
	}
	
	firstCenturyAvg = firstCenturySum / ((1799-1760+1)*12);
	secondCenturyAvg = secondCenturySum / ((1899-1800+1)*12);
	thirdCenturyAvg = thirdCenturySum / ((1999-1900+1)*12);
	fourthCenturyAvg = fourthCenturySum / ((2015-2000+1)*12);
	
	fprintf(out, "%d %f\n", 1700, firstCenturyAvg);
	printf("\nThe land average for the 18th century (1760-1799) is: %.1f", firstCenturyAvg);
	
	fprintf(out, "%d %f\n", 1800, secondCenturyAvg);
	printf("\nThe land average for the 19th century (1800-1899) is: %.1f", secondCenturyAvg);
	
	fprintf(out, "%d %f\n", 1900, thirdCenturyAvg);
	printf("\nThe land average for the 20th century (1900-1999) is: %.1f", thirdCenturyAvg);
	
	fprintf(out, "%d %f\n", 2000, fourthCenturyAvg);
	printf("\nThe land average for the 21th century (2000-2015) is: %.1f\n", fourthCenturyAvg);
	
	fclose(out);
}

// Q3
void getMonthlyAvgs(int *dates_index, struct date_entry dates[MAX_YEARS]) {
  FILE *out = fopen("MonthlyAvgs.txt", "w");
  float avgs[12] = {};
  int totalYears = (2015 - 1900) + 1;
  
  // Loop twelve times as we need 12 months
  for (int i = 0; i < 12; i++) {
	  float sum = 0.0;
	  
	  for (int j = 0; j < *dates_index; j++) {
		  char copied_date[11] = {};
		  strcpy(copied_date, dates[j].date);
		  	
		  char *token_year = strtok(copied_date, "-");
          char *token_month = strtok(NULL, "-");
          
		  if (atoi(token_year) < 1900) {
			 continue;
		  }
		  
		  int month = atoi(token_month);		  
		  if (month != i+1) {
			  continue;
		  }
		  
		  sum += dates[j].data.land_average_temperature;
	  }
	  
	 avgs[i] = sum / totalYears;
  }
  
  fprintf(out, "%s %f\n", "January", avgs[0]);
  printf("\n%s %.1f\n", "January", avgs[0]);
  
  fprintf(out, "%s %f\n", "February", avgs[1]);
  printf("%s %.1f\n", "February", avgs[1]);
  
  fprintf(out, "%s %f\n", "March", avgs[2]);
  printf("%s %.1f\n", "March", avgs[2]);
  
  fprintf(out, "%s %f\n", "April", avgs[3]);
  printf("%s %.1f\n", "April", avgs[3]);
  
  fprintf(out, "%s %f\n", "May", avgs[4]);
  printf("%s %.1f\n", "May", avgs[4]);
  
  fprintf(out, "%s %f\n", "June", avgs[5]);
  printf("%s %.1f\n", "June", avgs[5]);
  
  fprintf(out, "%s %f\n", "July", avgs[6]);
  printf("%s %.1f\n", "July", avgs[6]);
  
  fprintf(out, "%s %f\n", "August", avgs[7]);
  printf("%s %.1f\n", "August", avgs[7]);
  
  fprintf(out, "%s %f\n", "September", avgs[8]);
  printf("%s %.1f\n", "September", avgs[8]);
  
  fprintf(out, "%s %f\n", "October", avgs[9]);
  printf("%s %.1f\n", "October", avgs[9]);
  
  fprintf(out, "%s %f\n", "November", avgs[10]);
  printf("%s %.1f\n", "November", avgs[10]);
  
  fprintf(out, "%s %f\n", "December", avgs[11]);
  printf("%s %.1f\n", "December", avgs[11]);
  
  fclose(out);
}

// Q4
void getExtremeTempsByMonth(int *dates_index, struct date_entry dates[MAX_YEARS]) {
  int coldestYear = 0;
  int hottestYear = 0;
  
  int coldestMonth = 0;
  int hottestMonth = 0;
  
  int currentYear = 0;
  int currentMonth = 0;
  
  float coldestValue = 100;
  float hottestValue = 0.0;
  float currentValue = 0.0;
  
  for (int i = 0; i < *dates_index; i++) {	
	 char copied_date[11] = {};
	 strcpy(copied_date, dates[i].date);
		  	
	 char *token_year = strtok(copied_date, "-");
     char *token_month = strtok(NULL, "-");
     
     currentYear = atoi(token_year);
     currentMonth = atoi(token_month);     
     currentValue = dates[i].data.land_average_temperature;
     
     if (currentValue > hottestValue) {
		 hottestYear = currentYear;
		 hottestMonth = currentMonth;
		 hottestValue = currentValue;	 
	 } else if (currentValue < coldestValue) {
		coldestYear = currentYear;
		coldestMonth = currentMonth;
		coldestValue = currentValue;
	 }
  }

  printf("\nThe coldest temperature is %.1f, which occurred on %d-%d-1.\nThe hottest temperature is %.1f, which occurred on %d-%d-1.\n", coldestValue, coldestYear, coldestMonth, hottestValue, hottestYear, hottestMonth);
}

// Q5
void getExtremeTempsByYear() {
  FILE *in = fopen("YearlyLandAvgTemperatures.txt", "r");
  
  double currentTemperature = 0.0;
  double coldestValue = 100.0;
  double hottestValue = 0.0;
  
  int currentYear = 0;
  int coldestYear = 0;
  int hottestYear = 0;
  
  while (fscanf(in, "%d %lf", &currentYear, &currentTemperature) >= 1) {      
        if (currentTemperature > hottestValue) {
			hottestValue = currentTemperature;
			hottestYear = currentYear;
		} else if (currentTemperature < coldestValue) {
			coldestValue = currentTemperature;
			coldestYear = currentYear;
		}
    }
  
  printf("\nThe coldest year was %d.\nThe hottest year was %d.", coldestYear, hottestYear);
  fclose(in);
}

// Q8
void getData(int *dates_index, struct date_entry dates[MAX_YEARS]) {		
	FILE *temps = fopen("LandAverageTemperatures.txt", "w");
	FILE *maxTemps = fopen("LandMaxTemperatures.txt", "w");
	FILE *minTemps = fopen("LandMinTemperatures.txt", "w");
	FILE *avgLandUncert = fopen("LandAverageTemperaturesUncertainty.txt", "w");
	FILE *landAndOcean = fopen("LandAndOceanAverageTemperatures.txt", "w");
	
	for (int i = 0; i < *dates_index; i++) {
		int year = atoi(dates[i].date);
		
		fprintf(temps, "%s %f\n", dates[i].date, dates[i].data.land_average_temperature);
		fprintf(maxTemps, "%s %f\n", dates[i].date, dates[i].data.land_max_temperature);
		fprintf(minTemps, "%s %f\n", dates[i].date, dates[i].data.land_min_temperature);
		fprintf(avgLandUncert, "%d %f\n", year, dates[i].data.land_average_temperature_uncertainty);
		fprintf(landAndOcean, "%d %f\n", year, dates[i].data.land_and_ocean_average_temperature);
	}
	
	fclose(temps);
	fclose(maxTemps);
	fclose(minTemps);
	fclose(avgLandUncert);
	fclose(landAndOcean);
}

int main(int argc, char ** argv) {
  FILE *csv_data = fopen("GlobalTemperatures.csv", "r");

  int dates_index = 0;
  int column_index = 0;

  struct column_data columns = {};
  struct date_entry dates[MAX_YEARS] = {};

  char *token = NULL;
  char current_line[MAX_CHARACTERS] = {};

  // Read the first line to get the column names
  if (fgets(current_line, MAX_CHARACTERS, csv_data) == NULL) {
    fprintf(stderr, "Error reading CSV file\n");
    return 0;
  }

  // Get the column indices
  token = strtok(current_line, ",");
  column_index = 0;

  while (token != NULL) {
    if (strcmp(token, "dt") == 0) {
      columns.dt = column_index;
    } else if (strcmp(token, "LandAverageTemperature") == 0) {
      columns.land_average_temperature = column_index;
    } else if (strcmp(token, "LandAverageTemperatureUncertainty") == 0) {
      columns.land_average_temperature_uncertainty = column_index;
    } else if (strcmp(token, "LandMaxTemperature") == 0) {
      columns.land_max_temperature = column_index;
    } else if (strcmp(token, "LandMaxTemperatureUncertainty") == 0) {
      columns.land_max_temperature_uncertainty = column_index;
    } else if (strcmp(token, "LandMinTemperature") == 0) {
      columns.land_min_temperature = column_index;
    } else if (strcmp(token, "LandMinTemperatureUncertainty") == 0) {
      columns.land_min_temperature_uncertainty = column_index;
    } else if (strcmp(token, "LandAndOceanAverageTemperature") == 0) {
		columns.land_and_ocean_average_temperature = column_index;
	} else if (strcmp(token, "LandAndOceanAverageTemperatureUncertainty") == 0) {
		columns.land_and_ocean_average_temperature_uncertainty = column_index;
	}
	
    token = strtok(NULL, ",");
    column_index++;
  }
  
  // Read the rest of the lines
  while (fgets(current_line, MAX_CHARACTERS, csv_data) != NULL) {
    column_index = 0;

    // Gets rid of the newline added by fgets, otherwise this will cause bound related bugs
    current_line[strcspn(current_line, "\n")] = '\0';
    token = strtok(current_line, ",");

    // Parse each field
    while (token != NULL) {	  
      if (column_index == columns.dt) {
        strcpy(dates[dates_index].date, token);
      } else if (column_index == columns.land_average_temperature) {
        dates[dates_index].data.land_average_temperature = atof(token);
      } else if (column_index == columns.land_average_temperature_uncertainty) {
		  dates[dates_index].data.land_average_temperature_uncertainty = atof(token);
	  } else if (column_index == columns.land_max_temperature) {		  
		  dates[dates_index].data.land_max_temperature = atof(token);
	  } else if (column_index == columns.land_max_temperature_uncertainty) {
		  dates[dates_index].data.land_max_temperature_uncertainty = atof(token);
	  } else if (column_index == columns.land_min_temperature) {
		  dates[dates_index].data.land_min_temperature = atof(token);
	  } else if (column_index == columns.land_min_temperature_uncertainty) {
		  dates[dates_index].data.land_min_temperature_uncertainty = atof(token);
	  } else if (column_index == columns.land_and_ocean_average_temperature) {
		  dates[dates_index].data.land_and_ocean_average_temperature = atof(token);
	  } else if (column_index == columns.land_and_ocean_average_temperature_uncertainty) {
		  dates[dates_index].data.land_and_ocean_average_temperature_uncertainty = atof(token);
	  }

      token = strtok(NULL, ",");
      column_index++;

    }

    dates_index++;
  }
  
  getData(&dates_index, dates);
  getYearlyAverages(&dates_index, dates);
  getCenturyAverages(&dates_index, dates);
  getMonthlyAvgs(&dates_index, dates);
  getExtremeTempsByMonth(&dates_index, dates);
  getExtremeTempsByYear();  
  
  fclose(csv_data);
  return 0;
}
