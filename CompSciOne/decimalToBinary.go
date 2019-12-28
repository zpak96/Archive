/* Zane Paksi
* This program converts any decimal to binary by utilizing a stack.
*/

package main

import (
	"fmt"

	"github.com/golang-collections/collections/stack"
)

func main() {
	var input int
	var mod int
	fmt.Printf("Decimal to Binary :: ")
	fmt.Scanln(&input)
	n := stack.New()

	for input != 0 {
		mod = input % 2
		n.Push(mod)
		input /= 2
	}

	for n.Len() != 0 {
		val := n.Pop()
		fmt.Print(val, "")
	}
	fmt.Println("")

}
