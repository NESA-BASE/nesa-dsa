#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <cctype>
#include <bits/stdc++.h>
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

template<typename EnumType, EnumType... Values>
class EnumCheck;

template<typename EnumType>
class EnumCheck<EnumType>
{
public:
    template<typename IntType>
    static bool constexpr is_value(IntType) { return false; }
};

template<typename EnumType, EnumType V, EnumType... Next>
class EnumCheck<EnumType, V, Next...> : private EnumCheck<EnumType, Next...>
{
    using super = EnumCheck<EnumType, Next...>;

public:
    template<typename IntType>
    static bool constexpr is_value(IntType v)
    {
        return v == static_cast<IntType>(V) || super::is_value(v);
    }
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
    }

    // Method to find a Patient by ID
    Patient* findPatient(int id) {
        Patient* current = head;
        while (current != nullptr) {
            if (current->patient_id == id)
                return current;
            current = current->next;
        }
        return nullptr;
    }

    // Method to display all Patients
    void displayPatients() {
        Patient* current = head;
        while (current != nullptr) {
            cout << "Patient ID: " << current->patient_id << ", Name: " << current->name << ", DoB: " << current->dob << ", Gender: " << current->gender << endl;
            current = current->next;
        }
    }

    // Method to search for a Patient by ID and display details
    void searchPatient(int id) {
        Patient* patient = findPatient(id);
        if (patient != nullptr) {
            cout << "Patient ID: " << patient->patient_id << ", Name: " << patient->name << ", DoB: " << patient->dob << ", Gender: " << patient->gender << endl;
        } else {
            cout << "Patient with ID " << id << " not found." << endl;
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
    bool addDoctor(int doctor_id, string name, string specialization) {
        Doctor* newDoctor = new Doctor(doctor_id, name, specialization);
        newDoctor->next = head;
        head = newDoctor;
        return true;
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

    // Method to search for a Doctor by ID and display details
    void searchDoctor(int id) {
        Doctor* doctor = findDoctor(id);
        if (doctor != nullptr) {
            cout << "Doctor ID: " << doctor->doctor_id << ", Name: " << doctor->name << ", Specialization: " << doctor->specialization << endl;
        } else {
            cout << "Doctor with ID " << id << " not found." << endl;
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
    }

    // Method to find an Appointment by ID
    Appointment* findAppointment(int id) {
        Appointment* current = head;
        while (current != nullptr) {
            if (current->appointment_id == id)
                return current;
            current = current->next;
        }
        return nullptr;
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
    void searchAppointment(int id) {
        Appointment* appointment = findAppointment(id);
        if (appointment != nullptr) {
            cout << "Appointment ID: " << appointment->appointment_id << ", Patient ID: " << appointment->patient_id << ", Doctor ID: " << appointment->doctor_id << ", Appointment Date: " << appointment->appointment_date << endl;
        } else {
            cout << "Appointment with ID " << id << " not found." << endl;
        }
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

// Function to check if an appointment is possible in the Appointment List
bool isAppointmentNotValid(const AppointmentLL& appointmentList, int id, int doctor_id, int patient_id) {
    Appointment* current = appointmentList.getHead();
    while (current != nullptr) {
        if (current->appointment_id == id)
            return true;
        if (current->doctor_id == doctor_id && current->patient_id == patient_id)
            return true;
        current = current->next;
    }
    return false;
}

// Function to book an appointment
void registerAppointment(PatientLL& patientLl, DoctorLL& doctorLl, AppointmentLL& appointmentLl, int appointment_id, int patient_id, int doctor_id, string appointment_date) {
    Patient* patient = patientLl.findPatient(patient_id);
    Doctor* doctor = doctorLl.findDoctor(doctor_id);
    Appointment* appointment = appointmentLl.findAppointment(appointment_id);

    if (patient == nullptr && doctor == nullptr && appointment == nullptr) {
        appointmentLl.addAppointment(appointment_id, patient_id, doctor_id, appointment_date);
    } else {
        cout << "Appointment already exists" << endl;
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
bool valid_date(string year,string month,string day){
    int y = stoi(year);
    int m = stoi(month);
    int d = stoi(day);
    if (isdigit(y) || isdigit(m) || isdigit(d)) {
        return false;
    }
    unsigned short monthLen[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if (!y || !m || !d || m>12)
        return false;
    if (isLeapYear(y) && m==2)
        monthLen[1]++;
    if (d>monthLen[m-1])
        return false;
    return true;
}

// Function to validate non-empty string input from user
bool isValidStringInput(const string& input) {
    return !input.empty() && !all_of(input.begin(), input.end(), ::isspace);
}

bool checkGenderValue(string gender) {
    if (gender != "Male" || gender != "Female") {
        return false;
    }
    return true;
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
                bool isValidDate = false;
                bool isValidGender = false;

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

                vector<string> date;
doBVal:
                cout << "DoB: ";
                cin.ignore();
                getline(cin, dob);

                if (!isValidStringInput(dob)) {
                    cout << "Invalid date. Please enter a non-empty date.\n";
                    goto doBVal;
                }
//                stringstream ss(dob);
//                while (ss.good()) {
//                    string substr;
//                    getline(ss, substr, '/');
//                    date.push_back(substr);
//                }
//
//                if (!valid_date(date[2], date[1], date[0])) {
//                    cout << "Invalid date. Please enter a non-empty date.\n";
//                    goto doBVal;
//                }

genderVal:
                cout << "GENDER: ";
                cin.ignore();
                getline(cin, gender);

                if (!isValidStringInput(gender)) {
                    cout << "Invalid date. Please enter a non-empty date.\n";
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
                cin.ignore();
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
                        cout << "Doctor with ID " << id << "not found.\n";
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
                        cout << "Patient with ID " << id << "not found.\n";
                        continue;
                    }
                    isValidPID = true;
                }

                vector<string> date;
aDate:
                cout << "DATE: ";
                cin.ignore();
                getline(cin, appointment_date);

                if (!isValidStringInput(appointment_date)) {
                    cout << "Invalid date. Please enter a non-empty date.\n";
                    goto aDate;
                }
//                stringstream ss(dob);
//                while (ss.good()) {
//                    string substr;
//                    getline(ss, substr, '/');
//                    date.push_back(substr);
//                }
//
//                if (!valid_date(date[2], date[1], date[0])) {
//                    cout << "Invalid date. Please enter a non-empty date.\n";
//                    goto doBVal;
//                }

//                appointmentLl.addAppointment(id, patient_id, doctor_id, appointment_date);
                registerAppointment(patientLl, doctorLl, appointmentLl,id, patient_id, doctor_id, appointment_date);
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
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 7);
    return 0;
}
