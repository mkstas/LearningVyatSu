package main

import "fmt"

func main() {
	var n int

	fmt.Scanf("%d", &n)

	var count int
	var prevK int

	for i := 0; i < n; i++ {
		var k int

		fmt.Scanf("%d", &k)

		if k > 0 && prevK < 0 || k < 0 && prevK > 0 {
			count++
		}

		prevK = k
	}

	fmt.Printf("%d", count)
}