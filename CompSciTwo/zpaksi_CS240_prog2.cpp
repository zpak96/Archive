//Zane Paksi

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class ship {
  string name;
  string model;
  int energy;
  int photons;

  public:
    void setName(string n) {
      name = n;
    }
    void setModel(string m) {
      model = m;
    }
    void setEnergy(int e) {
      energy = e;
    }
    void setPhotons(int p) {
      photons = p;
    }
};

void getCommand(string &x) {
  string temp;
  cout << ":> ";
  getline(cin, temp);
  transform (temp.begin(), temp.end(), temp.begin(), ::tolower);
  x = temp;
}

int main() {
  string usertype;

  cout << "Are you a GameMaster or User?\nEnter 'GM', or 'User': ";
  getCommand(usertype);

  if (usertype == "gm") {
    cout << "You selected GameMaster.\nEnter 'B' to build a prototype ship\nEnter 'E' to edit an existing prototype\n";

    while (usertype == "gm") {
      string menutype, again;
      getCommand(menutype);

      if (menutype == "b") { // building a new ship
        string n, m, e, p;
        ship new_prototype;
        cout << "Prototype name";
        getCommand(n);
        new_prototype.setName(n);

        cout << "Model type (Ex: Frigate, Destroyer, etc)";
        getCommand(m);
        new_prototype.setModel(m);

        cout << "Ship energy";
        getCommand(e);
        new_prototype.setEnergy(stoi(e));

        cout << "Photon limit: ";
        getCommand(p);
        new_prototype.setPhotons(stoi(p));

        //HERE IS WHERE YOU SAVE THE SHIP INFO

        cout << "Would you like to create another ship?\nEnter y or n";
        getCommand(again);
        if (again == "y") {

        }

      } else if (menutype == "e") { // editing an existing ship

      } else { // invalid command
        cout << "Unknown command" << endl;
        continue;
      }



    } //End of GM while loop
  } else if (usertype == "user") {
    cout << "You selected User" << endl;
  }

  return 0;
}
