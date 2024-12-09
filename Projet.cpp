#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <regex>
#include <stdexcept>
#include <limits>
#include <iomanip>

using namespace std;

// Validation des chaînes de caracteres (lettres uniquement)
bool Valid(const string& val) {
    return !val.empty() && regex_match(val, regex("^[A-Za-z ]+$"));
}

// Validation de la date au format JJ/MM/AAAA
bool validerDate(const string& date) {
    regex pattern("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\\d{4}$");
    return regex_match(date, pattern);
}

// Exception personnalisee pour la validation
class ValidationException : public exception {
    string message;
public:
    explicit ValidationException(const string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class Patient {
protected:
    string nom;
    int age;
    string historiqueMedical;

public:
    // Constructeur avec validation
    Patient(string n = "Invalide", int a = 1, string hist = "Invalide") : nom(n), age(a), historiqueMedical(hist) {
        if (!Valid(n)) throw ValidationException("Nom invalide ! Le nom doit contenir uniquement des lettres.");
        if (a <= 0 || a > 150) throw ValidationException("Age invalide ! L'age doit etre entre 1 et 150.");
        if (!Valid(hist)) throw ValidationException("Historique invalide ! L'historique doit contenir uniquement des lettres.");
    }

    // Getters 
    string getNom() const { return nom; }
    int getAge() const { return age; }
    string getHistoriqueMedical() const { return historiqueMedical; }

    // Setters
    void setNom(const string& n) {
        if (n.empty() || !Valid(n)) throw ValidationException("Nom invalide ! Le nom ne peut pas etre vide.");
        nom = n;
    }

    void setAge(int a) {
        if (a <= 0 || a > 150) throw ValidationException("Age invalide ! L'age doit etre entre 1 et 150.");
        age = a;
    }

    void setHistoriqueMedical(const string& hist) {
        if (hist.empty() || !Valid(hist)) throw ValidationException("Historique invalide ! L'historique ne peut pas etre vide.");
        historiqueMedical = hist;
    }

    // Affichage des informations du patient
    virtual void affiche() const {
        cout << endl;
        cout << left << setw(20) << "Nom"
            << setw(10) << "Age"
            << setw(30) << "Historique Medical" << endl;
        cout << string(60, '-') << endl;
        cout << left << setw(20) << nom
            << setw(10) << age
            << setw(30) << historiqueMedical << endl;
        cout << string(60, '-') << endl;
    }

    virtual ~Patient() = default;
};

class TabPatient {
private:
    vector <Patient> Pat;

public:
    // Ajouter un patient
    void ajouterPatient(const Patient& p) {
        Pat.push_back(p);
        cout << endl;
        cout << "\033[1;32mPatient Ajoute avec succes !\033[0m" << endl;
    }

    // Afficher tous les patients
    void afficheTab() const {
        cout << endl;
        cout << left << setw(20) << "Nom"
            << setw(10) << "Age"
            << setw(30) << "Historique Medical" << endl;
        cout << string(60, '-') << endl;
        for (const auto& p : Pat) {
            cout << left << setw(20) << p.getNom()
                << setw(10) << p.getAge()
                << setw(30) << p.getHistoriqueMedical() << endl;
        }
        cout << string(60, '-') << endl;
        cout << endl;
        cout << "Nombre des Patients : " << nombrePatients() << endl;
    }

    // Recherche d'un patient par nom
    Patient* rechercherParNom(const string& nom) {
        for (auto& p : Pat) {
            if (p.getNom() == nom) {
                return &p;
            }
        }
        cout << "\n Aucun Patient Trouve !" << endl;
        return nullptr;
    }

    // Supprimer un patient par nom
    void supprimerParNom(const string& nomSuppression) {
        auto it = remove_if(Pat.begin(), Pat.end(), [&](const Patient& p) {
            return p.getNom() == nomSuppression;
            });
        Pat.erase(it, Pat.end());
    }

    // Nombre de patients
    size_t nombrePatients() const {
        return Pat.size();
    }
};

class Enfant : public Patient {
    string tuteur;
    string classeScolaire;

public:
    Enfant(string n, int a, string hist, string t, string c)
        : Patient(n, a, hist), tuteur(t), classeScolaire(c) {
    }

    void affiche() const override {
        Patient::affiche();
        cout << left << setw(20) << "Tuteur"
            << setw(30) << "Classe Scolaire" << endl;
        cout << string(60, '-') << endl;
        cout << left << setw(20) << tuteur
            << setw(30) << classeScolaire << endl;
        cout << string(60, '-') << endl;
    }
};

class Adulte : public Patient {
    string CIN;
public:
    Adulte(string n, int a, string hist, string c) : Patient(n, a, hist), CIN(c) {}

    void affiche() const override {
        Patient::affiche();
        cout << left << setw(20) << "CIN" << endl;
        cout << string(60, '-') << endl;
        cout << left << setw(20) << CIN << endl;
        cout << string(60, '-') << endl;
    }

};

class Medcin {
protected:
    string nomMedcin;
    string specialite;

public:
    Medcin(string n = "Invalide", string s = "Invalide") : nomMedcin(n), specialite(s) {
        if (!Valid(n)) throw ValidationException("Nom invalide ! Le nom du medecin ne peut pas etre vide.");
        if (!Valid(s)) throw ValidationException("Specialite invalide ! La specialite ne peut pas etre vide.");
    }
    // Getters
    string getNomMedcin() const { return nomMedcin; }
    string getSpecialite() const { return specialite; }

    //Seters
    void setNomMedcin(const string& n) {
        if (n.empty() || !Valid(n)) throw ValidationException("Nom invalide !");
        nomMedcin = n;
    }
    void setSpecialite(const string& s) {
        if (s.empty() || !Valid(s)) throw ValidationException("Specialite invalide !");
        specialite = s;
    }


    virtual void afficheMedcin() const {
        cout << left << setw(20) << "Nom"
            << setw(10) << "Specialite" << endl;
        cout << string(60, '-') << endl;
        cout << left << setw(20) << nomMedcin
            << setw(10) << specialite << endl;
        cout << string(60, '-') << endl;
    }
    virtual ~Medcin() = default;
};

class TabMedcin {
    vector<Medcin> Med;
public:
    void ajouteMedcin(const Medcin& m) {
        Med.push_back(m);
        cout << endl;
        cout << "\033[1;32mMedecin Ajoute avec succes !\033[0m" << endl;
    }
    void afficheTabMed() {
        cout << endl;
        cout << left << setw(20) << "Nom"
            << setw(10) << "Specialite" << endl;
        cout << string(60, '-') << endl;
        for (auto& m : Med) {
            cout << left << setw(20) << m.getNomMedcin()
                << setw(10) << m.getSpecialite() << endl;
        }
        cout << string(60, '-') << endl;
        cout << endl;
        cout << "Nombre des Medecins : " << nombreMedcins() << endl;
    }

    Medcin* rechercherMedcin(const string& nomRecherche) {
        for (auto& m : Med) {
            if (m.getNomMedcin() == nomRecherche) {
                return &m;
            }
        }
        return nullptr;
    }

    void supprimerMedcin(const string& nomSuppression) {
        auto it = remove_if(Med.begin(), Med.end(), [&](const Medcin& m) {
            return m.getNomMedcin() == nomSuppression;
            });
        Med.erase(it, Med.end());
    }

    size_t nombreMedcins() const {
        return Med.size();
    }

};
class RendezVous {
protected:
    Patient Pat;
    Medcin Med;
    string Date;

public:
    RendezVous(const Patient p, const Medcin m, string d) : Pat(p), Med(m), Date(d) {
        if (!validerDate(d)) throw ValidationException("Date invalide ! Veuillez respecter le format JJ/MM/AAAA.");
    }

    // Getters
    string getNomPat() const { return Pat.getNom(); }
    string getNomDoc() const { return Med.getNomMedcin(); }
    string getDate() const { return Date; }

    virtual void afficheRDV() const {
        cout << endl;
        cout << left << setw(20) << "Patient"
            << setw(10) << "Medecin"
            << setw(30) << "Date" << endl;
        cout << string(60, '-') << endl;
        cout << left << setw(20) << Pat.getNom()
            << setw(10) << Med.getNomMedcin()
            << setw(30) << Date << endl;
        cout << string(60, '-') << endl;
    }

    bool RechercheNom(const string& nom) const {
        return Pat.getNom() == nom || Med.getNomMedcin() == nom;
    }

    virtual ~RendezVous() = default;
};

class TabRendezVous {
    vector<RendezVous> tabRend;

public:
    void ajouteRendezVous(const RendezVous& v) {
        tabRend.push_back(v);
    }

    void afficheTabRendezVous() const {
        cout << left << setw(20) << "Patient"
            << setw(20) << "Medecin"
            << setw(20) << "Date" << endl;
        cout << string(60, '-') << endl;
        for (const auto& R : tabRend) {
            cout << left << setw(20) << R.getNomPat()
                << setw(20) << R.getNomDoc()
                << setw(20) << R.getDate() << endl;
        }
        cout << string(60, '-') << endl;
    }

    RendezVous* rechercherRendezVous(const string& nom) {
        for (auto& R : tabRend) {
            if (R.getNomPat() == nom) {
                return &R;
            }
        }
        cout << "\n Aucun Patient Trouve !" << endl;
        return nullptr;
    }

    void supprimerRendezVous(const string& nom) {
        bool trouve = false;
        for (auto it = tabRend.begin(); it != tabRend.end(); ++it) {
            if (it->getNomPat() == nom) {
                it = tabRend.erase(it);
                trouve = true;
                cout << endl;
                cout << "\033[1;31mRendez-vous du patient " << nom << " supprimé avec succes !\033[0m" << endl;
                break;
            }
        }

        if (!trouve) {
            cout << "\nAucun rendez-vous trouvé pour le patient " << nom << "." << endl;
        }
    }

    size_t NombreRendezVous() {
        return tabRend.size();
    }

    ~TabRendezVous() = default;
};


class RendezVousCritique : public RendezVous {
    int priorite;

public:
    RendezVousCritique(const Patient& p, const Medcin& m, string d, int pr)
        : RendezVous(p, m, d), priorite(pr) {
        if (pr < 1 || pr > 2) throw ValidationException("Priorite invalide ! La priorite doit etre entre 1 et 2.");
    }

    void afficheRDV() const override {
        RendezVous::afficheRDV();
        cout << left << setw(20) << "Priorite" << endl;
        cout << string(60, '-') << endl;
        cout << left << setw(20) << priorite << endl;
        cout << string(60, '-') << endl;
    }
};

// Classe representant le centre medical
class CentreMedical {
    vector<RendezVous*> rendezVous;
    vector<RendezVousCritique*> rendezVousUrgents;

public:
    void ajouterRendezVous(RendezVous* rdv) {
        rendezVous.push_back(rdv);
    }

    void ajouterRendezVousUrgent(RendezVousCritique* rdv) {
        rendezVousUrgents.push_back(rdv);
    }

    void afficherRendezVous() const {
        cout << "Rendez-vous normaux:" << endl;
        for (auto& rdv : rendezVous) {
            rdv->afficheRDV();
        }
        cout << "Rendez-vous urgents:" << endl;
        for (auto& rdvUrgent : rendezVousUrgents) {
            rdvUrgent->afficheRDV();
        }
    }
    ~CentreMedical() = default;
};

class InterfaceUtilisateur {
public:
    static void afficherTitre() {
        cout << "\033[1;36m";
        cout << string(80, '=') << endl;
        cout << string(20, ' ') << "Systeme de Gestion Medicale" << endl;
        cout << string(80, '=') << endl;
        cout << "\033[0m" << endl;
    }

    static void espaceTitre(const string& val) {
        cout << "\033[1;36m";
        cout << string(70, '=') << endl;
        cout << string((70 - val.size()) / 2, ' ') << val << endl;
        cout << string(70, '=') << endl;
        cout << "\033[0m" << endl;
    }

    static int menuPrincipal() {
        int choix;
        do {
            cout << "\033[1;33m";
            cout << "Choisissez un espace :\n";
            cout << endl;
            cout << "\033[1;32m[ 1 ]\033[0m Espace Patient\n";
            cout << "\033[1;32m[ 2 ]\033[0m Espace Medecin\n";
            cout << "\033[1;31m[ 0 ]\033[0m Quitter\n";
            cout << endl;
            cout << "Votre choix : ";
            cin >> choix;
        } while (choix < 0 || choix > 2);

        return choix;
    }

    static void Retour() {
        int choix;
        InterfaceUtilisateur::clearEcran();
        InterfaceUtilisateur::afficherTitre();
        choix = InterfaceUtilisateur::menuPrincipal();
    }

    static void clearEcran() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    static bool verifierMotDePasse() {
        string motpass;
        cout << "\033[1;98mVeuillez entrer votre mot de passe pour acceder : ";
        cin >> motpass;
        return motpass == "admin";
    }
};

class EspacePatient {
public:
    static void afficherMenu() {
        cout << endl;
        cout << string(20, '<') << " Menu Principal " << string(20, '>') << endl;
        cout << "\033[0m" << endl;
        cout << "\033[1;32m[ 1 ]\033[0m Consulter votre Donnees\n";
        cout << "\033[1;32m[ 2 ]\033[0m Consulter votre rendez-vous\n";
        cout << "\033[1;32m[ 3 ]\033[0m Annuler votre rendez-vous\n";
        cout << "\033[1;31m[ 0 ]\033[0m Exit\n";
        cout << endl;
        cout << "Votre choix : ";
    }

    static int gererEspace(bool val) {
        int choix;
        do {
            if (val) {
                InterfaceUtilisateur::clearEcran();
                InterfaceUtilisateur::espaceTitre("Bienvenue dans l'espace Patient");
            }
            afficherMenu();
            cin >> choix;
            if (choix == 0) { exit(0); }
            else if (choix >= 1 && choix <= 3) { return choix; }
            else { cout << "Choix invalide. Veuillez reessayer.\n"; }
        } while (true);
    }
};

class EspaceMedecin {
public:
    static void afficherMenu() {
        cout << endl;
        cout << string(20, '<') << " Menu Principal " << string(20, '>') << endl;
        cout << "\033[0m" << endl;
        cout << "\033[1;32m[ 1 ]\033[0m Ajouter un medecin\n";
        cout << "\033[1;32m[ 2 ]\033[0m Lister les medecins\n";
        cout << "\033[1;32m[ 3 ]\033[0m Comparer des patients\n";
        cout << "\033[1;32m[ 4 ]\033[0m Ajouter un patient\n";
        cout << "\033[1;32m[ 5 ]\033[0m Lister les patients\n";
        cout << "\033[1;32m[ 6 ]\033[0m Lister les rendez-vous\n";
        cout << "\033[1;31m[ 0 ]\033[0m Exit\n";
        cout << endl;
        cout << "Votre choix : ";
    }

    static int gererEspace(bool val) {
        if (val) {
            while (!InterfaceUtilisateur::verifierMotDePasse()) {
                cout << "\033[1;31mMot de passe incorrect ! Retour au menu principal.\033[0m\n";
            }
        }

        int choix;
        do {
            if (val) {
                InterfaceUtilisateur::clearEcran();
                InterfaceUtilisateur::espaceTitre("Bienvenue dans l'espace Medecin");
            }
            afficherMenu();
            cin >> choix;
            if (choix == 0) { exit(0); }
            else if (choix >= 1 && choix <= 6) { return choix; }
            else { cout << "Choix invalide. Veuillez reessayer.\n"; }
        } while (true);
    }
};


class Saisie {
public:
    // Fonction pour saisir les informations d'un patient
    static void saisirPatient(string* nom, int* age, string* hist) {
        cout << "Entrer le Nom du Patient : ";
        cin >> *nom;
        cout << "Entrer l'age du Patient : ";
        cin >> *age;
        cout << "Entrer l'historique du Patient : ";
        cin >> *hist;
    }

    // Fonction pour saisir les informations d'un médecin
    static void saisirMedecin(string* nom, string* spec) {
        cout << "Entrer le Nom du Medecin : ";
        cin >> *nom;
        cout << "Entrer Specialite du Medecin : ";
        cin >> *spec;
    }

    // Fonction pour saisir un nom 
    static string saisirNom() {
        string nom;
        cout << "Entrer Votre Nom : ";
        cin >> nom;
        return nom;
    }

    // Fonction pour saisir les noms de deux patients à comparer
    static void saisirComparaison(string* nom1, string* nom2) {
        cout << "Entrer Nom du 1er Patient : ";
        cin >> *nom1;
        cout << "Entrer Nom du 2eme Patient : ";
        cin >> *nom2;
    }
};

int main() {
    int choix, n = 0, age;
    bool user;
    string nom, hist, spec, nom1, nom2;
    TabPatient Pat;
    Patient P1("Younes", 20, "Fievre");
    Patient P2("Zineb", 21, "Mal en Tete");
    Patient P3("Mohamed", 20, "Fievre");
    Pat.ajouterPatient(Patient("Khalid", 30, "Toux"));
    Pat.ajouterPatient(P1);
    Pat.ajouterPatient(P2);
    Pat.ajouterPatient(P3);
    TabMedcin Med;
    Med.ajouteMedcin(Medcin("Rachid", "Pediatre"));
    Medcin M1("Younes", "Ophtalmologiste");
    Medcin M2("Mohamed", "Neurologue");
    Medcin M3("Ali", "Generaliste");
    Med.ajouteMedcin(M1);
    Med.ajouteMedcin(M2);
    Med.ajouteMedcin(M3);
    TabRendezVous RDV;
    RendezVous R1(P1, M1, "01/01/2025");
    RendezVous R2(P2, M2, "04/01/2025");
    RDV.ajouteRendezVous(R1);
    RDV.ajouteRendezVous(R2);
    RDV.ajouteRendezVous(RendezVous(P3, M3, "06/01/2025"));
    RendezVousCritique rdvCrt1(P1, M1, "09/12/2024", 1);
    RendezVousCritique rdvCrt2(P2, M2, "08/12/2024", 2);
    CentreMedical centre;
    centre.ajouterRendezVous(&R1);
    centre.ajouterRendezVous(&R2);
    centre.ajouterRendezVousUrgent(&rdvCrt1);
    centre.ajouterRendezVousUrgent(&rdvCrt2);

    do {
        InterfaceUtilisateur::clearEcran();
        InterfaceUtilisateur::afficherTitre();
        choix = InterfaceUtilisateur::menuPrincipal();
        switch (choix) {
        case 1: user = false; n = EspacePatient::gererEspace(true);break;
        case 2:	user = true;  n = EspaceMedecin::gererEspace(true);break;
        case 0: cout << "Merci d'avoir utilise le systeme. Au revoir !" << endl; return 0;
        default: cout << "Choix invalide. Veuillez ressayer.\n";break;
        }
    } while (choix < 1 || choix > 2);
    if (!user) {
        do {
            switch (n) {
            case 0: cout << "Merci d'avoir utilise le systeme. Au revoir !" << endl;return 0;
            case 1: { nom = Saisie::saisirNom(); Patient* P = Pat.rechercherParNom(nom); if (P != nullptr) P->affiche();break; }
            case 2: { nom = Saisie::saisirNom(); RendezVous* R = RDV.rechercherRendezVous(nom); if (R != nullptr) R->afficheRDV();break; }
            case 3: { cout << "Suppression du rendez-vous en cours..." << endl; nom = Saisie::saisirNom(); RDV.supprimerRendezVous(nom);break; }
            default: cout << "Choix invalide. Veuillez ressayer.\n";break;
            }
            n = EspacePatient::gererEspace(false);
        } while (n != 0);
    }
    if (user) {
        do {
            switch (n) {
            case 0: cout << "Merci d'avoir utilise le systeme. Au revoir !" << endl;return 0;
            case 1: Saisie::saisirMedecin(&nom, &spec);Med.ajouteMedcin(Medcin(nom, spec));break;
            case 2: Med.afficheTabMed();break;
            case 3: {
                Saisie::saisirComparaison(&nom1, &nom2);
                Patient* P1 = Pat.rechercherParNom(nom1);
                Patient* P2 = Pat.rechercherParNom(nom2);
                if (P1 != nullptr && P2 != nullptr) cout << (P1 == P2 ? "\nLes Deux Patients Sont le Meme\n" : "\nLes Deux Patients sont differents\n");break;
            }
            case 4: Saisie::saisirPatient(&nom, &age, &hist);Pat.ajouterPatient(Patient(nom, age, hist));break;
            case 5: Pat.afficheTab();break;
            case 6: RDV.afficheTabRendezVous();break;
            default: cout << "Choix invalide. Veuillez ressayer.\n";break;
            }
            n = EspaceMedecin::gererEspace(false);
        } while (n != 0);
    }
    return 0;
}
