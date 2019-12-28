/* Zane Paksi
User input is passed argument on run
[*.exe][filename][# of lines generated]
*
* This program will generate the requested number of randomized car records.
* Each record contains and ID, color, and mileage.
*/
package main

import (
	"encoding/csv"
	"fmt"
	"log"
	"math/rand"
	"os"
	"strconv"
	"time"
)

func check(err error) {
	if err != nil {
		panic(err)
	}
}

func main() {
	start := time.Now()

	//Array containing common car colors
	colors := [...]string{"black", "white", "silver", "green", "gray", "red",
		"brown", "blue"}

	//argsAll := os.Arg
	//fmt.Println("All Arguments passed ::", argsAll)
	fileName := os.Args[1] + ".csv"
	lines_str := os.Args[2]
	fmt.Println("File Name ::", fileName)
	fmt.Println("Number of cars requested ::", lines_str)

	//Must convert lines to int for this upcoming loop
	i, err := strconv.Atoi(lines_str)
	if err != nil {
		fmt.Println("Issue converting lines\nPlease try again.", err)
		os.Exit(2)
	}

	//We'll set our random num generator here
	r := rand.New(rand.NewSource(time.Now().UnixNano()))

	if i <= 10000000 { //Setting limit for lines able to be created

		//If lines are within our paramaters, let's create the file now
		f, err := os.OpenFile(fileName, os.O_WRONLY|os.O_CREATE|os.O_APPEND, 0755)
		check(err)
		defer f.Close()

		//This is where our "write-out" method is defined
		w := csv.NewWriter(f)
		defer w.Flush()

		for numLine := 0; numLine <= i; numLine++ { //Iteration for number of lines
			//fmt.Println("Iteration ::", numLine)

			//Need a CarID generated (Probably going to go from 1001-101001)
			carID := numLine + 1000
			one := strconv.Itoa(carID)

			//Car color is randomly selected from our array
			carColor := colors[rand.New(r).Intn(8)]

			//Car miles is randomly generated from 10,000-99,000
			carMiles := 10000 + rand.New(r).Intn(160000)
			three := strconv.Itoa(carMiles)
			//fmt.Println(carID, carColor, carMiles)

			var carGen = []string{one, carColor, three}
			w.Write(carGen)
			//fmt.Println("Wrote", numLine, "lines")

		} //End scope of numLine loop
	} else {
		fmt.Println("Line request exceeds limit")
		os.Exit(3)
	}
	fmt.Println("DONE")
	elapsed := time.Since(start)
	log.Printf("Time elapsed: %s", elapsed)
}
