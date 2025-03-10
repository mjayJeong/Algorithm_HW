#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 10000000


typedef struct node {
    char data;
    int freq;
    struct node* left;
    struct node* right;
} node;


typedef struct {
    char character;
    char code[30];
} HuffmanCode;


node* priority_queue[MAX_LEN + 1];
int queue_index = 0;
HuffmanCode huffman_codes[256];
int code_count = 0;
char code[30] = {0};
int code_index = -1;


node* createNode(char c, int frequency) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = c;
    new_node->freq = frequency;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void enqueue(node* new_data) {
    if (queue_index == MAX_LEN) {
        return;
    }
    queue_index++;
    int i = queue_index;
    while (i > 1 && priority_queue[i / 2]->freq > new_data->freq) {
        priority_queue[i] = priority_queue[i / 2];
        i /= 2;
    }
    priority_queue[i] = new_data;
}

node* dequeue(void) {
    if (queue_index == 0) {
        return NULL;
    }

    node* min_node = priority_queue[1];
    node* last_node = priority_queue[queue_index--];
    int i = 1;
    int child = 2;

    while (child <= queue_index) {
        if (child < queue_index && priority_queue[child]->freq > priority_queue[child + 1]->freq) {
            child++;
        }
        if (last_node->freq <= priority_queue[child]->freq) {
            break;
        }
        priority_queue[i] = priority_queue[child];
        i = child;
        child *= 2;
    }
    priority_queue[i] = last_node;
    return min_node;
}


node* buildHuffmanTree(void) {
    while (queue_index > 1) {
        node* first = dequeue();
        node* second = dequeue();
        node* combined_tree = createNode(0, first->freq + second->freq);
        combined_tree->left = first;
        combined_tree->right = second;
        enqueue(combined_tree);
    }
    return dequeue();
}


void getHuffmanCode(node* input_node) {
    if (input_node == NULL) {
        return;
    }
    if (input_node->data != 0) {
        HuffmanCode hc;
        hc.character = input_node->data;
        strcpy(hc.code, code);
        huffman_codes[code_count++] = hc;
    }
    code_index++;
    code[code_index] = '0';
    getHuffmanCode(input_node->left);
    code[code_index] = 0;
    code_index--;

    code_index++;
    code[code_index] = '1';
    getHuffmanCode(input_node->right);
    code[code_index] = 0;
    code_index--;
}


void printHuffmanCodes(FILE *file) {
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < code_count; j++) {
            if (huffman_codes[j].character == i) {
                fprintf(file, "%c:%s\n", huffman_codes[j].character, huffman_codes[j].code);
                break;
            }
        }
    }
}


void printTreeToFile(node* root, FILE *file) {
    if (root == NULL) {
        return;
    }
    if (root->data != 0) {
        if (root->data == ',' || root->data == '(' || root->data == ')' || root->data == '\\') {
            fprintf(file, "\\%c", root->data);
        } else {
            fprintf(file, "%c", root->data);
        }
    } else {
        fprintf(file, "(");
        printTreeToFile(root->left, file);
        fprintf(file, ",");
        printTreeToFile(root->right, file);
        fprintf(file, ")");
    }
}



void encodeStringToFile(char* str, FILE *file) {
    char* encoded_string = malloc(MAX_LEN * 30);
    encoded_string[0] = '\0';

    for (int i = 0; i < strlen(str); i++) {
        for (int j = 0; j < code_count; j++) {
            if (str[i] == huffman_codes[j].character) {
                strcat(encoded_string, huffman_codes[j].code);
                break;
            }
        }
    }
    fprintf(file, "%s", encoded_string);
    free(encoded_string);
}


void decodeStringUsingTree(const char* encoded_str, node* huffman_tree, FILE *file) {
    node* current_node = huffman_tree;
    size_t str_len = strlen(encoded_str);
    for (size_t i = 0; i < str_len; i++) {
        if (encoded_str[i] == '0') {
            if (current_node->left != NULL)
                current_node = current_node->left;
        } else if (encoded_str[i] == '1') {
            if (current_node->right != NULL)
                current_node = current_node->right;
        }
        if (current_node->left == NULL && current_node->right == NULL) {
            fprintf(file, "%c", current_node->data);
            current_node = huffman_tree;
        }
    }
}


