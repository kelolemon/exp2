//
// Created by 邓萌达 on 2019-06-14.
//

# include <cstdio>
# include <iostream>
# include <cstring>
# include <cmath>
# include <stack>
# include <utility>
# include <algorithm>

char a[100000];

struct node {
    char data;
    node *left_child;
    node *right_child;
};

inline void pause() {
    puts("");
    puts("successful! plz input the enter to continue");
    char p = getchar();
    p = getchar();
}

inline void put(char ch) {
    printf("%c", ch);
}

using namespace std;

inline void build(node *&x) {
    char ch;
    if ((ch = getchar()) == '#') {
        x = NULL;
        return;
    }
    x = (node *) malloc(sizeof(node));
    x->data = ch;
    build(x->left_child), build(x->right_child);
}

inline char getchar_file(FILE *input) {
    char ch;
    fscanf(input, "%c", &ch);
    return ch;
}

inline void create_tree(node *&x, FILE *input) {
    char ch;
    if ((ch = getchar_file(input)) == '#') {
        x = NULL;
        return;
    }
    x = (node *) malloc(sizeof(node));
    x->data = ch;
    create_tree(x->left_child, input), create_tree(x->right_child, input);
}

inline void _create_tree(node *&root) {
    node *st[100000];
    node *x;
    node *t;
    int i(1), flag(0), top(0);
    root = (node *) malloc(sizeof(node));
    root->data = a[i];
    i++;
    root->right_child = NULL;
    root->left_child = NULL;
    st[top++] = root;
    for (; a[i] != '\0';) {
        if (a[i] == '#' && flag == 0) flag = 1;
        else if (a[i] == '#' && flag == 1) {
            t = st[--top];
            for (; st[top - 1]->right_child == t;) t = st[--top];
        } else {
            x = (node *) malloc(sizeof(node));
            x->data = a[i];
            if (flag == 0) st[top - 1]->left_child = x, st[top++] = x;
            else st[top - 1]->right_child = x, flag = 0, st[top++] = x;
        }
        i++;
    }
}

inline void print_pre_code(node *x) {
    if (x == NULL) {
        put('#');
        return;
    }
    put(x->data);
    print_pre_code(x->left_child);
    print_pre_code(x->right_child);
}

inline void file_print_pre_code(node *x, FILE *output) {
    if (x == NULL) {
        fprintf(output, "%c", '#');
        return;
    }
    fprintf(output, "%c", x->data);
    file_print_pre_code(x->left_child, output);
    file_print_pre_code(x->right_child, output);
}

inline void print_middle_code(node *root) {
    if (root==NULL) return;
    stack < node * > st;
    node *x = root;
    for (; x != NULL || !st.empty();) {
        for (; x != NULL;) st.push(x), x = x->left_child;
        if (!st.empty()) {
            x = st.top();
            put(x->data);
            st.pop();
            x = x->right_child;
        }
    }
    return;
}

inline void print_suc_code(node *root) {
    if (root==NULL) return;
    stack < node * > st;
    node *x = NULL;
    node *y = NULL;
    st.push(root);
    for (; !st.empty();) {
        y = st.top();
        if ((y->left_child == NULL && y->right_child == NULL) ||
            (x != NULL && (x == y->left_child || x == y->right_child))) {
            put(y->data);
            st.pop();
            x = y;
        } else {
            if (y->right_child != NULL) st.push(y->right_child);
            if (y->left_child != NULL) st.push(y->left_child);
        }
    }
}

inline void destroy_tree(node *&x) {
    if (x == NULL) {
        free(x);
        return;
    }
    destroy_tree(x->left_child);
    destroy_tree(x->right_child);
    free(x);
}

int opt;
node *root1=(node*) malloc(sizeof(node));
node *root2=(node*) malloc(sizeof(node));
node *root3=(node*) malloc(sizeof(node));

int main() {
    a[0] = '$';
    puts("================exp2_1===================");
    for (;;) {
        puts("============input your choose you want to do ===================");
        puts("1.create the tree b1");
        puts("2.output the pre code and output in the file");
        puts("3.read from the file and create the b2 (Recursive way)");
        puts("4.read from the file and create the b3 (not Recursive way)");
        puts("5.put the middle code of the tree (not Recursive way)");
        puts("6.put the suc code of the tree (not Recursive way)");
        puts("7.destroy the tree b1,b2,b3");
        puts("-1.quite");
        scanf("%d", &opt);
        if (opt == 1) {
            puts("plz input the tree's pre code");
            puts("======");
            char ch = getchar();
            build(root1);
            pause();
        }
        if (opt == 2) {
            print_pre_code(root1);
            puts("");
            FILE *output;
            output = fopen("pre_code.dat", "w");
            file_print_pre_code(root1, output);
            fclose(output);
            pause();
        }
        if (opt == 3) {
            FILE *input;
            input = fopen("pre_code.dat", "r");
            create_tree(root2, input);
            fclose(input);
            pause();
        }
        if (opt == 4) {
            FILE *input;
            input = fopen("pre_code.dat", "r");
            fscanf(input, "%s", a + 1);
            _create_tree(root3);
            pause();
        }
        if (opt == 5) {
            print_middle_code(root2);
            puts("");
            pause();
        }
        if (opt == 6) {
            print_suc_code(root2);
            puts("");
            pause();
        }
        if (opt == 7) {
            destroy_tree(root1);
            destroy_tree(root2);
            destroy_tree(root3);
            pause();
        }
        if (opt == -1) break;
    }
}
