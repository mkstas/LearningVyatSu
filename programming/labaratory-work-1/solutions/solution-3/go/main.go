package main

import "fmt"

func main() {
	var n int

	fmt.Scanf("%d", &n)

	var a int = n % 10
	var b int = n / 10 % 10
	var max int = a
	var min int = a

	n /= 100

	if b > max && b > n {
		max = b
	}

	if n > max && n > b {
		max = n
	}

	if b < min {
		min = b
	}

	if n < min {
		min = n
	}

	if (max + min) / 2 < a + b + n - max - min {
		fmt.Printf("Yes")

		return
	}

	fmt.Printf("No")
}