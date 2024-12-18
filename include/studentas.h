#ifndef STUDENTAS_H_INCLUDED
#define STUDENTAS_H_INCLUDED

#include "lib.h"

/**
 * @brief Abstract father class for StudentasClass
 * 
 */

class Human {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    virtual ~Human() = 0;

    // Visiškai virtualūs metodai
    /**
     * @brief Set the First Name object
     * 
     * @param vardas 
     */
    virtual void setVardas(const std::string& vardas) = 0;
    /**
     * @brief Set the Last Name object
     * 
     * @param pavarde 
     */
    virtual void setPavarde(const std::string& pavarde) = 0;

    /**
     * @brief Get the First Name object
     * 
     * @return const std::string& 
     */
    virtual const std::string& getVardas() const = 0;
    /**
     * @brief Get the Last Name object
     * 
     * @return const std::string& 
     */
    virtual const std::string& getPavarde() const = 0;
};

inline Human::~Human() {}

/**
 * @brief Student data processing
 * 
 */

class StudentasClass : public Human{
private:
    std::vector<int> tarpRez_;
    int egzamRez_;
    double vidurkis_;
    double mediana_;
    double galutinis_;
    bool islaike_;

    // Privatūs pagalbiniai metodai
    void rastiVid();
    void rastiMed();
    void rastiRez();

public:
    /**
     * @brief Construct a new Studentas Class object
     * 
     */

    // Default konstruktorius
    StudentasClass() : 
        Human(),
        egzamRez_(0), 
        vidurkis_(0.0), 
        mediana_(0.0), 
        galutinis_(0.0),
        islaike_(false) {}
    
    /**
     * @brief Construct a new Studentas Class object
     * 
     * @param vardas 
     * @param pavarde 
     */

    // Parametrizuotas konstruktorius
    StudentasClass(const std::string& vardas, const std::string& pavarde) : 
        Human(), 
        egzamRez_(0), 
        vidurkis_(0.0), 
        mediana_(0.0), 
        galutinis_(0.0),
        islaike_(false) {
            this->setVardas(vardas);
            this->setPavarde(pavarde);
        }

    /**
     * @brief Destroy the Studentas Class object
     * 
     */

    ~StudentasClass(){
        tarpRez_.clear();
    };

    /**
     * @brief Construct a new Studentas Class object by copying data
     * 
     * @param other 
     */

    // Copy konstruktorius
    StudentasClass(const StudentasClass& other) : Human() {
        this->setVardas(other.getVardas());
        this->setPavarde(other.getPavarde());
        tarpRez_ = other.tarpRez_;
        egzamRez_ = other.egzamRez_;
        vidurkis_ = other.vidurkis_;
        mediana_ = other.mediana_;
        galutinis_ = other.galutinis_;
        islaike_ = other.islaike_;
    }

    /**
     * @brief Construct a new Studentas Class object by assigning data
     * 
     * @param other 
     * @return StudentasClass& 
     */

    // Copy assignment konstruktorius
    StudentasClass& operator=(const StudentasClass& other) {
        if (this != &other) {  // Apsauga nuo savęs priskyrimo
            vardas_ = other.vardas_;
            pavarde_ = other.pavarde_;
            tarpRez_ = other.tarpRez_;
            egzamRez_ = other.egzamRez_;
            vidurkis_ = other.vidurkis_;
            mediana_ = other.mediana_;
            galutinis_ = other.galutinis_;
            islaike_ = other.islaike_;
        }
        return *this;
    }

    // Get'eriai
    /**
     * @brief Get the First Name object
     * 
     * @return const std::string& 
     */
    const std::string& getVardas() const override { return vardas_; }
    /**
     * @brief Get the Last Name object
     * 
     * @return const std::string& 
     */
    const std::string& getPavarde() const override { return pavarde_; }
    /**
     * @brief Get the Intermediate Grades object
     * 
     * @return const std::vector<int>& 
     */
    const std::vector<int>& getTarpRez() const { return tarpRez_; }
    /**
     * @brief Get the Exam Grade object
     * 
     * @return int 
     */
    int getEgzamRez() const { return egzamRez_; }
    /**
     * @brief Get the Grade Average object
     * 
     * @return double 
     */
    double getVidurkis() const { return vidurkis_; }
    /**
     * @brief Get the Grade Median object
     * 
     * @return double 
     */
    double getMediana() const { return mediana_; }
    /**
     * @brief Get the Final Grade object
     * 
     * @return double 
     */
    double getGalutinis() const { return galutinis_; }
    
