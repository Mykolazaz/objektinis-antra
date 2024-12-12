#include "lib.h"
#include "studentas.h"

// Class'ės Studentas metodų realizacijos
// Privatūs member metodai
void StudentasClass::rastiVid() {
    vidurkis_ = tarpRez_.empty() ? 0.0 : 
                accumulate(tarpRez_.begin(), tarpRez_.end(), 0.0) / tarpRez_.size();
}

void StudentasClass::rastiMed() {
    if (tarpRez_.empty()) {
        mediana_ = 0.0;
        return;
    }
    
    std::vector<int> sorted = tarpRez_;
    sort(sorted.begin(), sorted.end());
    size_t n = sorted.size();
    mediana_ = (n % 2 == 0) ? 
                (sorted[n/2 - 1] + sorted[n/2]) / 2.0 : 
                sorted[n/2];
}

void StudentasClass::rastiRez() {
    rastiVid();
    rastiMed();
}

// Vieši member metodai
void StudentasClass::setTarpRez(const std::vector<int>& naujiTarpRez) {
    tarpRez_ = naujiTarpRez;
    rastiRez();
    rastiGalutini();
}

void StudentasClass::pridetiTarpRez(int rez) {
    tarpRez_.push_back(rez);
    rastiRez();
    rastiGalutini();
}

void StudentasClass::generuotiBalus(int kiekBalu) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 10);

    egzamRez_ = dist(mt);
    tarpRez_.clear();
    tarpRez_.reserve(kiekBalu);
    
    for (int i = 0; i < kiekBalu; i++) {
        tarpRez_.push_back(dist(mt));
    }
    
    rastiRez();
    rastiGalutini();
    rastiIslaike();
}

void StudentasClass::rastiGalutini(bool naudotiVidurki) {
    galutinis_ = naudotiVidurki ? 
                0.4 * vidurkis_ + 0.6 * egzamRez_ :
                0.4 * mediana_ + 0.6 * egzamRez_;
    rastiIslaike();
}

void StudentasClass::isimtiGalutini() {
    if (!tarpRez_.empty()) {
        egzamRez_ = tarpRez_.back();
        tarpRez_.pop_back();
    }
}

void StudentasClass::clear() {
    vardas_.clear();
    pavarde_.clear();
    tarpRez_.clear();
    egzamRez_ = 0;
    vidurkis_ = 0.0;
    mediana_ = 0.0;
    galutinis_ = 0.0;
}

bool StudentasClass::compare(const StudentasClass& b, int criteria) {
    switch (criteria) {
        case 0:
            return this->vardas_ > b.vardas_;
        case 1:
            return this->pavarde_ > b.pavarde_;
        case 2:
            return this->galutinis_ > b.galutinis_;
        default:
            return this->galutinis_ > b.galutinis_;
    }
}

std::ostream& StudentasClass::printInfo(std::ostream& os) const {
        os << std::left << std::setw(20) << pavarde_ << std::setw(20) << vardas_ 
        << std::setw(20) << std::setprecision(2) << std::fixed << galutinis_ << "\n";
        return os;
}

std::istream& operator>>(std::istream& is, StudentasClass& s) {
    std::string vardas, pavarde;
    
    is >> vardas >> pavarde;
    s.setVardas(vardas);
    s.setPavarde(pavarde);

    int balas;
    while (is >> balas) {
        s.pridetiTarpRez(balas);
    }

    s.isimtiGalutini();

    s.rastiGalutini();
    return is;
}

std::ostream& operator<<(std::ostream& os, const StudentasClass& s) {
    return s.printInfo(os);
}

// Ne member metodai darbui su klase Studentas
void inputManual(std::vector<StudentasClass> &studentai, int studSk){
    for (int i=0; i<studSk; i++){
        int arRandom;
        std::string input;
        bool praeitasBuvoTuscias = false;
        StudentasClass stud;

        std::cout << "Ar atsitiktinai generuoti sekančio studento balus? (0 arba 1):" << "\n";
        std::cin >> arRandom;

        std::string vardas, pavarde;
        int egzamRez;

        std::cout << "Įveskite studento vardą ir pavardę:" << "\n";
        std::cin >> vardas >> pavarde;
        
        stud.setVardas(vardas);
        stud.setPavarde(pavarde);
        
        if (arRandom == 0){
            std::cout << "Įveskite egzamino rezultatą: " << "\n";
            std::cin >> egzamRez;
            stud.setEgzamRez(egzamRez);

            std::cout << "Į vieną eilutę įveskite tarpinius rezultatus (2 ENTER paspausdimai stabdo įvedimą):" << "\n";

            while (true) {
                std::getline(std::cin, input);

                if (input.empty()) {
                    if (praeitasBuvoTuscias) {
                        break;
                    }
                    praeitasBuvoTuscias = true;
                } else {
                    praeitasBuvoTuscias = false;

                    std::stringstream ss(input);
                    int skaicius;
                    
                    while (ss >> skaicius) {
                        stud.pridetiTarpRez(skaicius);
                    }
                }
            }
        } else {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist(0, 10);

            stud.setEgzamRez(dist(mt));
            for (int index = 0; index < 15; index++){
                stud.pridetiTarpRez(dist(mt));
            }
        }
        studentai.push_back(stud);
        stud.clear();
    }
}

