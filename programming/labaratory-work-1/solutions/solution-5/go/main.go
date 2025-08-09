package main

import "fmt"

func main() {
	var a int
	var b int
	var x int
	var y int
	var z int

	fmt.Scanf("%d %d %d %d %d", &a, &b, &x, &y, &z)

	if x * z <= a * b || y * z <= a * b || x * y <= a * b {
		fmt.Printf("Yes")

		return
	}

	fmt.Printf("No")
}