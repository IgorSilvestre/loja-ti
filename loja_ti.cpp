#include <string>
#include <fstream>
#include <locale.h>
#include <ctype.h>
#include <cstdio>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <sys/stat.h>

using namespace std;
        
// GLOBAL VARIABLES
string op;
string tempStr;
string fileLine;
bool fileExists;

// STRUCT & CLASSES
struct Product {
    string id;
    string name;
    string price;
    string quantity;
};


// FUNCTIONS
string makeFileName (string fileName) {
    string filePATH = "resource_files/";
    string fileExtension = ".txt";
    string readyFileName = filePATH + fileName + fileExtension; 
    return readyFileName;
}

bool checkIfDirExists(const std::string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}

void printDB () {
    options: 
        printf ("\nSelecione banco de dados: \n");
        printf ("1. Produto\n");
        printf ("2. Funcionário\n"); 
        printf ("3. Fornecedor\n");
        printf ("4. Voltar\n");
        printf ("\nOpção: ");
        cin >> op;
 
    if (op != "1" && op != "2" && op != "3" && op != "4") {
        printf ("\nOpção inexistente, Tente novamente!\n");
        goto options;
    }
}
bool checkIfFileExists (string fileName, string baseFile) {
    if (baseFile == "product") {
        fstream baseFile;
        baseFile.open (makeFileName ("baseProductFile"), ios::in);
        if (!baseFile) {
            puts ("Erro ao abrir arquivo!\n");
        }
        while (!baseFile.eof ()) {
            baseFile >> tempStr;
            if (tempStr == fileName) {
                return true;
            }
        }
    }
    return false;
}
int listAllProducts () {
    ifstream baseProductFile;
    baseProductFile.open (makeFileName ("baseProductFile"));
    if (!baseProductFile) {
        puts ("\n\nFalha ao abrir arquivo");
        return 1;
    }
    while (!baseProductFile.eof ()) {
        baseProductFile >> fileLine;
        ifstream readFile;
        readFile.open (makeFileName (fileLine));
        if (!readFile) {
            puts ("\n\nFIM");
            return 1;
        }    
        while (!readFile.eof ()) {
            readFile >> fileLine;
            cout << "\n" + fileLine;
        }
        readFile.close ();
        cout << "\n\n";
    }
    baseProductFile.close ();
    return 0;
}
int createProduct () {
    Product newProduct;
    
    
    printf ("\nName: ");
    cin >> newProduct.name;
    if (checkIfFileExists (newProduct.name, "product") == true) {
        fileExists = true;
        printf ("Esse produto ja existe! Deseja sobrescreve-lo? [s/n] ");
        string overwrite;
        cin >> overwrite;
        if (overwrite == "s" || overwrite == "S") {}
        else {
            return 0;
        }
    }
    printf ("\nPreço: ");
    cin >> newProduct.price;
    printf ("\nQuantidade: ");
    cin >> newProduct.quantity;
    printf ("\nID do produto: ");
    cin >> newProduct.id;
    
    fstream newFile;
    newFile.open (makeFileName (newProduct.name), ios::out);
    if (!newFile) {
        printf("\n Erro ao abrir arquivo!");
        return 1;
    }

    newFile << "nome:" + newProduct.name + "\n";
    newFile << "Preço:" + newProduct.price + "\n";
    newFile << "Quantidade:" + newProduct.quantity + "\n";
    newFile << "ID:" + newProduct.id;

    newFile.close ();

    // ADD TO BASE FILE
    if (fileExists == false) {
        fstream baseProductFile;
        baseProductFile.open ("resource_files/baseProductFile.txt", ios::app);
        if (!baseProductFile) {
            printf("\n Erro ao abrir arquivo!");
            return 1;
        }
        baseProductFile << newProduct.name + "\n";

        baseProductFile.close ();
    }
    
    fileExists = false;
    printf ("Produto cadastrado!\n\n");
    return 0;
}

