
# Hospital Management System

This project is a simple Hospital Management System implemented in C++. It allows for managing patients, doctors, appointments, and ward beds within a hospital.

## Features

- **Patient Management**: Add, edit, and delete patient information.
- **Doctor Management**: Manage doctor information and their appointments.
- **Appointment Management**: Create, edit, and view appointments between doctors and patients.
- **Ward Management**: Assign patients and doctors to beds in a ward and manage bed status.

## Prerequisites

- C++ compiler (e.g., g++)
- Standard C++ libraries

## Getting Started

### Compilation

To compile the project, run the following command in your terminal:

```sh
g++ -o hospital_management main.cpp
```

### Execution

After compiling, you can run the executable:

```sh
./hospital_management
```

### Files

The system reads from and writes to the following CSV files:

- `doctors.csv`: Contains doctor information.
- `patients.csv`: Contains patient information.
- `appointments.csv`: Contains appointment information.
- `ward.csv`: Contains ward bed status information.

Ensure these files are in the same directory as the executable, or adjust the file paths in `main.cpp`.

## Usage

When you run the program, you will be presented with a login menu:

- **Admin Login**: Press `A`
- **Doctor Login**: Press `D`
- **Patient Login**: Press `P`
- **Ward Management**: Press `E`
- **Quit**: Press `Q`

### Admin Portal

Admins can perform the following actions:

- Create, edit, delete, and view appointments.
- Add and delete patients.

### Doctor Portal

Doctors can:

- View their appointments.
- Diagnose patients and add prescriptions.

### Patient Portal

Patients can:

- View their personal information and appointments.

### Ward Management

Manage ward beds by:

- Admitting patients to beds.
- Viewing bed status.
- Discharging patients from beds.

## Code Structure

### Classes

- **patient**: Manages patient information.
- **doctor**: Manages doctor information and interactions.
- **appointment**: Manages appointment details and status.
- **admin**: Provides admin functionalities to manage appointments and patients.
- **bed**: Manages bed assignment to patients and doctors.
- **ward**: Manages a collection of beds in a ward.

### Utility Functions

- `sleep(float seconds)`: Pauses the program for a given time.
- `timestamptodatetime(datetime &, int timestamp)`: Converts a timestamp to a readable datetime format.
- `convertToTimestamp(int year, int month, int day, int hour, int minute, int second)`: Converts a datetime to a timestamp.
- `load_doctors(vector<doctor> &, string)`, `load_patients(vector<patient> &, string)`, `load_appointments(vector<appointment> &, string, vector<doctor> &, vector<patient> &)`, `load_ward(ward &, string, vector<doctor> &, vector<patient> &)`: Load data from CSV files.
- `save_appintments(vector<appointment> &, string)`, `save_ward(ward &, string)`, `save_patients(vector<patient> &, string)`: Save data to CSV files.

## Future Improvements

- Add user authentication for different roles.
- Improve the user interface and error handling.
- Extend functionalities for more detailed hospital management.

## Contributing

Feel free to fork this project, open issues, and submit pull requests. Contributions are welcome!

## License

This project is licensed under the MIT License.
