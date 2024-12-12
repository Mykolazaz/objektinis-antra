#include "lib.h"
#include "studentas.h"

/**
 * @brief Tracks time for run-time measurements
 * 
 */

class Timer {
  private:
    using hrClock = std::chrono::high_resolution_clock;
    using durationDouble = std::chrono::duration<double>;
    std::chrono::time_point<hrClock> start;
  public:
    Timer() : start{ hrClock::now() } {};
    void reset() {
      start = hrClock::now();
    }
    double elapsed() const {
      return durationDouble (hrClock::now() - start).count();
    }
};

/**
 * @brief Generates student data
 * 
 * @param studGenSk Number of students
 * @param ndGenSk Number of homework grades
 */

void generateEntries(int studGenSk, int ndGenSk){
    std::cout << "Failo generavimas pradėtas..." << "\n";

    std::string failoPav = "info" + std::to_string(studGenSk) + ".txt";
    std::ofstream fw(failoPav, std::ios::binary);

    studGenSk += 1;
    ndGenSk += 1;

    Timer generLaikas;

    std::stringstream buffer;

    buffer << std::left << std::setw(15) << "Pavarde" << std::setw(15) << "Vardas";
    
    for (int i = 1; i < ndGenSk; i++){
        buffer << "ND" << std::setw(2) << std::left << i << " ";
    }

    buffer << std::setw(10) << "Egzaminimas" << "\n";
    
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 10);

    for (int i = 1; i < studGenSk; i++){
        buffer << std::left << std::setw(15) << ("Pavarde"+std::to_string(i))
        << std::setw(15) << ("Vardas"+std::to_string(i));
        
        for (int j = 1; j < ndGenSk; j++){
            buffer << std::setw(5) << dist(mt);    
        }

        buffer << std::setw(10) << dist(mt) << "\n";

        if (buffer.tellp() > 64 * 1024 * 1024) {
            fw << buffer.rdbuf();
            buffer.str("");
            buffer.clear();
        }
    }

    fw << buffer.rdbuf();
    
    fw.close();

    std::cout << std::to_string(studGenSk-1) + " įrašų generavimas: " << generLaikas.elapsed() << "\n";
    std::cout << "Failo generavimas baigtas." << "\n";
}

/**
 * @brief Processes student data
 * 
 * @tparam Container Vector or list
 * @param failoPav Name of file containing student data
 * @param rusiavKateg Sorting by first name, last name or final grade
 * @param testStrat Sorting methodology option
 */

