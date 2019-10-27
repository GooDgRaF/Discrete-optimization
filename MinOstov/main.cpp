#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


unsigned int i,k;


double x,y;


struct point
 {
     unsigned int ID;
     double x;
     double y;
 };

struct edge
{
    point v;
    point w;
    double weight;
} ;

vector<point> Points;
vector<edge> Edges;


double distanceM (point &v, point &w)
{
    double d = abs(v.x - w.x)+abs(v.y - w.y);
    return d;
}

void Merge(unsigned int v, unsigned int w, unsigned int p, unsigned int q,
            vector<unsigned int> &tree_id, vector<unsigned int> &circular_list, vector<unsigned int> &size_of_tree)
{
    unsigned int u,tmpV, tmpW;
    tree_id[w] = p; u = circular_list[w];
    while (tree_id[u] != p)
    {
        tree_id[u] = p; u = circular_list[u];
    }
   size_of_tree[p] = size_of_tree[p] + size_of_tree[q];
   tmpV = circular_list[v]; tmpW = circular_list[w];
   circular_list[v] = tmpW; circular_list[w] = tmpV;
};
int main()
{
/** ����� 1 ���������� ������� ����� **/

    /** ��������� ���� ��� ������ **/

    ifstream inputFile;
    inputFile.open("in.txt");

    if (inputFile.is_open())
    {
        cout << "Let's start!\n";
    }
    else
    {
       cout << "Error. Can't open file!";
       return -1;

    }cout << endl;

    /** ��������� ������ Points **/
inputFile >> k;
i = 0;
    for (unsigned int s = k; s>0;s--)
    {
        inputFile >> x >> y;
        Points.push_back(point{i,x,y});
        i++;
    }

    inputFile.close();

    /** ��������� ������ Edges **/

    for (unsigned int i = 0; i<k; i++)
    {
        for (unsigned int j = 0; j < k;j++)
        {
            if (j > i)
            {

                Edges.push_back(edge{Points[i],Points[j],distanceM(Points[i],Points[j])});
            }

        }

    }



/** ����� 2 �������� �������-�������� **/

unsigned int cost(0);
vector<edge> minSpantree;

    /** �������������� ������ ��������, �������� �������� �� ���� � ��������� ������**/
vector<unsigned int> tree_id(k);
for (unsigned int i=0; i<k; i++) {tree_id[i] = i;}

vector<unsigned int> size_of_tree(k,1);

vector<unsigned int> circular_list(k);
for (unsigned int i=0; i<k; i++) {circular_list[i] = i;}


    /** ��������� ������ Edges �� �� �������� ����� **/

    sort(Edges.begin(),Edges.end(),[](const edge &ed, const edge &rib){return ed.weight <= rib.weight; });

    /** ��� �������� **/

    for (unsigned int j = 0; minSpantree.size() != k-1; j++)
    {
        int p,q,v,w;
        v = Edges[j].v.ID;
        w = Edges[j].w.ID;
        p = tree_id[v];
        q = tree_id[w];

        if (p != q)
        {
            if (size_of_tree[p] > size_of_tree[q])
            {
                Merge(w,v,q,p, tree_id, circular_list, size_of_tree);
            }
            else
                {Merge(v,w,p,q, tree_id, circular_list, size_of_tree);}
            minSpantree.push_back(Edges[j]);
            cost = cost + Edges[j].weight;
        }
    }

/** ����� 3 ������ � ��������� ���� **/

    /** ��������� ���� ��� ������ **/

ofstream outFile;
outFile.open("out.txt");
    if (outFile.is_open())
    {
        cout << "Let's write!\n";
    }
    else
    {
       cout << "Error. Can't open file!";
       return -1;

    }cout << endl;


    /** ������ ������ ��������� � �������� � ���� **/


vector<unsigned int> print_to_file;


 for (unsigned int i = 0; i < Points.size(); i++)
 {   print_to_file.clear();
     for (unsigned int j = 0; j < minSpantree.size(); j++)
     {
         if (minSpantree[j].v.ID == i)
         {
             print_to_file.push_back(minSpantree[j].w.ID + 1);
         }

     }
     for (unsigned int j = 0; j < minSpantree.size(); j++)
     {
        if (minSpantree[j].w.ID == i)
         {
             print_to_file.push_back(minSpantree[j].v.ID + 1);
         }
     }

     sort(print_to_file.begin(), print_to_file.end());

     for (const auto &element : print_to_file)
    {
        outFile << element << " ";
    }

     outFile << 0 <<  endl;
 }


outFile << cost;

outFile.close();
    cout << "Well done!" << endl;


    return 0;
}
