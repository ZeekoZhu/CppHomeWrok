#include <iostream>
#include "BinaryTree.h"
#include <string>

using namespace std;

int main()
{
    char datas[] = { '1','2',' ',' ','3','4','5',' ',' ',' ','1' };
    char datas1[] = { '1',' ','2',' ','3','4',' ','5',' ',' ',' ' };
    BinaryTree tree2(datas, 11);
    BinaryTree tree(datas1, 11);
    tree.PreVisit([](BinaryNode& c)->void {cout << c.data << " "; });
    string res;
    if (tree2.IsSimilarTo(tree))
    {
        res = "����";
    }
    else
    {
        res = "������";
    }
    cout << endl << res << endl;

    // ����-�ֵܱ�ʾ��������ʵ��һ�ö���������ö������еĽڵ������ָ���ӣ��Һ���ָ���ֵܣ���Ҷ�ӽ�����û�����ӵĽڵ�
    // ��ô��ͳ��Ҷ�ӽڵ�ĸ���������ô��
    int count = 0;
    tree.PreVisit([&count](BinaryNode& n)->void {
        if (n.lchild == nullptr)
        {
            count++;
        }
    });
    cout << "Ҷ�ӽ��ĸ���Ϊ��" << count;
}