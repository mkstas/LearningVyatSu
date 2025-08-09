package main

import "fmt"

func main() {
	var n int
	var minN int
	var minI int

	for i := 1; n != 0 || i == 1; i++ {
		fmt.Scanf("%d", &n)

		if (n < minN || i == 1) && n != 0 {
			minN = n
			minI = i
		}
	}

	fmt.Printf("%d", minI)
}