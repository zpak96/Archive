//Zane Paksi

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void shuffle(string &x, string &y) {
  string temp;

  if (x.size() < y.size()) { //ensure to iterate over the smaller string to avoid index out of range
    for (int i=0; i<x.size(); i++) {
      temp += string() + x[i] + y[i];
    }

    //append the remainder of the longer string
    temp += string() + y.substr(x.size());
    //cout << "first " << temp << endl;
  } else {
    for (int i=0; i<y.size(); i++) {
      temp += string() + x[i] + y[i];
    }

    temp += string() + x.substr(y.size());
    //cout << "second " << temp << endl;
  }
  //the new string is stored in temp, now make sentence1 equal to temp
  x = temp;
}

int main() { //main function
  string in1;
  string in2;

  cout << "Sentence 1: ";
  getline(cin,in1);

  cout << "Sentence 2: ";
  getline(cin,in2);

  if (!in1.empty() && !in2.empty()) { //checking to ensure no empty strings
    //lowercase this string
    transform (in1.begin(), in1.end(), in1.begin(), ::tolower);

    //uppercase this string
    transform (in2.begin(), in2.end(), in2.begin(), ::toupper);

    //call the shuffle function
    shuffle(in1,in2);
  } else {
    cout << "Error! One or more strings are empty, restarting.." << endl;
    cout << endl;
    main();
  }

  //print the mixed string and end the program
  cout << in1 << endl;
}
