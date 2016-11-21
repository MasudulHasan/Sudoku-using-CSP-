#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
using namespace std;
//#define Max        100000
#define xx         first
#define yy         second
#define pb         push_back
#define ll         long long
//#define inf        INT_Max/3
#define mod        1000000007ll
#define PI         acos(-1.0)
#define linf       (1ll<<60)-1
#define FOR(I,A,B) for(int I = (A); I < (B); ++I)
#define REP(I,N)   FOR(I,0,N)
#define ALL(A)     ((A).begin(), (A).end())
#define set0(ar)   memset(ar,0,sizeof ar)
#define vsort(v)   sort(v.begin(),v.end())
#define setinf(ar) memset(ar,126,sizeof ar)
#define MaxC 100000
#define Max (1+(1<<6)) // Why? :D
#define inf 10007
#define vc vector<int>
#define pr pair<int,int>
int Board[11][11];
//vector < vc >Domain[11];
vc Domain[11][11];
vc Unit[11];
bool checkBoard[11][11];
int valueSelection=0,variableSelection=0;
vector< pair <int,int> > unassigned;

bool compare( pr a, pr b ) {
    if(Domain[a.first][a.second].size() < Domain[b.first][b.second].size())return a<b;
}

bool comparePair( pr a, pr b ) {
    return a.second>b.second;
}


bool DegreeCompare( pr a, pr b ) {
    int CountA=0,CountB=0;
    int I=a.first;
    int J=a.second;
    for(int j=1;j<=9;j++){
        if(Board[I][j]==0){
            CountA++;
        }
        if(Board[j][J]==0){
            CountA++;
        }
    }
    I=b.first;
    J=b.second;
    for(int j=1;j<=9;j++){
        if(Board[I][j]==0){
            CountB++;
        }
        if(Board[j][J]==0){
            CountB++;
        }
    }
    //if(CountA > CountB)return a>b;
    return CountA>CountB;
    //return a<b;
}

void InitialSetup(){
    int I=1,J=1,k=1;
    while(1){
        for(int i=I;i<I+3;i++){
            for(int j=J;j<J+3;j++){
                if(Board[i][j]!=0)Unit[k].push_back(Board[i][j]);
            }
        }
        I=I+3;
        k++;
        if(I==10){
            J=J+3;
            I=1;
        }
        if(I==1&&J==10)break;
    }
}

void printInitialSetup(){
    cout<<endl<<endl;
    for(int i=1;i<=9;i++){
        int Size=Unit[i].size();
        for(int k=0;k<Size;k++){
            cout<<Unit[i][k]<<",";
        }
        cout<<endl;
    }

}

void printInitialConstraint(){

    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            int Size=Domain[i][j].size();
            for(int k=0;k<Domain[i][j].size();k++){
                cout<<Domain[i][j][k];
                if(k<Size-1)cout<<",";
            }
            cout<<"     ";

        }
        cout<<endl;
    }

}

int getPosition(int I,int J){
    if((I>=1&&I<=3)&&(J>=1&&J<=3))return 1;
    if((I>=4&&I<=6)&&(J>=1&&J<=3))return 2;
    if((I>=7&&I<=9)&&(J>=1&&J<=3))return 3;
    if((I>=1&&I<=3)&&(J>=4&&J<=6))return 4;
    if((I>=4&&I<=6)&&(J>=4&&J<=6))return 5;
    if((I>=7&&I<=9)&&(J>=4&&J<=6))return 6;
    if((I>=1&&I<=3)&&(J>=7&&J<=9))return 7;
    if((I>=4&&I<=6)&&(J>=7&&J<=9))return 8;
    if((I>=7&&I<=9)&&(J>=7&&J<=9))return 9;
}

vc getDomain(int I,int J){
    set<int> s;
    for(int j=1;j<=9;j++){
        if(Board[I][j]!=0){
            s.insert(Board[I][j]);
        }
        if(Board[j][J]!=0){
            s.insert(Board[j][J]);
        }
    }

    int pos=getPosition(I,J);
    for(int i=0;i<Unit[pos].size();i++){
        s.insert(Unit[pos][i]);
    }
    int first[] = {1,2,3,4,5,6,7,8,9};
    int second[11];
    std::set<int>::iterator it;
    int i=0;
    /*cout<<"Element of the set "<<endl;
    for (it=s.begin(); it!=s.end(); ++it){
        std::cout << ' ' << *it;
    }*/

    for (it=s.begin(); it!=s.end(); ++it){
        second[i++]=*it;
    }
    std::vector<int> v(11);
    std::vector<int>::iterator It;
    std::sort (first,first+9);
    std::sort (second,second+i);
    It=std::set_difference (first, first+9, second, second+i, v.begin());
    v.resize(It-v.begin());
    /*std::cout << "The difference has " << (v.size()) << " elements:\n";
    for (It=v.begin(); It!=v.end(); ++It)
        std::cout << ' ' << *It;
    std::cout << '\n';
    s.clear();*/
    return v;
}

void SetInitialConstraint(){
    InitialSetup();
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(Board[i][j]!=0){
                Domain[i][j].push_back(Board[i][j]);
            }
            else{
                vector<int>v;
                v=getDomain(i,j);
                //cout<<i<<" "<<j<<" : ";
                if(v.size()==1){
                    Board[i][j]=v[0];
                }
                for(int k=0;k<v.size();k++){
                    Domain[i][j].push_back(v[k]);
                    //cout<<v[i]<<"  ";
                }
                //cout<<endl;
            }
        }
    }
}

void printBoard(){
    cout<<endl<<endl;
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            cout<<Board[i][j]<<" ";
        }
        cout<<endl;
    }

}

