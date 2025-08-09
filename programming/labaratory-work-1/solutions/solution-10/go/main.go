package main

import "fmt"

func main() {
	var m int

	fmt.Scanf("%d", &m)

	var goodGroup int
	var nSkip int
	var avgSkip float32

	for i := 0; i < m; i++ {
		var k int
		var sumSkip int

		fmt.Scanf("%d", &k)

		for j := 0; j < k; j++ {
			fmt.Scanf("%d", &nSkip)

			sumSkip += nSkip
		}

		avgSkip = float32(sumSkip) / float32(k)

		if avgSkip < 10 && goodGroup == 0 {
			goodGroup = i
		}
	}

	if goodGroup != 0 {
		fmt.Printf("The good group %d", goodGroup)

		return
	}

	fmt.Printf("No")
}