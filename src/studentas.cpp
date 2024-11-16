#include "lib.h"
#include "studentas.h"

double mediana(std::vector<int> &v){
    size_t n = v.size();
    sort(v.begin(), v.end());
    if (n % 2 == 0) { //dviejų vidurinių variacinės eilutės skaičių vidurkis
        return (v[n/2 - 1] + v[n/2]) / 2.0;
    } else {
        return v[n/2];
    }
}

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
        
        std::string vardas, pavarde;
        iss >> pavarde >> vardas;
        stud.setPavarde(pavarde);
        stud.setVardas(vardas);

        std::vector<int> tarpRez;
        int balas;
        while (iss >> balas) {
            tarpRez.push_back(balas);
        }

        if (!tarpRez.empty()) {
            stud.setEgzamRez(tarpRez.back());
            tarpRez.pop_back();
            stud.setTarpRez(tarpRez);
        }

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