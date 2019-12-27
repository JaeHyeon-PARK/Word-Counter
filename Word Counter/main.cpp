#include <stdio.h>
#include "BST.h"

#define LINE_SIZE 400

using std::string;

int main(void)
{
	BST<string, int> *tree = new BST<string, int>();	// Ű�� string�̰�, value�� int�� �����˻�Ʈ��

	FILE *fp;
	char fname[40], line[LINE_SIZE];;
	char seps[] = " %.,-_'\"?!()[]:\t\n;", *token;

	printf("�Է����� �̸�? ");
	gets_s(fname);

	if ((fp = fopen(fname, "r")) == NULL) {
		printf("���� ����\n");
		return -1;
	}

	while (fgets(line, LINE_SIZE, fp) != NULL) {
		for (token = strtok(line, seps); token != NULL; token = strtok(NULL, seps)) {
			if (token[0] < 0 || !isalpha(token[0]))		// ���� ���ĺ����� �����ϴ� �ܾ �ƴ�
				continue;
			for (int i = 0; token[i] != NULL; i++) {	// ��� �ܾ�� �ҹ��ڷ� ��ȯ
				if (isupper(token[i]))
					token[i] = 'a' + token[i] - 'A';
			}
			string charToStr(token);
			int count;
			if (tree->getValue(token, count) == -1)	// �ܾ Ʈ���� ���� ���ο� �ܾ��� ���
				tree->insertNode(token, 1);				// �󵵼��� 1���Ͽ� ����
			else {
				tree->updateNode(token, ++count);		// �տ� ���� �ܾ��� ���, �󵵼��� 1 ����
			}
		}
	}

	printf("1. ���� �˻� Ʈ���� ����:\n");
	tree->printTree();					// Ʈ���� ���̿� ��� ���� ���

	printf("\n2. ���� �˻� Ʈ���� ����� �ܾ�� �󵵼� ���:\n");
	tree->inorder();					// inorder�� ��ȸ�ϸ鼭 "[�ܾ�, �󵵼�]"�� ���� ���

	return 0;
}