#include <iostream>
#include <string>
#include <limits>
#include <ios>  
class Course;
class Student;
class Faculty;
class Admin;

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// --- Date Class ---
class Date {
private:
    int day;
    int month;
    int year;

public:
    // Default constructor
    Date() : day(1), month(1), year(2000) {}

    // Parameterized constructor
    Date(int d, int m, int y) : day(1), month(1), year(2000) {
        // Basic validation (can be more robust)
        if (m >= 1 && m <= 12 && d >= 1 && d <= 31 && y > 1900) {
            day = d;
            month = m;
            year = y;
        } else {
            std::cout << "Warning: Invalid date provided, using default 1/1/2000.\n";
        }
    }

    void setDate(int d, int m, int y) {
         if (m >= 1 && m <= 12 && d >= 1 && d <= 31 && y > 1900) {
            day = d;
            month = m;
            year = y;
        } else {
            std::cout << "Warning: Invalid date provided, keeping previous date.\n";
        }
    }

    void display() const {
        std::cout << day << "/" << month << "/" << year;
    }

    // Getters (optional, but good practice)
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
};

// --- Faculty Class ---
class Faculty {
private:
    std::string name;
    std::string id;
    Date joinDate;
    Course** techcourseList; // Dynamic array of Course pointers
    int courseCount;
    int maxCourses; // Capacity of the array

    // Private helper to resize array if needed
    void resizeCourseList() {
        maxCourses = (maxCourses == 0) ? 5 : maxCourses * 2; // Start with 5, then double
        Course** newList = new Course*[maxCourses];
        for (int i = 0; i < courseCount; ++i) {
            newList[i] = techcourseList[i];
        }
        delete[] techcourseList; // Delete the old array
        techcourseList = newList;
    }


public:
    Faculty(std::string n = "Unknown", std::string i = "F000", int d = 1, int m = 1, int y = 2000)
        : name(n), id(i), joinDate(d, m, y), techcourseList(nullptr), courseCount(0), maxCourses(0) {}

    ~Faculty() {
        delete[] techcourseList;
    }

    // --- Getters ---
    std::string getName() const { return name; }
    std::string getId() const { return id; }

    // --- Setters ---
    void setFacultyData(const std::string& n, const std::string& i) {
        name = n;
        id = i;
    }

    void setJoinDate(int d, int m, int y) {
        joinDate.setDate(d, m, y);
    }

    // --- Course Management ---
    bool addCourse(Course* course) {
        if (!course) return false; // Don't add nullptrs
        if (courseCount == maxCourses) {
            resizeCourseList();
        }
        // Prevent adding duplicates (optional but good)
        for(int i=0; i<courseCount; ++i) {
            if(techcourseList[i] == course) {
                // std::cout << "Faculty " << name << " already teaches this course.\n";
                return false; // Already added
            }
        }
        techcourseList[courseCount++] = course;
        return true;
    }

    // --- Display ---
    void displayInfo() const; // Declaration only, needs Course definition
};

// --- Student Class ---
class Student {
private:
    std::string name;
    std::string id;
    Date joinDate;
    Course** courseList; // Dynamic array of Course pointers
    int courseCount;
    int maxCourses;     // Capacity of the array

    void resizeCourseList() {
        maxCourses = (maxCourses == 0) ? 5 : maxCourses * 2; // Start with 5, then double
        Course** newList = new Course*[maxCourses];
        for (int i = 0; i < courseCount; ++i) {
            newList[i] = courseList[i];
        }
        delete[] courseList; // Delete the old array
        courseList = newList;
    }

public:
    Student(std::string n = "Unknown", std::string i = "S000", int d = 1, int m = 1, int y = 2000)
        : name(n), id(i), joinDate(d, m, y), courseList(nullptr), courseCount(0), maxCourses(0) {}

    ~Student() {
        // Only delete the array of pointers, not the Course objects
        delete[] courseList;
    }

