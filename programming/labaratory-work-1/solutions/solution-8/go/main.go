package main

import "fmt"

func main() {
	var n int

	fmt.Scanf("%d", &n)

	var eng int
	var ger int
	var fra int

	for i := n; i > 0; i-- {
		var ans int

		fmt.Scanf("%d", &ans)

		switch ans {
		case 1:
			eng++
		case 2:
			ger++
		case 3:
			fra++
		}
	}

	fmt.Printf("%d %d %d", eng, ger, fra)
}