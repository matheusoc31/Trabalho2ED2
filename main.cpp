#include "./headers/libraries.h"

void printBT(const std::string& prefix, NoAVL* node, bool isRight) {
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isRight ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->getKey() << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isRight ? "│   " : "    "), node->getRight(), true);
        printBT( prefix + (isRight ? "│   " : "    "), node->getLeft(), false);
    }
}

void preOrder(NoAVL *root) {
    if(root != NULL)
    {
        printf("%d ", root->getKey());
        preOrder(root->getLeft());
        preOrder(root->getRight());
    }
}


int main()
{
    cout << "Hello world!" << endl;
    int ARVORE;

    cout << "Digite a árvore de balanceamento desejada:" << endl;
    cout << "1. AVL" << endl;
    cout << "2. AVL Modificada" << endl;
    cout << "3. Vermelho-Preta" << endl;
    cout << "4. Splay" << endl;
    cout << "5. B" << endl;
    cout << "> ";
    cin >> ARVORE;
    while(ARVORE < 1 || ARVORE > 5) {
        cout << "Opção inválida. Tente novamente." << endl;
        cout << "Digite a árvore de balanceamento desejada:" << endl;
        cout << "1. AVL" << endl;
        cout << "2. AVL Modificada" << endl;
        cout << "3. Vermelho-Preta" << endl;
        cout << "4. Splay" << endl;
        cout << "5. B" << endl;
        cout << "> ";
        cin >> ARVORE;
    }

    fstream deputados, entradaInsercao, saidaInsercao, entradaBusca, saidaBusca, entradaRemocao, saidaRemocao;
//    int exemplo[] = {10, 20, 30, 5, 3, 50, 40, 70, 60, 90};
//    int exSize = sizeof(exemplo)/sizeof(int);
    int qtdNInsercao, qtdNBusca, qtdNRemocao, nLines, i, j, k, v, seedIdx, lineCount, randDepIdx, idxDup;
    unsigned int *comp, *copias;
    string line, tableCell, filename, treeName;
    GastoDeputado *allDeputados;//, *conjuntoDeputados;
    clock_t startTime, endTime;
    double cpuTime, minTime, propGastoArvore, arvoreOuArquivo;

    double auxTimeAVL = 0, auxTimeAVLMod = 0;
    unsigned int auxCompAVL = 0, auxCopiasAVL = 0, auxCompAVLMod = 0, auxCopiasAVLMod = 0;

    int *NInsercao, *NBusca, *NRemocao;
    int *gastoIdInseridos, *gastoIdBuscaRemocao;
    int nSeed = 5;
    int seedVec[nSeed];

    comp = new unsigned int();
    copias = new unsigned int();

    srand(1);
    for(v = 0; v < nSeed; v++) {
        seedVec[i] = randomInt(0, pow(2, 31));
    }

    AVLTree *myAVL, *myAVLAux;
    AVLTreeModified *myAVLMod, *myAVLModAux;
    /// vp
    /// splay
    /// b

    deputados.open("deputies_dataset_tratado.csv", ios::in);

    if(!deputados.is_open()) {
        cout << "Sem dataset." << endl;
        delete comp;
        delete copias;
        return 0;
    }

    nLines = 0;

    while(getline(deputados, line)) { //conta o numero de linhas do arquivo
        nLines++;
    }; nLines--; // desconta o cabeçalho

    allDeputados = new GastoDeputado[nLines];

    deputados.clear();              // clearing e
    deputados.seekg(0, ios::beg);   // voltando ao inicio do arquivo

    getline(deputados, line);       // pulando o cabeçalho
    cout << line << endl;
    lineCount = 0;
    while(getline(deputados, tableCell, ';')) {

        allDeputados[lineCount].setGastoId(lineCount+1);

        allDeputados[lineCount].setBuggedDate(tableCell);

        getline(deputados, tableCell, ';');
        allDeputados[lineCount].setReceiptDate(tableCell);

        getline(deputados, tableCell, ';');
        allDeputados[lineCount].setDeputyId(stoi(tableCell));

        getline(deputados, tableCell, ';');
        allDeputados[lineCount].setPoliticalParty(tableCell);

        getline(deputados, tableCell, ';');
        allDeputados[lineCount].setStateCode(tableCell);

        getline(deputados, tableCell, ';');
        allDeputados[lineCount].setDeputyName(tableCell);

        getline(deputados, tableCell, ';');
        allDeputados[lineCount].setReceiptSocialSecurityNumber(tableCell);

        getline(deputados, tableCell, ';');
        allDeputados[lineCount].setReceiptDescription(tableCell);

        getline(deputados, tableCell, ';');
        allDeputados[lineCount].setEstablishmentName(tableCell);

        getline(deputados, tableCell, '\n');
        allDeputados[lineCount].setReceiptValue(stoi(tableCell));

        lineCount++;
    }

    deputados.close();

//    cout << "Preorder traversal of the constructed AVL tree is " << endl;
//    preOrder(myAVL->getRaiz());
//
//    cout << "\nTree: " << endl;
//    printBT("", myAVL->getRaiz(), false);
//
//    int searchKey;
//
//    cout << "Busca:" << endl;
//
//    GastoDeputado* searchDep = new GastoDeputado;
//
//    do{
//        cout << "Chave = ";
//        cin >> searchKey;
//
//        if(searchKey == 0)
//            break;
//
//        myAVL->buscaDep(searchKey);
//    } while (searchKey != 0);
//
//    cout << "\nRemoção: " << endl;
//    do{
//        cout << "Chave = ";
//        cin >> searchKey;
//
//        if(searchKey == 0)
//            break;
//
//        myAVL->removeNo(searchKey);
//        cout << "Preorder traversal of the new AVL tree is " << endl;
//        preOrder(myAVL->getRaiz());
//
//        cout << "\nTree after deletion of " << searchKey << endl;
//        printBT("", myAVL->getRaiz(), false);
//    } while (searchKey != 0);
//
//    delete myAVL;
//    delete searchDep;

    entradaInsercao.open("entradaInsercao.txt", ios::in | ios::binary);

    if(!entradaInsercao.is_open()) {
        cout << "Sem entradaInsercao." << endl;
        delete comp;
        delete copias;
        return 0;
    }

    entradaInsercao >> qtdNInsercao;
    NInsercao = new int[qtdNInsercao];

    for(v = 0; j < qtdNInsercao; v++) {
        entradaInsercao >> NInsercao[v];
    }

    entradaInsercao.close();

    entradaBusca.open("entradaBusca.txt", ios::in | ios::binary);

    if(!entradaBusca.is_open()) {
        cout << "Sem entradaBusca." << endl;
        delete comp;
        delete copias;
        return 0;
    }

    entradaBusca >> qtdNBusca;
    NBusca = new int[qtdNBusca];

    for(v = 0; j < qtdNBusca; v++) {
        entradaBusca >> NBusca[v];
    }

    entradaBusca.close();

    entradaRemocao.open("entradaRemocao.txt", ios::in | ios::binary);

    if(!entradaRemocao.is_open()) {
        cout << "Sem entradaRemocao." << endl;
        delete comp;
        delete copias;
        return 0;
    }

    entradaRemocao >> qtdNRemocao;
    NRemocao = new int[qtdNRemocao];

    for(v = 0; j < qtdNRemocao; v++) {
        entradaRemocao >> NRemocao[v];
    }

    entradaRemocao.close();

    switch(ARVORE) {
        case 1:
            treeName = "./Resultados/AVL/";
            break;
        case 2:
            treeName = "./Resultados/AVLModificada/";
            break;
        case 3:
            treeName = "./Resultados/VP";
            break;
        case 4:
            treeName = "./Resultados/Splay";
            break;
        case 5:
            treeName = "./Resultados/B";
            break;
        default:
            treeName = "FAILTREENAME";

    }

    saidaInsercao.open("saidaInsercao.txt", ios::app);
    saidaBusca.open("saidaBusca.txt", ios::app);
    saidaRemocao.open("saidaRemocao.txt", ios::app);

    switch(ARVORE) {
        case 1:
            saidaInsercao << "************************" << endl;
            saidaInsercao << "AVL\n" << endl;
            saidaInsercao << "************************" << endl;
            saidaBusca << "************************" << endl;
            saidaBusca << "AVL\n" << endl;
            saidaBusca << "************************" << endl;
            saidaRemocao << "************************" << endl;
            saidaRemocao << "AVL\n" << endl;
            saidaRemocao << "************************" << endl;
            break;
        case 2:
            saidaInsercao << "************************" << endl;
            saidaInsercao << "AVL Modificada\n" << endl;
            saidaInsercao << "************************" << endl;
            saidaBusca << "************************" << endl;
            saidaBusca << "AVL Modificada \n" << endl;
            saidaBusca << "************************" << endl;
            saidaRemocao << "************************" << endl;
            saidaRemocao << "AVL Modificada \n" << endl;
            saidaRemocao << "************************" << endl;
            break;
        case 3:
            /// vp
            break;
        case 4:
            /// splay
            break;
        case 5:
            /// b
            break;
        default:
            cout << "FAIL" << endl;
            return 0;
    }


    double timeInsercaoAVL[qtdNInsercao] = {0}, timeBuscaAVL[qtdNInsercao][qtdNBusca] = {0},
            timeBuscaOrdenadaAVL[qtdNInsercao][qtdNBusca] = {0}, timeRemocaoAVL[qtdNInsercao][qtdNRemocao] = {0},
             timeRemocaoOrdenadaAVL[qtdNInsercao][qtdNRemocao] = {0};
    unsigned int compInsercaoAVL[qtdNInsercao] = {0}, compBuscaAVL[qtdNInsercao][qtdNBusca] = {0},
            compBuscaOrdenadaAVL[qtdNInsercao][qtdNBusca] = {0}, compRemocaoAVL[qtdNInsercao][qtdNRemocao] = {0},
             compRemocaoOrdenadaAVL[qtdNInsercao][qtdNRemocao] = {0};
    unsigned int copiasInsercaoAVL[qtdNInsercao] = {0}, copiasBuscaAVL[qtdNInsercao][qtdNBusca] = {0},
            copiasBuscaOrdenadaAVL[qtdNInsercao][qtdNBusca] = {0}, copiasRemocaoAVL[qtdNInsercao][qtdNRemocao] = {0},
             copiasRemocaoOrdenadaAVL[qtdNInsercao][qtdNBusca] = {0};

    double timeInsercaoAVLMod[qtdNInsercao] = {0}, timeBuscaAVLMod[qtdNInsercao][qtdNBusca] = {0},
            timeBuscaOrdenadaAVLMod[qtdNInsercao][qtdNBusca] = {0}, timeRemocaoAVLMod[qtdNInsercao][qtdNRemocao] = {0},
             timeRemocaoOrdenadaAVLMod[qtdNInsercao][qtdNRemocao] = {0};
    unsigned int compInsercaoAVLMod[qtdNInsercao] = {0}, compBuscaAVLMod[qtdNInsercao][qtdNBusca] = {0},
            compBuscaOrdenadaAVLMod[qtdNInsercao][qtdNBusca] = {0}, compRemocaoAVLMod[qtdNInsercao][qtdNRemocao] = {0},
             compRemocaoOrdenadaAVLMod[qtdNInsercao][qtdNRemocao] = {0};
    unsigned int copiasInsercaoAVLMod[qtdNInsercao] = {0}, copiasBuscaAVLMod[qtdNInsercao][qtdNBusca] = {0},
            copiasBuscaOrdenadaAVLMod[qtdNInsercao][qtdNBusca] = {0}, copiasRemocaoAVLMod[qtdNInsercao][qtdNRemocao] = {0},
             copiasRemocaoOrdenadaAVLMod[qtdNInsercao][qtdNBusca] = {0};

    for(i = 0; i < qtdNInsercao; i++) {
        switch(ARVORE) {
            case 1:
                myAVL = new AVLTree;
                myAVLAux = new AVLTree;
                break;
            case 2:
                myAVLMod = new AVLTreeModified;
                myAVLModAux = new AVLTreeModified;
                break;
            case 3:
                /// vp
                break;
            case 4:
                /// splay
                break;
            case 5:
                /// b
                break;

        }
        for(seedIdx = 0; seedIdx < nSeed; seedIdx++) {
            srand(seedVec[seedIdx]);
            gastoIdInseridos = new int[NInsercao[i]];

            /** 1.INSERÇÃO **/
            for(k = 0; k < NInsercao[i]; k++) {
                gastoIdInseridos[k] = randomInt(0, nLines-1);
            }
            *comp = *copias = 0;
            startTime = clock();
            for(k = 0; k < NInsercao[i]; k++) {
                switch(ARVORE) {
                    case 1:
                        myAVL->insereDep(allDeputados[gastoIdInseridos[k]], comp, copias);
                        break;
                    case 2:
                        myAVLMod->insereDep(allDeputados[gastoIdInseridos[k]], comp, copias);
                        break;
                    case 3:
                        /// vp
                        break;
                    case 4:
                        /// splay
                        break;
                    case 5:
                        /// b
                        break;
                }
            }
            endTime = clock();
            cpuTime = (double)(endTime - startTime)/(CLOCKS_PER_SEC);
            timeInsercaoAVL[i] += (double) cpuTime/5; ///tempo gasto/numero de seeds (para calcular a media)
            compInsercaoAVL[i] += (unsigned int) *copias/5; ///numero de comparacoes/numero de seeds (para calcular a media)
            copiasInsercaoAVL[i] += (unsigned int) *copias/5; ///numero de copias /numero de seeds (para calcular a media)
            /// DESEMPENHO DA INSERÇÃO AQUI;

            saidaInsercao << "NInsercao = " << NInsercao[i] << endl;
            saidaInsercao << "Tempo médio de inserção: " << timeInsercaoAVL[i] << endl;
            saidaInsercao << "Número médio de comparações de chaves: " << compInsercaoAVL[i] << endl;
            saidaInsercao << "Número médio de cópias de registros : " << copiasInsercaoAVL[i] << endl;

            /** 2.BUSCA **/
            saidaBusca << "\n******** NInsercao = " << NInsercao[i] << " ********\n" << endl;
            for(j = 0; j < qtdNBusca; j++) {
                gastoIdBuscaRemocao = new int[NBusca[j]];
                propGastoArvore = NInsercao[i]/(NInsercao[i]+NBusca[j]); /// proporcao dos gasto_id's a serem gerados para a busca, que vão estar entre os gasto_id's inseridos
                for(k = 0; k < NBusca[j]; k++) {
                    /// preenche vetor gastoIdBuscaRemocao com
                    /// parte de gastoIds da arvore,
                    /// parte gastoIds do conjunto inteiro
                    arvoreOuArquivo = (double) (rand() % 10000 + 1)/10000; /// numero aleatorio entre 0 e 1
                    if(arvoreOuArquivo <= propGastoArvore) { /// se arvoreOuArquivo < propGastoArvore, retira gasto_id dentre os inseridos
                        gastoIdBuscaRemocao[k] = gastoIdInseridos[randomInt(0, NInsercao[i]-1)];
                    } else {                                 /// caso contrario, retira do arquivo geral
                        gastoIdBuscaRemocao[k] = randomInt(0, nLines-1);
                    }
                }
                *comp = *copias = 0;
                startTime = clock();
                for(k = 0; k < NBusca[j]; k++) { /// BUSCA de fato
                    switch(ARVORE) {
                        case 1:
                            myAVL->buscaDep(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 2:
                            myAVLMod->buscaDep(gastoIdBuscaRemocao[k], comp, copias);
                        case 3:
                            /// vp
                            break;
                        case 4:
                            /// splay
                            break;
                        case 5:
                            /// b
                            break;
                    }
                }
                endTime = clock();
                cpuTime = (double)(endTime - startTime)/(CLOCKS_PER_SEC);
                timeBuscaAVL[i][j] += (double) cpuTime/5; ///tempo gasto/numero de seeds (para calcular a media)
                compBuscaAVL[i][j] += (unsigned int) *copias/5; ///numero de comparacoes/numero de seeds (para calcular a media)
                copiasBuscaAVL[i][j] += (unsigned int) *copias/5; ///numero de copias /numero de seeds (para calcular a media)
                /// DESEMPENHO DA BUSCA AQUI;

                saidaBusca << "NBusca = " << NBusca[j] << endl;
                saidaBusca << "Tempo médio de busca: " << timeBuscaAVL[i] << endl;
                saidaBusca << "Número médio de comparações de chaves: " << compBuscaAVL[i] << endl;
                saidaBusca << "Número médio de cópias de registros : " << copiasBuscaAVL[i] << endl;

                /// DUPLICA 30% do vetor gastoIdBuscaRemocao:
                idxDup = (int) NBusca[j]*0.7;
                for(k = idxDup; k < NBusca[j]; k++) {
                    gastoIdBuscaRemocao[k] = gastoIdBuscaRemocao[k-idxDup];
                }
                /// ORDENA vetor gastoIdBuscaRemocao:
                ordena(gastoIdBuscaRemocao, NBusca[j], comp, copias);

                *comp = *copias = 0;
                startTime = clock();
                for(k = 0; k < NBusca[j]; k++) { /// BUSCA ORDENADA de fato
                    switch(ARVORE) {
                        case 1:
                            myAVL->buscaDep(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 2:
                            myAVLMod->buscaDep(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 3:
                            /// vp
                            break;
                        case 4:
                            /// splay
                            break;
                        case 5:
                            /// b
                            break;
                    }
                }
                endTime = clock();
                cpuTime = (double)(endTime - startTime)/(CLOCKS_PER_SEC);
                timeBuscaOrdenadaAVL[i][j] += (double) cpuTime/5; ///tempo gasto/numero de seeds (para calcular a media)
                compBuscaOrdenadaAVL[i][j] += (unsigned int) *copias/5; ///numero de comparacoes/numero de seeds (para calcular a media)
                copiasBuscaOrdenadaAVL[i][j] += (unsigned int) *copias/5; ///numero de copias /numero de seeds (para calcular a media)
                /// DESEMPENHO DA BUSCA ORDENADA AQUI;

                saidaBusca << "\nBusca Ordenada: " << endl;
                saidaBusca << "NBusca = " << NBusca[j] << endl;
                saidaBusca << "Tempo médio de busca ordenada: " << timeBuscaAVL[i] << endl;
                saidaBusca << "Número médio de comparações de chaves: " << compBuscaAVL[i] << endl;
                saidaBusca << "Número médio de cópias de registros : " << copiasBuscaAVL[i] << endl;

                delete [] gastoIdBuscaRemocao;
            }

            /** 3.REMOÇÃO **/
            saidaRemocao << "\n******** NInsercao = " << NInsercao[i] << " ********\n" << endl;
            *myAVLAux = *myAVL;
            for(j = 0; j < qtdNRemocao; j++) {
                gastoIdBuscaRemocao = new int[NRemocao[j]];
                propGastoArvore = NInsercao[i]/(NInsercao[i]+NRemocao[j]); /// proporcao dos gasto_id's a serem gerados para a remoção, que vão estar entre os gasto_id's inseridos
                for(k = 0; k < NRemocao[j]; k++) {
                    /// preenche vetor gastoIdBuscaRemocao com
                    /// parte de gastoIds da arvore,
                    /// parte gastoIds do conjunto inteiro
                    arvoreOuArquivo = (double) (rand() % 10000 + 1)/10000; /// numero aleatorio entre 0 e 1
                    if(arvoreOuArquivo <= propGastoArvore) { /// se arvoreOuArquivo < propGastoArvore, retira gasto_id dentre os inseridos
                        gastoIdBuscaRemocao[k] = gastoIdInseridos[randomInt(0, NInsercao[i]-1)];
                    } else {                                 /// caso contrario, retira do arquivo geral
                        gastoIdBuscaRemocao[k] = randomInt(0, nLines-1);
                    }
                }
                *comp = *copias = 0;
                startTime = clock();
                for(k = 0; k < NRemocao[j]; k++) { /// REMOÇÃO de fato
                    switch(ARVORE) {
                        case 1:
                            myAVLAux->removeNo(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 2:
                            myAVLModAux->removeNo(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 3:
                            /// vp
                            break;
                        case 4:
                            /// splay
                            break;
                        case 5:
                            /// b
                            break;
                    }
                }
                endTime = clock();
                cpuTime = (double)(endTime - startTime)/(CLOCKS_PER_SEC);
                timeRemocaoAVL[i][j] += (double) cpuTime/5; ///tempo gasto/numero de seeds (para calcular a media)
                compRemocaoAVL[i][j] += (unsigned int) *copias/5; ///numero de comparacoes/numero de seeds (para calcular a media)
                copiasRemocaoAVL[i][j] += (unsigned int) *copias/5; ///numero de copias /numero de seeds (para calcular a media)
                /// DESEMPENHO DA REMOÇÃO AQUI;

                saidaRemocao << "NRemocao = " << NRemocao[j] << endl;
                saidaRemocao << "Tempo médio de Remocao: " << timeRemocaoAVL[i] << endl;
                saidaRemocao << "Número médio de comparações de chaves: " << compRemocaoAVL[i] << endl;
                saidaRemocao << "Número médio de cópias de registros : " << copiasRemocaoAVL[i] << endl;

                switch(ARVORE) {
                    case 1:
                        *myAVLAux = *myAVL;
                        break;
                    case 2:
                        *myAVLModAux = *myAVLMod;
                        break;
                    case 3: /// vp
                        break;
                    case 4: /// splay
                        break;
                    case 5: /// b
                        break;
                }
                /// DUPLICA 30% do vetor gastoIdBuscaRemocao:
                idxDup = (int) NRemocao[j]*0.7;
                for(k = idxDup; k < NRemocao[j]; k++) {
                    gastoIdBuscaRemocao[k] = gastoIdBuscaRemocao[k-idxDup];
                }
                /// ORDENA vetor gastoIdBuscaRemocao:
                ordena(gastoIdBuscaRemocao, NRemocao[j], comp, copias);

                *comp = *copias = 0;
                startTime = clock();
                for(k = 0; k < NBusca[j]; k++) { /// REMOÇÃO ORDENADA de fato
                    switch(ARVORE) {
                        case 1:
                            myAVLAux->removeNo(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 2:
                            myAVLModAux->removeNo(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 3:
                            /// vp
                            break;
                        case 4:
                            /// splay
                            break;
                        case 5:
                            /// b
                            break;
                    }
                }
                endTime = clock();
                cpuTime = (double)(endTime - startTime)/(CLOCKS_PER_SEC);
                timeRemocaoOrdenadaAVL[i][j] += (double) cpuTime/5; ///tempo gasto/numero de seeds (para calcular a media)
                compRemocaoOrdenadaAVL[i][j] += (unsigned int) *copias/5; ///numero de comparacoes/numero de seeds (para calcular a media)
                copiasRemocaoOrdenadaAVL[i][j] += (unsigned int) *copias/5; ///numero de copias /numero de seeds (para calcular a media)
                /// DESEMPENHO DA REMOÇÃO ORDENADA AQUI;

                saidaRemocao << "\nRemoção Ordenada:";
                saidaRemocao << "NRemocao = " << NRemocao[j] << endl;
                saidaRemocao << "Tempo médio de Remocao: " << timeRemocaoAVL[i] << endl;
                saidaRemocao << "Número médio de comparações de chaves: " << compRemocaoAVL[i] << endl;
                saidaRemocao << "Número médio de cópias de registros : " << copiasRemocaoAVL[i] << endl;

                switch(ARVORE) {
                    case 1:
                        *myAVLAux = *myAVL;
                        break;
                    case 2:
                        *myAVLModAux = *myAVLMod;
                        break;
                    case 3: /// vp
                        break;
                    case 4: /// splay
                        break;
                    case 5: /// b
                        break;
                }

                delete [] gastoIdBuscaRemocao;
            }

            delete [] gastoIdInseridos;
            ///delete [] gastoIdBuscaRemocao;
        }
        /// ADICIONA ESTATISTICAS PARCIAIS

        saidaInsercao.close();
        saidaBusca.close();
        saidaRemocao.close();

        delete myAVL;
        delete myAVLAux;
        /// delete vp
        /// delete splay
        /// delete b
    }

    return 0;
}