    // --- Getters ---
    std::string getName() const { return name; }
    std::string getId() const { return id; }
    int getCourseCount() const { return courseCount; }
    Course* getCourseAtIndex(int index) const {
        if (index >= 0 && index < courseCount) {
            return courseList[index];
        }
        return nullptr;
    }


    // --- Setters ---
    void setStudentData(const std::string& n, const std::string& i) {
        name = n;
        id = i;
    }

    void setJoinDate(int d, int m, int y) {
        joinDate.setDate(d, m, y);
    }

    // --- Course Management ---
     bool addCourse(Course* course) {
        if (!course) return false;
        if (courseCount == maxCourses) {
            resizeCourseList();
        }
        for(int i=0; i<courseCount; ++i) {
            if(courseList[i] == course) {
                // std::cout << "Student " << name << " already registered for this course.\n";
                return false; // Already added
            }
        }
        courseList[courseCount++] = course;
        return true;
    }

    bool dropCourse(Course* course) {
        if (!course) return false;
        int foundIndex = -1;
        for (int i = 0; i < courseCount; ++i) {
            if (courseList[i] == course) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex != -1) {
            // Shift elements back to fill the gap
            for (int i = foundIndex; i < courseCount - 1; ++i) {
                courseList[i] = courseList[i + 1];
            }
            courseList[courseCount - 1] = nullptr; // Optional: clear last pointer
            courseCount--;
            return true;
        }
        return false; // Course not found
    }


    // --- Display ---
    void displayInfo() const; // Declaration, needs Course definition
};


// --- Course Class ---
class Course {
private:
    std::string title;
    std::string code;
    Date startDate;
    Student** studentList; // Dynamic array of Student pointers
    int studentCount;
    int maxStudents;      // Capacity of the array
    Faculty* tec;         // Pointer to the Faculty teaching the course

    void resizeStudentList() {
        maxStudents = (maxStudents == 0) ? 10 : maxStudents * 2; // Start with 10, then double
        Student** newList = new Student*[maxStudents];
        for (int i = 0; i < studentCount; ++i) {
            newList[i] = studentList[i];
        }
        delete[] studentList; // Delete the old array
        studentList = newList;
    }


public:
    Course(std::string t = "Untitled", std::string c = "C000", int d = 1, int m = 1, int y = 2000)
        : title(t), code(c), startDate(d, m, y), studentList(nullptr), studentCount(0), maxStudents(0), tec(nullptr) {}

    ~Course() {
        delete[] studentList;
    }

    // --- Getters ---
    std::string getTitle() const { return title; }
    std::string getCode() const { return code; }
    Faculty* getFaculty() const { return tec; } // Return pointer

    // --- Setters ---
    void setCourceData(const std::string& t, const std::string& c) {
        title = t;
        code = c;
    }

    void setStartDate(int d, int m, int y) {
        startDate.setDate(d, m, y);
    }

    void assignTeacher(Faculty* teacher) {
        tec = teacher; // Assign the pointer
    }

    // --- Student Management ---
    bool addStudent(Student* student) {
        if (!student) return false;
        if (studentCount == maxStudents) {
            resizeStudentList();
        }
        for(int i=0; i<studentCount; ++i) {
            if(studentList[i] == student) {
                 // std::cout << "Student " << student->getName() << " already in course " << title << ".\n";
                 return false; // Already added
            }
        }
        studentList[studentCount++] = student;
        return true;
    }

    bool removeStudent(Student* student) {
        if (!student) return false;
        int foundIndex = -1;
        for (int i = 0; i < studentCount; ++i) {
            if (studentList[i] == student) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex != -1) {
            // Shift elements back
            for (int i = foundIndex; i < studentCount - 1; ++i) {
                studentList[i] = studentList[i + 1];
            }
            studentList[studentCount - 1] = nullptr;
            studentCount--;
            return true;
        }
        return false; // Student not found
    }


