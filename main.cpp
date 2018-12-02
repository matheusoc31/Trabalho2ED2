#include "./headers/libraries.h"

void printBT(const std::string& prefix, No_splay* node, bool isRight) {
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isRight ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->getInfo() << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isRight ? "│   " : "    "), node->getDir(), true);
        printBT( prefix + (isRight ? "│   " : "    "), node->getEsq(), false);
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

void preOrder(No_splay *root) {
    if(root != NULL)
    {
        printf("%d ", root->getInfo());
        preOrder(root->getEsq());
        preOrder(root->getDir());
    }
}

void copyTree(No_splay* from, No_splay* to) {

    if(from == NULL){
        to = NULL;
        return;
    }

    to->setInfo(from->getInfo());
    to->setDep(from->getDep());

    No_splay *esq, *dir;
    esq = new No_splay;
    dir = new No_splay;

    copyTree(from->getEsq(), esq);
    to->setEsq(esq);

    copyTree(from->getDir(), dir);
    to->setDir(dir);
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

    fstream deputados, entradaInsercao, saidaInsercao, entradaBusca, saidaBusca, entradaRemocao, saidaRemocao, teste;
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
    //int *gastoIdInseridos, *gastoIdBuscaRemocao;
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
    Arv_VP *myVP, *myVPAux;
    arv_splay *mySplay, *mySplayAux;
    arv_B *myB, *myBAux;

    deputados.open("deputies_dataset_tratado.csv", ios::in);

    if(!deputados.is_open()) {
        cout << "Sem dataset." << endl;
        delete [] comp;
        delete [] copias;
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
    cout << "Lendo conjunto de dados... ";
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
    cout << "Leitura concluída." << endl;

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
        delete [] comp;
        delete [] copias;
        return 0;
    }

    entradaInsercao >> qtdNInsercao;
    NInsercao = new int[qtdNInsercao];

    for(v = 0; v < qtdNInsercao; v++) {
        entradaInsercao >> NInsercao[v];
    }

    entradaInsercao.close();

    entradaBusca.open("entradaBusca.txt", ios::in | ios::binary);

    if(!entradaBusca.is_open()) {
        cout << "Sem entradaBusca." << endl;
        delete [] comp;
        delete [] copias;
        return 0;
    }

    entradaBusca >> qtdNBusca;
    NBusca = new int[qtdNBusca];

    for(v = 0; v < qtdNBusca; v++) {
        entradaBusca >> NBusca[v];
    }

    entradaBusca.close();

    entradaRemocao.open("entradaRemocao.txt", ios::in | ios::binary);

    if(!entradaRemocao.is_open()) {
        cout << "Sem entradaRemocao." << endl;
        delete [] comp;
        delete [] copias;
        return 0;
    }

    entradaRemocao >> qtdNRemocao;
    NRemocao = new int[qtdNRemocao];

    for(v = 0; v < qtdNRemocao; v++) {
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
            treeName = "./Resultados/VP/";
            break;
        case 4:
            treeName = "./Resultados/Splay/";
            break;
        case 5:
            treeName = "./Resultados/B/";
            break;
    }

    saidaInsercao.open(treeName + "saidaInsercao.txt", ios::app);
    saidaBusca.open(treeName + "saidaBusca.txt", ios::app);
    saidaRemocao.open(treeName + "saidaRemocao.txt", ios::app);

    switch(ARVORE) {
        case 1:
            cout << "** AVL **" << endl;
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
            cout << "** AVL Modificada **" << endl;
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
            cout << "** VP **" << endl;
            saidaInsercao << "************************" << endl;
            saidaInsercao << "VP\n" << endl;
            saidaInsercao << "************************" << endl;
            saidaBusca << "************************" << endl;
            saidaBusca << "VP\n" << endl;
            saidaBusca << "************************" << endl;
            saidaRemocao << "************************" << endl;
            saidaRemocao << "VP\n" << endl;
            saidaRemocao << "************************" << endl;
            break;
        case 4:
            cout << "** Splay **" << endl;
            saidaInsercao << "************************" << endl;
            saidaInsercao << "Splay\n" << endl;
            saidaInsercao << "************************" << endl;
            saidaBusca << "************************" << endl;
            saidaBusca << "Splay\n" << endl;
            saidaBusca << "************************" << endl;
            saidaRemocao << "************************" << endl;
            saidaRemocao << "Splay\n" << endl;
            saidaRemocao << "************************" << endl;
            break;
        case 5:
            cout << "** B **" << endl;
            saidaInsercao << "************************" << endl;
            saidaInsercao << "B\n" << endl;
            saidaInsercao << "************************" << endl;
            saidaBusca << "************************" << endl;
            saidaBusca << "B\n" << endl;
            saidaBusca << "************************" << endl;
            saidaRemocao << "************************" << endl;
            saidaRemocao << "B\n" << endl;
            saidaRemocao << "************************" << endl;
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
            myVP = new Arv_VP;
            myVPAux = new Arv_VP;
            break;
        case 4:
            mySplay = new arv_splay;
            mySplayAux = new arv_splay;
            break;
        case 5:
            myB = new arv_B(5);
            myBAux = new arv_B(5);
            break;

    }


    for(i = 0; i < qtdNInsercao; i++) {
        cout << "NInserção = " << NInsercao[i] << endl;
        saidaInsercao << "\nNInsercao = " << NInsercao[i] << endl;
        saidaBusca << "\n******** NInsercao = " << NInsercao[i] << " ********\n" << endl;
        saidaRemocao << "\n******** NInsercao = " << NInsercao[i] << " ********\n" << endl;

        if(NInsercao[i] == 500000)
            nSeed = 3;

        for(seedIdx = 0; seedIdx < nSeed; seedIdx++) {
            cout << "seed = " << seedVec[seedIdx] << endl;
            saidaInsercao << "****** seed = " << seedVec[seedIdx] << endl;
            saidaBusca << "****** seed = " << seedVec[seedIdx] << endl;
            saidaRemocao << "****** seed = " << seedVec[seedIdx] << endl;

            srand(seedVec[seedIdx]);
            int gastoIdInseridos[NInsercao[i]] = {0};

            /** 1.INSERÇÃO **/
            cout << "Inserindo gasto_id's..." << endl;
            for(k = 0; k < NInsercao[i]; k++) {
                gastoIdInseridos[k] = randomInt(0, nLines-1);
            }

            cout << "Inserindo deputados... ";
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
                        myVP->inserir(allDeputados[gastoIdInseridos[k]], comp, copias);
                        break;
                    case 4:
                        mySplay->insereDep(allDeputados[gastoIdInseridos[k]], comp, copias);
                        break;
                    case 5:
//                        teste.open("teste.txt", ios::app);
//                        cout << "gastoIdInseridos[" << k << "] = " << gastoIdInseridos[k] << ";" << endl;
//                        teste << "gastoIdInseridos[" << k << "] = " << gastoIdInseridos[k] << ";" << endl;
//                        teste.close();
                        myB->insere(allDeputados[gastoIdInseridos[k]], comp, copias);
                        break;
                }
            }
            endTime = clock();
            cpuTime = (double)(endTime - startTime)/(CLOCKS_PER_SEC);
            timeInsercaoAVL[i] += (double) cpuTime; ///tempo gasto/numero de seeds (para calcular a media)
            compInsercaoAVL[i] += (unsigned int) *comp; ///numero de comparacoes/numero de seeds (para calcular a media)
            copiasInsercaoAVL[i] += (unsigned int) *copias; ///numero de copias /numero de seeds (para calcular a media)
            /// DESEMPENHO DA INSERÇÃO AQUI;
            cout << "Deputados Inseridos." << endl;

            saidaInsercao << "Tempo de inserção: " << cpuTime << "s" << endl;
            saidaInsercao << "Número de comparações de chaves: " << *comp << endl;
            saidaInsercao << "Número de cópias de registros : " << *copias << endl;


            /** 2.BUSCA **/

            for(j = 0; j < qtdNBusca; j++) {
                cout << "NInsercao = " << NInsercao[i] << endl;
                cout << "seedIdx = " << seedIdx << endl;
                cout << "NBusca = " << NBusca[j] << endl;
                cout << "Montando vetor de gasto_id's..." << endl;

                int gastoIdBuscaRemocao[NBusca[j]] = {0};

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

                cout << "Buscando deputados... ";
                *comp = *copias = 0;
                startTime = clock();
                for(k = 0; k < NBusca[j]; k++) { /// BUSCA de fato
                    switch(ARVORE) {
                        case 1:
                            myAVL->buscaDep(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 2:
                            myAVLMod->buscaDep(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 3:
                            myVP->busca(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 4:
                            mySplay->buscaDep(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 5:
                            myB->busca(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                    }
                }
                endTime = clock();
                cpuTime = (double)(endTime - startTime)/(CLOCKS_PER_SEC);
                timeBuscaAVL[i][j] += (double) cpuTime; ///tempo gasto/numero de seeds (para calcular a media)
                compBuscaAVL[i][j] += (unsigned int) *comp; ///numero de comparacoes/numero de seeds (para calcular a media)
                copiasBuscaAVL[i][j] += (unsigned int) *copias; ///numero de copias /numero de seeds (para calcular a media)
                /// DESEMPENHO DA BUSCA AQUI;
                cout << "Busca concluída." << endl;

                saidaBusca << "\n***** NBusca = " << NBusca[j] << endl;
                saidaBusca << "Busca normal:" << endl;
                saidaBusca << "Tempo de busca: " << cpuTime << "s" << endl;
                saidaBusca << "Número de comparações de chaves: " << *comp << endl;
                saidaBusca << "Número de cópias de registros : " << *copias << endl;

                /// DUPLICA 30% do vetor gastoIdBuscaRemocao:
                cout << "Duplicando 30% do vetor de gasto_id's..." << endl;
                idxDup = (int) NBusca[j]*0.7;
                for(k = idxDup; k < NBusca[j]; k++) {
                    gastoIdBuscaRemocao[k] = gastoIdBuscaRemocao[k-idxDup];
                }
                /// ORDENA vetor gastoIdBuscaRemocao:
                cout << "Ordenando vetor..." << endl;
                ordena(gastoIdBuscaRemocao, NBusca[j], comp, copias);

                cout << "Buscando deputados ordenados... ";
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
                            myVP->busca(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 4:
                            mySplay->buscaDep(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 5:
                            myB->busca(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                    }
                }
                endTime = clock();
                cpuTime = (double)(endTime - startTime)/(CLOCKS_PER_SEC);
                timeBuscaOrdenadaAVL[i][j] += (double) cpuTime; ///tempo gasto/numero de seeds (para calcular a media)
                compBuscaOrdenadaAVL[i][j] += (unsigned int) *comp; ///numero de comparacoes/numero de seeds (para calcular a media)
                copiasBuscaOrdenadaAVL[i][j] += (unsigned int) *copias; ///numero de copias /numero de seeds (para calcular a media)
                /// DESEMPENHO DA BUSCA ORDENADA AQUI;
                cout << "Busca concluída." << endl;

                saidaBusca << "Busca Ordenada: " << endl;
                saidaBusca << "Tempo de busca ordenada: " << cpuTime << "s" << endl;
                saidaBusca << "Número de comparações de chaves: " << *comp << endl;
                saidaBusca << "Número de cópias de registros : " << *copias << endl;

            } /** FIM BUSCA **/


            /** 3.REMOÇÃO **/

            for(j = 0; j < qtdNRemocao; j++) {

                switch(ARVORE) {
                    case 1:
                        myAVL->deleteSubTree(myAVL->getRaiz());
                        myAVLAux->deleteSubTree(myAVLAux->getRaiz());
                        for(k = 0; k < NInsercao[i]; k++) {
                            myAVLAux->insereDep(allDeputados[gastoIdInseridos[k]], comp, copias);
                        }
                        break;
                    case 2:
                        myAVLMod->deleteSubTree(myAVLMod->getRaiz());
                        myAVLModAux->deleteSubTree(myAVLModAux->getRaiz());
                        for(k = 0; k < NInsercao[i]; k++) {
                            myAVLModAux->insereDep(allDeputados[gastoIdInseridos[k]], comp, copias);
                        }
                        break;
                    case 3:
                        myVPAux->deleteSubTree(myVPAux->getRaiz());
                        myVPAux->setRaiz(NULL);
                        for(k = 0; k < NInsercao[i]; k++) {
                            myVPAux->inserir(allDeputados[gastoIdInseridos[k]], comp, copias);
                        }
                        break;
                    case 4:
                        if(mySplayAux->getRaiz() != NULL) {
                            mySplayAux->deleteSubTree(mySplayAux->getRaiz()->getEsq());
                            mySplayAux->deleteSubTree(mySplayAux->getRaiz()->getDir());
                        }
                        mySplayAux->setRaiz(NULL);
                        for(k = 0; k < NInsercao[i]; k++) {
                            mySplayAux->insereDep(allDeputados[gastoIdInseridos[k]], comp, copias); /// VAI SER IGUAL A mySplay
                        }
                        break;
                    case 5:
                        myBAux->deletarArvore(myBAux->getRaiz());
                        delete myBAux->getRaiz();
                        myBAux->setRaiz(NULL);
                        for(k = 0; k < NInsercao[i]; k++) {
                            myBAux->insere(allDeputados[gastoIdInseridos[k]], comp, copias);
                        }
                        break;
                }

                cout << "NInsercao = " << NInsercao[i] << endl;
                cout << "seedIdx = " << seedIdx << endl;
                cout << "NRemocao = " << NRemocao[j] << endl;
                cout << "Montando vetor de gasto_id's... " << endl;

                int gastoIdBuscaRemocao[NRemocao[j]] = {0};

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


//                cout << "Preorder traversal of the tree (before 1st removal) is: " << endl;
//                myVP->preOrder(myVP->getRaiz());
//                cout << "BEFORE*********" << endl;
//                cout << endl;

                /// *********************************************************** ERRO NESSE BLOCO:

                cout << "Removendo deputados... ";
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
                            myVPAux->remover(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 4:
                            mySplayAux->removeDep(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 5:
                            myBAux->deletar(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                    }
                }
                endTime = clock();
                cpuTime = (double)(endTime - startTime)/(CLOCKS_PER_SEC);
                timeRemocaoAVL[i][j] += (double) cpuTime; ///tempo gasto/numero de seeds (para calcular a media)
                compRemocaoAVL[i][j] += (unsigned int) *comp; ///numero de comparacoes/numero de seeds (para calcular a media)
                copiasRemocaoAVL[i][j] += (unsigned int) *copias; ///numero de copias /numero de seeds (para calcular a media)
                /// DESEMPENHO DA REMOÇÃO AQUI;
                cout << "Remoção concluída" << endl;

                saidaRemocao << "\n***** NRemocao = " << NRemocao[j] << endl;
                saidaRemocao << "Remoção normal:" << endl;
                saidaRemocao << "Tempo de Remoção: " << cpuTime << "s" << endl;
                saidaRemocao << "Número de comparações de chaves: " << *comp << endl;
                saidaRemocao << "Número de cópias de registros : " << *copias << endl;


//                cout << "Preorder traversal of the tree (after 1st removal) is: " << endl;
//                myVP->preOrder(myVP->getRaiz());
//                cout << "AFTER*********" << endl;
//                cout << endl;


                /// ***********************************************************

//                cout << "Preorder traversal of the tree (before sorting) is: " << endl;
//                preOrder(mySplay2->getRaiz());
//                cout << endl;

                switch(ARVORE) {
                    case 1:
                        myAVL->deleteSubTree(myAVL->getRaiz());
                        myAVLAux->deleteSubTree(myAVLAux->getRaiz());
                        for(k = 0; k < NInsercao[i]; k++) {
                            myAVLAux->insereDep(allDeputados[gastoIdInseridos[k]], comp, copias);
                        }
                        break;
                    case 2:
                        myAVLMod->deleteSubTree(myAVLMod->getRaiz());
                        myAVLModAux->deleteSubTree(myAVLModAux->getRaiz());
                        for(k = 0; k < NInsercao[i]; k++) {
                            myAVLModAux->insereDep(allDeputados[gastoIdInseridos[k]], comp, copias);
                        }
                        break;
                    case 3:
                        myVPAux->deleteSubTree(myVPAux->getRaiz());
                        myVPAux->setRaiz(NULL);
                        for(k = 0; k < NInsercao[i]; k++) {
                            myVPAux->inserir(allDeputados[gastoIdInseridos[k]], comp, copias);
                        }
                        break;
                    case 4:
                        mySplayAux->deleteSubTree(mySplayAux->getRaiz()->getEsq());
                        mySplayAux->deleteSubTree(mySplayAux->getRaiz()->getDir());
                        mySplayAux->setRaiz(NULL);
                        for(k = 0; k < NInsercao[i]; k++) {
                            mySplayAux->insereDep(allDeputados[gastoIdInseridos[k]], comp, copias); /// VAI SER IGUAL A mySplay
                        }
                        break;
                    case 5:
                        myBAux->deletarArvore(myBAux->getRaiz());
                        delete myBAux->getRaiz();
                        myBAux->setRaiz(NULL);
                        for(k = 0; k < NInsercao[i]; k++) {
                            myBAux->insere(allDeputados[gastoIdInseridos[k]], comp, copias);
                        }
                        break;
                }


                /// DUPLICA 30% do vetor gastoIdBuscaRemocao:
                cout << "Duplicando 30% do vetor de gasto_id's..." << endl;
                idxDup = (int) NRemocao[j]*0.7;
                for(k = idxDup; k < NRemocao[j]; k++) {
                    gastoIdBuscaRemocao[k] = gastoIdBuscaRemocao[k-idxDup];
                }
                /// ORDENA vetor gastoIdBuscaRemocao:
                cout << "Ordenando vetor... " << endl;
                ordena(gastoIdBuscaRemocao, NRemocao[j], comp, copias);


//                for(k = 0; k < NRemocao[j]; k++) {
//                    cout << gastoIdBuscaRemocao[k] << " ";
//                } cout << endl << "NInsercao = " << NInsercao[i] << "; NRemocao = " << NRemocao[j] << endl;
//
//
//                cout << "is raiz NULL? " << (mySplay->getRaiz() == NULL) << endl;
//
//                cout << "Preorder traversal of the Tree is: " << endl;
//                preOrder(mySplay->getRaiz());


                cout << "Removendo deputados ordenados... ";
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
                            myVPAux->remover(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 4:
                            mySplayAux->removeDep(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                        case 5:
                            myBAux->deletar(gastoIdBuscaRemocao[k], comp, copias);
                            break;
                    }
                }
                endTime = clock();
                cpuTime = (double)(endTime - startTime)/(CLOCKS_PER_SEC);
                timeRemocaoOrdenadaAVL[i][j] += (double) cpuTime; ///tempo gasto/numero de seeds (para calcular a media)
                compRemocaoOrdenadaAVL[i][j] += (unsigned int) *comp; ///numero de comparacoes/numero de seeds (para calcular a media)
                copiasRemocaoOrdenadaAVL[i][j] += (unsigned int) *copias; ///numero de copias /numero de seeds (para calcular a media)
                /// DESEMPENHO DA REMOÇÃO ORDENADA AQUI;
                cout << "Remoção concluída" << endl;

                saidaRemocao << "\nRemoção Ordenada:" << endl;
                saidaRemocao << "Tempo de Remoção: " << cpuTime << "s" << endl;
                saidaRemocao << "Número de comparações de chaves: " << *comp << endl;
                saidaRemocao << "Número de cópias de registros : " << *copias << endl;

            } /** FIM REMOÇÃO **/

            switch(ARVORE) {
                case 1:
                    myAVL->deleteSubTree(myAVL->getRaiz());
//                    myAVL->deleteSubTree(myAVL->getRaiz()->getRight());
                    myAVL->setRaiz(NULL);

                    myAVLAux->deleteSubTree(myAVLAux->getRaiz());
//                    myAVLAux->deleteSubTree(myAVLAux->getRaiz()->getRight());
                    myAVLAux->setRaiz(NULL);
                    break;
                case 2:
                    myAVLMod->deleteSubTree(myAVLMod->getRaiz());
//                    myAVLMod->deleteSubTree(myAVLMod->getRaiz()->getRight());
                    myAVLMod->setRaiz(NULL);

                    myAVLModAux->deleteSubTree(myAVLModAux->getRaiz());
//                    myAVLModAux->deleteSubTree(myAVLModAux->getRaiz()->getRight());
                    myAVLModAux->setRaiz(NULL);
                    break;
                case 3:
                    myVP->deleteSubTree(myVP->getRaiz());
                    myVP->setRaiz(NULL);

                    myVPAux->deleteSubTree(myVPAux->getRaiz());
                    myVPAux->setRaiz(NULL);
                    break;
                case 4:
                    mySplay->deleteSubTree(mySplay->getRaiz()->getEsq());
                    mySplay->deleteSubTree(mySplay->getRaiz()->getDir());
                    mySplay->setRaiz(NULL);

                    mySplayAux->deleteSubTree(mySplayAux->getRaiz()->getEsq());
                    mySplayAux->deleteSubTree(mySplayAux->getRaiz()->getDir());
                    mySplayAux->setRaiz(NULL);
                    break;
                case 5:
                    myB->deletarArvore(myB->getRaiz());
                    delete myB->getRaiz();
                    myB->setRaiz(NULL);

                    myBAux->deletarArvore(myBAux->getRaiz());
                    delete myBAux->getRaiz();
                    myBAux->setRaiz(NULL);
                    break;
            }
        } /** FIM SEED **/

        /// ADICIONA ESTATISTICAS PARCIAIS

        saidaInsercao << "\n*********************" << endl;
        saidaInsercao << "NInsercao = " << NInsercao[i] << endl;
        saidaInsercao << "Tempo médio de inserção: " << (double) timeInsercaoAVL[i]/5.0 << "s" << endl;
        saidaInsercao << "Número médio de comparações de chaves: " << compInsercaoAVL[i]/5 << endl;
        saidaInsercao << "Número médio de cópias de registros: " << copiasInsercaoAVL[i]/5 << endl;
        saidaInsercao << "*********************\n" << endl;

    } /** FIM INSERÇÃO **/

    delete [] comp;
    delete [] copias;
    delete [] allDeputados;
    delete [] NInsercao;
    delete [] NBusca;
    delete [] NRemocao;

    switch(ARVORE) {
        case 1:
            delete myAVL;
            delete myAVLAux;
            break;
        case 2:
            delete myAVLMod;
            delete myAVLModAux;
            break;
        case 3:
            delete myVP;
            delete myVPAux;
            break;
        case 4:
            delete mySplay;
            delete mySplayAux;
            break;
        case 5:
            delete myB;
            delete myBAux;
            break;
    }

    saidaInsercao.close();
    saidaBusca.close();
    saidaRemocao.close();

    return 0;
}
