/* Zane Paksi
* This program uses a mclaurin series to sum
* the value of Pi. This specific program iterates 100 Million times.
*
*/

package main

import (
	"fmt"
	"log"
	"math"
	"time"
)

func main() {
	start := time.Now()

	var myPi float64
	truePi := math.Pi

	for i := 0; i <= 100000000; i++ { //Summing Pi
		myPi += math.Pow(-1.0, float64(i)) / ((2.0 * float64(i)) + 1.0)
	}

	fmt.Println(":: 100 Million Iterations ::")
	fmt.Println("Math.Pi ::", truePi)
	fmt.Println("Calculated Pi ::", (4.0 * myPi))
	fmt.Println("Error ::", truePi-(4.0*myPi))

	elapsed := time.Since(start)
	log.Printf("Time elapsed: %s", elapsed)
}