    // --- Display ---
    void displayInfo() const {
        std::cout << "------------------------------\n";
        std::cout << "Course Title: " << title << " (" << code << ")\n";
        std::cout << "Start Date: ";
        startDate.display();
        std::cout << "\n";
        std::cout << "Teacher: ";
        if (tec) {
            std::cout << tec->getName() << " (ID: " << tec->getId() << ")\n";
        } else {
            std::cout << "Not Assigned\n";
        }
        std::cout << "Enrolled Students (" << studentCount << "/" << maxStudents << "):\n";
        if (studentCount == 0) {
            std::cout << "  <None>\n";
        } else {
            for (int i = 0; i < studentCount; ++i) {
                if(studentList[i]) { // Check if pointer is valid
                   std::cout << "  - " << studentList[i]->getName() << " (ID: " << studentList[i]->getId() << ")\n";
                } else {
                   std::cout << "  - <Invalid Student Record>\n";
                }
            }
        }
        std::cout << "------------------------------\n";
    }
};


void Student::displayInfo() const {
    std::cout << "------------------------------\n";
    std::cout << "Student Name: " << name << " (ID: " << id << ")\n";
    std::cout << "Join Date: ";
    joinDate.display();
    std::cout << "\n";
    std::cout << "Enrolled Courses (" << courseCount << "/" << maxCourses << "):\n";
    if (courseCount == 0) {
        std::cout << "  <None>\n";
    } else {
        for (int i = 0; i < courseCount; ++i) {
             if(courseList[i]) { // Check pointer validity
                std::cout << "  - " << courseList[i]->getTitle() << " (" << courseList[i]->getCode() << ")\n";
             } else {
                std::cout << "  - <Invalid Course Record>\n";
             }
        }
    }
    std::cout << "------------------------------\n";
}

void Faculty::displayInfo() const {
    std::cout << "------------------------------\n";
    std::cout << "Faculty Name: " << name << " (ID: " << id << ")\n";
    std::cout << "Join Date: ";
    joinDate.display();
    std::cout << "\n";
    std::cout << "Teaching Courses (" << courseCount << "/" << maxCourses << "):\n";
    if (courseCount == 0) {
        std::cout << "  <None>\n";
    } else {
        for (int i = 0; i < courseCount; ++i) {
             if(techcourseList[i]) { // Check pointer validity
                std::cout << "  - " << techcourseList[i]->getTitle() << " (" << techcourseList[i]->getCode() << ")\n";
             } else {
                 std::cout << "  - <Invalid Course Record>\n";
             }
        }
    }
    std::cout << "------------------------------\n";
}


// --- Admin Class ---
class Admin {
private:
    std::string name;
    std::string id;
    Date joinDate;

    Course** courseList;
    int courseCount;
    int maxCourses;

    Student** studentList;
    int studentCount;
    int maxStudents;

    Faculty** facultyList;
    int facultyCount;
    int maxFaculty;

    void resizeCourseList() {
        maxCourses = (maxCourses == 0) ? 10 : maxCourses * 2;
        Course** newList = new Course*[maxCourses];
        for (int i = 0; i < courseCount; ++i) newList[i] = courseList[i];
        delete[] courseList;
        courseList = newList;
    }
    void resizeStudentList() {
        maxStudents = (maxStudents == 0) ? 20 : maxStudents * 2;
        Student** newList = new Student*[maxStudents];
        for (int i = 0; i < studentCount; ++i) newList[i] = studentList[i];
        delete[] studentList;
        studentList = newList;
    }
    void resizeFacultyList() {
        maxFaculty = (maxFaculty == 0) ? 5 : maxFaculty * 2;
        Faculty** newList = new Faculty*[maxFaculty];
        for (int i = 0; i < facultyCount; ++i) newList[i] = facultyList[i];
        delete[] facultyList;
        facultyList = newList;
    }

    Student* findStudentById(const std::string& studentId) {
        for (int i = 0; i < studentCount; ++i) {
            if (studentList[i] && studentList[i]->getId() == studentId) {
                return studentList[i];
            }
        }
        return nullptr; // Not found
    }