bool isAssignmentComplete(){
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(Board[i][j]==0)return false;
        }
    }
    return true;
}

bool isConsistant(int I,int J,int value){
    set<int> s;
    for(int j=1;j<=9;j++){
        if(Board[I][j]!=0){
            s.insert(Board[I][j]);
        }
        if(Board[j][J]!=0){
            s.insert(Board[j][J]);
        }
    }

    int pos=getPosition(I,J);
    for(int i=0;i<Unit[pos].size();i++){
        s.insert(Unit[pos][i]);
    }
    std::set<int>::iterator it;
    /*cout<<"Element of the set "<<endl;
    for (it=s.begin(); it!=s.end(); ++it){
        std::cout << ' ' << *it;
    }*/
    it=s.find(value);
    if(it==s.end())return true;
    else return false;
}

vc valueOdering(int x,int y,vc v){
    vector < pair<int,int> > tempvector;
    bool temp=false;
    int Total=0;
    for(int i=0;i<v.size();i++){
            Total=0;
        for(int j=1;j<=9;j++){
            if(Board[x][j]==0){
                temp=false;
                for(int k=0;k<Domain[x][j].size();k++){
                    if(Domain[x][j][k]==v[i]){
                        temp==true;
                        break;
                    }
                }
                if(temp){
                    Total+=Domain[x][j].size()-1;
                }
                else Total+=Domain[x][j].size();
            }
            if(Board[j][y]==0){
                temp=false;
                for(int k=0;k<Domain[j][x].size();k++){
                    if(Domain[j][y][k]==v[i]){
                        temp==true;
                        break;
                    }
                }
                if(temp){
                    Total+=Domain[j][y].size()-1;
                }
                else Total+=Domain[j][y].size();
            }
        }
        tempvector.push_back(make_pair(v[i],Total));

    }

    sort(tempvector.begin(),tempvector.end(),comparePair);
    vector<int>Rvector;
    for(int i=0;i<tempvector.size();i++){
        Rvector.push_back(tempvector[i].first);
    }
    return Rvector;

}


void forwardChecking(int x,int y,int value){
    int pos;
    bool temp=false;
    for(int j=1;j<=9;j++){
            if(j!=y){
                if(Board[x][j]==0){
                    temp=false;
                    for(int k=0;k<Domain[x][j].size();k++){
                        if(Domain[x][j][k]==value){
                            temp==true;
                            pos=k;
                            break;
                        }
                    }
                    if(temp){
                        Domain[x][j].erase(Domain[x][j].begin()+pos);
                    }
                }
            }
            if(j!=x){
            if(Board[j][y]==0){
                    temp=false;
                    for(int k=0;k<Domain[j][x].size();k++){
                        if(Domain[j][y][k]==value){
                            temp==true;
                            pos=k;
                            break;
                        }
                    }
                    if(temp){
                        Domain[j][y].erase(Domain[j][y].begin()+pos);
                    }
                }
            }
        }



}



bool recursiveBacktrack(int pos){
    if(isAssignmentComplete()){
        return true;
    }
    pair<int,int>var;
    //sort(unassigned.begin(),unassigned.end(),compare);
    //sort(unassigned.begin(),unassigned.end(),DegreeCompare);
    //cout<<"HERE "<<variableSelection<<endl;
    var=unassigned[pos];
    int x=var.first;
    int y=var.second;
    variableSelection++;
    //vc TempV=valueOdering(x,y,Domain[x][y]);
    //Domain[x][y]=TempV;
    //sort(Domain[x][y].begin(),Domain[x][y].end());
    for(int i=0;i<Domain[x][y].size();i++){
        bool temp=isConsistant(x,y,Domain[x][y][i]);
        if(!temp)continue;
        Board[x][y]=Domain[x][y][i];
        valueSelection++;
        //forwardChecking(x,y,Domain[x][y][i]);
        //unassigned.erase(unassigned.begin());
        //int Random=(rand()+10)%1971;
        //pos=(pos+Random)%unassigned.size();
        bool result=recursiveBacktrack(pos+1);
        if(!result){
            Board[x][y]=0;
            //unassigned.insert(unassigned.begin(),make_pair(x,y));
        }
        else return true;
    }
    return false;
}


int main()
{

//#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
//#endif


    int i,j,k,l,m,n,o,p,t,x1,x2,x3,x4,x5,x6,x7,x8,x9;
    for(int i=1;i<=9;i++){
        cin>>x1>>x2>>x3>>x4>>x5>>x6>>x7>>x8>>x9;
        Board[i][1]=x1;
        Board[i][2]=x2;
        Board[i][3]=x3;
        Board[i][4]=x4;
        Board[i][5]=x5;
        Board[i][6]=x6;
        Board[i][7]=x7;
        Board[i][8]=x8;
        Board[i][9]=x9;

    }
    printBoard();
    //InitialSetup();
    //getDomain(2,1);
    SetInitialConstraint();
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            if(Board[i][j]==0){
                unassigned.push_back(make_pair(i,j));
            }
        }
    }

    printBoard();
    //for(int i=0;i<unassigned.size();i++){
    //    cout<<unassigned[i].first<<" "<<unassigned[i].second<<endl;
    //}
    //printInitialConstraint();
    //cout<<endl<<endl;
    //printBoard();
    recursiveBacktrack(0);
    cout<<"Variable selection "<<variableSelection<<endl;
    cout<<"Value Selection "<<valueSelection<<endl;
    //vc TempV=valueOdering(1,4,Domain[1][4]);
    //cout<<endl<<endl;
    //for(int i=0;i<TempV.size();i++)cout<< TempV[i]<<" ";

    printBoard();
    return 0;

}