    // Set'eriai
    /**
     * @brief Set the First Name object
     * 
     * @param vardas 
     */
    void setVardas(const std::string& vardas) override { vardas_ = vardas; }
    /**
     * @brief Set the Last Name object
     * 
     * @param pavarde 
     */
    void setPavarde(const std::string& pavarde) override { pavarde_ = pavarde; }
    /**
     * @brief Set the Exam Grade object
     * 
     * @param rez 
     */
    void setEgzamRez(int rez) { egzamRez_ = rez; rastiGalutini(); }
    /**
     * @brief Set the Intermediate Grades object
     * 
     * @param naujiTarpRez 
     */
    void setTarpRez(const std::vector<int>& naujiTarpRez);
    
    // Metodai
    /**
     * @brief Add a Single Intermediate Grade
     * 
     * @param rez 
     */
    void pridetiTarpRez(int rez);
    /**
     * @brief Generate random Intermediate Grades and Exam Grade
     * 
     * @param kiekBalu 
     */
    void generuotiBalus(int kiekBalu = 15);
    /**
     * @brief Calculate the Final Grade
     * 
     * @param naudotiVidurki 
     */
    void rastiGalutini(bool naudotiVidurki = true);
    /**
     * @brief Remove the last Intermediate Grade and replace it with Exam Grade
     * 
     */
    void isimtiGalutini();
    /**
     * @brief Remove all saved data
     * 
     */
    void clear();
    /**
     * @brief Update Passing Grade boolean islaike
     * 
     */
    void rastiIslaike(){ islaike_ = (galutinis_ >= 5.0); }
    /**
     * @brief Recheck and return Passing Grade boolean
     * 
     * @return true 
     * @return false 
     */
    bool arIslaike() const { return islaike_; }
    /**
     * @brief Compares Students either by First Name, Last Name or Final Grade
     * 
     * @param b 
     * @param criteria 
     * @return true 
     * @return false 
     */
    bool compare(const StudentasClass& b, int criteria = 2);
    std::ostream& printInfo(std::ostream& os) const;

    //Friend'ai įvedimo ir išvedimo operacijoms
    friend std::istream& operator>>(std::istream& is, StudentasClass& s);
    friend std::ostream& operator<<(std::ostream& os, const StudentasClass& s);
};


// Pre-v1.0, ne member metodai darbui su klase Studentas
/**
 * @brief Lets the user manually input Student data into a Vector
 * 
 * @param studentai Vector of Students
 * @param studSk Number of Students
 */
void inputManual(std::vector<StudentasClass> &studentai, int studSk);
/**
 * @brief Lets the user manually input Student data into a List
 * 
 * @param studentaiList List of Students
 * @param studSk Number of Students
 */
void inputManualList(std::list<StudentasClass> &studentaiList, int studSk);
/**
 * @brief Reads Student data from a File
 * 
 * @param studentai 
 * @param failoPav 
 */
void inputScan(std::vector<StudentasClass> &studentai, std::string failoPav);
/**
 * @brief Outputs Student data from nanual user input and displays the Grade Average or Median
 * 
 * @param Lok 
 * @param vidMed Grade Average or Median
 */
void outputManual(StudentasClass Lok, int vidMed);
/**
 * @brief Outputs Student data into a summary File
 * 
 * @param studentai 
 */
void outputScan(std::vector<StudentasClass> &studentai);
/**
 * @brief Randomly generates Student data
 * 
 * @param studGenSk Number of students
 * @param ndGenSk Number of homework grades
 */
void generateEntries(int studGenSk, int ndGenSk);
/**
 * @brief Intermediate function for choosing vector or list containers
 * 
 * @param failoPav Name of file containing Student data
 * @param rusiavKateg Sorting by First name, Last name or Final grade
 * @param useVector 
 * @param testStrat Sorting methodology option
 */
void inputSplitSort(std::string failoPav, int rusiavKateg, int useVector, int testStrat);
/**
 * @brief Processes Student data
 * 
 * @tparam Container Vector or list
 * @param failoPav Name of file containing Student data
 * @param rusiavKateg Sorting by First name, Last name or Final grade
 * @param testStrat Sorting methodology option
 */
void inputSplitSortImpl(std::string failoPav, int rusiavKateg, int testStrat);

#endif