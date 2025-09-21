# 🎓 Student Result Management System (C++ & MySQL)

A **console-based Student Result Management System** built in **C++** with **MySQL database integration** and **Admin login authentication**.  
This project helps manage student records efficiently with CRUD operations (Create, Read, Update, Delete), percentage calculation, and grading.

---

## 🚀 Features

- 🔐 **Admin Login System** (Email + Password stored securely in MySQL with SHA2 hashing).  
- 📝 **Add Student Records** (with marks for 5 subjects).  
- 📖 **View All Students** with percentage and grade calculation.  
- 🔍 **Search Student** by Roll Number.  
- ✏️ **Update Student Records** (marks and details).  
- ❌ **Delete Student Records**.  
- 📊 **Auto Grade Calculation** based on percentage.  
- 💾 **Persistent Storage** using MySQL database (`student_db`).  

---

## 🛠️ Tech Stack

- **C++17**  
- **MySQL 8+** (with `mysql-connector-c++`)  
- **Linux (Ubuntu/Debian)**  

---

## 📂 Database Setup

Run the following SQL script in MySQL to set up the database:

```sql
CREATE DATABASE IF NOT EXISTS student_db;
USE student_db;

-- Students Table
CREATE TABLE IF NOT EXISTS students (
  roll INT PRIMARY KEY,
  name VARCHAR(100) NOT NULL,
  sub1 INT NOT NULL,
  sub2 INT NOT NULL,
  sub3 INT NOT NULL,
  sub4 INT NOT NULL,
  sub5 INT NOT NULL,
  percentage FLOAT,
  grade CHAR(1)
);

-- Admins Table
CREATE TABLE IF NOT EXISTS admins (
  email VARCHAR(255) PRIMARY KEY,
  password_hash VARCHAR(255) NOT NULL
);

-- Insert Demo Admin
INSERT INTO admins (email, password_hash)
VALUES ('baihelahusain@gmail.com', SHA2('Bah$5000USD', 256))
ON DUPLICATE KEY UPDATE password_hash = VALUES(password_hash);

-- Create MySQL User for Application
CREATE USER IF NOT EXISTS 'student_user'@'localhost' IDENTIFIED BY 'Student@1234';
GRANT ALL PRIVILEGES ON student_db.* TO 'student_user'@'localhost';
FLUSH PRIVILEGES;
```

## ⚙️ Installation & Setup (Linux)
-**sudo apt update && sudo apt upgrade -y**

### Install build tools
-**sudo apt install g++ cmake make -y**

### Install MySQL Server & Client
-**sudo apt install mysql-server mysql-client -y**
### Install MySQL Connector for C++
-**sudo apt install libmysqlcppconn-dev -y**

## Clone The Repo
-**git clone https://github.com/<your-username>/student-result-management.git
cd student-result-management**