    Faculty* findFacultyById(const std::string& facultyId) {
        for (int i = 0; i < facultyCount; ++i) {
            if (facultyList[i] && facultyList[i]->getId() == facultyId) {
                return facultyList[i];
            }
        }
        return nullptr; 
    }

    Course* findCourseByCode(const std::string& courseCode) {
        for (int i = 0; i < courseCount; ++i) {
            if (courseList[i] && courseList[i]->getCode() == courseCode) {
                return courseList[i];
            }
        }
        return nullptr;
    }


public:
    Admin(std::string n = "Admin", std::string i = "A001", int d = 1, int m = 1, int y = 2000)
        : name(n), id(i), joinDate(d, m, y),
          courseList(nullptr), courseCount(0), maxCourses(0),
          studentList(nullptr), studentCount(0), maxStudents(0),
          facultyList(nullptr), facultyCount(0), maxFaculty(0)
    {}

    ~Admin() {
        for (int i = 0; i < courseCount; ++i) {
            delete courseList[i];
        }
        delete[] courseList;

        for (int i = 0; i < studentCount; ++i) {
            delete studentList[i];
        }
        delete[] studentList;

        for (int i = 0; i < facultyCount; ++i) {
            delete facultyList[i];
        }
        delete[] facultyList;
         std::cout << "\nAdmin Portal shutting down. All data cleared.\n";
    }

    void createStudent() {
        if (studentCount == maxStudents) {
            resizeStudentList();
        }
        std::string name, id;
        int d, m, y;

        std::cout << "Enter Student Name: ";
        std::getline(std::cin, name);
        std::cout << "Enter Student ID (e.g., S001): ";
        std::getline(std::cin, id);

        if (findStudentById(id)) {
            std::cout << "Error: Student ID '" << id << "' already exists.\n";
            return;
        }

        std::cout << "Enter Join Date (day month year): ";
        std::cin >> d >> m >> y;
        clearInputBuffer();

        Student* newStudent = new Student(name, id, d, m, y);
        studentList[studentCount++] = newStudent;
        std::cout << "Student '" << name << "' created successfully.\n";
    }

    void createFaculty() {
         if (facultyCount == maxFaculty) {
            resizeFacultyList();
        }
        std::string name, id;
        int d, m, y;

        std::cout << "Enter Faculty Name: ";
        std::getline(std::cin, name);
        std::cout << "Enter Faculty ID (e.g., F001): ";
        std::getline(std::cin, id);

        if (findFacultyById(id)) {
            std::cout << "Error: Faculty ID '" << id << "' already exists.\n";
            return;
        }

        std::cout << "Enter Join Date (day month year): ";
        std::cin >> d >> m >> y;
        clearInputBuffer();

        Faculty* newFaculty = new Faculty(name, id, d, m, y);
        facultyList[facultyCount++] = newFaculty;
        std::cout << "Faculty '" << name << "' created successfully.\n";
    }

    void createCourse() {
         if (courseCount == maxCourses) {
            resizeCourseList();
        }
        std::string title, code;
        int d, m, y;

        std::cout << "Enter Course Title: ";
        std::getline(std::cin, title);
        std::cout << "Enter Course Code (e.g., CS101): ";
        std::getline(std::cin, code);

        if (findCourseByCode(code)) {
            std::cout << "Error: Course Code '" << code << "' already exists.\n";
            return;
        }

        std::cout << "Enter Start Date (day month year): ";
        std::cin >> d >> m >> y;
        clearInputBuffer();

        Course* newCourse = new Course(title, code, d, m, y);
        courseList[courseCount++] = newCourse;
        std::cout << "Course '" << title << "' created successfully.\n";
    }

