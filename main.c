#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LENGTH_BRANDS 10
#define LENGTH_TYPE_OF_PAPERS 10
#define LENGTH_PACK_OF_PAPERS 10

int length_vector_brands = 0;
int length_vector_type_of_paper = 0;
int length_vector_pack_of_paper = 0;

// Struct MARCA
typedef struct brand {
    int cod_brand;
    char description[100];
} Brand;

// Struct TIPO
typedef struct type_of_paper {
    int cod_type_of_paper;
    char description[100];
} TypeOfPaper;

// Struct PACOTE DE PAPEIS
typedef struct pack_of_paper {
    int cod_pack_of_paper;
    int cod_type_of_paper;
    int amount_of_papers;
    char amount[3];
    int cod_brand;
    float price;
} PackOfPaper;

void correctionName(char index[]) {
    for (int i = 0; index[i] != '\0'; i++) {
        if (index[i] == '\n') {
            index[i] = '\0';
        }
    }
}

int loadTypeOfPaperByCode(int code, TypeOfPaper typeOfPapers[], int length) {
    int index = -1;
    for (int i = 0; i < length; i++) {
        if (code == typeOfPapers[i].cod_type_of_paper) {
            return i;
        }
    }
    return index;
}

int loadPackOfPaperByCode(int code, PackOfPaper packOfPapers[], int length) {
    int index = -1;
    for (int i = 0; i < length; i++) {
        if (code == packOfPapers[i].cod_pack_of_paper) {
            return i;
        }
    }
    return index;
}

int loadBrandByCode(int code, Brand brands[], int length) {
    int index = -1;
    for (int i = 0; i < length; i++) {
        if (code == brands[i].cod_brand) {
            return i;
        }
    }
    return index;
}

int loadBrandWithMoreAmountPackOfPaper(PackOfPaper packOfPapers[], Brand brands[], int lengthPackOfPapers,
                                       int lengthBrands) {
    int cod_brand;
    int amountOfPackOfPaper = 0;
    int prevAmountOfPackOfPaper = 0;
    for (int i = 0; i < lengthBrands; i++) {
        Brand brand = brands[i];
        for (int j = 0; j < lengthPackOfPapers; j++) {
            if (j == 0 && brand.cod_brand == packOfPapers[j].cod_brand) {
                cod_brand = brand.cod_brand;
                amountOfPackOfPaper++;
                prevAmountOfPackOfPaper++;
            } else if (brand.cod_brand == packOfPapers[j].cod_brand) {
                amountOfPackOfPaper++;
                if (prevAmountOfPackOfPaper < amountOfPackOfPaper) {
                    cod_brand = brand.cod_brand;
                    prevAmountOfPackOfPaper = amountOfPackOfPaper;
                }
            }
        }
        amountOfPackOfPaper = 0;
    }
    return loadBrandByCode(cod_brand, brands, lengthBrands);
}

int searchBrandByName(Brand brands[], int length_brands, char name_brand[]) {
    int index = -1;
    for (int i = 0; i < length_brands; i++) {
        correctionName(brands[i].description);
        if (strcmp(name_brand, brands[i].description) == 0) {
            return i;
        }
    }
    return index;
}

void showBrand(Brand brand, int index) {
    printf("\n=== Marca %d ===", index + 1);
    printf("\nCodigo: %d", brand.cod_brand);
    printf("\nDescricao: %s", brand.description);
    printf("\n\n");
}

int getOptionBetweenARange(int start, int end) {
    int option;
    do {
        scanf("%d", &option);
        printf("%d",(int)(option < start || option > end));
    } while (option < start || option > end);
    return option;
}

int showMenu() {
    printf("\n\n=== Sistemas Dunder Mifflin ===\n");
    printf("1 - Cadastro de marca dos pacotes\n");
    printf("2 - Cadastro de tipo de papel existente\n");
    printf("3 - Cadastro de pacote de papeis\n");
    printf("4 - Mostra todos os cadastros\n");
    printf("5 - Mostrar a marca que possui a maior quantidade de pacotes \n");
    printf("6 - Mostrar o preco total dos pacotes do sistema e separa quantos pacotes cada marca possui no sistema \n");
    printf("7 - Opcao de realizar uma busca pela marca dos papeis, para a retirada de pacotes;\n");
    printf("8 - Finalizar\n");
    printf("Digite a opcao: ");
    return getOptionBetweenARange(1, 8);
}

