#pragma once
#include <ctime>
#include <string>

using std::string;

int calendar[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Time;
class Clock;

class Time {
protected:
	int year = 2000, month = 1, day = 1;
	int hour = 0, minute = 0, second = 0;

	virtual void spend(int seconds) {
		second += seconds % 60;
		if (second >= 60) {
			second -= 60;
			minute++;
		}
		minute += (seconds % 3600) / 60;
		if (minute >= 60) {
			minute -= 60;
			hour++;
		}
		hour += (seconds % 86400) / 3600;
		if (hour >= 24) {
			hour -= 24;
			day++;
		}
		day += seconds / 86400;
		while (day > calendar[month]) {
			day -= calendar[month];
			month++;
			if (month > 12) {
				month = 1;
				year++;
			}
		}

	}

public:
	Time() {}
	Time(int period) {
		year = 0;
		spend(period);
	}

	Time operator+(int period) {
		Time ret(*this);
		ret.spend(period);
		return ret;
	}
	int operator-(Time &time) {
		tm info1 = { 0 };
		info1.tm_year = year - 1900;
		info1.tm_mon = month - 1;
		info1.tm_mday = day;
		info1.tm_hour = hour;
		info1.tm_min = minute;
		info1.tm_sec = second;
		int time1 = mktime(&info1);
		tm info2 = { 0 };
		info2.tm_year = time.year - 1900;
		info2.tm_mon = time.month - 1;
		info2.tm_mday = time.day;
		info2.tm_hour = time.hour;
		info2.tm_min = time.minute;
		info2.tm_sec = time.second;
		int time2 = mktime(&info2);
		return time1 - time2;
	}
	bool operator<(const Time &time) {
		if (year != time.year)return year < time.year;
		if (month != time.month)return month < time.month;
		if (day != time.day)return day < time.day;
		if (hour != time.hour)return hour < time.hour;
		if (minute != time.minute)return minute < time.minute;
		if (second != time.second)return second < time.second;
		return false;
	}
	bool operator>(const Time &time) {
		if (year != time.year)return year > time.year;
		if (month != time.month)return month > time.month;
		if (day != time.day)return day > time.day;
		if (hour != time.hour)return hour > time.hour;
		if (minute != time.minute)return minute >time.minute;
		if (second != time.second)return second > time.second;
		return false;
	}

	string toString(bool enter = true) {
		string ret = string();
		int start = 0;
		if (month- 1 > 0 || start) {
			start++;
			ret += std::to_string(month - 1) + "月";
		}
		if (day - 1 > 0 || start) {
			start++;
			ret += std::to_string(day - 1) + "日";
		}
		if (hour > 0 || start) {
			start++;
			ret += std::to_string(hour) + "时";
		}
		if (enter && start)ret += "\n";
		if (minute > 0 || start) {
			start++;
			ret += std::to_string(minute) + "分";
		}
		if (second > 0 || start) {
			start++;
			ret += std::to_string(second) + "秒";
		}
		return ret;
	}
};
class Clock : public Time {
private:
	clock_t past = 0, previous = clock();

	virtual void spend(int seconds) {
		overnight = false;
		second += seconds % 60;
		if (second >= 60) {
			second -= 60;
			minute++;
		}
		minute += (seconds % 3600) / 60;
		if (minute >= 60) {
			minute -= 60;
			hour++;
		}
		hour += (seconds % 86400) / 3600;
		if (hour >= 24) {
			hour -= 24;
			day++;
			overnight = true;
		}
		day += seconds / 86400;
		while (day > calendar[month]) {
			day -= calendar[month];
			month++;
			if (month > 12) {
				month = 1;
				year++;
			}
		}

	}

public:
	int overnight = false;

	Clock() {
		previous = clock();
	}
	Clock(int past) {
		spend(past);
		this->past = past;
		previous = clock();
	}

	void pass(int rate) {
		clock_t current = clock();
		spend((current - previous) * 60 * rate / 1000);
		past += (current - previous) * 60 * rate / 1000;
		previous = current;
	}
	void getDate(char *buffer) {
		sprintf(buffer, "%d年%02d月%02d日", year, month, day);
	}
	void getTime(char *buffer) {
		sprintf(buffer, "%02d:%02d:%02d", hour, minute, second);
	}
	int getPast() { return past; }
};
