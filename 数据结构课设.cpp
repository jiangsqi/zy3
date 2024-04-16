#include<iostream>
#include<cstdio>
#include<cstring>
#include<malloc.h>
using namespace std;
typedef struct node//�����ṹ�� 
{
	int parent;		//���ڵ�
	char letter;	//��������������ַ� 
	int lchild;		//���ӽ��
	int rchild;		//�Һ��ӽ��
	double weight;	//Ȩֵ
}*HuffmanTree;
void Select(HuffmanTree& tree, int n, int& s1, int& s2)//��ȨֵС�� 
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
void CreateHuff(HuffmanTree& tree, char* letters, int* weights, int n)//������������ 
{
	int m = 2 * n - 1;
	tree = (HuffmanTree)calloc(m + 1, sizeof(node));//���ٿռ� 
	for (int i = 1; i <= n; i++)
	{
		tree[i].weight = weights[i - 1];
		tree[i].letter = letters[i - 1];
	}
	for (int i = n + 1; i <= m; i++)
	{
		int s1 = 0, s2 = 0;
		Select(tree, i - 1, s1, s2);//����Select���������Ҹ��ڵ���С������ ������ֵ��S1��S2 
		tree[i].weight = tree[s1].weight + tree[s2].weight;//�����½��tree[i],Ȩֵ����tree[s1]��tree[s2]�ĺ� 
		tree[i].lchild = s1;//s1Ϊ�½������� 
		tree[i].rchild = s2;//s2Ϊ�½����Һ��� 
		tree[s1].parent = i;
		tree[s2].parent = i;
	}
}
void HuffmanCoding(HuffmanTree& tree, char**& HuffCode, int n)//���������� 
{
	HuffCode = (char**)malloc(sizeof(char*) * (n + 1));//���ٿռ� 
	char* tempcode = (char*)malloc(sizeof(char) * n);//��ʱ��Ź��������� 
	tempcode[n - 1] = '\0';//��������Ϊ�� 
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
		HuffCode[i] = (char*)malloc(sizeof(char) * (n - start));//���ٴ�ű�������Ŀռ� 
		strcpy(HuffCode[i], &tempcode[start]);

	}
	free(tempcode);
}
void HuffmanDecoding(HuffmanTree ht, int n, char* pwd)//����������
{
	cout << ht[0].letter;
	int len = strlen(pwd);//��ȡ�û�����ı��볤�� 
	int i = 0;
	int node = 2 * n - 1;//�Ӹ��ڵ���� 
	while (i < len)
	{
		if (pwd[i] == '0')
		{
			node = ht[node].lchild;
			i++;
			if (ht[node].lchild == 0 && ht[node].rchild == 0)
			{
				cout << ht[node].letter;//�����ǰ������ 
				node = 2 * n - 1;//���´Ӹ��ڵ�������� 
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
	CreateHuff(Tree, letter, weight, 26);//���ô���������������
	char** HuffCode = { 0 };
	HuffmanCoding(Tree, HuffCode, 26);//���ù��������뺯��
	cout << endl;
	printf("    ��ӭʹ��\n");
	while (1)
	{
		printf("��ѡ����Ҫʹ�õĹ���\nA:���뷢�� B:���� C:����ʹ��\n");
		char p;
		cin >> p;
		int n = 0;
		int f = 0;
		int m = 0;
		switch (p)//ѡ�������жϲ�ͬ���룬ִ�в�ͬ����
		{
			case'A': //���뷢������ 
				char x[100];
				printf("��������Ҫ������ַ�����\n");
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
						cout << "�������������������" << endl;
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
				printf("������������Ҫ������ַ����ÿո������\n");
				for (int i = 0; i < n; i++)
				{
					cin >> letters[i];
				}
				printf("���ַ�������Ϊ:\n");
				for (int i = 0; i < n; i++)
				{
					for (int j = 0; j < 26; j++)
						if (letters[i] == letter[j])
							printf("%s ", HuffCode[j + 1]);
				}
				cout << endl;
				break;
			case'B'://���� ���� 
				for (int i = 1; i <= 26; i++)
					printf("%s ", HuffCode[i]);
				cout << endl;
				char s[100];
				cout << "������Ҫ��ԭ�ĸ���" << endl;
				cin >> m;
				cout << "�����������ϱ�����з���(��������)" << endl;
				cin >> s;
				cout << "�������" << endl;
				HuffmanDecoding(Tree, 26, s);
				cout << endl;
				break;
			case'C':
				exit(0);break;
			default:
				printf("�����������������\n");
				break; 
		}
	}
	return 0;
}
