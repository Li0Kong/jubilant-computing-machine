package main

import (
	"fmt"
)

// 判断某一年是否是闰年
func isLeapYear(year int) bool {
	return (year%4 == 0 && year%100 != 0) || (year%400 == 0)
}

// 获取某一年某一月的天数
func getDaysInMonth(year, month int) int {
	switch month {
	case 4, 6, 9, 11:
		return 30
	case 2:
		if isLeapYear(year) {
			return 29
		} else {
			return 28
		}
	default:
		return 31
	}
}

// 获取某一年某一月第一天是星期几
func getWeekday(year, month int) int {
	day := 1
	y := year
	m := month
	if m == 1 || m == 2 {
		m += 12
		y--
	}
	c := y / 100
	y = y % 100
	return (y + y/4 + c/4 - 2*c + 26*(m+1)/10 + day - 1) % 7
}

// 打印日历
func printCalendar(year int) {
	fmt.Printf("       Calendar %d\n", year)
	fmt.Println("=============================")
	fmt.Println("  Sun Mon Tue Wed Thu Fri Sat")

	for month := 1; month <= 12; month++ {
		fmt.Println()
		fmt.Printf("         %d月\n", month)

		daysInMonth := getDaysInMonth(year, month)
		weekday := getWeekday(year, month)

		for i := 0; i < weekday; i++ {
			fmt.Print("    ")
		}
		for day := 1; day <= daysInMonth; day++ {
			fmt.Printf("%4d", day)
			weekday++
			if weekday == 7 {
				fmt.Println()
				weekday = 0
			}
		}
		fmt.Println()
	}
}

func main() {
	var year int

	fmt.Print("Enter year: ")
	_, err := fmt.Scanln(&year)
	if err != nil {
		fmt.Println("Invalid input. Please enter a valid year.")
		return
	}

	printCalendar(year)
}
