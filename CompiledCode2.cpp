#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    Node* lchild;
    string data;
    Node* rchild;
    int height;


};

class AVL{
public:
    Node* root;

    AVL(){ root = nullptr; }

    int NodeHeight(Node* p);
    int BalanceFactor(Node* p);
    Node* LLRotation(Node* p);
    Node* RRRotation(Node* p);
    Node* LRRotation(Node* p);
    Node* RLRotation(Node* p);

    Node* rInsert(Node* p, string key);
    void Inorder(Node* p);
    void Inorder(){ Inorder(root); }
    Node* getRoot(){ return root; }
    Node *search_movie(Node *p,string movie);
};

int AVL::NodeHeight(Node *p) {
    int hl;
    int hr;

    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;

    return hl > hr ? hl + 1 : hr + 1;
}

int AVL::BalanceFactor(Node *p) {
    int hl;
    int hr;

    hl = (p && p->lchild) ? p->lchild->height : 0;
    hr = (p && p->rchild) ? p->rchild->height : 0;

    return hl - hr;
}

Node* AVL::LLRotation(Node *p) {
    Node* pl = p->lchild;
    Node* plr = pl->rchild;

    pl->rchild = p;
    p->lchild = plr;

    p->height = NodeHeight(p);
    pl->height = NodeHeight(pl);

    if (root == p){
        root = pl;
    }
    return pl;
}

Node* AVL::RRRotation(Node *p) {
    Node* pr = p->rchild;
    Node* prl = pr->lchild;

    pr->lchild = p;
    p->rchild = prl;

    p->height = NodeHeight(p);
    pr->height = NodeHeight(pr);

    if (root == p){
        root = pr;
    }
    return pr;
}

Node* AVL::LRRotation(Node *p) {
    Node* pl = p->lchild;
    Node* plr = pl->rchild;

    pl->rchild = plr->lchild;
    p->lchild = plr->rchild;

    plr->lchild = pl;
    plr->rchild = p;

    pl->height = NodeHeight(pl);
    p->height = NodeHeight(p);
    plr->height = NodeHeight(plr);

    if (p == root){
        root = plr;
    }
    return plr;
}

Node* AVL::RLRotation(Node *p) {
    Node* pr = p->rchild;
    Node* prl = pr->lchild;

    pr->lchild = prl->rchild;
    p->rchild = prl->lchild;

    prl->rchild = pr;
    prl->lchild = p;

    pr->height = NodeHeight(pr);
    p->height = NodeHeight(p);
    prl->height = NodeHeight(prl);

    if (root == p){
        root = prl;
    }
    return prl;
}

Node* AVL::rInsert(Node *p, string key) {
    Node* t;
    if (p == nullptr){
        t = new Node;
        t->data = key;
        t->lchild = nullptr;
        t->rchild = nullptr;
        t->height = 1;
        return t;
    }

    if (key < p->data){
        p->lchild = rInsert(p->lchild, key);
    } else if (key > p->data){
        p->rchild = rInsert(p->rchild, key);
    }

    p->height = NodeHeight(p);

    if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == 1) {
        return LLRotation(p);
    } else if (BalanceFactor(p) == 2 && BalanceFactor(p->lchild) == -1){
        return LRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == -1){
        return RRRotation(p);
    } else if (BalanceFactor(p) == -2 && BalanceFactor(p->rchild) == 1){
        return RLRotation(p);
    }

    return p;
}

void AVL::Inorder(Node *p) {
    if (p){
        Inorder(p->lchild);
        cout << p->data << ", " << flush;
        Inorder(p->rchild);
    }
}
Node*AVL::search_movie(Node *p,string movie)
{
    bool flag;
    if(p==NULL)
    {
        flag=false;
    }
    else
    {

    if(p->data==movie)
    {
        flag=true;
    }
    else
    {
        rInsert(p,movie);
    }
    if(flag==false&&p->lchild!=NULL)
    {
        search_movie(p->lchild,movie);
    }
    if(flag==false&&p->rchild!=NULL)
    {
        search_movie(p->rchild,movie);
    }
    }
    return p;

}



int lives_count=9;