void showPackOfPaper(PackOfPaper packOfPaper, TypeOfPaper typeOfPapers[], Brand brands[], int lengthTypeOfPapers,
                     int lengthBrands, int index) {
    printf("\n=== Pacote %d ===", index + 1);
    printf("\nCodigo: %d", packOfPaper.cod_pack_of_paper);

    int typeOfPaper = loadTypeOfPaperByCode(packOfPaper.cod_type_of_paper, typeOfPapers, lengthTypeOfPapers);
    printf("\nDescricao do tipo de papel: %s", typeOfPapers[typeOfPaper].description);

    printf("Quantidade de folhas no pacote: %d", packOfPaper.amount_of_papers);
    setbuf(stdin, 0);
    printf("\nTamanho das folhas: %s", packOfPaper.amount);
    int brand = loadBrandByCode(packOfPaper.cod_brand, brands, lengthBrands);
    correctionName(brands[brand].description);
    printf("Descricao da marca: %s", brands[brand].description);
    printf("\nPreco: R$%.2f", packOfPaper.price);

    printf("\n\n");
}

void showTypeOfPaper(TypeOfPaper typeOfPaper, int index) {
    printf("\n=== Tipo %d ===", index + 1);
    printf("\nCodigo: %d", typeOfPaper.cod_type_of_paper);
    printf("\nDescricao: %s", typeOfPaper.description);
    printf("\n\n");
}

void registerBrand(Brand brands[]) {
    int isTheBrandAlreadyExists;
    Brand brand;
    do {
        printf("\nDigite o codigo da marca: ");
        scanf("%d", &brand.cod_brand);
        isTheBrandAlreadyExists = loadBrandByCode(brand.cod_brand, brands, length_vector_brands);
        if (isTheBrandAlreadyExists != -1) {
            printf("\nMarca ja existente!Tente outro codigo!\n\n");
        }
    } while (isTheBrandAlreadyExists != -1);
    setbuf(stdin, 0);
    printf("\nDigite a descricao da marca: ");
    fgets(brand.description, 30, stdin);
    brands[length_vector_brands] = brand;
    length_vector_brands++;
}


// FUNÇÃO DE CADASTRO DE TIPOS DE PAPEIS
void registerTypeOfPaper(TypeOfPaper typeOfPapers[]) {
    int isTheTypeOfPaperAlreadyExists;
    TypeOfPaper typeOfPaper;
    do {
        printf("\nDigite o codigo do tipo de papel: ");
        scanf("%d", &typeOfPaper.cod_type_of_paper);
        isTheTypeOfPaperAlreadyExists = loadTypeOfPaperByCode(typeOfPaper.cod_type_of_paper, typeOfPapers,
                                                              length_vector_type_of_paper);

        if (isTheTypeOfPaperAlreadyExists != -1) {
            printf("\nTipo de papel ja esta cadastrado!\n");
            printf("Tente novamente!\n");
        }
    } while (isTheTypeOfPaperAlreadyExists != -1);

    setbuf(stdin, 0);
    printf("\nDigite a descricao do tipo de papel: ");
    fgets(typeOfPaper.description, 30, stdin);
    typeOfPapers[length_vector_type_of_paper] = typeOfPaper;
    length_vector_type_of_paper++;
}