template <typename Container>
void inputSplitSortImpl(std::string failoPav, int rusiavKateg, int testStrat) {
    Timer bendrLaikas;

    // Failo nuskaitymo pradžia
    Timer uzdLaikas;

    failoPav = failoPav + ".txt";
    std::ifstream fr(failoPav);
    std::string eilute;
    std::getline(fr, eilute);

    Container visiStudentai;
    if constexpr (std::is_same_v<Container, std::vector<StudentasClass>>) {
        visiStudentai.reserve(1000000);
    }

    while (std::getline(fr, eilute)) {
        std::istringstream iss(eilute);
        StudentasClass stud;
        
        iss >> stud;

        visiStudentai.push_back(stud);
    }

    if constexpr (std::is_same_v<Container, std::vector<StudentasClass>>) {
        visiStudentai.shrink_to_fit();
    }

    fr.close();

    // Failo nuskaitymo pabaiga
    std::cout << "Įrašų nuskaitymas: " << uzdLaikas.elapsed() << "\n";

    // Visų studentų rikiavimo pradžia
    uzdLaikas.reset();

    auto sortFunction = [rusiavKateg](StudentasClass &a, StudentasClass &b) {
        return a.compare(b, rusiavKateg);
    };

    if constexpr (std::is_same_v<Container, std::vector<StudentasClass>>) {
        std::sort(visiStudentai.begin(), visiStudentai.end(), sortFunction);
    } else {
        visiStudentai.sort(sortFunction);
    }

    // Visų studentų rikiavimo pabaiga
    std::cout << "Įrašų rikiavimas (sort f-ja) mažėjimo tvarka: " << uzdLaikas.elapsed() << "\n";

    // Studentų dalijimo pradžia
    uzdLaikas.reset();

    Container protingi, kvaili;

    switch (testStrat) {
        // Studentai skaidomi į du naujus to paties tipo konteinerius
        case 1: {
            for (const auto &student : visiStudentai) {
                if (student.arIslaike()) {
                    protingi.push_back(student);
                } else {
                    kvaili.push_back(student);
                }
            }
            visiStudentai.clear();

            // Studentų dalijimo pabaiga (1)
            std::cout << "Įrašų dalijimas į 'protingus' ir 'kvailus': " << uzdLaikas.elapsed() << "\n";
            
            break;
        }

        // Studentai skaidomi panaudojant tik vieną naują konteinerį
        case 2: {
            auto it = visiStudentai.begin();
            while (it != visiStudentai.end()) {
                if (!it->arIslaike()) {
                    kvaili.push_back(*it);
                    it = visiStudentai.erase(it);
                } else {
                    ++it;
                }
            }

            // Studentų dalijimo pabaiga (2)
            std::cout << "Įrašų dalijimas į 'visiStudentai' ir 'kvailus': " << uzdLaikas.elapsed() << "\n";

            break;
        }

        // Studentai apdorojami greičiausiu metodu naudojant numatytuosius algoritmus
        case 3: {
            auto iter = std::stable_partition(visiStudentai.begin(), visiStudentai.end(),
                [](const StudentasClass &s) { return s.arIslaike(); });
            
            kvaili.insert(kvaili.end(), iter, visiStudentai.end());
            visiStudentai.erase(iter, visiStudentai.end());

            // Studentų dalijimo pabaiga (3)
            std::cout << "Įrašų dalijimas į 'protingus' ir 'kvailus': " << uzdLaikas.elapsed() << "\n";
            
            break;
        }
    }

    // "Protingų" studentų rašymo pradžia
    uzdLaikas.reset();
    
    std::string failasProtingi = "protingi.txt";
    std::ofstream fwProtingi(failasProtingi);
    
    fwProtingi << std::left << std::setw(20) << "Pavarde"
               << std::setw(20) << "Vardas" << std::setw(20) << "Galutinis (vid.)" << "\n";
    fwProtingi << "-------------------------------------------------------" << "\n";

    if (testStrat == 2 || testStrat == 3) {
        for (const auto &student : visiStudentai) {
            fwProtingi << student;
        }
    } else {
        for (const auto &student : protingi) {
            fwProtingi << student;
        }
    }

    fwProtingi.close();
    protingi.clear();

    // "Protingų" studentų rašymo pabaiga
    std::cout << "'Protingų' studentų įrašų rašymas: " << uzdLaikas.elapsed() << "\n";

    // "Kvailų" studentų rašymo pradžia
    uzdLaikas.reset();

    std::string failasKvaili = "kvaili.txt";
    std::ofstream fwKvaili(failasKvaili);

    fwKvaili << std::left << std::setw(20) << "Pavarde"
             << std::setw(20) << "Vardas" << std::setw(20) << "Galutinis (vid.)" << "\n";
    fwKvaili << "-------------------------------------------------------" << "\n";

    for (const auto &student : kvaili) {
        fwKvaili << student;
    }

    fwKvaili.close();
    kvaili.clear();

    // "Kvailų" studentų rašymo pabaiga
    std::cout << "'Kvailų' studentų įrašų rašymas: " << uzdLaikas.elapsed() << "\n" << "\n";

    std::cout << "Bendras veikimo laikas be generavimo: " << bendrLaikas.elapsed() << "\n" << "\n";
}

/**
 * @brief Intermediate function for choosing vector or list containers
 * 
 * @param failoPav Name of file containing student data
 * @param rusiavKateg Sorting by first name, last name or final grade
 * @param useVector 
 * @param testStrat Sorting methodology option
 */

void inputSplitSort(std::string failoPav, int rusiavKateg, int useVector, int testStrat) {
    if (useVector == 1) {
        inputSplitSortImpl<std::vector<StudentasClass>>(failoPav, rusiavKateg, testStrat);
    } else {
        inputSplitSortImpl<std::list<StudentasClass>>(failoPav, rusiavKateg, testStrat);
    }
}