#include<iostream>
#include <list>
#include <stack>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
#define MAX 15

int teste_obj[3][3]={{1,2,3},
                     {4,5,6},
                     {7,8,0}};

struct Node {
    int arr[3][3];
    list<Node> antecessores;
    void printnode(int arr[3][3]);
};

struct NodeVisitado {
    int visitado[3][3];

};

void Node::printnode(int arr[3][3]){
    for (int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            cout << arr[i][j]<< " ";
        }
        cout << "\n";
    }
}

void print_antecessores(list<Node> &lista){

	list<Node> :: iterator it;

    for(it = lista.begin(); it != lista.end(); ++it){
		it->printnode(it->arr);
		cout<<"\n";
    }
}


bool checa_objetivo(Node node){

    for(int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            if(teste_obj[i][j]!=node.arr[i][j])
                return false;
        }
    }
    return true;
}

bool checa_visitado(Node node, list<NodeVisitado> &lista){

    list<NodeVisitado> :: iterator it;

    for(it = lista.begin(); it != lista.end(); ++it){
        int i=0, j=0;
        for(i=0; i<3; ++i){
            for(j=0; j<3; ++j){
                if(it->visitado[i][j]!=node.arr[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
}

void swap (Node node, int i, int j, int si, int sj, stack<Node> &pilha, list<NodeVisitado> &lista, NodeVisitado visit){

    int aux;
    int x=0, y=0;
    bool check;

    x=i+(si);
    y=j+(sj);

    node.antecessores.push_back(node);

    aux = node.arr[i][j];
    node.arr[i][j]=node.arr[x][y];
    node.arr[x][y]=aux;

    check=checa_visitado(node, lista);
        if(check==false){
        for(int i=0; i<3; ++i){
            for(int j=0; j<3; ++j){
                visit.visitado[i][j]=node.arr[i][j];
            }
        }

        pilha.push(node);
        lista.push_back(visit);

        node.printnode(node.arr);
        cout << "\n\n";
    }
    else
        cout << "ja visitado\n";

}

void expande (Node topo, stack<Node> &pilha, list<NodeVisitado> &lista, NodeVisitado visit){

int vi, vj;

    for(int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            if(topo.arr[i][j]==0){
                vi=i;
                vj=j;
            }
        }
    }

    if(vi+1<=2){
        swap(topo, vi, vj, 1, 0, pilha, lista, visit);
    }
    if(vj+1<=2){
        swap(topo, vi, vj, 0, 1, pilha, lista, visit);
    }
    if(vi-1>=0){
        swap(topo, vi, vj, -1, 0, pilha, lista, visit);
    }
    if(vj-1>=0){
        swap(topo, vi, vj, 0, -1, pilha, lista, visit);
    }
}

int main()
{
    Node topo;
    NodeVisitado visit;
    int i=0, j=0, cont=0;
    stack<Node> pilha;
    list<NodeVisitado> lista;
    bool fim;


    printf("Digite 0 para indicar o espaço vazio\n");

    for(i=0; i<3; ++i){
        for(j=0; j<3; ++j){
            cin >> topo.arr[i][j];
            visit.visitado[i][j]=topo.arr[i][j];
        }
    }
    pilha.push(topo);
    lista.push_back(visit);

    while(!pilha.empty()){
    	cont++;
        topo = pilha.top();
        pilha.pop();
        fim=checa_objetivo(topo);
        if(fim==true){
            cout << "resultado encontrado depois de " << cont << " iteracoes\n";
            print_antecessores(topo.antecessores);
            topo.printnode(topo.arr);
            return 0;
        }
        else{
            if(cont<MAX){
                expande(topo, pilha, lista, visit);
            }
        }
    }

    cout << "Resultado otimo nao encontrado";
    return 0;
}
