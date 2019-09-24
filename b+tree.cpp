#include<iostream>
#include<cmath>
#include<algorithm>
#include<fstream>
using namespace std;
struct tree{
    string **data = new string*[10];
    int i;
    tree()
    {
        for(i=0; i<10; i++)
        {
            data[i] = new string[2];
        }
    }
    tree* link[25] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
    tree* prev = NULL;
    int number = 0;
};
tree* root = NULL;
ofstream ofile;
tree* findBlock(string a, tree* t1){
    if(!(*t1).link[0]){
        return t1;
    }
    for(int i=0; i<10; i++){
        if ((*t1).number == i || a < (*t1).data[i][0]){
            t1 = (*t1).link[i];
            return findBlock(a, t1);
        }
        else if((*t1).link[i+1] == NULL){
            tree *t3 = new tree();
            (*t3).prev = t1;
            (*t1).link[i+1] = t3;
            return t3;
        }
    }
    if(a >= (*t1).data[9][0]){
        t1 = (*t1).link[10];
        return findBlock(a, t1);
    }
}

void bubbleSort(string **arr, int n){
    int i, j;
    for (i = 0; i < n-1; i++)
    for (j = 0; j < n-i-1; j++)
        if (arr[j][0] > arr[j+1][0]){
            swap(arr[j][0], arr[j+1][0]);
            swap(arr[j][1], arr[j+1][1]);
        }
}

void link_leaf(tree *temp){
    if(!temp || !(*temp).link[0]){
        return;
    }
    while((*(*temp).link[0]).link[0] != NULL){
        temp = (*temp).link[0];
    }
    if(temp == root){
        for(int i=0; i<(*temp).number; i++){
            tree *t1 = (*temp).link[i];
            (*t1).link[(*t1).number] = (*temp).link[i+1];
        }
    }
    else{
        tree *t1 = (*temp).prev;
        for(int i=0; i<(*t1).number; i++){
            tree *t2 = (*t1).link[i];
            tree *t3 = (*t2).link[(*t2).number];
            (*t3).link[(*t3).number] = (*(*t1).link[i+1]).link[0];
            for(int i=0; i<(*t2).number; i++){
                tree *t4 = (*t2).link[i];
                (*t4).link[(*t4).number] = (*t2).link[i+1];
            }
        }
        tree *t2 = (*t1).link[(*t1).number];
        for(int i=0; i<(*t2).number; i++){
                tree *t4 = (*t2).link[i];
                (*t4).link[(*t4).number] = (*t2).link[i+1];
            }
    }
}

