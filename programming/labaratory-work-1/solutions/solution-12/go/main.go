package main

import "fmt"

func main() {
	var n int

	fmt.Scanf("%d", &n)

	var sum int

	for i := 1; i < n; i++ {
		if n % i == 0 {
			sum += i
		}
	}

	if sum == n {
		fmt.Printf("Yes")

		return
	}

	fmt.Printf("No")
}