// FUNÇÃO PARA CADASTRO DE PACOTES DE PAPEIS
void registerPackOfPaper(PackOfPaper packOfPapers[], TypeOfPaper typeOfPapers[], Brand brands[]) {
    int isThePackOfPaperAlreadyExists, isTheTypeOfPaperAlreadyExists, isTheBrandAlreadyExists;
    PackOfPaper packOfPaper;
    do {
        printf("\nDigite o codigo do pacote de papeis: ");
        scanf("%d", &packOfPaper.cod_pack_of_paper);
        isThePackOfPaperAlreadyExists = loadPackOfPaperByCode(packOfPaper.cod_pack_of_paper, packOfPapers,
                                                              length_vector_pack_of_paper);

        if (isThePackOfPaperAlreadyExists != -1) {
            printf("\nPacote ja cadastrado!\n");
            printf("Tente novamente!\n");
        }
    } while (isThePackOfPaperAlreadyExists != -1);

    do {
        printf("\nDigite o codigo do tipo de papel desse pacote: ");
        scanf("%d", &packOfPaper.cod_type_of_paper);
        isTheTypeOfPaperAlreadyExists = loadTypeOfPaperByCode(packOfPaper.cod_type_of_paper, typeOfPapers,
                                                              length_vector_type_of_paper);
        if (isTheTypeOfPaperAlreadyExists == -1) {
            printf("\nTipo nao existe! Tente novamente!\n\n");
        }
    } while (isTheTypeOfPaperAlreadyExists == -1);

    printf("\nDigite a quantidade de folhas que o pacote possui: ");
    scanf("%d", &packOfPaper.amount_of_papers);
    setbuf(stdin, 0);
    printf("\nDigite qual o tamanho das folhas (A0,A1,A2,A3 ou A4) do pacote: ");
    fgets(packOfPaper.amount, 3, stdin);
    correctionName(packOfPaper.amount);
    do {
        printf("\nDigite o codigo da marca do pacote: ");
        scanf("%d", &packOfPaper.cod_brand);
        isTheBrandAlreadyExists = loadBrandByCode(packOfPaper.cod_brand, brands, length_vector_brands);
        if (isTheBrandAlreadyExists == -1) {
            printf("\nMarca nao existe! Tente novamente!\n\n");
        }
    } while (isTheBrandAlreadyExists == -1);
    printf("\nDigite o preco do pacote de papeis: ");
    scanf("%f", &packOfPaper.price);
    packOfPapers[length_vector_pack_of_paper] = packOfPaper;
    length_vector_pack_of_paper++;
}

// FUNÇÃO DE MOSTRAR OS DADOS CADASTRADOS
void show(PackOfPaper packOfPapers[], TypeOfPaper typeOfPapers[], Brand brands[]) {
    printf("\n============================= MARCAS ==========================\n\n");
    for (int b = 0; b < length_vector_brands; b++) {
        showBrand(brands[b], b);
    }

    printf("\n============================= TIPOS DE PAPEIS ==========================\n\n");
    for (int c = 0; c < length_vector_type_of_paper; c++) {
        showTypeOfPaper(typeOfPapers[c], c);
    }

    printf("\n============================= PACOTES DE PAPEIS ==========================\n\n");
    for (int d = 0; d < length_vector_pack_of_paper; d++) {
        showPackOfPaper(packOfPapers[d], typeOfPapers, brands, length_vector_type_of_paper, length_vector_brands, d);
    }
}

// FUNÇÃO PARA MOSTRAR A MARCA COM MAIS PACOTES DE PAPEIS
void showTheBrandThatHasTheMostPackagesOfPapers(PackOfPaper packOfPapers[], Brand brands[], int lengthPackOfPapers,
                                                int lengthBrands) {
    int indexOfBrandWithMorePackagesOfPapers = loadBrandWithMoreAmountPackOfPaper(packOfPapers, brands,
                                                                                  lengthPackOfPapers, lengthBrands);
    if (indexOfBrandWithMorePackagesOfPapers == -1) {
        printf("Não foi possivel encontrar a marca com maior numeros de pacotes");
    } else {
        showBrand(brands[indexOfBrandWithMorePackagesOfPapers], indexOfBrandWithMorePackagesOfPapers);
    }
}

// FUNÇÃO PARA RETIRAR PACOTE DE PAPEIS DE ACORDO COM A PESQUISA DA MARCA
void removePackage(int cod_paper, PackOfPaper packOfPapers[], int length_pack_of_paper) {
    int topOfArrayMiddle = 0;
    PackOfPaper remover[10];
    for (int i = 0; i < length_pack_of_paper; i++) {
        if (cod_paper != packOfPapers[i].cod_pack_of_paper) {
            remover[topOfArrayMiddle] = packOfPapers[i];
            topOfArrayMiddle++;
        }
    }

    for (int i = 0; i < length_pack_of_paper; i++) {
        packOfPapers[i] = remover[i];
    }
    length_vector_pack_of_paper--;
}