void insert_in_tree(string a, string b, tree* t1, tree* c1, tree* c2){
    if((*t1).number < 10){
        (*t1).data[(*t1).number][0] = a;
        (*t1).data[(*t1).number][1] = b;
        if((*t1).number == 0){
            (*t1).number++;
            (*t1).link[0] = c1;
            (*t1).link[1] = c2;
            if(c1 != NULL){
                if((*c1).link[0] == NULL){
                    (*c1).link[(*c1).number] = c2;
                }
            }
            return;
        }
        int position = (*t1).number;
        for(int i=0; i<(*t1).number; i++){
            if(a <= (*t1).data[i][0]){
                position = i;
                break;
            }
        }
        for(int i=(*t1).number; i>position; i--){
            (*t1).data[i][0] = (*t1).data[i-1][0];
            (*t1).data[i][1] = (*t1).data[i-1][1];
        }
        (*t1).data[position][0] = a;
        (*t1).data[position][1] = b;
        (*t1).number++;
        if(position == 9 || position == (*t1).number - 1){
            (*t1).link[position] = c1;
            (*t1).link[position+1] = c2;
        }
        else{
            for(int i=10; i>=position+1; i--){
                (*t1).link[i] = (*t1).link[i-1];
            }
            (*t1).link[position] = c1;
            (*t1).link[position+1] = c2;
        }
        if(c1 == NULL){
            (*t1).link[(*t1).number] = (*t1).link[(*t1).number - 1];
            (*t1).link[(*t1).number - 1] = NULL;
        }
        return;
    }
    else if((*t1).link[0] == NULL){
        string **arr = new string*[11];
        for(int i=0; i<11; i++){
        	arr[i] = new string[2];
        }
        arr[0][0] = a;
        arr[0][1] = b;
        for(int i=1; i<11; i++){
            arr[i][0] = (*t1).data[i - 1][0];
            arr[i][1] = (*t1).data[i - 1][1];
        }
        bubbleSort(arr, 11);
        tree *tn1 = new tree();
        tree *tn2 = new tree();
        for(int i=0; i<6; i++){
            (*tn1).data[i][0] = arr[i][0];
            (*tn1).data[i][1] = arr[i][1];
        }
        for(int i=6; i<11; i++){
            (*tn2).data[i-6][0] = arr[i][0];
            (*tn2).data[i-6][1] = arr[i][1];
        }
        (*tn1).number = 6;
        (*tn2).number = 5;
        tree *temp;
        if(t1 == root){
            tree *tn3 = new tree();
            (*tn3).number = 0;
            (*tn3).prev = NULL;
            root = tn3;
            temp = root;
            (*tn1).prev = root;
            (*tn2).prev = root;
            insert_in_tree((*tn2).data[0][0], (*tn2).data[0][1], tn3, tn1, tn2);
        }
        else{
            temp = (*t1).prev;
            (*tn1).prev = temp;
            (*tn2).prev = temp;
            insert_in_tree((*tn2).data[0][0], (*tn2).data[0][1], temp, tn1, tn2);
        }
        link_leaf(root);
    }
    else{
        string **arr = new string*[11];
        for(int i=0; i<11; i++){
        	arr[i] = new string[2];
        }
        arr[0][0] = a;
        arr[0][1] = b;
        for(int i=1; i<11; i++){
            arr[i][0] = (*t1).data[i - 1][0];
            arr[i][1] = (*t1).data[i - 1][1];
        }
        bubbleSort(arr, 11);
        tree *tn1 = new tree();
        tree *tn2 = new tree();
        for(int i=0; i<5; i++){
            (*tn1).data[i][0] = arr[i][0];
            (*tn1).data[i][1] = arr[i][1];
        }
        for(int i=6; i<11; i++){
            (*tn2).data[i-6][0] = arr[i][0];
            (*tn2).data[i-6][1] = arr[i][1];
        }
        (*tn1).number = 5;
        (*tn2).number = 5;
        tree *temp;
        if(t1 == root){
            temp = new tree();
            (*temp).data[0][0] = arr[5][0];
            (*temp).data[0][1] = arr[5][1];
            (*temp).number = 1;
            (*temp).link[0] = tn1;
            (*temp).link[1] = tn2;
            root = temp;
            (*tn1).prev = root;
            (*tn2).prev = root;
        }
        else{
            temp = (*t1).prev;
            (*tn1).prev = temp;
            (*tn2).prev = temp;
            insert_in_tree(arr[5][0], arr[5][1], temp, tn1, tn2);
        }
        for(int i=0; i<5; i++){
            for(int j=0; j<6; j++){
                if((*tn1).data[i][0] == (*t1).data[j][0]){
                    (*tn1).link[i] = (*t1).link[j];
                    (*tn1).link[i+1] = (*t1).link[j+1];
                    (*(*t1).link[j]).prev = tn1;
                    (*(*t1).link[j+1]).prev = tn1;
                    break;
                }
            }
        }
        for(int i=0; i<5; i++){
            for(int j=5; j<10; j++){
                if((*tn2).data[i][0] == (*t1).data[j][0]){
                    (*tn2).link[i] = (*t1).link[j];
                    (*tn2).link[i+1] = (*t1).link[j+1];
                    (*(*t1).link[j]).prev = tn2;
                    (*(*t1).link[j+1]).prev = tn2;
                    break;
                }
            }
        }
        if((*c1).data[0][0] < arr[5][0]){
            if((*c1).data[0][0] >= (*tn1).data[(*tn1).number - 1][0]){
                (*tn1).link[(*tn1).number] = c1;
                (*tn2).link[0] = c2;
                (*c1).prev = tn1;
                (*c2).prev = tn2;
            }
            else{
                for(int i=0; i<5; i++){
                    if((*c1).data[0][0] < (*tn1).data[i][0]){
                        (*tn1).link[i] = c1;
                        (*tn1).link[i+1] = c2;
                        (*c1).prev = tn1;
                        (*c2).prev = tn1;
                        break;
                    }
                }
            }
        }
        else{
                for(int i=0; i<5; i++){
                    if((*c1).data[0][0] < (*tn2).data[i][0]){
                        (*tn2).link[i] = c1;
                        (*tn2).link[i+1] = c2;
                        (*c1).prev = tn2;
                        (*c2).prev = tn2;
                        break;
                    }
                }
        }
        link_leaf(root);
        return;
    }
}

