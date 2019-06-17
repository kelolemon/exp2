//
// Created by 邓萌达 on 2019-06-16.
//

# include <cstdio>
# include <iostream>
# include <cmath>
# include <queue>
# include <cstring>
# include <stack>

# define INF 1000000000

using namespace std;

int d[1000];
int v[1000];
int tot;
int n,m;

int x,y,z;


struct node {
    int s, t, w;
    int next; // 指向下一个以x为起点的边在p中的位置
} p[1000000];

int fel[1000000];
// fel 数组相当于一个指针，指向以x为起点的边在边表 p中的最后出现的位置，-1则不存在下一个

inline void init() {
    tot = 0;
    memset(fel, -1, sizeof(fel)); //初始化指针
}

int a[1000][1000];

inline void add_edge(int s, int t, int w) { //使用数组模拟指针
    p[tot].next = fel[s];
    p[tot].s = s, p[tot].t = t;
    p[tot].w = w;
    fel[s] = tot++;
}

int origin[1000][1000];

inline void read_info() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) a[i][j] = INF;
    for (int i = 1; i <= m; i++)
        scanf("%d%d%d", &x, &y, &z), add_edge(x, y, z), add_edge(y, x, z), a[x][y] = z, a[y][x] = z;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            origin[i][j]=a[i][j];
}

inline void init_spfa() {
    memset(v, 0, sizeof(v));
    for (int i = 1; i <= n; i++) d[i] = INF;
}

inline int find_min_path_spfa(int s, int t) {
    init_spfa();
    queue<int> q;
    d[s] = 0;
    v[s] = 1;
    int a_path[1000];
    a_path[s]=-1;
    q.push(s);
    for (; !q.empty();) {
        int x = q.front();
        q.pop();
        for (int i = fel[x]; i != -1; i = p[i].next) {
            int y = p[i].t;
            if (d[y] > d[x] + p[i].w) {
                d[y] = d[x] + p[i].w;
                a_path[y]=x;
                if (!v[y]) v[y] = 1, q.push(y);
            }
        }
    }
    int ans(d[t]);
    stack<int>st;
    st.push(t);
    for (;t!=s;){
        t=a_path[t];
        st.push(t);
    }
    st.pop();
    printf("%d",s);
    for (;!st.empty();st.pop()){
        printf("->%d",st.top());
    }
    printf(":");
    return ans;
}

int path[1000][1000];

inline void floyd() {
    FILE *output=fopen("ALLPath.dat","w");
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (i != j && a[i][j] != INF) path[i][j] = i;
            else path[i][j] = -1;
        }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (a[i][j] > a[i][k] + a[k][j])
                    a[i][j] = a[i][k] + a[k][j], path[i][j] = path[k][j];
    int a_path[1000];
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (a[i][j]!=INF && i!=j){
                fprintf(output,"%d->%d's_shortest_path_is_long:_%d.and_its_path_is:",
                        i,j,a[i][j]);
                int k=path[i][j];
                int t(0);
                a_path[t]=j;
                for (;k!=-1 && k!=i;){
                    t++,a_path[t]=k;
                    k=path[i][k];
                }
                t++,a_path[t]=i;
                fprintf(output,"%d->",i);
                for (int l=t-1;l;l--){
                    fprintf(output,"%dlong:%d.%d->",a_path[l],
                            origin[a_path[l+1]][a_path[l]],a_path[l]);
                }
                fprintf(output,"%d:%d",j,origin[a_path[1]][j]);
                fprintf(output,"\n");
            }
    fclose(output);
}

int easy[1000][1000];

inline int read_short_path(int s,int t){
    FILE *input=fopen("ALLPath.dat","r");
    for (int i=1;i<=n*n-n;i++){
        char st[1000];
        fscanf(input,"%s",st);
        if (st[0]-'0' == s && st[3]-'0'==t){
            printf("%s\n",st);
            break;
        }
    }
    fclose(input);
    return 1;
}

inline void pause() {
    puts("");
    puts("successful! plz input the enter to continue");
    char p = getchar();
    p = getchar();
}

inline void save_info(){
    FILE *output=fopen("path.dat","w");
    for (int x=1;x<=n;x++)
        for (int i=fel[x];i!=-1;i=p[i].next)
            fprintf(output,"%d->%d:%d\n",p[i].s,p[i].t,p[i].w);
    fclose(output);
}

int opt;

int main() {
    init();
    puts("==============exp2_2==============");
    for (;;){
        puts("============input your choose you want to do ===================");
        puts("1. input the path");
        puts("2. save all path");
        puts("3. search the two places' shortest path");
        puts("4. write the ALLPath.dat");
        puts("5. search the shortest path from ALLPath.dat");
        puts("-1. exit");
        scanf("%d",&opt);
        if (opt==1) read_info(),pause();
        if (opt==2) save_info(),pause();
        if (opt==3) {
            puts("plz input two places:");
            scanf("%d%d",&x,&y);
            cout<<find_min_path_spfa(x,y)<<endl;
            pause();
        }
        if (opt==4){
            floyd();
            pause();
        }
        if (opt==5){
            puts("plz input two places:");
            scanf("%d%d",&x,&y);
            read_short_path(x,y);
        }
        if (opt==-1) break;
    }
}