    void registerCourse() {
        std::string studentId, courseCode;
        std::cout << "Enter Student ID to register: ";
        std::getline(std::cin, studentId);
        std::cout << "Enter Course Code to register for: ";
        std::getline(std::cin, courseCode);

        Student* student = findStudentById(studentId);
        Course* course = findCourseByCode(courseCode);

        if (!student) {
            std::cout << "Error: Student with ID '" << studentId << "' not found.\n";
            return;
        }
        if (!course) {
            std::cout << "Error: Course with code '" << courseCode << "' not found.\n";
            return;
        }

        bool addedToStudent = student->addCourse(course);
        bool addedToCourse = course->addStudent(student);

        if (addedToStudent && addedToCourse) {
            std::cout << "Student '" << student->getName() << "' successfully registered for course '" << course->getTitle() << "'.\n";
        } else if (!addedToStudent && !addedToCourse) {
             std::cout << "Student '" << student->getName() << "' is already registered for course '" << course->getTitle() << "'.\n";
        }
        else {
             std::cout << "Warning: Registration partially completed. Check data consistency.\n";
             if(addedToStudent) student->dropCourse(course); // Attempt rollback
             if(addedToCourse) course->removeStudent(student); // Attempt rollback
        }
    }

     void dropCourse() {
        std::string studentId, courseCode;
        std::cout << "Enter Student ID to drop course: ";
        std::getline(std::cin, studentId);
        std::cout << "Enter Course Code to drop: ";
        std::getline(std::cin, courseCode);

        Student* student = findStudentById(studentId);
        Course* course = findCourseByCode(courseCode);

        if (!student) {
            std::cout << "Error: Student with ID '" << studentId << "' not found.\n";
            return;
        }
        if (!course) {
            std::cout << "Error: Course with code '" << courseCode << "' not found.\n";
            return;
        }

        bool droppedFromStudent = student->dropCourse(course);
        bool removedFromCourse = course->removeStudent(student);

        if (droppedFromStudent && removedFromCourse) {
            std::cout << "Student '" << student->getName() << "' successfully dropped course '" << course->getTitle() << "'.\n";
        } else if (!droppedFromStudent && !removedFromCourse) {
            std::cout << "Error: Student '" << student->getName() << "' was not registered for course '" << course->getTitle() << "'.\n";
        } else {
            std::cout << "Warning: Drop partially completed. Check data consistency.\n";
        }
    }


    void assignFaculty() {
        std::string facultyId, courseCode;
        std::cout << "Enter Faculty ID to assign: ";
        std::getline(std::cin, facultyId);
        std::cout << "Enter Course Code to assign to: ";
        std::getline(std::cin, courseCode);

        Faculty* faculty = findFacultyById(facultyId);
        Course* course = findCourseByCode(courseCode);

         if (!faculty) {
            std::cout << "Error: Faculty with ID '" << facultyId << "' not found.\n";
            return;
        }
        if (!course) {
            std::cout << "Error: Course with code '" << courseCode << "' not found.\n";
            return;
        }

        // Check if course already has a teacher
        if (course->getFaculty() != nullptr && course->getFaculty() != faculty) {
             std::cout << "Warning: Course '" << course->getTitle() << "' already assigned to '" << course->getFaculty()->getName() << "'. Overwriting.\n";
             course->getFaculty()->addCourse(nullptr); // This needs a proper remove method in Faculty
        } else if (course->getFaculty() == faculty) {
            std::cout << "Faculty '" << faculty->getName() << "' is already assigned to course '" << course->getTitle() << "'.\n";
            return; \
        }


        course->assignTeacher(faculty);
        faculty->addCourse(course); // Add course to faculty's list

        std::cout << "Faculty '" << faculty->getName() << "' successfully assigned to course '" << course->getTitle() << "'.\n";
    }

    void displayStudentInfo() {
        std::string studentId;
        std::cout << "Enter Student ID to display info: ";
        std::getline(std::cin, studentId);
        Student* student = findStudentById(studentId);
        if (student) {
            student->displayInfo();
        } else {
            std::cout << "Error: Student with ID '" << studentId << "' not found.\n";
        }
    }