void lives(int index)
{
    if(index==0)
    {
        lives_count-=1;
        cout<<"You have "<<lives_count<<" lives."<<endl;
    }
}

int substring_matching(char input,string answer,string &masked)
{
    int flag = 0;
    for(long long unsigned int i=0;i<answer.size();i++)
    {
        if(answer[i]==input)
        {masked[i] = input; flag = 1;}
    }
    return flag;
}

int generateHash(string s,int mod) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    int len = s.length();
    unsigned long long int key = 0;

    for (int i=len-1; i>=0; i--) {
        key += pow(int(s[i]) - int('a'), i);
        key%=mod;
        // cout<<s<<" Key is: "<<key<<endl;
    }
    return key;
}

string handleSpaces(string str) {
    for (int i=0; i<str.size(); i++) {
        if (str[i] == ' ') {
            str[i] = '/';
        }
    }
    return str;
}

class HashTable {
    int capacity;
    int curlen;
    vector<string> hashtable;

    public:

    HashTable(): capacity(2003), curlen(0) {
        vector<string> mytable(capacity,"");
        hashtable = mytable;
    }

    void push(string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        long long int key;
        if (s.empty()) return;
        key = generateHash(s,capacity) % capacity;

        for (int i=0; i<capacity; i++) {
            if (hashtable[(key + i) % capacity] == "") {
                hashtable[(key+i)%capacity] = s;
                break;
            }
        }
        curlen++;
    }

    void print() {
        for (int i=0; i<capacity; i++) {
            if (hashtable[i] != "") cout<<i<<" "<<hashtable[i]<<", ";
        }
        cout<<endl;
    }

    //return 1 if found, 0 if not found
    int search(string mov) {
        transform(mov.begin(), mov.end(), mov.begin(), ::tolower);
        long long int k;
        k = generateHash(mov,capacity) % capacity;
        if (hashtable[k] == mov) return 1;
        for  (int i=0; i<capacity; i++) {
            if (hashtable[(k+i)%capacity] == mov) return 1;
            else if (hashtable[(k+i)%capacity] == "") return 0;
        }
        return 0;
    }
};

vector<string> suggest(char c, Node *root)
{
    vector<string> movies;
    if (!root) return movies;

    if (root->data[0] == c)
    {
        movies.push_back(root->data);
    }

    if (root->data[0] >= c)
    {
        vector<string> suggestions;
        suggestions = suggest(c, root->lchild);
        movies.insert(movies.end(), suggestions.begin(), suggestions.end());
    }

    if (root->data[0] <= c)
    {
        vector<string> suggestions;
        suggestions = suggest(c, root->rchild);
        movies.insert(movies.end(), suggestions.begin(), suggestions.end());
    }

    return movies;
}

void delay(long long int x) {
    int l;
    for (long long int i = 0; i<x; i++) {
        l=0;
    }
}

void printSuggestions(AVL tlr) {
    vector <string> suggestions;
    char c;
    cin>>c;
    suggestions = suggest(c, tlr.root);
    int suggestionslen = (suggestions.size() < 4)?suggestions.size():4;
    for (int i=0; i<suggestionslen; i++) {
        cout<<suggestions[i]<<endl;
    }
}


/*bool compare(string s1,string s2)
{
    int sum1=0,sum2=0;
    long long unsigned int size;
    if(s1.size()>=s2.size())
    {size=(s1.size());}
    else
    {size=(s2.size());}
    for(long long unsigned int i=0;i<size;i++)
    {
     if(i<s1.size())
       {sum1+=s1[i];}
     if(i<s2.size()) {
            sum2+=s2[i];
    }
    }
    if(sum1<sum2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
*/

int size1 = 0;

void movie_count(Node *root){
    if(root!=NULL)
    {
        size1++;
        movie_count(root->lchild);
        movie_count(root->rchild);
    }
}

Node* level_order(Node *root,int i)
{
    queue<Node*> q;
   q.push(root);
   while(!q.empty())
   {
      if(i<=0)
      {break;}
q.push(q.front()->lchild);
q.push(q.front()->rchild);
   if(q.front()!=NULL)
       {i--;}
       q.pop();

   }
   return q.front();

}

