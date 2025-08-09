package main

import "fmt"

func main() {
	var n int
	var m int

	fmt.Scanf("%d %d", &n, &m)

	var count int

	for i := n; i <= m; i++ {
		var a int = i % 10
		var b int = i / 10 % 10;
		var c int = i / 100 % 10;
		var d int = i / 1000 % 10;
		var e int = i / 10000 % 10;
		var f int = i / 100000 % 10;

		if a + b + c == d + e + f {
			count++;
		}
	}

	fmt.Printf("%d", count)
}