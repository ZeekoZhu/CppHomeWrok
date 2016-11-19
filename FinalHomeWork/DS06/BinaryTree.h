#pragma once
#include <stack>
#include <functional>
#include <vector>
using namespace std;

typedef char T;
class BinaryTree;
class BinaryNode
{
public:
    friend class BinaryTree;
    T data;
    BinaryNode* lchild;
    BinaryNode* rchild;
    BinaryNode() : data(0), lchild(nullptr), rchild(nullptr)
    {
    }

    explicit BinaryNode(T& data) : lchild(nullptr), rchild(nullptr)
    {
        this->data = data;
    }
};

class BinaryTree
{
    BinaryNode* root = nullptr;

public:
    /*
     * 6.36
     */
    BinaryTree(T* datas, int count)
    {
        this->root = new BinaryNode(datas[0]);
        BinaryNode* that = this->root->lchild;
        stack<BinaryNode*> trace;
        trace.push(this->root);
        bool isLeft = true;         // ָʾ��ǰ�ڵ��ǲ�������
        bool shouldLink = false;    // ָʾ�Ƿ�Ӧ�����Ӻ��
        BinaryNode* before = this->root;
        for (int i = 1; i < count; i++)
        {
            BinaryNode* parent = trace.top();
            if (datas[i] == ' ')
            {
                // ջΪ���������
                if (trace.empty())
                {
                    return;
                }

                // �����ǰ�ڵ�����ڵ㣬�� that ָ���ұߵ��ֵܽڵ�
                if (isLeft)
                {
                    isLeft = false;
                }
                // �����ǰ�ڵ����ҽڵ㣬������Ѱ��һ���յ�������
                else
                {
                    // �ܵ�����Ľڵ��˫����Ҷ�ӽ�㣬���ԣ�Ҫ�ѵ�ǰ�ڵ��ĸ�׼�¼������������һ���ڵ㣬�ͰѺ�����ù�ȥ
                    before = parent;
                    shouldLink = true;
                    do
                    {
                        // Ѱ�ҿյ�������
                        trace.pop();
                        if (trace.empty())
                        {
                            return;
                        }
                        parent = trace.top();
                    } while (parent->rchild != nullptr);
                }
                that = parent->rchild;
            }
            else
            {
                // �жϵ�ǰ�ڵ������λ��
                isLeft ? that = parent->lchild = new BinaryNode(datas[i])
                    : that = parent->rchild = new BinaryNode(datas[i]);
                // ���Ӻ�̽ڵ�
                if (!isLeft && shouldLink)
                {
                    shouldLink = false;
                    before->rchild = that;
                }
                trace.push(that);
                that = that->lchild;
                isLeft = true;
            }
        }
    }

    /// <summary>
    /// 6.37 ����������������ж��Ƿ�����
    /// </summary>
    bool IsSimilarTo(BinaryTree& other) const
    {
        BinaryNode* _this = this->root;
        BinaryNode* that = other.root;
        stack<BinaryNode*> thisTrace;
        stack<BinaryNode*> thatTrace;
        thisTrace.push(_this);
        thatTrace.push(that);
        _this = _this->lchild;
        that = that->lchild;
        bool isLeft = true;
        while (!thisTrace.empty() && !thatTrace.empty())
        {
            if ((_this == nullptr && that != nullptr)
                || (_this != nullptr && that == nullptr))
            {
                return false;
            }
            if (_this == nullptr)
            {
                if (isLeft)
                {
                    isLeft = false;
                }
                else
                {
                    BinaryNode* thisTmp;
                    BinaryNode* thatTmp;
                    do
                    {
                        thisTmp = thisTrace.top();
                        thatTmp = thatTrace.top();
                        thisTrace.pop();
                        thatTrace.pop();
                        if (thisTrace.empty())
                        {
                            return thatTrace.empty();
                        }
                    } while ((thisTrace.top()->rchild == nullptr && thatTrace.top()->rchild == nullptr)
                        || (thisTrace.top()->rchild == thisTmp && thatTrace.top()->rchild == thatTmp));
                }

                _this = thisTrace.top()->rchild;
                that = thatTrace.top()->rchild;
            }
            else
            {
                thisTrace.push(_this);
                thatTrace.push(that);
                _this = _this->lchild;
                that = that->lchild;
                isLeft = true;
            }
        }
        return true;
    }

    /// <summary>
    /// 6.56 �������������
    /// </summary>
    void PreVisit(function<void(BinaryNode&)> action) const
    {
        BinaryNode* that = this->root;
        stack<BinaryNode*> thatTrace;
        action(*that);
        thatTrace.push(that);
        that = that->lchild;
        bool isLeft = true;
        while (!thatTrace.empty())
        {
            if (that == nullptr)
            {
                if (isLeft)
                {
                    isLeft = false;
                }
                else
                {
                    BinaryNode* thatTmp;
                    do
                    {
                        thatTmp = thatTrace.top();
                        thatTrace.pop();
                        if (thatTrace.empty())
                        {
                            return;
                        }
                    } while ((thatTrace.top()->rchild == nullptr) || (thatTrace.top()->rchild == thatTmp));
                }
                that = thatTrace.top()->rchild;
            }
            else
            {
                thatTrace.push(that);
                action(*that);
                that = that->lchild;
                isLeft = true;
            }
        }
    }

    /// <summary>
    /// 6.60 ��ȡ��̽ڵ㣬�Դ洢�ṹ��ûɶ�ر��Ҫ��
    /// </summary>
    static BinaryNode* GetNextNode(BinaryNode* p)
    {
        return p->lchild == nullptr ? p->rchild : p->lchild;
    }
};

