#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
using namespace std;

struct Data
{
    int y;
    int x;
    int cnt;
};

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--){
        int H, W; cin >> H >> W;
        vector<string> arr(H);
        map<char, int> key;
        string str;
        for(int i=0; i<H; i++) cin>>arr[i];
        cin >> str;
        if(str[0] != '0'){
            for(int i=0; i<str.length(); i++) key[str[i]]++;
        }

        int ans = 0, cnt = 0;
        vector<Data> start;
        for(int i=0; i<H; i++){
            if(arr[i][0] == '$'){
                cnt++;
                arr[i][0] = '.';
                start.push_back({i, 0, 0});
            }
            else if(arr[i][0] >= 'A' && arr[i][0] <= 'Z' && key[arr[i][0]] > 0){
                arr[i][0] = '.';
                start.push_back({i, 0, 0});
            }
            else if(arr[i][0] >= 'a' && arr[i][0] <= 'z'){
                key[arr[i][0]]++;
                arr[i][0] = '.';
                start.push_back({i, 0, 0});
            }
            if(arr[i][W-1] == '$'){
                cnt++;
                arr[i][W-1] = '.';
                start.push_back({i, W-1, 0});
            }
            else if(arr[i][W-1] >= 'A' && arr[i][W-1] <= 'Z' && key[arr[i][W-1]] > 0){
                arr[i][W-1] = '.';
                start.push_back({i, W-1, 0});
            }
            else if(arr[i][W-1] >= 'a' && arr[i][W-1] <= 'z'){
                key[arr[i][W-1]]++;
                arr[i][W-1] = '.';
                start.push_back({i, W-1, 0});
            }
        }
        for(int i=0; i<W; i++){
            if(arr[0][i] == '$'){
                cnt++;
                arr[0][i] = '.';
                start.push_back({0, i, 0});
            }
            else if(arr[0][i] >= 'A' && arr[0][i] <= 'Z' && key[arr[0][i]] > 0){
                arr[0][i] = '.';
                start.push_back({0, i, 0});
            }
            else if(arr[0][i] >= 'a' && arr[0][i] <= 'z'){
                key[arr[0][i]]++;
                arr[0][i] = '.';
                start.push_back({0, i, 0});
            }
            if(arr[H-1][i] == '$'){
                cnt++;
                arr[H-1][i] = '.';
                start.push_back({H-1, i, 0});
            }
            else if(arr[H-1][i] >= 'A' && arr[H-1][i] <= 'Z' && key[arr[H-1][i]] > 0){
                arr[H-1][i] = '.';
                start.push_back({H-1, i, 0});
            }
            else if(arr[H-1][i] >= 'a' && arr[H-1][i] <= 'z'){
                key[arr[H-1][i]]++;
                arr[H-1][i] = '.';
                start.push_back({H-1, i, 0});
            }
        }

        queue<Data> que;
        vector<vector<bool>> visited(H, vector<bool>(W));
        for(int i=0; i<start.size(); i++){
            que.push({start[i].y, start[i].x, cnt});
        }
        while(!que.empty()){
            Data cur = que.front();
            que.pop();
            
            int dy[4] = {-1 ,1, 0, 0};
            int dx[4] = {0, 0, -1, 1};
            for(int i=0; i<4; i++){
                int y = cur.y + dy[i];
                int x = cur.x + dx[i];
                if(y < 0 || y >= H || x < 0 || x >= W || arr[y][x] == '*' || visited[y][x]) continue;
                if(arr[y][x] == '$'){
                    arr[y][x] = '.';
                    cnt++;
                    visited[y][x] = true;
                    que.push({y, x, cnt});
                }
                else if(arr[y][x] >= 'A' && arr[y][x] <= 'Z' || key[arr[y][x]] > 0){
                    arr[y][x] = '.';
                    visited[y][x] = true;
                    que.push({y, x, cnt});
                }
                else if(arr[y][x] >= 'a' && arr[y][x] <= 'z'){
                    key[arr[y][x]]++;
                    while(!que.empty()) que.pop();
                    for(int i=0; i<start.size(); i++){
                        que.push({start[i].y, start[i].x, cnt});
                    }
                    visited[]
                }
            }
        }
    }

    return 0;
}