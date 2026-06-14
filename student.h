#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100

// =========================
// 構造体
// =========================
typedef struct {

    char name[100];

    int score;

} Student;


// =========================
// 関数宣言
// =========================
int inputNumber(const char *message);

void inputStudent(Student students[],
                  int *count);

void displayStudents(Student students[],
                     int count);

void displayAverage(Student students[],
                    int count);

void searchStudent(Student students[],
                   int count);

void displayMaxMin(Student students[],
                   int count);

void sortByScore(Student students[],
                 int count);

void sortByName(Student students[],
                int count);

void saveStudents(Student students[],
                  int count);

void loadStudents(Student students[],
                  int *count);

#endif
