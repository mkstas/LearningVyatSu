package main

import "fmt"

func main() {
	var n int

	fmt.Scanf("%d", &n)

	var prevK int = 0
	var count int = 0
	var maxCount int = 0

	for i := 0; i < n; i++ {
		var k int

		fmt.Scanf("%d", &k)

		if k > prevK {
			count++
		}

		if k <= prevK {
			count = 1
		}

		if (count > maxCount) {
			maxCount = count
		}
	}

	fmt.Printf("%d", maxCount)
}