#include "MissingData.h"
#include <sstream>

string monthInfo[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"}; // specify the 12 month in string array

int monthDayNums[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // specify the last day of month for 12 month 

string weekdays[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}; // specify the weekday for one week

string getNextMonth(string currMonth, int& v) // gets the next month by parameter of current month 
{
	int i = 0;// initilize with zero
	for( i = 0; i < 12; i++)  // iterates until twelve and compares the value with the current month
	{ 
		if(monthInfo[i] == currMonth)
			break; // breaks when the i value found for current month 
	}
	v = i;  // another parameter that bounds monthInfo and monthdayNums toghether(see later) , that gets the value of i(month position)
	if(i == 11)
	{
		return "Jan"; // this means if i= 11(which indicates that the month is December) returns January
	}
	else
	{
		return monthInfo[i + 1]; // if not it returns the next value in monthInfo string array
	}
}

string getNextWeekDay(string currWeekDay) // gets parameter as currentWeekDay
{
	int i = 0;// initilize with zero
	for(i = 0; i < 7; i++) // iterates through i from 0 to 7
	{
		if(weekdays[i] == currWeekDay) // if given parameter is equal to the weeks int array index i, it breaks and i is last value
			break;
	}
	if(i == 6) // if this i value that break is 6, this mean it is Sunday and it returns Monday then
	{
		return "Mon";
	}
	else // if not, it returns next array member at index i+1, which is next weekday
	{
		return weekdays[i + 1];
	}
}

int getMonthNum(string month) // gets the month number by input parameter of month string
{
	int i = 0;// initilize with zero
	for(i = 0; i < 12; i++)
	{
		if(monthInfo[i] == month) // when found
			return i + 1; // returns i+1 since array starts with index of 0
	}
	return 1; // why to return to 1 this man ??????????????????????????????????????????????????????????????????????????/
}

string fixDate(string beforeData)
{
	int day = 0; // initilize with zero
	string month;
	int year = 0;// initilize with zero
	string hour;
	string weekday;
	string other;
	string res;
	string nextHour;
	string nextMonth;
	int nextDay;
	int nextYear;
	string nextWeekday;
	
	stringstream ss(beforeData); // the beforeData is converted to stringstream (ss leaves the whitespace)
	ss>>weekday>>month>>day>>hour>>other>>year;  // extract the values of the beforedata and assign to date members by streamstream
	int currHour = atoi(hour.c_str()); //  get the current hour by converting from string to integer
	
	int flag = 0;// initilize with zero
	if(currHour == 23) // if current hour is 23 then next is 00:00
	{
		nextHour = "00:00:00";
		flag = 1;  // flag becomes one since weekday iterates further
	}
	else
	{ // next hour iteration
		if(currHour + 1 >= 10) // 09 becomes 9 after atoi function. if hour is less than 9, we need to substitue 0 before and concatenate with result
			nextHour = to_string(currHour + 1) + ":00:00";
		else
			nextHour = "0" + to_string(currHour + 1) + ":00:00";
	}
	int v = 0; // initilize with zero
	nextMonth = getNextMonth(month, v); // nextmonth is monthInfo[i+1] and v = i or january if month is december
	if(flag == 1) // if one day changes(23->00) and flag is one -> nextDay = day +1 (for example Thu Feb 01 -> Thu Feb 02) 
	{
		nextDay = day + 1; // 
		if(day == monthDayNums[v]) // if the day is equal to the last day of the month, next day becomes 1 
		{
			nextDay = 1;
		}
		else // else month will not iterate and remains the same
		{
			nextMonth = month; // the same month 
		}
	}
	else // if flag is not iterated and there is no day change (missing data within 0-23 hours range)
	{
		nextDay = day; // days remain the same
		nextMonth = month; // month remain the same as well 
	}
	if(nextMonth == "Jan" && month == "Dec") // if month iterates which means there is year change 
	{
		nextYear = year + 1;// next year which is in integer datatype will iterate by one 
	}
	else // if it is not the case, next year remains the same
	{
		nextYear = year;
	}

	if (flag == 1)
	{
		nextWeekday = getNextWeekDay(weekday); // one day change means iteration of weekday by one value which getNextWeekDay does (if Sun -> Mon)
	}
	else
	{
		nextWeekday = weekday; // if no day change, then remains the same 
	}

	string next_day = ""; // make empty string that takes value as a string of nextday integer value 
	if(nextDay < 10)
		next_day = "0" + to_string(nextDay); // the same thing as with hour 
	else next_day = to_string(nextDay); // if > 10, like 17 -> becomes -> 18
	res = nextWeekday + " " + nextMonth + " " + next_day + " " + nextHour + " BST " + to_string(nextYear); 
	return res; // returns the concatenated string above
}

int compareWithDate(string initTime, string startTime, string endTime) // 
{
	int day = 0; // initilize with zero
	string month;
	int year = 0; // initilize with zero
	string hour;
	string week;
	string other;

	stringstream ss(initTime); // converts the initial time to stringstream
	ss>>week>>month>>day>>hour>>other>>year; // extracts the value to the weekday, month,day of month, hour, UTC and year
	int month1 = getMonthNum(month); // gets the month index
	if(month1 >= 10) // if month is more than 10 
		month = to_string(month1); // new month is become number_as_string month index
	else
		month = "0" + to_string(month1); // the same if it is less than 10, number_as_string month index becomes 0 contatenated
	string dayStr; // day as string 
	if(day >= 10)
	{
		dayStr = to_string(day); // conversion of the int day to day_as_string
	}else
	{
		dayStr = "0" + to_string(day); // if less than then concatenate with 0 
	}
	string dateTime = to_string(year) + "/" + month + "/" + dayStr; // (YYYY/M/D) type string conversion of the initTime
	if(dateTime >= startTime && dateTime <= endTime) // then if this time ???????????????????????????????????????????????????????????????????
		return 1;
	return 0;
}


double getRandNum(double initNum, int range) // add variance 
{
	int randNum = rand() % 2; // gets whether one or two 
	if(randNum == 0) // if is equal to zero then go this way, if no go next way
		return initNum - rand()/double(RAND_MAX) * range; // initnumber is speed 
	else
		return initNum + rand()/double(RAND_MAX) * range;
}


string transDateFormat(string date) //"2010/08/01" to 20100801
{
	string year = date.substr(0, 4);
	string month = date.substr(5, 2);
	string day = date.substr(8);
	return year+month+day;
}