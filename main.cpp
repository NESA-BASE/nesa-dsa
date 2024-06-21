#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cctype>
using namespace std;

struct Patient {
    int patient_id;
    string name;
    string dob;
    string gender;
    Patient* next;

    Patient(int patient_id, string name, string dob, string gender) : patient_id(patient_id), name(name), dob(dob), gender(gender), next(nullptr) {}

};

struct Doctor {
    int doctor_id;
    string name;
    string specialization;
    Doctor* next;

    Doctor(int doctor_id, string name, string specialization): doctor_id(doctor_id), name(name), specialization(specialization), next(
            nullptr) {}
};

struct Appointment {
    int appointment_id;
    int patient_id;
    int doctor_id;
    string appointment_date;
    Appointment* next;

    Appointment(int appointment_id, int patient_id, int doctor_id, string appointment_date): appointment_id(appointment_id), patient_id(patient_id), doctor_id(doctor_id),
                                                                                             appointment_date(appointment_date), next(
                    nullptr) {}

};

class PatientLL {
    Patient* head;

public:
    // Constructor
    PatientLL() : head(nullptr) {}

    // Method to add a new Patient
    void addPatient(int patient_id, string name, string dob, string gender) {
        Patient* newPatient = new Patient(patient_id, name, dob, gender);
        newPatient->next = head;
        head = newPatient;
        cout << "Patient " << patient_id << " added successfully." << endl;
    }

    // Method to display all Patients
    void displayPatients() {
        Patient* current = head;
        while (current != nullptr) {
            cout << "Patient ID: " << current->patient_id << ", Name: " << current->name << ", DoB: " << current->dob << ", Gender: " << current->gender << endl;
            current = current->next;
        }
    }

    // Getter for the head of the Patient list
    Patient* getHead() const {
        return head;
    }
};

class DoctorLL {
    Doctor* head;

public:
    // Constructor
    DoctorLL() : head(nullptr) {}

    // Method to add a new Doctor
    void addDoctor(int doctor_id, string name, string specialization) {
        Doctor* newDoctor = new Doctor(doctor_id, name, specialization);
        newDoctor->next = head;
        head = newDoctor;
        cout << "Doctor " << doctor_id << " added successfully." << endl;
    }

    // Method to find a Doctor by ID
    Doctor* findDoctor(int id) {
        Doctor* current = head;
        while (current != nullptr) {
            if (current->doctor_id == id)
                return current;
            current = current->next;
        }
        return nullptr;
    }

    // Method to display all Doctors
    void displayDoctors() {
        Doctor* current = head;
        while (current != nullptr) {
            cout << "Doctor ID: " << current->doctor_id << ", Name: " << current->name << ", Specialization: " << current->specialization << endl;
            current = current->next;
        }
    }

    // Getter for the head of the Doctor list
    Doctor* getHead() const {
        return head;
    }
};

class  AppointmentLL {
    Appointment* head;

public:
    // Constructor
    AppointmentLL() : head(nullptr) {}

    // Method to add a new Appointment
    void addAppointment(int appointment_id, int patient_id, int doctor_id, string appointment_date) {
        Appointment* newAppointment = new Appointment(appointment_id, patient_id, doctor_id, appointment_date);
        newAppointment->next = head;
        head = newAppointment;
        cout << "Appointment " << appointment_id << " added successfully" << endl;
    }

    // Method to display all Appointments
    void displayAppointments() {
        Appointment* current = head;
        while (current != nullptr) {
            cout << "Appointment ID: " << current->appointment_id << ", Patient ID: " << current->patient_id << ", Doctor ID: " << current->doctor_id << ", Appointment Date: " << current->appointment_date << endl;
            current = current->next;
        }
    }

    // Method to search for a Appointment by ID and display details
    Appointment* findAppointmentByDate(int patient_id, int doctor_id, string appointment_date) {
        Appointment* current = head;

        while (current != nullptr) {
            if (current->patient_id == patient_id && current->doctor_id == doctor_id && current->appointment_date == appointment_date) {
                return current;
            }
            current = current->next;
        }

        return nullptr;
    }

    // Getter for the head of the Appointment list
    Appointment* getHead() const {
        return head;
    };
};

// function to validate if it is a leap year
bool isLeapYear(unsigned short year){
    return (!(year%4) && (year%100) || !(year%400));
}

// Function to check if a patient ID exists in the patient list
bool isPatientIdExists(const PatientLL& patientList, int id) {
    Patient* current = patientList.getHead();
    while (current != nullptr) {
        if (current->patient_id == id)
            return true;
        current = current->next;
    }
    return false;
}

