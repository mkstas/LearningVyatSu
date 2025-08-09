package main

import "fmt"

func main() {
	var k1 float32
	var b1 float32
	var k2 float32
	var b2 float32
	var e float32

	fmt.Scanf("%f %f %f %f %f", &k1, &b1, &k2, &b2, &e);

	if (k1 == k2) {
		fmt.Printf("No")

		return
	}

	var x float32 = (b2 - b1) / (k1 - k2)
	var y float32 = k1 * x + b1

	if x * x + y * y <= e * e {
		fmt.Printf("Yes")

		return
	}

	fmt.Printf("No")
}