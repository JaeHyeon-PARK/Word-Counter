#include <stdio.h>
#include "BST.h"

#define LINE_SIZE 400

using std::string;

int main(void)
{
	BST<string, int> *tree = new BST<string, int>();	// 키가 string이고, value가 int인 이진검색트리

	FILE *fp;
	char fname[40], line[LINE_SIZE];;
	char seps[] = " %.,-_'\"?!()[]:\t\n;", *token;

	printf("입력파일 이름? ");
	gets_s(fname);

	if ((fp = fopen(fname, "r")) == NULL) {
		printf("파일 오류\n");
		return -1;
	}

	while (fgets(line, LINE_SIZE, fp) != NULL) {
		for (token = strtok(line, seps); token != NULL; token = strtok(NULL, seps)) {
			if (token[0] < 0 || !isalpha(token[0]))		// 영어 알파벳으로 시작하는 단어가 아님
				continue;
			for (int i = 0; token[i] != NULL; i++) {	// 모든 단어는 소문자로 변환
				if (isupper(token[i]))
					token[i] = 'a' + token[i] - 'A';
			}
			string charToStr(token);
			int count;
			if (tree->getValue(token, count) == -1)	// 단어가 트리에 없는 새로운 단어일 경우
				tree->insertNode(token, 1);				// 빈도수를 1로하여 저장
			else {
				tree->updateNode(token, ++count);		// 앞에 나온 단어일 경우, 빈도수를 1 증가
			}
		}
	}

	printf("1. 이진 검색 트리의 정보:\n");
	tree->printTree();					// 트리의 깊이와 노드 수를 출력

	printf("\n2. 이진 검색 트리에 저장된 단어와 빈도수 출력:\n");
	tree->inorder();					// inorder로 순회하면서 "[단어, 빈도수]"의 쌍을 출력

	return 0;
}