// Function to check if a doctor ID exists in the doctor list
bool isDoctorIdExists(const DoctorLL& patientList, int id) {
    Doctor* current = patientList.getHead();
    while (current != nullptr) {
        if (current->doctor_id == id)
            return true;
        current = current->next;
    }
    return false;
}

// Function to check if appointment ID exists in the doctor list
bool isAppointmentIdExists(const AppointmentLL& appointmentList, int id) {
    Appointment* current = appointmentList.getHead();
    while (current != nullptr) {
        if (current->doctor_id == id)
            return true;
        current = current->next;
    }
    return false;
}

// Function to book an appointment
void registerAppointment(AppointmentLL& appointmentLl, int appointment_id, int patient_id, int doctor_id, string appointment_date) {
    if (appointmentLl.findAppointmentByDate(patient_id, doctor_id, appointment_date) == nullptr) {
        appointmentLl.addAppointment(appointment_id, patient_id, doctor_id, appointment_date);
    } else {
        cout << "Appointment already exists. Please schedule another appointment on a later date." << endl;
    }
}

// Function to validate integer input from user
bool isValidIntegerInput() {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

// Function to validate the date
bool valid_date(string dateString, int choice){
    // Check for valid format (dd/mm/yyyy)
    if (dateString.length() != 10 || dateString[2] != '/' || dateString[5] != '/') {
        cout << "Invalid date. Please provide a valid date (DD/MM/YYYY).\n";
        return false;
    }
    // Extract day, month, and year from string
    stringstream ss(dateString);
    int d, m, y;
    char ch;

    ss >> d >> ch >> m >> ch >> y;
    unsigned short monthLen[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if (!y || !m || !d || m>12) {
        cout << "Invalid date. Please provide a valid date (DD/MM/YYYY).\n";
        return false;
    }
    if (isLeapYear(y) && m==2)
        monthLen[1]++;
    if (d>monthLen[m-1]) {
        cout << "Invalid date. Please provide a valid date (DD/MM/YYYY).\n";
        return false;
    }
    // Check for valid year range (e.g., avoid dates before 1900 or far future)
    if (y < 1950 || y > 2050) {
        cout << "Invalid date. Please provide a date between years (1950 - 2050).\n";
        return false;
    }

    //Get the current date
    time_t now = time(0);
    tm* today = localtime(&now);
    // Years since 1900
    int currentYear = today->tm_year + 1900;
    //Years is 0-based
    int currentMonth = today->tm_mon - 1;

    if (choice == 1) { // Check if it's patient registration
        // DoB must be in the past
        if (y > currentYear || (y == currentYear && m > today->tm_mon + 1) || (y == currentYear && m == today->tm_mon + 1 && d > today->tm_mday)) {
            cout << "Invalid date. DoB(Date of Birth) must be in the past.\n";
            return false;
        }
    } else if (choice == 3) { // Check if it's appointment registration
        // Appointment date must be in the future relative to today's date
        if (y < currentYear || (y == currentYear && m < currentMonth) || (y == currentYear && m == currentMonth && d <= today->tm_mday)) {
            cout << "Invalid date. Appointment date must be in the future.\n";
            return false;
        }
    }
    return true;
}

// Function to validate non-empty string input from user
bool isValidStringInput(const string& input) {
    return !input.empty() && !all_of(input.begin(), input.end(), ::isspace);
}

// Function to display the welcome message
void displayWelcomeMessage() {
    cout << " =============================================================================================== " << endl;
    cout << "|                              Welcome to RUHENGERI HEALTHCARE SYSTEM!                           |" << endl;
    cout << "|                            ***********************************************                     |" << endl;
    cout << "|                                                                                                |" << endl;
    cout << "|                                  Credits to BIRAMAHIRE Dan Bellamy.                            |" << endl;
    cout << " ================================================================================================ " << endl;
}

bool validateGender(const std::string& genderStr) {
    // Convert the string to lowercase for case-insensitive comparison
    string gender = genderStr;
    transform(gender.begin(), gender.end(), gender.begin(), ::tolower);

    return gender == "male" || gender == "female";
}

int main() {
    PatientLL patientLl;
    AppointmentLL appointmentLl;
    DoctorLL doctorLl;
    displayWelcomeMessage();

    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Register a Patient" << endl;
        cout << "2. Register a Doctor" << endl;
        cout << "3. Register an Appointment" << endl;
        cout << "4. Display Patients" << endl;
        cout << "5. Display Doctors" << endl;
        cout << "6. Display Appointments" << endl;
        cout << "7. Exit" << endl;
        in:
        cout << "Enter your choice: ";
        cin >> choice;
        if (!isValidIntegerInput()) {
            cout << "Please provide a valid input (integer).\n";
            goto in;
        }

        switch (choice) {
            case 1: {
                cout << "PATIENT REGISTRATION" << endl;
                cout << "--------------------" << endl;

                int id;
                string name;
                string dob;
                string gender;
                bool isValidId = false;

                while (!isValidId) {
                    cout << "ID: ";
                    cin >> id;
                    if (!isValidIntegerInput() || id <= 0) {
                        cout << "Invalid ID. Please enter a positive integer.\n";
                        continue;
                    } else if (isPatientIdExists(patientLl, id)) {
                        cout << "Patient with ID " << id << " already exists.\n";
                        continue;
                    }
                    isValidId = true;
                }

                patientNameVal:
                cout << "NAME: ";
                cin.ignore();
                getline(cin, name);

                if (!isValidStringInput(name)) {
                    cout << "Invalid name. Please enter a non-empty name.\n";
                    goto patientNameVal;
                }

                doBVal:
                cout << "DoB: ";
                getline(cin, dob);

                if (!valid_date(dob, choice)) {
                    goto doBVal;
                }

                genderVal:
                cout << "GENDER: ";
                getline(cin, gender);

                if (!validateGender(gender)) {
                    cout << "Invalid gender. Please enter 'Male' or 'Female'.\n";
                    goto genderVal;
                }

                patientLl.addPatient(id, name, dob, gender);
                break;
            }
            case 2: {
                cout << "DOCTOR REGISTRATION" << endl;
                cout << "--------------------" << endl;
                int id;
                string name;
                string specialization;
                bool isValidId = false;
                while (!isValidId) {
                    cout << "ID: ";
                    cin >> id;
                    if (!isValidIntegerInput() || id <= 0) {
                        cout << "Invalid ID. Please enter a positive integer.\n";
                        continue;
                    } else if (isDoctorIdExists(doctorLl, id)) {
                        cout << "Doctor with ID " << id << " already exists.\n";
                        continue;
                    }
                    isValidId = true;
                }
                doctorNameVal:
                cout << "NAME: ";
                cin.ignore();
                getline(cin, name);

                if (!isValidStringInput(name)) {
                    cout << "Invalid name. Please provide a name.\n";
                    goto doctorNameVal;
                }
                doctorSpecificationVal:
                cout << "SPECIFICATION: ";
                getline(cin, specialization);

                if (!isValidStringInput(specialization)) {
                    cout << "Invalid specialization. Please provide a specialization.\n";
                    goto doctorSpecificationVal;
                }
                doctorLl.addDoctor(id, name, specialization);
                break;
            }
            case 3: {
                cout << "APPOINTMENT REGISTRATION" << endl;
                cout << "--------------------" << endl;
                int id;
                int doctor_id;
                int patient_id;
                string appointment_date;
                bool isValidId = false;
                bool isValidDID = false;
                bool isValidPID = false;

                while (!isValidId) {
                    cout << "ID: ";
                    cin >> id;
                    if (!isValidIntegerInput() || id <= 0) {
                        cout << "Invalid ID. Please enter a positive integer.\n";
                        continue;
                    } else if (isAppointmentIdExists(appointmentLl, id)) {
                        cout << "Appointment with ID " << id << " already exists.\n";
                        continue;
                    }
                    isValidId = true;
                }
                while (!isValidDID) {
                    cout << "D_ID: ";
                    cin >> doctor_id;
                    if (!isValidIntegerInput() || doctor_id <= 0) {
                        cout << "Invalid ID. Please enter a positive integer.\n";
                        continue;
                    } else if (!isDoctorIdExists(doctorLl, doctor_id)) {
                        cout << "Doctor with ID " << doctor_id << " not found.\n";
                        continue;
                    }
                    isValidDID = true;
                }

                while (!isValidPID) {
                    cout << "P_ID: ";
                    cin >> patient_id;
                    if (!isValidIntegerInput() || patient_id <= 0) {
                        cout << "Invalid ID. Please enter a positive integer.\n";
                        continue;
                    } else if (!isPatientIdExists(patientLl, patient_id)) {
                        cout << "Patient with ID " << patient_id << " not found.\n";
                        continue;
                    }
                    isValidPID = true;
                }

                // Clear the input buffer
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                aDate:
                cout << "DATE: ";
                getline(cin, appointment_date);

                if (!valid_date(appointment_date, choice)) {
                    goto aDate;
                }

//                appointmentLl.addAppointment(id, patient_id, doctor_id, appointment_date);
                registerAppointment(appointmentLl,id, patient_id, doctor_id, appointment_date);
                break;
            }
            case 4: {
                patientLl.displayPatients();
                break;
            }
            case 5: {
                doctorLl.displayDoctors();
                break;
            }
            case 6: {
                appointmentLl.displayAppointments();
                break;
            }
            case 7: {
                cout << "Exiting..." << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);
    return 0;
}