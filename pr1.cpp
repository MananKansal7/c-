#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include <fstream>

using namespace std;

// Define a struct to hold user information
struct UserInfo {
    string name;
    int age;
    string sex;
    string email;
    string address;
    string city;
    string state;
    int pincode;
    string username;
    string password;
    list<string> healthIssues;  // Linked list to store health issues
    double height;  // Height in cm
    double weight;  // Weight in kg
    // You can add more fields as needed for nutritional information, etc.
};

// Create a hashmap to store user data using their username as the key
unordered_map<string, UserInfo> userDatabase;

// Define admin username and password
const string adminUsername = "admin";
const string adminPassword = "admin123";

// Function to handle admin login
bool adminLogin() {
    string username, password;

    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    if (username == adminUsername && password == adminPassword) {
        cout << "Admin login successful!\n";
        return true;
    } else {
        cout << "Incorrect admin credentials. Login failed.\n";
        return false;
    }
}

// Function to view user data
void viewUserData() {
    cout << "User Data:\n";
    for (const auto& entry : userDatabase) {
        const UserInfo& user = entry.second;
        cout << "Username: " << entry.first << endl;
        cout << "Name: " << user.name << endl;
        cout << "Age: " << user.age << endl;
        // Add more fields as needed
        cout << "---------------------------\n";
    }
}

// Function to save user data to a file
void saveUserData() {
    ofstream file("userData.txt");

    if (file.is_open()) {
        for (const auto& entry : userDatabase) {
            const UserInfo& user = entry.second;
            file << user.username << " " << user.password << " " << user.name << " " << user.age << " "
                 << user.sex << " " << user.email << " " << user.address << " " << user.city << " "
                 << user.state << " " << user.pincode << " " << user.height << " " << user.weight << "\n";
        }
        file.close();
        cout << "User data saved successfully.\n";
    } else {
        cerr << "Unable to open file for writing.\n";
    }
}

// Function to load user data from a file
void loadUserData() {
    ifstream file("userData.txt");

    if (file.is_open()) {
        while (!file.eof()) {
            UserInfo user;
            file >> user.username >> user.password >> user.name >> user.age >> user.sex >> user.email
                 >> user.address >> user.city >> user.state >> user.pincode >> user.height >> user.weight;

            // Check if the read operation was successful
            if (!file.fail()) {
                userDatabase[user.username] = user;
            }
        }

        file.close();
        cout << "User data loaded successfully.\n";
    } else {
        cerr << "Unable to open file for reading. Starting with an empty user database.\n";
    }
}

// Function to handle user registration
void registerUser() {
    UserInfo newUser;

    cout << "Enter your name: ";
    cin.ignore(); // Ignore newline character in buffer
    getline(cin, newUser.name);
    cout << "Enter your age: ";
    cin >> newUser.age;
    cout << "Enter your sex (Male/Female): ";
    cin >> newUser.sex;
    cout << "Enter your email: ";
    cin >> newUser.email;
    cout << "Enter your address: ";
    cin.ignore(); // Ignore newline character in buffer
    getline(cin, newUser.address);
    cout << "Enter your city: ";
    cin >> newUser.city;
    cout << "Enter your state: ";
    cin >> newUser.state;
    cout << "Enter your pincode: ";
    cin >> newUser.pincode;
    cout << "Enter your desired username: ";
    cin >> newUser.username;
    cout << "Enter your desired password: ";
    cin >> newUser.password;
    cout << "Enter your height (in cm): ";
    cin >> newUser.height;
    cout << "Enter your weight (in kg): ";
    cin >> newUser.weight;

    // Check if the username already exists
    if (userDatabase.find(newUser.username) != userDatabase.end()) {
        cout << "Username already exists. Please choose a different username.\n";
        return;
    }

    // Add the new user to the database
    userDatabase[newUser.username] = newUser;

    cout << "Registration successful!\n";
}