void inputManualList(std::list<StudentasClass> &studentaiList, int studSk){
    for (int i=0; i<studSk; i++){
        int arRandom;
        std::string input;
        bool praeitasBuvoTuscias = false;
        StudentasClass stud;

        std::cout << "Ar atsitiktinai generuoti sekančio studento balus? (0 arba 1):" << "\n";
        std::cin >> arRandom;

        std::string vardas, pavarde;
        int egzamRez;

        std::cout << "Įveskite studento vardą ir pavardę:" << "\n";
        std::cin >> vardas >> pavarde;
        
        stud.setVardas(vardas);
        stud.setPavarde(pavarde);
        
        if (arRandom == 0){
            std::cout << "Įveskite egzamino rezultatą: " << "\n";
            std::cin >> egzamRez;
            stud.setEgzamRez(egzamRez);

            std::cout << "Į vieną eilutę įveskite tarpinius rezultatus (2 ENTER paspausdimai stabdo įvedimą):" << "\n";

            while (true) {
                std::getline(std::cin, input);

                if (input.empty()) {
                    if (praeitasBuvoTuscias) {
                        break;
                    }
                    praeitasBuvoTuscias = true;
                } else {
                    praeitasBuvoTuscias = false;

                    std::stringstream ss(input);
                    int skaicius;
                    
                    while (ss >> skaicius) {
                        stud.pridetiTarpRez(skaicius);
                    }
                }
            }
        } else {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist(0, 10);

            stud.setEgzamRez(dist(mt));
            for (int index = 0; index < 15; index++){
                stud.pridetiTarpRez(dist(mt));
            }
        }
        studentaiList.push_back(stud);
        stud.clear();
    }
}

void inputScan(std::vector<StudentasClass> &studentai, std::string failoPav) {
    std::cout << "Failo apdorojimas pradėtas..." << "\n";
    
    failoPav = failoPav + ".txt";
    std::ifstream fr(failoPav);

    std::string eilute;

    std::getline(fr, eilute);

    while (std::getline(fr, eilute)) {
        std::istringstream iss(eilute);
        StudentasClass stud;
        
        iss >> stud;

        studentai.push_back(stud);
    }

    fr.close();
}

void outputManual(StudentasClass stud, int vidMed){
    if(vidMed == 0){
        std::cout << std::left << std::setw(20) << stud.getPavarde()
        << std::setw(20) << stud.getVardas() << std::setw(20)<< std::setprecision(2) << std::fixed <<
        stud.getVidurkis() << "\n";
    } else {
        std::cout << std::left << std::setw(20) << stud.getPavarde()
        << std::setw(20) << stud.getVardas() << std::setw(20) << std::setprecision(2) << std::fixed <<
        stud.getMediana() << "\n";
    }
    
}

void outputScan(std::vector<StudentasClass> &studentai){
    std::sort(studentai.begin(), studentai.end(), 
              [](const StudentasClass &a, const StudentasClass &b) {
                  return a.getPavarde() < b.getPavarde();
              });
    
    std::ofstream fw("kursiokai_bendra.txt");

    fw << std::left << std::setw(20) << "Pavarde" << std::setw(20) << "Vardas" << std::setw(20) << "Galutinis (Vid.)" << std::setw(20) << "Galutinis (Med.)" << "\n";
    fw << "---------------------------------------------------------------------------" << "\n";

    for (const StudentasClass &stud : studentai){
        try {
            if (stud.getVidurkis() == 0) {
                throw std::runtime_error("Nepakankamai įvertinimų studentui " + stud.getVardas() + " " + stud.getPavarde() + ".");
            }

            std::vector<int> visiRez = stud.getTarpRez();
            visiRez.push_back(stud.getEgzamRez());

            fw << std::left << std::setw(20) << stud.getPavarde() << std::setw(20) << stud.getVardas() << std::setw(20) << std::setprecision(2) << std::fixed <<
            stud.getVidurkis() << std::setw(20) << std::setprecision(2) << std::fixed << stud.getMediana() << "\n";
        }

        catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << "\n";
        exit(EXIT_FAILURE);
        }
    }
    std::cout << "Pasirinktas failas nuskaitytas ir studentai surikiuoti pagal pavardes." << "\n";
    fw.close();
}