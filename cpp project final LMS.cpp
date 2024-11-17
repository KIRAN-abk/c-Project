#include <bits/stdc++.h>
using namespace std;

class Elevator {
private:
    int currentFloor;
    bool powerOn;
    bool fireEmergency;

public:
    Elevator() : currentFloor(0), powerOn(false), fireEmergency(false) {}

    void setPower(bool state) {
        if (fireEmergency) {
            cout << "Cannot turn on power. Fire emergency is active!" << endl;
        } else {
            powerOn = state;
            if (!powerOn) {
                cout << "Power is off. Elevator is moving to the nearest floor..." << endl;
                moveToNearestFloor();
            } else {
                cout << "Power is on. Elevator is ready to be used." << endl;
            }
        }
    }

    void setFireEmergency(bool state) {
        fireEmergency = state;
        if (fireEmergency) {
            cout << "Fire emergency! Elevator is moving to the ground floor and opening doors..." << endl;
            moveToGroundFloor();
            powerOn = false;
        } else {
            cout << "Fire emergency cleared. Please turn on the power to use the elevator." << endl;
        }
    }

    void moveToNearestFloor() {
        if (powerOn) {
            cout << "Elevator is at floor " << currentFloor << endl;
        } else {
            while (currentFloor > 0) {
                currentFloor--;
                cout << "Moving to floor " << currentFloor << endl;
            }
            cout << "Doors opening..." << endl;
        }
    }

    void moveToGroundFloor() {
        while (currentFloor > 0) {
            currentFloor--;
            cout << "Moving to floor " << currentFloor << endl;
        }
        cout << "Doors opening..." << endl;
    }

    void pressButtonOutside(string direction, int targetFloor) {
        if (!powerOn) {
            cout << "Elevator cannot be used. Power is off." << endl;
            return;
        }

        if (fireEmergency) {
            cout << "Elevator is in fire emergency mode." << endl;
            return;
        }

        if (targetFloor < 0 || targetFloor > 15) {
            cout << "Invalid floor. Please choose a floor between 0 and 15." << endl;
            return;
        }

        if (targetFloor == currentFloor) {
            cout << "You are already at floor " << targetFloor << ". Doors opening..." << endl;
            return;
        }

        if (direction == "up") {
            if (currentFloor == 15) {
                cout << "Elevator is at the top floor (15). Cannot move up." << endl;
                return;
            } else if (currentFloor < targetFloor) {
                moveUp(targetFloor);
            } else {
                cout << "Elevator is moving down. Please press the down button." << endl;
            }
        } else if (direction == "down") {
            if (currentFloor == 0) {
                cout << "Elevator is at the ground floor (0). Cannot move down." << endl;
                return;
            } else if (currentFloor > targetFloor) {
                moveDown(targetFloor);
            } else {
                cout << "Elevator is moving up. Please press the up button." << endl;
            }
        } else {
            cout << "Invalid button press. Use 'up' or 'down'." << endl;
        }
    }

    void moveUp(int targetFloor) {
        while (currentFloor < targetFloor) {
            currentFloor++;
            cout << "Moving up to floor " << currentFloor << endl;
        }
        cout << "Reached floor " << currentFloor << ". Doors opening..." << endl;
    }

    void moveDown(int targetFloor) {
        while (currentFloor > targetFloor) {
            currentFloor--;
            cout << "Moving down to floor " << currentFloor << endl;
        }
        cout << "Reached floor " << currentFloor << ". Doors opening..." << endl;
    }

    bool isPowerOn() const {
        return powerOn;
    }

    bool isFireEmergency() const {
        return fireEmergency;
    }

    int getCurrentFloor() {
        return currentFloor;
    }
};

int main() {
    Elevator elevator;
    int option, targetFloor;
    string direction;

    while (true) {
        if (elevator.isFireEmergency()) {
            cout << "\nFire emergency active! Only options to turn off fire emergency or exit are available.\n";
            cout << "1. Turn off fire emergency\n2. Exit\n";
        } else if (elevator.isPowerOn()) {
            cout << "\n1. Turn power off\n2. Trigger fire emergency\n3. Press outside button\n4. Exit\n";
        } else {
            cout << "\n1. Turn power on\n2. Trigger fire emergency\n3. Exit\n";
        }
        cin >> option;

        if (elevator.isFireEmergency()) {
            if (option == 1) {
                elevator.setFireEmergency(false);
            } else if (option == 2) {
                cout << "Exiting..." << endl;
                return 0;
            } else {
                cout << "Invalid option. Fire emergency is active!" << endl;
            }
        } else if (!elevator.isPowerOn()) {
            if (option == 1) {
                elevator.setPower(true);
            } else if (option == 2) {
                elevator.setFireEmergency(true);
            } else if (option == 3) {
                cout << "Exiting..." << endl;
                return 0;
            } else {
                cout << "Power is off. No other options are available." << endl;
            }
        } else {
            switch (option) {
                case 1:
                    elevator.setPower(false);
                    break;
                case 2:
                    elevator.setFireEmergency(true);
                    break;
                case 3:
                    if (elevator.getCurrentFloor() == 15) {
                        direction = "down";
                    } else if (elevator.getCurrentFloor() == 0) {
                        direction = "up";
                    } else {
                        cout << "Press 'up' or 'down': ";
                        cin >> direction;
                    }

                    cout << "Which floor would you like to go to? (0-15): ";
                    cin >> targetFloor;
                    elevator.pressButtonOutside(direction, targetFloor);
                    break;
                case 4:
                    cout << "Exiting..." << endl;
                    return 0;
                default:
                    cout << "Invalid option. Try again." << endl;
            }
        }
    }

    return 0;
}

