#include <iostream>
#include <math.h>
using namespace std;

int arr[11][1024];
int table[10];

int n,m;

int bits(int num)
{
    int res=0;
    while(num){
        res += num % 2;
        num /= 2;
    }
    return res;
}
void reset()
{
    for(int i=1;i<11;i++){
        for(int j=0;j<1024;j++){
            arr[i][j]=0;
        }
    }
}
void solve(int idx, int num, int past)
{
    if(idx==n+1)
        return;
    if(num&table[idx-1])
        return;
    if(num & num<<1)
        return;
    if(num & num>>1)
        return;
    if(num & past>>1)
        return;
    if(num & past<<1)
        return;
    
    // cout << idx << num << past << "\n";
    arr[idx][num] = arr[idx-1][past] + bits(num);
    for(int i=0;i<pow(2,m);i++){
        solve(idx+1,i,num);
    }
    return;
}

int main()
{
    int c;

    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> c;
    for(int i=0;i<c;i++){
        reset();
        cin >> n >> m;
        char* str;
        for(int j=0;j<n;j++){
            cin >> str;
            for(int k=0;k<m;k++){
                table[j] *= 2;
                if(str[k]=='x')
                    table[j] += 1;
            }
        }

        for(int j=0;j<pow(2,m);j++){
            solve(1,j,0);
        }
        int res=0;
        for(int j=1; j<=n; j++){
            for(int i=0;i<pow(2,m);i++){
                // cout << arr[n][i] << "\n";
                if(arr[j][i]>res)
                    res = arr[n][i];
            }   
        }
        cout << res << "\n";
    }
}