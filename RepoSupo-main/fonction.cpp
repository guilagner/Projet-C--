#include "autoclass.hpp"

void headerfilegenerator(std::string className, std::map<std::string, std::string> attributs)
{
    size_t ctn = 0;
    std::ofstream headerFile(className + ".h");
    std::string constructor = "";
    std::string headerName = className;

    for (int i = 0; headerName[i] != '\0'; i++)
    {
        headerName[i] = toupper(headerName[i]);
    }
    headerFile << "#ifndef " << headerName << "_H" << std::endl;
    headerFile << "#define " << headerName << "_H" << std::endl;
    headerFile << "#include <iostream>" << std::endl;
    headerFile << "#include <string>" << std::endl;

    headerFile << std::endl;
    headerFile << "class " << className << " {" << std::endl;
    headerFile << "public:" << std::endl;
    for (const auto &elem : attributs)
    {
        if (ctn + 1 >= attributs.size())
        {
            if (elem.second == "string")
                constructor += "std::";
            constructor += elem.second + " _" + elem.first;
        }
        else
        {
            if (elem.second == "string")
                constructor += "std::";
            constructor += elem.second + " _" + elem.first + ", ";
        }
        ctn++;
    }
    ctn = 0;
    headerFile << "\t" << className << "();" << std::endl;
    headerFile << "\t" << className << "(" << constructor << ");" << std::endl;
    headerFile << endl;
    std::string tmp;
    for (const auto &elem : attributs)
    {
        tmp = elem.first;
        tmp[0] = toupper(tmp[0]);
        if (elem.second == "string")
        {
            headerFile << "\t"
                       << "std::" << elem.second << " get" << tmp << "() const;" << std::endl;
            headerFile << "\tvoid set" << tmp << "("
                       << "std::" << elem.second << " " << elem.first << ");" << std::endl;
        }
        else
        {
            headerFile << "\t" << elem.second << " get" << tmp << "() const;" << std::endl;
            headerFile << "\tvoid set" << tmp << "(" << elem.second << " " << elem.first << ");" << std::endl;
        }
        headerFile << std::endl;
    }
    headerFile << "private:" << std::endl;
    for (const auto &elem : attributs)
    {
        if (elem.second == "string")
        {
            headerFile << "\t"
                       << "std::" << elem.second << " " << elem.first << ";" << std::endl;
        }
        else
            headerFile << "\t"
                       << elem.second << " " << elem.first << ";" << std::endl;
    }
    headerFile << "};" << std::endl;
    headerFile << std::endl;
    headerFile << "#endif // " << headerName << "_H" << std::endl;
    headerFile.close();
}

