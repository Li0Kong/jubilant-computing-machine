#include <stdio.h>

// 判断某一年是否是闰年
int is_leap_year(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return 1;
    } else {
        return 0;
    }
}

// 获取某一年某一月的天数
int get_days_in_month(int year, int month) {
    switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        case 2:
            return is_leap_year(year) ? 29 : 28;
        default:
            return 31;
    }
}

// 获取某一年某一月第一天是星期几
int get_weekday(int year, int month) {
    int day = 1;
    int y = year;
    int m = month;
    if (m == 1 || m == 2) {
        m += 12;
        y--;
    }
    int c = y / 100;
    y = y % 100;
    int week = (y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + day - 1) % 7;
    if (week < 0) {
        week += 7;
    }
    return week;
}

// 打印日历
void print_calendar(int year) {
    printf("       Calendar %d\n", year);
    printf("=============================\n");
    printf("  Sun Mon Tue Wed Thu Fri Sat\n");

    int month, day, weekday;
    for (month = 1; month <= 12; month++) {
        printf("\n");
        // 打印月份名称
        printf("         %d月\n", month);
        
        int days_in_month = get_days_in_month(year, month);
        int weekday = get_weekday(year, month);

        // 打印每个月的第一行
        for (int i = 0; i < weekday; i++) {
            printf("    ");
        }
        for (day = 1; day <= days_in_month; day++) {
            printf("%4d", day);
            weekday++;
            if (weekday == 7) {
                printf("\n");
                weekday = 0;
            }
        }
        printf("\n");
    }
}

int main() {
    int year;

    printf("Enter year: ");
    scanf("%d", &year);

    print_calendar(year);

    return 0;
}
