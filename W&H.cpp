#include<bits/stdc++.h>
#include<random>

using namespace std;

//defining
int currentIndex;
const int boardSize = 10;
char board[boardSize][boardSize];

//randomness setup
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> distr(0,boardSize-1);
//

class animal
{
    public:
    int ID;
    char type;
    int hunger;
    int x;
    int y;
    static void randomizePosition(int selfIndex);
    void hungerChecker(int selfIndex);
};


vector<animal> animals;

pair<char,int> collisionChecker(int x, int y)
{
    for(int i = 0; i<animals.size(); i++)
    {
        if(animals[i].x == x)
        {
            if(animals[i].y == y)
            {
                return make_pair(animals[i].type, i);
            }
        }
    }
    return make_pair('0','0');
}

int assignIndex()
{
    currentIndex++;
    return currentIndex;
}

void animal::randomizePosition(int selfIndex)
{
    int x,y, collisionerIndex;
    char collisionType;
    x = distr(gen);
    y = distr(gen);
    char type = animals[selfIndex].type;
    //meeting conditions

    collisionType = collisionChecker(x,y).first;
    collisionerIndex = collisionChecker(x,y).second;
    animals[selfIndex].x = x;
    animals[selfIndex].y = y;
    if(collisionType == '0');
    else if(type == 'H' && collisionType == 'H')
    {
        animal temp{};
        temp.ID = assignIndex();
        temp.type = 'H';
        animals.push_back(temp);
    }
    else if(type == 'H' && collisionType == 'W')
    {
        animals[collisionerIndex].hunger = 0;
        animals.erase(animals.begin() + selfIndex);
    }
    else if(type == 'W' && collisionType == 'H')
    {
        animals[selfIndex].hunger = 0;
        animals.erase(animals.begin() + collisionerIndex);
        cout<<"nigger";
    }
    else if(type == 'W' && collisionType == 'W')
    {
        animal temp{};
        temp.ID = assignIndex();
        temp.type = 'W';
        temp.hunger = 0;
        animals.push_back(temp);
    }
}

void animal::hungerChecker(int selfIndex)
{
    animals[selfIndex].hunger++;
    if(animals[selfIndex].hunger++>=5 && animals[selfIndex].type == 'W')
    {
        animals.erase(animals.begin()+selfIndex);
    }
}

void clearBoard()
{
    for(auto & i : board)
    {
        for(char & k : i)
        {
            k = ' ';
        }
    }
}

void updateProjection()
{
    clearBoard();
    
    for(auto & animal : animals)
    {
        board[animal.x][animal.y] = animal.type;
    }

    for(int i = 0; i<boardSize; i++)
    {
        for(int k = 0; k<boardSize; k++)
        {
            cout<<board[k][i]<<" ";
        }
        cout<<"\n";
    }
}

int main()
{  
    clearBoard();

    //declarations

    currentIndex = -1;
    int reps;
    cin>>reps;

    set<pair<int,int>> usedCords;

    //initialization

    for(int i = 0; i<20; i++)
    {
        animal temp{};
        temp.ID=assignIndex();
        temp.type='H';

        int x,y;
        while(true)
        {
            x = distr(gen);
            y = distr(gen);
            if(!usedCords.count(make_pair(x,y)))
            {
                temp.x = x;
                temp.y = y;
                usedCords.insert(make_pair(x,y));
                break;
            }
        }
        animals.push_back(temp);
    }
    for(int i = 0; i<5; i++)
    {
        animal temp{};
        temp.ID=assignIndex();
        temp.type='W';
        temp.hunger = 0;

        int x,y;
        while(true)
        {
            x = distr(gen);
            y = distr(gen);
            if(!usedCords.count(make_pair(x,y)))
            {
                usedCords.insert(make_pair(x,y));
                temp.x = x;
                temp.y = y;
                break;
            }
        }
        animals.push_back(temp);
    }

    //simulation

    for(int k = 0; k<reps; k++)
    {
        cout<<"\n"<<k<<"\n";
        updateProjection();
        for(int i = 0; i<animals.size(); i++)
        {
            animals[i].randomizePosition(i);
            animals[i].hungerChecker(i);
        }
    }
}