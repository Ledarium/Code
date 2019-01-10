#include <bits/stdc++.h>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

#define sz(a) int(a.size())
#define pb(e) push_back(e)
#define mp make_pair
#define vD(x) cerr << #x << "=" << x << "\n";
#define cD(x) {for (auto it: x) cerr << it << " "; cerr << endl;}
#define cont_read(cont, size) for (int tmp = 0; tmp<size; tmp++) cin >> cont[tmp];
#define bit_set(var, bit) var |= (1<<bit) //set bit to 1
#define bit_rem(var, bit) var &= ~(1<<bit) // set bit to 0
#define bit_chk(var, bit) (var & (1<<bit)) //check bit
#define bit_swp(var, bit) var ^= (1<<bit) //0 -> 1, 1 -> 0
typedef long long ll;
typedef vector<int> vi;
typedef set<int> si;

int q(string a)
{
    int out = 0;
    for(int i = 0; i<sz(a); i++)
    {
        a[i] = (a[i]-'0')%2+'0';
    }
    vD(a);
    a.erase(0, min(a.find_first_not_of('0'), a.size()-1));
    for(auto it = a.rbegin(); it<a.rend(); it++)
    {
        out <<= 1;
        out+=(*it-'0')%2;
    }
    return(out);
}

int main()
{
    cin.sync_with_stdio(0);
    unsigned int mas[1000000];
    unsigned int t;
    string k;
    char typ;
    cin >> t;
    for(int i=0; i<t; i++)
    {
        cin >> typ >> k;
        if(typ=='?')
            cout << mas[q(k)] << '\n';
        else
        {
            if(typ=='+')
                mas[q(k)]+=1;
            else
                mas[q(k)]-=1;
        }
    }
#ifdef DEBUG
    printf("\nTime elapsed: %ldms", 1000 * (int)clock() / CLOCKS_PER_SEC);
#endif
}