     void displayFacultyInfo() {
        std::string facultyId;
        std::cout << "Enter Faculty ID to display info: ";
        std::getline(std::cin, facultyId);
        Faculty* faculty = findFacultyById(facultyId);
        if (faculty) {
            faculty->displayInfo();
        } else {
            std::cout << "Error: Faculty with ID '" << facultyId << "' not found.\n";
        }
    }

    void displayCourseInfo() {
        std::string courseCode;
        std::cout << "Enter Course Code to display info: ";
        std::getline(std::cin, courseCode);
        Course* course = findCourseByCode(courseCode);
        if (course) {
            course->displayInfo();
        } else {
            std::cout << "Error: Course with code '" << courseCode << "' not found.\n";
        }
    }

    void displayAllStudents() const {
        std::cout << "\n--- All Students (" << studentCount << ") ---\n";
        if (studentCount == 0) {
            std::cout << "<No students in system>\n";
        } else {
            for (int i = 0; i < studentCount; ++i) {
                 if(studentList[i]) studentList[i]->displayInfo();
            }
        }
         std::cout << "---------------------------\n";
    }
     void displayAllFaculty() const {
        std::cout << "\n--- All Faculty (" << facultyCount << ") ---\n";
        if (facultyCount == 0) {
            std::cout << "<No faculty in system>\n";
        } else {
            for (int i = 0; i < facultyCount; ++i) {
                if(facultyList[i]) facultyList[i]->displayInfo();
            }
        }
         std::cout << "---------------------------\n";
    }
     void displayAllCourses() const {
        std::cout << "\n--- All Courses (" << courseCount << ") ---\n";
        if (courseCount == 0) {
            std::cout << "<No courses in system>\n";
        } else {
            for (int i = 0; i < courseCount; ++i) {
                 if(courseList[i]) courseList[i]->displayInfo();
            }
        }
         std::cout << "---------------------------\n";
    }
};


// --- Menu Function ---
void displayMenu() {
    std::cout << "\n===== Student Course Registration Portal =====\n";
    std::cout << "1. Create New Student\n";
    std::cout << "2. Create New Faculty\n";
    std::cout << "3. Create New Course\n";
    std::cout << "4. Register Student for Course\n";
    std::cout << "5. Drop Student from Course\n";
    std::cout << "6. Assign Faculty to Course\n";
    std::cout << "7. Display Student Information\n";
    std::cout << "8. Display Faculty Information\n";
    std::cout << "9. Display Course Information\n";
    std::cout << "10. Display All Students\n";
    std::cout << "11. Display All Faculty\n";
    std::cout << "12. Display All Courses\n";
    std::cout << "0. Exit\n";
    std::cout << "===========================================\n";
    std::cout << "Enter your choice: ";
}

// --- Main Function ---
int main() {
    Admin portalAdmin("Aizaz Akmal", "AD001", 1, 1, 2023); // Create the admin instance

    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        clearInputBuffer(); // Consume the newline character left by std::cin

        switch (choice) {
            case 1:
                portalAdmin.createStudent();
                break;
            case 2:
                portalAdmin.createFaculty();
                break;
            case 3:
                portalAdmin.createCourse();
                break;
            case 4:
                portalAdmin.registerCourse();
                break;
            case 5:
                portalAdmin.dropCourse();
                break;
            case 6:
                portalAdmin.assignFaculty();
                break;
            case 7:
                portalAdmin.displayStudentInfo();
                break;
            case 8:
                portalAdmin.displayFacultyInfo();
                break;
            case 9:
                portalAdmin.displayCourseInfo();
                break;
             case 10:
                portalAdmin.displayAllStudents();
                break;
            case 11:
                portalAdmin.displayAllFaculty();
                break;
            case 12:
                portalAdmin.displayAllCourses();
                break;
            case 0:
                std::cout << "Exiting Portal...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}