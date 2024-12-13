#include "studentas.h"
#include "studentas.cpp"        
#include "lib.h"
#include <gtest/gtest.h>

// Test default constructor
TEST(StudentasClassTest, DefaultConstructor) {
    StudentasClass student;
    EXPECT_EQ(student.getVardas(), "");
    EXPECT_EQ(student.getPavarde(), "");
    EXPECT_EQ(student.getEgzamRez(), 0);
    EXPECT_EQ(student.getTarpRez().size(), 0);
    EXPECT_DOUBLE_EQ(student.getVidurkis(), 0.0);
    EXPECT_DOUBLE_EQ(student.getMediana(), 0.0);
    EXPECT_DOUBLE_EQ(student.getGalutinis(), 0.0);
    EXPECT_FALSE(student.arIslaike());
}

// Test parameterized constructor
TEST(StudentasClassTest, ParameterizedConstructor) {
    StudentasClass student("Jonas", "Jonaitis");
    EXPECT_EQ(student.getVardas(), "Jonas");
    EXPECT_EQ(student.getPavarde(), "Jonaitis");
}

// Test copy constructor
TEST(StudentasClassTest, CopyConstructor) {
    StudentasClass filledStudent;
    filledStudent.setVardas("Tom");
    filledStudent.setPavarde("Ford");
    filledStudent.generuotiBalus(5);

    StudentasClass copiedStudent(filledStudent);
    EXPECT_EQ(copiedStudent.getVardas(), filledStudent.getVardas());
    EXPECT_EQ(copiedStudent.getPavarde(), filledStudent.getPavarde());
    EXPECT_EQ(copiedStudent.getTarpRez(), filledStudent.getTarpRez());
}

// Test copy assignment
TEST(StudentasClassTest, CopyAssignment) {
    StudentasClass assignedStudent;
    StudentasClass filledStudent;
    filledStudent.setVardas("Tom");
    filledStudent.setPavarde("Ford");
    filledStudent.generuotiBalus(5);

    assignedStudent = filledStudent;
    EXPECT_EQ(assignedStudent.getVardas(), filledStudent.getVardas());
    EXPECT_EQ(assignedStudent.getPavarde(), filledStudent.getPavarde());
    EXPECT_EQ(assignedStudent.getTarpRez(), filledStudent.getTarpRez());
}

// TEST(StudentasClassTest, MoveOperation) {
//     StudentasClass assignedStudent;
//     StudentasClass filledStudent;
//     filledStudent.setVardas("Tom");
//     filledStudent.setPavarde("Ford");
//     filledStudent.generuotiBalus(5);

//     assignedStudent = std::move(filledStudent);
//     EXPECT_NE(assignedStudent.getVardas(), filledStudent.getVardas());
//     EXPECT_NE(assignedStudent.getPavarde(), filledStudent.getPavarde());
//     EXPECT_NE(assignedStudent.getTarpRez(), filledStudent.getTarpRez());
// }

// Test setters and getters
TEST(StudentasClassTest, SettersAndGetters) {
    StudentasClass student;
    student.setVardas("Tom");
    student.setPavarde("Ford");
    student.setEgzamRez(9);
    student.pridetiTarpRez(7);
    student.pridetiTarpRez(8);

    EXPECT_EQ(student.getVardas(), "Tom");
    EXPECT_EQ(student.getPavarde(), "Ford");
    EXPECT_EQ(student.getEgzamRez(), 9);
    EXPECT_EQ(student.getTarpRez().size(), 2);
    EXPECT_EQ(student.getTarpRez()[0], 7);
    EXPECT_EQ(student.getTarpRez()[1], 8);
}

// Test adding intermediate grades
TEST(StudentasClassTest, AddIntermediateGrades) {
    StudentasClass student;
    student.pridetiTarpRez(6);
    student.pridetiTarpRez(9);

    const std::vector<int>& pazymiai = student.getTarpRez();
    ASSERT_EQ(pazymiai.size(), 2);
    EXPECT_EQ(pazymiai[0], 6);
    EXPECT_EQ(pazymiai[1], 9);
}

// Test grade generation
TEST(StudentasClassTest, GradeGeneration) {
    StudentasClass student;
    student.generuotiBalus(10);
    
    EXPECT_EQ(student.getTarpRez().size(), 10);
    EXPECT_TRUE(student.getEgzamRez() > 0 && student.getEgzamRez() <= 10);
    
    for (int grade : student.getTarpRez()) {
        EXPECT_TRUE(grade >= 0 && grade <= 10);
    }
}

// Test calculating final grade using average
TEST(StudentasClassTest, CalculateFinalGradeWithAverage) {
    StudentasClass student;
    student.pridetiTarpRez(6);
    student.pridetiTarpRez(9);
    student.setEgzamRez(8);

    student.rastiGalutini(true); // Vidurkis
    EXPECT_DOUBLE_EQ(student.getGalutinis(), 7.8); // Vidurkis yra 7.5, tada (6+9)/2*0.4 + 8*0.6
}

// Test calculating final grade using median
TEST(StudentasClassTest, CalculateFinalGradeWithMedian) {
    StudentasClass student;
    student.pridetiTarpRez(6);
    student.pridetiTarpRez(9);
    student.setEgzamRez(8);

    student.rastiGalutini(false); // Mediana
    EXPECT_DOUBLE_EQ(student.getGalutinis(), 7.8); // Mediana yra 7.5, tada (7.5*0.4 + 8*0.6)
}

// Test passing status
TEST(StudentasClassTest, PassingGrade) {
    StudentasClass student;

    student.setEgzamRez(10);
    student.pridetiTarpRez(10);
    student.pridetiTarpRez(10);
    student.rastiGalutini();
    student.rastiIslaike();

    EXPECT_TRUE(student.arIslaike());

    student.setEgzamRez(1);
    student.setTarpRez(std::vector<int>{1, 1});
    student.rastiGalutini();
    student.rastiIslaike();

    EXPECT_FALSE(student.arIslaike());
}

// Test comparison
TEST(StudentasClassTest, Comparison) {
    StudentasClass student1, student2;
    
    student1.setVardas("Axel");
    student1.setPavarde("Smithson");
    student1.setEgzamRez(8);

    student2.setVardas("Bob");
    student2.setPavarde("Johnson");
    student2.setEgzamRez(6);

    // Pagal vardą
    EXPECT_FALSE(student1.compare(student2, 0));
    
    // Pagal pavardę
    EXPECT_TRUE(student1.compare(student2, 1));
    
    // Pagal galutinį balą
    EXPECT_TRUE(student1.compare(student2, 2));
}

// Test clear method
TEST(StudentasClassTest, ClearData) {
    StudentasClass student("Jonas", "Jonaitis");
    student.pridetiTarpRez(6);
    student.pridetiTarpRez(9);
    student.setEgzamRez(8);

    student.clear();

    EXPECT_EQ(student.getVardas(), "");
    EXPECT_EQ(student.getPavarde(), "");
    EXPECT_EQ(student.getTarpRez().size(), 0);
    EXPECT_EQ(student.getEgzamRez(), 0);
}

// Google Test runner
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}