CREATE TABLE MAJOR
{
    MajorName CHAR(20),
    NoOfCreditHours INT,
    PRIMARY KEY (MajorName)
};

CREATE TABLE STUDENT
{
    StudentId INT,
    StudentName CHAR(10),
    MajorName CHAR(20),
    PRIMARY KEY (StudentId),
    FOREIGN KEY (MajorName) REFERENCES MAJOR(MajorName)
};