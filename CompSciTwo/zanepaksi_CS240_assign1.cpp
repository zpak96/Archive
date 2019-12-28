/* Zane Paksi
// I've created a class so that each ship can be on object.
// I think this will make handling movement easier between objects.
*/

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class traveller {
  private:
    //Privatize coordinates
    int x, y, z;

  public:
    void setCoordinates(int a, int b, int c) {
      x = a;
      y = b;
      z = c;
    } //setCoordinates

    //Methods to move our traveller
    void moveX(int a) {
        x += a;
    }//moveX
    void moveY(int b) {
      y += b;
    }//moveY
    void moveZ(int c) {
      z += c;
    }//moveZ

    string getCoordinates() {
        //convert xyz to strings
        auto strX = std::to_string(x);
        auto strY = std::to_string(y);
        auto strZ = std::to_string(z);
        string coordinates = strX + "," + strY + "," + strZ;
        return coordinates;
    } //getCoordinates

    void coordinateCheck() {
      string navigationError = "Surrounding asteroid fields prevent travel in this direction,\nTurning around.";
      if (x < 0 || x > 8) {
        if (x < 0) {
          x = 0;
        } else if (x > 8) {
          x = 8;
        }
        cout << navigationError << endl;
      } else if (y < 0 || y > 8) {
        if (y < 0) {
          y = 0;
        } else if (y > 8) {
          y = 8;
        }
        cout << navigationError << endl;
    } else if (z < 0 || z > 8) {
      if (z < 0) {
        z = 0;
      } else if (z > 8) {
        z = 8;
      }
      cout << navigationError << endl;
    }
  } // need to optimize this method. lots of code repitition, lampda? map?

}; //traveller class

void greeting() {
  string msg;
  msg = (
    "Welcome to the U.S.S Enterprise:\nSensor scans indicate a Klingon Warship is roaming this sector.\nLocate the ship before any casualties occur.\nType help more information"
  );
    cout << msg << endl;
}

void getCommand(string &x) {
  string temp;
  cout << ":> ";
  getline(cin, temp);
  transform (temp.begin(), temp.end(), temp.begin(), ::tolower);
  x = temp;
}

int main(){
  traveller enterprise;
  traveller klingon;

  string command;
  string word;
  vector<std::string> vec;

  map<std::string, int> navigationData;
  navigationData["up"] = 1;
  navigationData["down"] = -1;
  navigationData["right"] = 1;
  navigationData["left"] = -1;
  navigationData["forward"] = 1;
  navigationData["back"] = -1;

  //set initial coordinates
  enterprise.setCoordinates(8,8,8);
  klingon.setCoordinates(0,0,0);

  greeting();
  cout << "Your current location is: " << enterprise.getCoordinates() << endl;

  //get initial command to start loop
  getCommand(command);

  while (true) {
    //input filter #1
    while (command.length() < 3) {
      cout << "Invalid entry, please enter a new command." << endl;
      getCommand(command);
    }

    //get and parse the command
    stringstream ss(command);
    while (getline(ss, word, ' ')) {
      vec.emplace_back(word);
    } //command parsing while loop

    if (vec.size() == 1) {
        if (vec[0] == "help") {
          string helpMsg = "Usable commands:\nmove -directions (y-axis) = up, down, (x-axis) = left, right, (z-axis) = forward, back EX: 'move up'\n";
          helpMsg += "sensor scan -This will display the location of the klingon";
          cout << helpMsg << endl;
        }
    }
    else if (vec.size() == 2) {
      if (vec[0] == "move") {
        if (navigationData.find(vec[1]) != navigationData.end()) {

          if (vec[1] == "up" || vec[1] == "down") {
            enterprise.moveY(navigationData[vec[1]]);
          }
          else if (vec[1] == "right" || vec[1] == "left") {
            enterprise.moveX(navigationData[vec[1]]);
          }
          else if (vec[1] == "forward" || vec[1] == "back") {
            enterprise.moveZ(navigationData[vec[1]]);
          } else {
            cout << "critical error" << endl;
          }
          enterprise.coordinateCheck();
          cout << enterprise.getCoordinates() << endl;
        } else {
          cout << "Unable to move in that direction" << endl;

        } // Navigation map search scope
      } else if (vec[0] == "sensor") {
        if (vec[1] == "scan") {
          cout << "Scans show the klingon war ship is located at: " << klingon.getCoordinates() << endl;
        } else {
          cout << "Invalid command";
        }
      }
    } //vector size check

    //request new command to maintain loop
    getCommand(command);
    //clear vector and temp variable for next command input
    word.clear();
    vec.clear();
    ss.clear();
  } //while loop
} //main function