void searchByBrandToRemovePackagePackages(Brand brands[], PackOfPaper packOfPapers[], int length_brands,
                                          int length_pack_of_paper) {
    int cod_paper,ident;
    int isBrandExists, isPackagesExists;
    char name_brand[100];
    do {
        setbuf(stdin, 0);
        printf("\nDigite o nome da marca: ");
        fgets(name_brand, 100, stdin);
        correctionName(name_brand);
        isBrandExists = searchBrandByName(brands, length_brands, name_brand);
        if (isBrandExists == -1) {
            printf("\nMarca nao existe! Tente novamente!\n\n");
        }
    } while (isBrandExists == -1);

    do {
        printf("\nInsira o codigo do pacote a retirar: ");
        scanf("%d", &cod_paper);
        isPackagesExists = loadPackOfPaperByCode(cod_paper, packOfPapers, length_pack_of_paper);
        ident = 0;
        if (isPackagesExists == -1) {
            printf("\nCodigo invalido! Tente novamente!\n\n");
        } else {
            int brandIndex = loadBrandByCode(packOfPapers[isPackagesExists].cod_brand, brands, length_brands);
             if (strcmp(name_brand, brands[brandIndex].description) == 0) {
                removePackage(cod_paper, packOfPapers, length_pack_of_paper);
             } else {
                 ident = 1;
                printf("\nCodigo nao condizente com a marca! Tente novamente!\n\n");
             }
        }
    }while(isPackagesExists == -1 || ident == 1);
}

//Funcao calcula preço total pacotes
float calculateTotalPrice(PackOfPaper packOfPapers[], int length_pack_of_paper) {
    float total = 0;
    for (int i = 0; i < length_pack_of_paper; i++) {
        total += packOfPapers[i].price;
    }
    return total;
}

//Funcao que conta pacotes por marca
void countPackagesByBrand(PackOfPaper packOfPapers[], Brand brands[], int length_pack_of_paper, int length_brands) {
    int brandCount[length_brands];
    for (int i = 0; i < length_brands; i++) {
        brandCount[i] = 0;
    }

    for (int i = 0; i < length_pack_of_paper; i++) {
        int brandIndex = loadBrandByCode(packOfPapers[i].cod_brand, brands, length_brands);
        if (brandIndex != -1) {
            brandCount[brandIndex]++;
        }
    }

    printf("=== Quantidade de pacotes por marca ===\n");
    for (int i = 0; i < length_brands; i++) {
        correctionName(brands[i].description);
        printf("%s: %d pacotes\n",brands[i].description, brandCount[i]);
    }
}

int main() {
    Brand brands[LENGTH_BRANDS];
    TypeOfPaper typeOfPapers[LENGTH_TYPE_OF_PAPERS];
    PackOfPaper packOfPapers[LENGTH_PACK_OF_PAPERS];
    int option;

    do {
        option = showMenu();

        switch (option) {
            case 1:
                registerBrand(brands);
                break;
            case 2:
                registerTypeOfPaper(typeOfPapers);
                break;
            case 3:
                registerPackOfPaper(packOfPapers, typeOfPapers, brands);
                break;
            case 4:
                show(packOfPapers, typeOfPapers, brands);
                break;
            case 5:
                showTheBrandThatHasTheMostPackagesOfPapers(packOfPapers, brands, length_vector_pack_of_paper,
                                                           length_vector_brands);
                break;
            case 6:
                printf("\nPreco total dos pacotes: R$%.2f\n", calculateTotalPrice(packOfPapers, length_vector_pack_of_paper));
                countPackagesByBrand(packOfPapers, brands, length_vector_pack_of_paper, length_vector_brands);
                break;
            case 7:
                searchByBrandToRemovePackagePackages(brands, packOfPapers, length_vector_brands,
                                                     length_vector_pack_of_paper);
                break;
        }
    } while (option != 8);

    return 0;
}
