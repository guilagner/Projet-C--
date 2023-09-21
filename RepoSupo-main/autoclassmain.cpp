#include "autoclass.hpp"

using namespace std;

map<string, string> attr;
vector<string> attributTypes = {"int", "float", "double", "char", "string", "bool"};

void dispAttr()
{
    cout << "Les attributs et leurs types sont sont:" << endl;
    cout << "-------------------" << endl;
    for (const auto &p : attr)
        std::cout << p.first << " => " << p.second << '\n';
    cout << "-------------------" << endl;
}

bool checkType(string type)
{
    for (int i = 0; type[i] != '\0'; i++)
    {
        type[i] = tolower(type[i]);
    }
    if (find(attributTypes.begin(), attributTypes.end(), type) == attributTypes.end())
    {
        cout << "Type ne correspond pas à la liste, reesayer" << endl;
        return false;
    }
    return true;
}

void displayAttribut()
{
    for (const auto &n : attributTypes)
    {
        std::cout << n << std::endl;
    }
}

string getType(string attribut)
{
    string type;

    cout << "Veuillez entrer le type de l'attribut parmis la Liste ci-dessous: " << endl;
    displayAttribut();
    getline(cin, type);
    if (!validateEntry(type))
    {
        cout << "Merci de na pas utilsé de caractère spéciaux";
    }
    if (!checkType(type))
    {
        cout << "Type ne fais pas partie de la liste, Veuillez reessayer" << endl;
        getType(attribut);
    }
    attr.emplace(make_pair(attribut, type));

    return type;
}

void menu(string className)
{
    string attribut;
    string another;
    bool boucleinf = true;

    cout << "Veuillez entrer un attribut de la classe:\n"
         << "(l'attribut \"end\" est interdit)"
         << endl;
    getline(cin, attribut);
    if (!validateEntry(attribut))
    {
        cout << "Erreur, vous ne pouvez pas utilisez de caractère spéciaux" << endl;
    }
    if (!validateEntryAttribut(attribut))
    {
        cout << "Erreur, vous ne pouvez pas des nom de methode ou fonction du language c++" << endl;
    }
    if (attribut == "end")
    {
        cout << "Erreur, attribut end trouvé." << endl;
        // cin.clear();
        // cin.ignore();
        menu(className);
    }
    else
    {
        getType(attribut);

        while (boucleinf == true)
        {
            cout << "Voulez vous ajouter un autre attribut (Y/N)?" << endl;
            getline(cin, another);
            if (another == "y" || another == "Y")
            {
                boucleinf = false;
                menu(className);
            }
            else if (another == "n" || another == "N")
            {
                boucleinf = false;
                dispAttr();
                break;
            }
            else
            {
                cout << "Entrer \"y\" ou \"n\" svp." << endl;
                continue;
            }
        }
    }
}

int main()
{

    string className;

    cout << "Veuillez entrer le nom de la classe:" << endl;
    getline(cin, className);
    try
    {
        validateEntry(className)
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error:9001 Merci de ne pas utiliser de Caractère spéciaux =>" << e.what() << '\n';
    }

    className[0] = toupper(className[0]);
    menu(className);
    headerfilegenerator(className, attr);
    // sourcefilegenerator(className, attr);
    // mainfilegenerator(className, attr);
    // makefilegenerator(className);

    return 0;
}