// Function to handle user login
void loginUser() {
    string username, password;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    // Check if the username exists in the database
    if (userDatabase.find(username) != userDatabase.end()) {
        // Check if the entered password matches the stored password
        if (userDatabase[username].password == password) {
            cout << "Login successful!\n";

            // Ask about health issues
            cout << "What health issues are you facing? (Enter 'done' when finished)\n";
            string issue;
            cin.ignore(); // Ignore newline character in buffer
            do {
                cout << "Enter a health issue: ";
                getline(cin, issue);
                if (issue != "done") {
                    userDatabase[username].healthIssues.push_back(issue);
                }
            } while (issue != "done");

            // Calculate BMI
            double bmi = (userDatabase[username].weight) / ((userDatabase[username].height / 100.0) * (userDatabase[username].height / 100.0));
            cout << "Your BMI is: " << bmi << " (";

            // Determine health status based on BMI
            if (bmi < 18.5) {
                cout << "Underweight";
            } else if (bmi >= 18.5 && bmi < 25.0) {
                cout << "Normal/Healthy Weight";
            } else if (bmi >= 25.0 && bmi < 30.0) {
                cout << "Overweight";
            } else {
                cout << "Obese";
            }

            cout << ")\n";

            // Determine age group
            if (userDatabase[username].age < 2) {
                cout << "You are an infant.\n";
            } else if (userDatabase[username].age < 13) {
                cout << "You are a child.\n";
            } else if (userDatabase[username].age < 18) {
                cout << "You are a teenager.\n";
            } else {
                cout << "You are an adult.\n";
            }

            // Display menu for further options
            int menuChoice;
            do {
                // Display menu options
                cout << "\n1. Display Nutritional Information\n";
                cout << "2. Suggested Meals and Health Tips\n";
                cout << "3. Logout\n";
                cout << "Enter your choice: ";
                cin >> menuChoice;

                switch (menuChoice) {
                    case 1:
                        // Display nutritional information based on health issues
                        cout << "Displaying Nutritional Information:\n";
                        for (const auto& issue : userDatabase[username].healthIssues) {
                            cout << "Nutritional Information for " << issue << ":\n";
                            // Add conditions to display nutritional information based on health issues
                            if (issue == "Diabetes") {
                                cout << "   - Recommended Calories: 2000\n";
                                cout << "   - Recommended Proteins: 50g\n";
                                cout << "   - Recommended Fats: 30g\n";
                                cout << "   - Recommended Carbs: 250g\n";
                            } else if (issue == "Heart Disease") {
                                cout << "   - Recommended Calories: 1500\n";
                                cout << "   - Recommended Proteins: 40g\n";
                                cout << "   - Recommended Fats: 20g\n";
                                cout << "   - Recommended Carbs: 180g\n";
                            }
                            // Add more conditions for other health issues
                            cout << "---------------------------\n";
                        }
                        break;
                    case 2:
                        // Suggest meals and
                        // Suggest meals and health tips based on health condition
                        cout << "Suggested Meals and Health Tips:\n";
                        for (const auto& issue : userDatabase[username].healthIssues) {
                            cout << "Suggested Meals for " << issue << ":\n";
                            // Add conditions to suggest meals based on health issues
                            if (issue == "Diabetes") {
                                cout << "   - Meal: Quinoa and black bean salad with grilled chicken\n";
                                cout << "   - Nutritional Values:\n";
                                cout << "     - Calories: 400\n";
                                cout << "     - Proteins: 25g\n";
                                cout << "     - Fats: 15g\n";
                                cout << "     - Carbs: 45g\n";
                                cout << "Health Tips:\n";
                                cout << "- Limit intake of sugary foods and beverages.\n";
                                cout << "- Choose whole grains over refined grains.\n";
                                cout << "- Include a variety of fruits and vegetables in your diet.\n";
                            } else if (issue == "Heart Disease") {
                                cout << "   - Meal: Baked salmon with quinoa and steamed broccoli\n";
                                cout << "   - Nutritional Values:\n";
                                cout << "     - Calories: 500\n";
                                cout << "     - Proteins: 30g\n";
                                cout << "     - Fats: 20g\n";
                                cout << "     - Carbs: 35g\n";
                                cout << "Health Tips:\n";
                                cout << "- Include omega-3 rich foods in your diet.\n";
                                cout << "- Limit saturated and trans fats.\n";
                                cout << "- Choose lean protein sources.\n";
                            }
                            // Add more conditions for other health issues
                            cout << "---------------------------\n";
                        }
                        break;
                    case 3:
                        cout << "Logging out...\n";
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                }
            } while (menuChoice != 3);

        } else {
            cout << "Incorrect password. Login failed.\n";
        }
    } else {
        cout << "Username not found. Please register first.\n";
    }
}

int main() {
    // Load existing user data from the file
    loadUserData();

    int choice;
    do {
        // Display menu options
        cout << "\n1. Register\n";
        cout << "2. User Login\n";
        cout << "3. Admin Login\n";
        cout << "4. Save User Data\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                if (adminLogin()) {
                    // Admin-specific functionality can be added here
                    viewUserData();
                }
                break;
            case 4:
                // Save user data to the file
                saveUserData();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}