string rand_movie(Node* root)
{
    movie_count(root);
    int index=(rand())%7;
    return (level_order(root,index))->data;
}

string remove_consonants(string str)
{
    for(long long unsigned int i=0;i<str.size();i++)
    {
        if(str[i]!='a' && str[i]!='e' && str[i]!='i' && str[i]!='o' && str[i]!='u' && str[i]!=' ')
        {
          str[i]='-';
        }
        if (str[i] == ' ' || str[i] == '/') {
            str[i]='/';
        }
    }
    return str;
}

int menu() {
    cout<<"WELCOME TO HANGMAN!!!"<<endl;
    cout<<"This game was developed by Dhruv Gupta, Hrithik Bhagat, Shivam Singh and Kushagra Bansal."<<endl;
    cout<<"\n\nINSTRUCTIONS FOR THE GAME\n"<<endl;
    cout<<"You have 3 lives. Try to score as many points as possible. You have to guess 1 alphabet at a time.\n";
    cout<<"All the vowels of the movie are given and you have 9 chances to guess the movie correctly"<<endl;
    cout<<"Please select players: (1 or 2)"<<endl;

    int choice;
    cin>>choice;

    if (choice != 1 && choice != 2) {
        system("cls");
        return menu();
    }

    return choice;
}

int main()
{
    srand(time(0));  // Initialize random number generator.
    int mylives = 3;
    int choice = menu();

    vector<string> movies{"The Exorcist",
"Inception",
"Catch Me If You Can",
"The Lord of the Rings",
"Interstellar",
"Jurassic Park",
"Avengers: Infinity War",
"harry potter and half blood prince",
"lost",
"Inside Out",
"godfather",
"Blade Runner",
"Ratatouille",
"The Terminator",
"The Incredibles",
"The Amazing Spiderman",
"Gully Boy",
"Yeh Jawaani Hai Deewani",
"Hum Aapke Hain Kaun",
"Gangs of Wasseypur",
"Sardar Udham",
"Zindagi Na Milegi Dobara",
"Bajrangi Bhaijaan",
"Dilwale Dulhania Le Jayenge",
"Tiger Zinda Hai",
"Chennai Express",
"Prem Ratan Dhan Payo",
"Bhool Bhulaiyaa",
"Tanu Weds Manu",
"Thugs Of Hindostan",
"Toilet Ek Prem Katha",
"drishyam 2",
"thank god",
"ram setu",
"social network",
"shazam",
"the dark knight rises",
"jolly llb",
"iron man",
"thor",
"ant man",
"doctor strange",
"captain america the first avenger",
"black widow"};

    HashTable *table = new HashTable();

     AVL tlr;

    tlr.root = tlr.rInsert(tlr.root, "exorcist");
    tlr.root = tlr.rInsert(tlr.root, "inception");
    tlr.root = tlr.rInsert(tlr.root, "catch me if you can");
    tlr.root = tlr.rInsert(tlr.root, "the lord of the rings");
    tlr.root = tlr.rInsert(tlr.root, "interstellar");
    tlr.root = tlr.rInsert(tlr.root, "jurassic park");
    tlr.root = tlr.rInsert(tlr.root, "avengers infinity war");
    tlr.root = tlr.rInsert(tlr.root, "harry potter and half blood prince");
    tlr.root = tlr.rInsert(tlr.root, "lost");
    tlr.root = tlr.rInsert(tlr.root, "inside out");
    tlr.root = tlr.rInsert(tlr.root, "godfather");
    tlr.root = tlr.rInsert(tlr.root, "blade runner");
    tlr.root = tlr.rInsert(tlr.root, "ratatouille");
    tlr.root = tlr.rInsert(tlr.root, "the terminals");
    tlr.root = tlr.rInsert(tlr.root, "the incredibles");
    tlr.root = tlr.rInsert(tlr.root, "the amazing spider man");
    tlr.root = tlr.rInsert(tlr.root, "gully boy");
    tlr.root = tlr.rInsert(tlr.root, "yeh jawaani hai deewani");
    tlr.root = tlr.rInsert(tlr.root, "hum aapke hai kaun");
    tlr.root = tlr.rInsert(tlr.root, "gangs of wasseypur");
    tlr.root = tlr.rInsert(tlr.root, "sardar uddham");
    tlr.root = tlr.rInsert(tlr.root, "zindagi na milegi dobara");
    tlr.root = tlr.rInsert(tlr.root, "bajrangi bhaijan");
    tlr.root = tlr.rInsert(tlr.root, "dilwale dulhaniya le jayenge");
    tlr.root = tlr.rInsert(tlr.root, "tiger zinda hai");
    tlr.root = tlr.rInsert(tlr.root, "chennai express");
    tlr.root = tlr.rInsert(tlr.root, "prem ratan dhan payo");
    tlr.root = tlr.rInsert(tlr.root, "bhool bhulaiya");
    tlr.root = tlr.rInsert(tlr.root, "tanu weds manu");
    tlr.root = tlr.rInsert(tlr.root, "thugs of hindostan");
    tlr.root = tlr.rInsert(tlr.root, "toilet ek prem katha");
    tlr.root = tlr.rInsert(tlr.root, "the dark knight rises");
    tlr.root = tlr.rInsert(tlr.root, "thank god");
    tlr.root = tlr.rInsert(tlr.root, "ram setu");
    tlr.root = tlr.rInsert(tlr.root, "drishyam 2");
    tlr.root = tlr.rInsert(tlr.root, "social network");
    tlr.root = tlr.rInsert(tlr.root, "shazam");
    tlr.root = tlr.rInsert(tlr.root, "jolly llb");
    tlr.root = tlr.rInsert(tlr.root, "iron man");
    tlr.root = tlr.rInsert(tlr.root, "black widow");
    tlr.root = tlr.rInsert(tlr.root, "thor");
    tlr.root = tlr.rInsert(tlr.root, "captain america the first avenger");
    tlr.root = tlr.rInsert(tlr.root, "doctor strange");
    tlr.root = tlr.rInsert(tlr.root, "ant man");


    while (mylives > 0){

        lives_count = 9;
        string mymovie;
        system("cls");
        cout<<"You have "<<mylives<<" lives left"<<endl;
        if (choice == 1) {
            cout<<"SINGLE-PLAYER MODE"<<endl;
            mymovie = rand_movie(tlr.root);
            while (table->search(mymovie) == 1) { //hashtable
                mymovie = rand_movie(tlr.root);
            }
            delay(10000000000);
        }

        else {
            cout<<"MULTIPLAYER MODE"<<endl;
            cout<<"Enter a letter to get suggestions from our database: ";
            printSuggestions(tlr);
            cout<<"\n\nEnter a movie from our database or any other movie you want: \n\n"<<endl;
            std::getline(std::cin >> std::ws, mymovie);
            while (table->search(mymovie) == 1) {
                cout<<"This movie has already been used. Please select another movie"<<endl;
                std::getline(std::cin >> std::ws, mymovie);
                system("cls");
            }

            tlr.root = tlr.search_movie(tlr.root,mymovie);
            //tlr.Inorder();
            //delay(1000000000);t
        }

        table->push(mymovie);
        system("cls");
        string masked = remove_consonants(mymovie);
        mymovie = handleSpaces(mymovie);
        cout<<masked<<endl;

        while (lives_count>0 && mymovie!=masked) {
            char guess;
            cin>>guess;
            int res = substring_matching(guess, mymovie, masked);
            cout<<masked<<endl;
            lives(res);
        }
        system("cls");
        if (lives_count == 0) {
            cout<<"You have LOST!! Please try again...\n";
            mylives--;
        }
        else {
            cout<<"You have WON the game! SIIIUUUUUUUUUUU"<<endl;
        }

        delay(10000000000);
    }

    cout<<"Thanks for playing! Keep hanging!!"<<endl;
    delay(10000000000);
    /*

    cout<<mymovie<<endl;

    string movie;
    cin>>movie;
    tlr.search_movie(tlr.getRoot(),movie);
    tlr.Inorder();
    cout << endl;
    cout << tlr.root->data << endl;
    */

    return 0;
}
