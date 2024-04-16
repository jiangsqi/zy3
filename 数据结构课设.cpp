#include<iostream>
#include<cstdio>
#include<cstring>
#include<malloc.h>
using namespace std;
typedef struct node//创建结构体 
{
	int parent;		//根节点
	char letter;	//数据域，所代表的字符 
	int lchild;		//左孩子结点
	int rchild;		//右孩子结点
	double weight;	//权值
}*HuffmanTree;
void Select(HuffmanTree& tree, int n, int& s1, int& s2)//找权值小的 
{
	int min = 0;
	for (int i = 1; i <= n; i++)
	{
		if (tree[i].parent == 0)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++)
	{
		if (tree[i].parent == 0 && tree[i].weight < tree[min].weight)
		{
			min = i;
		}
	}
	s1 = min;
	for (int i = 1; i <= n; i++)
	{
		if (tree[i].parent == 0 && i != s1)
		{
			min = i;
			break;
		}
	}
	for (int i = min + 1; i <= n; i++)
	{
		if (tree[i].parent == 0 && i != s1 && tree[i].weight < tree[min].weight)
		{
			min = i;
		}
	}
	s2 = min;
}
void CreateHuff(HuffmanTree& tree, char* letters, int* weights, int n)//创建哈夫曼树 
{
	int m = 2 * n - 1;
	tree = (HuffmanTree)calloc(m + 1, sizeof(node));//开辟空间 
	for (int i = 1; i <= n; i++)
	{
		tree[i].weight = weights[i - 1];
		tree[i].letter = letters[i - 1];
	}
	for (int i = n + 1; i <= m; i++)
	{
		int s1 = 0, s2 = 0;
		Select(tree, i - 1, s1, s2);//调用Select函数，查找根节点最小的两个 树，赋值给S1，S2 
		tree[i].weight = tree[s1].weight + tree[s2].weight;//创造新结点tree[i],权值等于tree[s1]和tree[s2]的和 
		tree[i].lchild = s1;//s1为新结点的左孩子 
		tree[i].rchild = s2;//s2为新结点的右孩子 
		tree[s1].parent = i;
		tree[s2].parent = i;
	}
}
void HuffmanCoding(HuffmanTree& tree, char**& HuffCode, int n)//哈夫曼编码 
{
	HuffCode = (char**)malloc(sizeof(char*) * (n + 1));//开辟空间 
	char* tempcode = (char*)malloc(sizeof(char) * n);//临时存放哈夫曼编码 
	tempcode[n - 1] = '\0';//根结点编码为空 
	for (int i = 1; i <= n; i++)
	{
		int start = n - 1;
		int doing = i;
		int parent = tree[doing].parent;
		while (parent)
		{
			if (tree[parent].lchild == doing)
				tempcode[--start] = '0';
			else
				tempcode[--start] = '1';
			doing = parent;
			parent = tree[parent].parent;
		}
		HuffCode[i] = (char*)malloc(sizeof(char) * (n - start));//开辟存放编码数组的空间 
		strcpy(HuffCode[i], &tempcode[start]);

	}
	free(tempcode);
}
void HuffmanDecoding(HuffmanTree ht, int n, char* pwd)//哈夫曼解码
{
	cout << ht[0].letter;
	int len = strlen(pwd);//获取用户输入的编码长度 
	int i = 0;
	int node = 2 * n - 1;//从根节点出发 
	while (i < len)
	{
		if (pwd[i] == '0')
		{
			node = ht[node].lchild;
			i++;
			if (ht[node].lchild == 0 && ht[node].rchild == 0)
			{
				cout << ht[node].letter;//输出当前数据域 
				node = 2 * n - 1;//重新从根节点出发编译 
			}
		}
		if (pwd[i] == '1')
		{
			node = ht[node].rchild;
			i++;
			if (ht[node].lchild == 0 && ht[node].rchild == 0)
			{
				cout << ht[node].letter;
				node = 2 * n - 1;
			}
		}
	}

}
int main()
{
	HuffmanTree Tree;
	char letter[26] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z' };
	int weight[26] = { 186,64,13,22,32,103,21,15,47,571,5,32,20,57,63,15,1,48,51,80,23,7,17,2,16,38 };
	CreateHuff(Tree, letter, weight, 26);//调用创建哈夫曼树函数
	char** HuffCode = { 0 };
	HuffmanCoding(Tree, HuffCode, 26);//调用哈夫曼编码函数
	cout << endl;
	printf("    欢迎使用\n");
	while (1)
	{
		printf("请选择您要使用的功能\nA:编码发报 B:译码 C:结束使用\n");
		char p;
		cin >> p;
		int n = 0;
		int f = 0;
		int m = 0;
		switch (p)//选择函数，判断不同输入，执行不同功能
		{
			case'A': //编码发报功能 
				char x[100];
				printf("请输入您要输入的字符长度\n");
				scanf("%s", x);
				while (1)
				{
					for (int i = 0; i < strlen(x); i++)
					{
						if (x[i] < '0' || x[i]>'9')
							f = 1;
					}
					if (f == 1)
					{
						cout << "输入错误，请您重新输入" << endl;
						scanf("%s", x);
						f = 0;
					}
					else
						break;
				}
				for (int i = 0; i < strlen(x); i++)
				{
					n = n * 10 + x[i] - '0';
				}
				char c;
				char letters[26];
				printf("请依次输入您要输入的字符（用空格隔开）\n");
				for (int i = 0; i < n; i++)
				{
					cin >> letters[i];
				}
				printf("该字符集编码为:\n");
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < 26; j++)
						if (letters[i] == letter[j])
							printf("%s ", HuffCode[j + 1]);
				}
				cout << endl;
				break;
			case'B'://译码 功能 
				for (int i = 1; i <= 26; i++)
					printf("%s ", HuffCode[i]);
				cout << endl;
				char s[100];
				cout << "输入您要还原的个数" << endl;
				cin >> m;
				cout << "请您依据以上编码进行发报(连续输入)" << endl;
				cin >> s;
				cout << "译码输出" << endl;
				HuffmanDecoding(Tree, 26, s);
				cout << endl;
				break;
			case'C':
				exit(0);break;
			default:
				printf("输入错误，请重新输入\n");
				break; 
		}
	}
	return 0;
}
