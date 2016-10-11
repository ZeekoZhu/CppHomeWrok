#include <iostream>
#include <stack>

using namespace std;



bool Check(int N, int M)
{
	// ��ʾ��һ����ջ����
	int orderedIndex = 1;
	// �Ǹ�ջ
	stack<int> tmpStack;

	for (int i = 0; i < N; i++)
	{
		// ����һ����ջ����
		int tmp;
		cin >> tmp;

		// ���Ҫ��ջ��������һ����ջ������ȣ���ô��������ջ�Ĺ��̣�ֱ�ӵ���
		if (tmp == orderedIndex && orderedIndex <= N)
		{
			orderedIndex++;
			continue;
		}
		// ���Ҫ��ջ������ջ��Ԫ����ȣ��͵���
		else if (!tmpStack.empty() && tmp == tmpStack.top())
		{
			tmpStack.pop();
		}
		// ���Ҫ��ջ����������һ��Ҫ��ջ����
		else if (tmp > orderedIndex)
		{
			// �Ͳ��ϵ���������ջ��ֱ����һ��Ҫ��ջ������Ҫ��ջ�������
			while (tmpStack.size() < M && orderedIndex != tmp && orderedIndex <= N)
			{
				tmpStack.push(orderedIndex++);
			}
			// ���ջ���ˣ�����һ��Ҫ��ջ������Ҫ��ջ��������
			if (orderedIndex != tmp && tmpStack.size() == M)
			{
				// ˵�������ջ�����Ǵ����
				return false;
			}

			// ������ջ���̣�ֱ�ӵ���
			orderedIndex++;
		}
	}

	// ���ջ��ȫ���ˣ���ô������о��ǿ��е�
	return tmpStack.empty();
}


int main()
{
	int M; // stack capacity
	int N; // length of push sequence
	int K; // check times
	cin >> M;
	cin >> N;
	cin >> K;
	stack<int> tmpStack;
	for (int i = 0; i < K; i++)
	{
		cout << (Check(N, M) ? "YES" : "NO") << endl;
	}
}