void leafTraverse(){
    tree *traversal = root;
    while((*traversal).link[0] != NULL){
        traversal = (*traversal).link[0];
    }
    while(traversal != NULL){
        for(int i=0; i<(*traversal).number; i++){
            //cout<<(*traversal).data[i][0]<<"  ";
        }
        traversal = (*traversal).link[(*traversal).number];
    }
}

void Insert(string a, string b){
    if(root ==NULL){
        tree* t1 = new tree();
        root = t1;
        (*t1).data[0][0] = a;
        (*t1).data[0][1] = b;
        (*t1).number += 1;
        return;
    }
    tree *t2 = root;
    t2 = findBlock(a, t2);
    insert_in_tree(a, b, t2, NULL, NULL);
}

void traverse(tree *t){
    if(t == NULL){
        return;
    }
    else if((*t).link[0] == NULL){
        for(int i=0; i<(*t).number; i++){
            cout<<(*t).data[i][0]<<"   ";
        }
        return;
    }
    int i=0;
    while(i <= (*t).number){
        traverse((*t).link[i]);
        i += 1;
    }
    return;
}

int searchValue(string a, tree* temp){
    if(temp == NULL){
        cout<<"null"<<endl;
        return -1;
    }
    if((*temp).link[0] == NULL){
        for(int i=0; i<(*temp).number; i++){
            if((*temp).data[i][0] == a){
                cout<<"found\n"<<(*temp).data[i][0]<<"--"<<(*temp).data[i][1]<<endl;
                ofile<<(*temp).data[i][1]<<endl;
                return 1;
            }
        }
        cout<<"not found"<<endl;
        return -1;
    }
    else if (a < (*temp).data[0][0]){
        searchValue(a, (*temp).link[0]);
    }
    else if(a >= (*temp).data[(*temp).number-1][0]){
        searchValue(a, (*temp).link[(*temp).number]);
    }
    else{
        for(int i=1; i<(*temp).number; i++){
            if(a < (*temp).data[i][0]){
                //cout<<1<<"  "<<(*temp).data[i][0]<<endl;
                int x = searchValue(a, (*temp).link[i]);
                if(x == 1){
                    return 1;
                }
                return -1;
            }
        }
    }
}

int main(){
    string input,str;
    ifstream iFile;
    iFile.open("usa2.txt");
    ofile.open("out.txt");
    if(!iFile){
        cout<<"file cannot be opened"<<endl;
        exit(1);
    }
    int i = 1;
    while(getline(iFile, input)){
        int i;
        string str1="",str2="";
        for(i=1;;i++)
        {
        	if(input[i] == '|') break;
        	else str1+=input[i];
        }
        for(int j=i+1; j<input.length(); j++)
        {
        	str2+=input[j];
        }
        Insert(str1, str2);
    }
    leafTraverse();
    tree *print = root;
    traverse(print);
    cout<<endl<<"enter word"<<endl;
    while(cin>>str && str!=""){
        tree *temp = root;
        searchValue(str, temp);
    }
}

