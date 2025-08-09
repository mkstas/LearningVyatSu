package main

import "fmt"

func main() {
	var n int
	var m int
	var sum int = 0

	fmt.Scanf("%d", &n)
	fmt.Scanf("%d", &m)

	for i := 0; i < m; i++ {
		sum += n % 10
		n /= 10
	}

	fmt.Printf("%d", sum)
}