void sourcefilegenerator(std::string className, std::vector<std::string> attributs)
{
    std::ofstream sourceFile(className + ".cpp");
    std::string constructor, tmp;
    sourceFile << "#include \"" << className << ".h\"" << std::endl;
    sourceFile << std::endl;
    sourceFile << "    // Constructeur par défaut" << std::endl;
    sourceFile << "\n";
    sourceFile << className << "::" << className << "()"
               << "{\n";
    for (size_t i = 0; i < attributs.size(); i++)
    {
        sourceFile << "\t" << attributs[i] << " = \"\";\n";
    }
    sourceFile << "}";
    sourceFile << "\n";
    for (size_t i = 0; i < attributs.size(); i++)
    {
        if (i + 1 >= attributs.size())
            constructor += "std::string _" + attributs[i];
        else
            constructor += "std::string _" + attributs[i] + ", ";
    }
    sourceFile << className << "::" << className << "(" << constructor << ")"
               << "{\n\n";
    for (size_t i = 0; i < attributs.size(); i++)
    {
        sourceFile << "\tthis->" << attributs[i] << " = _" << attributs[i] << ";" << std::endl;
    }
    sourceFile << "}\n";

    // getvalue/setvalue
    sourceFile << "\n";
    for (size_t i = 0; i < attributs.size(); i++)
    {
        tmp = attributs[i];
        tmp[0] = toupper(tmp[0]);
        sourceFile << "std::string " << className << "::get" << tmp << "()const{\n";
        sourceFile << "\treturn " << attributs[i] << ";\n";
        sourceFile << "}\n";
        sourceFile << "void " << className << "::set" << tmp << "("
                   << "std::string " << attributs[i] << "){\n";
        sourceFile << "\tthis->" << attributs[i] << " = " << attributs[i] << ";\n";
        sourceFile << "}";
    }
    sourceFile.close();
}
void mainfilegenerator(std::string className, std::map<std::string, std::string> attributs)
{
    std::ofstream mainFile("main.cpp");
    std::string tmp;
    mainFile << "#include \"" << className << ".h\"" << std::endl;
    mainFile << std::endl;
    mainFile << "int main() {" << std::endl;
    mainFile << "\t" << className << " obj;\n";
    mainFile << "\tsrand((unsigned) time(NULL));" << std::endl;
    for (size_t i = 0, j = 1; i < attributs.size(); i++, j++)
    {
        tmp = attributs[i];
        tmp[0] = toupper(tmp[0]);
        mainFile << "\tint randomNb" << j << " = rand() % 100;" << std::endl;
        mainFile << "\tobj.set" << tmp << "(std::to_string(randomNb" << j << "));\n";
    }
    for (size_t i = 0; i < attributs.size(); i++)
    {
        tmp = attributs[i];
        tmp[0] = toupper(tmp[0]);
        mainFile << "\tstd::cout << \"" << attributs[i] << " = \" "
                 << "<< obj.get" << tmp << "() << std::endl;" << std::endl;
    }

    mainFile << "\n\treturn 0;" << std::endl;
    mainFile << "}" << std::endl;
    mainFile.close();
}

void makefilegenerator(std::string className)
{
    std::ofstream makefile("Makefile");
    makefile << "CXX = g++" << std::endl;
    makefile << "CXXFLAGS = -std=c++11 -Wall" << std::endl;
    makefile << std::endl;
    makefile << "all: myprogram" << std::endl;
    makefile << std::endl;
    makefile << "myprogram: " << className << ".cpp main.cpp" << std::endl;
    makefile << "\t$(CXX) $(CXXFLAGS) -o myprogram " << className << ".cpp main.cpp" << std::endl;
    makefile << std::endl;
    makefile << "clean:" << std::endl;
    makefile << "\trm -f myprogram" << std::endl;
    makefile << "\trm -f " << className << ".h" << std::endl;
    makefile << "\trm -f " << className << ".cpp" << std::endl;
    makefile << "\trm -f main.cpp" << std::endl;
    makefile.close();
}
// fonction pour les données valide
bool validateEntry(const std::string blabla)
{
    for (char x : blabla)
    {
        if (!isalnum(x))
        {
            std::cout << "Code 187 : Merci de ne pas utilisé de caractère spéciaux ";
            return false;
        }
    }

    return true;
}
// fonction pour les donnée attribut
bool validateEntryAttribut(const std::string blabla)
{
    if (blabla == "string" || blabla == "int" || blabla == "float" || blabla == "double" || blabla == "char" || blabla == "bool" || blabla == "std" || blabla = "null" || blabla = "NULL" || blabla = "vector" || blabla = "operator")
    {
        return false;
    }

    return true;
}
// fonction pour le duplicate
bool duplicate(const std::string attrName, std::vector<std::string> attr)
{
    // adapt to map
    return find(attr.begin(), attr.end(), attrName) != attr.end();
}

// Fonction pour valider le nom d' un fichier
bool isValidFileName(const string &fileName)
{
    for (char c : fileName)
    {
        if (!isalnum(c) || c == '_' || c == '.')
        {
            return false;
        }
    }
    return true;
}