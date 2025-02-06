#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp> // Bibliotheque JSON de nlohmann

using namespace std;

using json = nlohmann::json; //Uitlisation de la bibliotheque JSON de nlohmann

// Fonction pour afficher les informations du fichier .uproject
void showInfos(const std::string& UprojectPath) {
    std::ifstream file(UprojectPath);
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << UprojectPath << std::endl;
        return;
    }

    json project;
    file >> project;

    std::cout << "Nom du jeu : " << project["FileDescription"]["ProjectName"] << std::endl;
    //std::cout << "Version Unreal Engine : " << project["EngineAssociation"]["Version"] << std::endl;
    std::cout << "Version Unreal Engine : " << project["EngineAssociation"] << std::endl;
    if (project["EngineAssociation"]["FromSource"]) {
        std::cout << "Version : From Source" << std::endl; 
    }
    
    std::cout << "Plugins utilisés :" << std::endl;
    for (const auto& Plugin : project["Plugins"]) {
        std::cout << " - " << Plugin["Name"] << std::endl;
    }
}

// Fonction pour compiler le projet via UBT
void buildProject(const std::string& uprojectPath) {
    std::string command = "Build.bat MyProjectEditor Win64 Development";
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Erreur lors de la compilation !" << std::endl;
    } else {
        std::cout << "Compilation réussie !" << std::endl;
    }
}

// Fonction pour packager le projet via UAT
void packageProject(const std::string& uprojectPath, const std::string& packagePath) {
    std::string command = "RunUAT.bat BuildCookRun -project=" + uprojectPath + 
                          " -noP4 -platform=Win64 -clientconfig=Shipping -serverconfig=Shipping -cook -allmaps -stage -archive -archivedirectory=" + packagePath;
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Erreur lors du packaging !" << std::endl;
    } else {
        std::cout << "Packaging réussi !" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // Vérification du nombre d'arguments
    /*if (argc < 3) {
        std::cerr << "Usage : MyTool [CHEMIN DU UPROJECT] <commande> [arguments]" << std::endl;
        std::cerr << "Commandes possibles :" << std::endl;
        std::cerr << "  show-infos" << std::endl;
        std::cerr << "  build" << std::endl;
        std::cerr << "  package [CHEMIN DU PACKAGE]" << std::endl;
        return 1;
    }

    std::string uprojectPath = argv[1];
    std::string action = argv[2];

    if (action == "show-infos") {
        showInfos(uprojectPath);
    } else if (action == "build") {
        buildProject(uprojectPath);
    } else if (action == "package") {
        if (argc < 4) {
            std::cerr << "Erreur : chemin du package manquant pour la commande package." << std::endl;
            return 1;
        }
        std::string packagePath = argv[3];
        packageProject(uprojectPath, packagePath);
    } else {
        std::cerr << "Commande inconnue : " << action << std::endl;
        return 1;
    }*/

    std::cout << "Bonjour !" << std::endl;
    std::cout << "Ce programme permet de manipuler des projets Unreal Engine." << std::endl;

    std::cout << "Entrez le chemin du fichier .uproject :" << std::endl;
    std::string uprojectPath;
    std::getline(std::cin, uprojectPath);

    std::cout << "Quelle commande souhaitez-vous utiliser ?" << std::endl;
    std::cout << "0 : show-infos" << std::endl;
    std::cout << "1 : build" << std::endl;
    std::cout << "2 : package" << std::endl;
    
    std::string action;
    std::getline(std::cin, action);

    if (action == "0") {
        showInfos(uprojectPath);
    } else if (action == "1") {
        buildProject(uprojectPath);
    } else if (action == "2") {
        std::cout << "Entrez le chemin du package :" << std::endl;
        std::string packagePath;
        std::getline(std::cin, packagePath);
        packageProject(uprojectPath, packagePath);
    } else {
        std::cerr << "Commande inconnue : " << action << std::endl;
    }

    return 0;
}

// C:\Users\shola\RiderProjects\ToolingApp\ToolingApp\TestProject.uproject