int updateProduct () {
    printf ("\nNome do produto: ");
    string oldProductName;
    cin >> oldProductName;
    if (checkIfFileExists (oldProductName, "product") == false) {
        printf ("\n\nArquivo inexistente!\n\n");
        return 1;
    }
    if (op == "1") {
        Product newProduct;

        printf ("\nName: ");
        cin >> newProduct.name;
        printf ("\nPreço: ");
        cin >> newProduct.price;
        printf ("\nQuantidade: ");
        cin >> newProduct.quantity;
        printf ("\nID do produto: ");
        cin >> newProduct.id;
    
        fstream newFile;
        newFile.open (makeFileName (newProduct.name), ios::out);
        if (!newFile) {
            printf("\n Erro ao abrir arquivo!");
            return 1;
        }
        newFile << "nome:" + newProduct.name + "\n";
        newFile << "Preço:" + newProduct.price + "\n";
        newFile << "Quantidade:" + newProduct.quantity + "\n";
        newFile << "ID:" + newProduct.id;

        newFile.close ();
        // CHANGE BASE FILE
        if (oldProductName != newProduct.name) {
            ifstream baseProductFile;
            baseProductFile.open (makeFileName ("baseProductFile"));
            if (!baseProductFile) {
                printf("\n Erro ao abrir arquivo!");
                return 1;
            }
            ofstream tempFile;
            tempFile.open (makeFileName ("tempFile"));
            if (!tempFile) {
                printf("\n Erro ao abrir arquivo!");
                return 1;
            }
            while (!baseProductFile.eof ()) {
                baseProductFile >> fileLine;
                if (oldProductName != fileLine) {
                    tempFile << "\n" + fileLine;
                }
            }
            tempFile << "\n" + newProduct.name;
            tempFile.close ();
            baseProductFile.close ();

            // REMOVE BASE FILE NAME
            string oldNameStr = makeFileName ("baseProductFile");
            const char * oldNameChar = oldNameStr.c_str ();
            remove (oldNameChar);
            
            // RENAME TEMP WITH BASE FILE NAME
            string newNameStr = makeFileName ("tempFile");
            const char * tempChar = newNameStr.c_str ();
            rename (tempChar, oldNameChar);
            
            // REMOVE OLD FILE
            string tempStr = makeFileName (oldProductName);
            tempChar = tempStr.c_str ();
            remove (tempChar);   
        }
            
        fileExists = false;
        printf ("Produto cadastrado!\n\n");
        return 0;
    }
    return 0;
}

int deleteProduct () {
    printf ("\nNome do produto para deletar: ");
    string productName;
    cin >> productName;
    
    ifstream baseProductFile;
    baseProductFile.open (makeFileName ("baseProductFile"));
    if (!baseProductFile) {
        puts ("\n\nFalha ao abrir arquivo!");
        return 1;
    }
    ofstream tempFile;
    tempFile.open (makeFileName ("tempFile"));
    if (!tempFile) {
        puts ("\n\nFalha ao abrir arquivo!");
        return 1;
    }
    while (!baseProductFile.eof ()) {
        baseProductFile >> fileLine;
        if (fileLine != productName) {
            tempFile << "\n" + fileLine;
        }
    }
    // REMOVE BASE FILE NAME
    string oldNameStr = makeFileName ("baseProductFile");
    const char * oldNameChar = oldNameStr.c_str ();
    remove (oldNameChar);
            
    // RENAME TEMP WITH BASE FILE NAME
    string newNameStr = makeFileName ("tempFile");
    const char * tempChar = newNameStr.c_str ();
    rename (tempChar, oldNameChar);
            
    // REMOVE OLD FILE
    string tempStr = makeFileName (productName);
    tempChar = tempStr.c_str ();
    remove (tempChar);
    return 0;
}

int main () {
    setlocale(LC_ALL,"");
    
    if (checkIfDirExists ("resource_files") == false) {
        mkdir ("resource_files", 0777);
    }

    fstream baseProductFile;
    baseProductFile.open (makeFileName ("baseProductFile"), ios::app);
    baseProductFile.close ();

    // MAKING FILES
    menu:
        printf ("PROGRAMA DE TI\n\n");
        printf ("1. Criar\n");
        printf ("2. Ler\n");
        printf ("3. Alterar\n");
        printf ("4. Deletar\n");
        printf ("\nOpção: ");
        cin >> op;
        printf ("\n"); 
        
    if (op != "1" && op != "2" && op != "3" && op != "4") {
        printf ("\nOpção inexistente, Tente novamente!\n");
        goto menu;
    }

    if (op == "1") {
        op = "";
        printDB ();
        if (op == "1") {
            createProduct ();
        }
        goto menu;
    }
    if (op == "2") {
        printDB ();
        string op2;
        oldProductNameBy:
            printf ("\n1. Pesquisar por nome");
            printf ("\n2. Listar todos");
            printf ("\n3. Voltar");
            printf ("\nOpção: ");
            cin >> op2;
        if (op == "1") {
            if (op2 == "1") {
                printf ("Digite nome do produto desejado: ");
                cin >> tempStr;
                cout << "\n\n";

                fstream oldProductNameFile;
                oldProductNameFile.open (makeFileName (tempStr));
                if (!oldProductNameFile) {
                    printf ("\nArquivo inexistente!\n");
                    goto oldProductNameBy;
                }
                else {
                    while (!oldProductNameFile.eof ()) {
                        oldProductNameFile >> fileLine;
                        cout << fileLine + "\n";
                    }
                    oldProductNameFile.close ();
                }

            }
            if (op2 == "2") {
                listAllProducts ();
            }
        }
        goto menu;
    }
    if (op == "3") {
        printDB ();
        if (op == "1") {
            updateProduct ();
        }
        goto menu;
    }
    if (op == "4") {
        printDB ();
        if (op == "1") {
            deleteProduct ();
        }
        goto menu;
    }

    return 0;
}