node* buildHuffmanTreeFromEncoding(const char* encoding) {
    int len = strlen(encoding);
    node** stack = malloc(MAX_LEN * sizeof(node*));
    int top = -1;
    node* root = NULL;
    node* current = NULL;

    for (int i = 0; i < len; i++) {
        if (encoding[i] == '(') {
            if (current != NULL) {
                stack[++top] = current;
            }
            current = createNode(0, 0);
        } else if (encoding[i] == ')') {
            if (top >= 0) {
                node* parent = stack[top--];
                if (parent->left == NULL) {
                    parent->left = current;
                } else {
                    parent->right = current;
                }
                current = parent;
            }
        } else if (encoding[i] == '\\') {
            i++;
            if (encoding[i] == ',' || encoding[i] == '(' || encoding[i] == ')' || encoding[i] == '\\') {
                node* new_node = createNode(encoding[i], 0);
                if (current->left == NULL) {
                    current->left = new_node;
                } else {
                    current->right = new_node;
                }
            }
        } else if (encoding[i] != ',') {
            node* new_node = createNode(encoding[i], 0);
            if (current->left == NULL) {
                current->left = new_node;
            } else {
                current->right = new_node;
            }
        }
    }
    while (top >= 0) {
        root = stack[top--];
    }
    if (root == NULL) {
        root = current;
    }
    free(stack);
    return root;
}

char* readHuffmanTreeEncodingFromFile(FILE *file, char* huffman_tree_encoding) {
    fscanf(file, "%[^\n]", huffman_tree_encoding);
    return huffman_tree_encoding;
}


char* readEncodedStringFromFile(FILE *file, char* encoded_str) {
    fseek(file, 0, SEEK_SET);
    fscanf(file, "%*[^\n]\n");
    fscanf(file, "%[^\n]", encoded_str);
    return encoded_str;
}



// main 함수
int main() {
    int frequencies[256] = {0};
    FILE *file = fopen("hw3_input.txt", "r");
    if (!file) {
        perror("fail to open file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *word = (char *)malloc(fileSize + 1);
    if (!word) {
        perror("fail to memory allocation");
        fclose(file);
        return 1;
    }
    if (fgets(word, fileSize + 1, file) == NULL) {
        perror("cannot read");
        fclose(file);
        free(word);
        return 1;
    }
    size_t len = strlen(word);
    if (len > 0 && word[len - 1] == '\n') {
        word[len - 1] = '\0';
    }
    fclose(file);

    for (int i = 0; i < strlen(word); i++) {
        frequencies[(unsigned char)word[i]]++;
    }
    for (int i = 0; i < 256; i++) {
        if (frequencies[i] > 0) {
            enqueue(createNode((char)i, frequencies[i]));
        }
    }

    node* huffman_tree = buildHuffmanTree();
    getHuffmanCode(huffman_tree);

    FILE *output1 = fopen("hw3_output1.txt", "w");
    if (!output1) {
        printf("fail to open file");
        return 1;
    }
    printTreeToFile(huffman_tree, output1);
    fprintf(output1, "\n");
    encodeStringToFile(word, output1);

    fclose(output1);

    // 디코딩 부분
    char *huffman_tree_encoding = malloc(MAX_LEN * 2);
    char *encoded_string = malloc(MAX_LEN * 30);

    FILE *input_file = fopen("hw3_output1.txt", "r");
    if (!input_file) {
        perror("fail to open file");
        return 1;
    }
    readHuffmanTreeEncodingFromFile(input_file, huffman_tree_encoding);
    readEncodedStringFromFile(input_file, encoded_string);
    fclose(input_file);

    node* new_huffman_tree = buildHuffmanTreeFromEncoding(huffman_tree_encoding);
    
    FILE *output2 = fopen("hw3_output2.txt", "w");
    if (!output2) {
        perror("fail to open file");
        return 1;
    }
    
    code_count = 0;
    getHuffmanCode(new_huffman_tree);
    printHuffmanCodes(output2);
    decodeStringUsingTree(encoded_string, new_huffman_tree, output2);

    fclose(output2);

    free(huffman_tree_encoding);
    free(encoded_string);
    free(word);

    return 0;
}
