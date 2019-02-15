/*

exemplu G :

        * 1
     /       \
    / 1        \  1
   *2--------*3
  |       77    |
  | 1            | 1
  *4--------*5
           66

G ca o colectie de muchii sortate crescator dupa costul este :
5
        cost
1 2     1
1 3     1
2 4     1
3 5     1
4 5     66
2 3     77

L intial este

       -------------------------
L : | 1 | 2   | 3   | 4   |  5 |
      -------------------------
        1     2      3      4      5


astfel :
parcurg sirul muchiilor ordonate dupa costuri
        - pentru muchie curenta (i,j) daca extremitatile sale in L
            sunt in arbori disjuncti atunci
                            - execut unificare ( nume nod extremitate "dreapta"
                                                il depun in arborele extremitatii "stangi"

OBS : evident sunt de practicat optimizari IMPORTANTE   !!!!

- citeste G(X,U)
- sorteaza muchiile din G crescator dupa costuri
- intializea L
- pentru i=1 pana la n-1 executa
                  pentru j=1 pana la m numarul de muchii executa
                          daca L[G[j][1]] !=L[G[j][2]]   atunci
                                      - afiseaza  G[j][1]  si G[j][2]
                                      -  pentru k=1 pana la n
                                            daca L[k]=L[G[j][2]] atunci L[k]=L[G[j][1]]


                                        sf_executa

==========================================
Optimizari de practicat in cazul alg lui Kruskal

Vizeaza o parcurgere eficienta a sirului de muchii in cautarea primei
cu extremitati in arbori disjuncti

Intentia practic inseamna ca fiecare noua parcurgere sa nu fie reluata
de la inceputul colectiei ci dupa ultima muchie care a generat o unificare

Adica fiecare noua parcurgere de tipul

                  pentru j=1 pana la m numarul de muchii executa
                          daca L[G[j][1]] !=L[G[j][2]]   atunci
                                      - afiseaza  G[j][1]  si G[j][2]
                                      -  pentru k=1 pana la n
                                            daca L[k]=L[G[j][2]] atunci L[k]=L[G[j][1]]


nu este eficient sa reinceapa cu 1 ( prima muchie din sir )
ci urmatoarea celei care a generat o unificare
( adica retin indexul acesteia si viitoare parcurgere incepe dupa acest index )

*/

#include<fstream>
#include<iostream>
using namespace std;
int n, m=1;
int top;
int l[100];

typedef struct
{
    int x;
    int y;
    double cost;
}muchie;

muchie v[100];

ifstream fin("input.dat");
ofstream fout("output.dat");

int read_data()
{
    fin>>n;
    while(true)
    {
        fin>>v[m].x;
        fin>>v[m].y;
        fin>>v[m].cost;
        m++;
        if(fin.eof()) break;
    }
    m=m-2;
    for(int i=1;i<=n;i++)
        l[i]=i;
    fin.close();
    return 0;
}

int sort_data()
{
    int g=0;
    while(g==0)
    {
        g=1;
        for(int i=1;i<m;i++)
            if(v[i].cost>v[i+1].cost)
            {
                swap(v[i].cost,v[i+1].cost);
                swap(v[i].x,v[i+1].x);
                swap(v[i].y,v[i+1].y);
                g=0;
            }
    }
}

int arbori()
{
    int i=0;
    for(int j=1;j<=m;j++)
    {
        if(l[v[j].x]!=l[v[j].y])
        {
            cout<<v[j].x<<" "<<v[j].y<<endl;
            int z=l[v[j].y];
            i++;
            for(int k=1;k<=n;k++)
                if(l[k]==z)
                    l[k]=l[v[j].x];
        }
        if(i==n-1)
            break;
    }
}

int main()
{
    read_data();
    sort_data();
    arbori();
}
