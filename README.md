# BankAccountsManager (v2)

A powerful and extensible **C++ console-based banking system** designed to manage both **clients and users** securely through a file-based architecture. This is an upgraded version of my earlier project with **enhanced features**, including **user authentication**, **permissions**, and improved data handling.

---

## 💡 Features

### 🔐 User Management System
- Add new users with credentials and permissions
- Authenticate users via username/password
- Delete users from the system
- Save/load users to file
- Permission-based access control

### 🧾 Client Account Management
- View full list of clients
- Add new clients with full information
- Delete or update existing accounts
- Find client details by account number
- Perform financial transactions (Deposit / Withdraw)
- View total balance across all clients

### 💾 Data Persistence
- All user and client data stored in structured text files
- Reliable save/load functions for consistent state

---

## 🧰 Technologies Used
- **C++ Standard Library**: `iostream`, `fstream`, `vector`, `string`, `sstream`, `algorithm`
- **Custom Library**: `MyInputLib.h` – for input validation and formatting
- **Text-based File Storage**: `Bank Project.txt` (clients), `Users.txt` (users)

---

## 📂 File Descriptions

| File Name             | Description                                             |
|----------------------|---------------------------------------------------------|
| `Bank Project.cpp`   | Main source file containing the full application logic |
| `MyInputLib.h`       | Custom helper functions for user input and validation  |
| `Bank Project.txt`   | Text file storing client account data                  |
| `Users.txt`          | Text file storing system user credentials & permissions|
| `.gitignore`         | Excludes binaries or generated files from Git tracking |

---

## 🚀 How to Use
1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/BankAccountsManager.git
   cd BankAccountsManager


🎯 Objective
This project demonstrates practical use of file I/O, structs, vectors, string manipulation, and user authentication in C++. It’s a great exercise in building small systems that resemble real-world use cases, and serves as a stepping stone to more robust, database-driven applications.

🧠 Future Improvements (Planned)
Encrypted user passwords

Role-based access control (e.g., Admin vs Clerk)

Transaction history logs

GUI version with Qt or web-based frontend
