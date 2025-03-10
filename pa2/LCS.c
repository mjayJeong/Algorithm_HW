#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 121

int max(int a, int b) {return (a > b) ? a : b;}

int sum(int *arr, int size) 
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum;
}

char *compare_two(char *seq1, char *seq2) 
{
    int len1 = strlen(seq1);
    int len2 = strlen(seq2);

    int **table = (int **)malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        table[i] = (int *)malloc((len2 + 1) * sizeof(int));
    }

    for (int i = 0; i <= len1; i++)
    {
        for (int j = 0; j <= len2; j++)
        {
            if (i == 0 || j == 0)
            {
                table[i][j] = 0;
            } else if (seq1[i-1] == seq2[j-1]) {
                table[i][j] = table[i-1][j-1] + 1;
            } else {
                table[i][j] = max(table[i-1][j], table[i][j-1]);
            }
        }
    }

    int lcs_length = table[len1][len2];
    char *actual_lcs = (char *)malloc((lcs_length + 1) * sizeof(char));
    actual_lcs[lcs_length] = '\0';

    int i = len1, j = len2;
    while (i > 0 && j > 0 && lcs_length > 0) 
    {
        if (seq1[i - 1] == seq2[j - 1]) {
            actual_lcs[--lcs_length] = seq1[i - 1]; 
            i--;
            j--;
        } else if (table[i - 1][j] >= table[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    for (int i = 0; i <= len1; i++) {
        free(table[i]);
    }
    free(table);

    return actual_lcs;
}


char *compare_three(char *seq1, char *seq2, char *seq3) {
    int len1 = strlen(seq1);
    int len2 = strlen(seq2);
    int len3 = strlen(seq3);

    int ***table = (int ***)malloc((len1 + 1) * sizeof(int **));
    for (int i = 0; i <= len1; i++) {
        table[i] = (int **)malloc((len2 + 1) * sizeof(int *));
        for (int j = 0; j <= len2; j++) {
            table[i][j] = (int *)malloc((len3 + 1) * sizeof(int));
        }
    }
    
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            for (int k = 0; k <= len3; k++) {
                if (i == 0 || j == 0 || k == 0) {
                    table[i][j][k] = 0;
                } else if (seq1[i - 1] == seq2[j - 1] && seq1[i - 1] == seq3[k - 1]) {
                    table[i][j][k] = table[i - 1][j - 1][k - 1] + 1;
                } else {
                    table[i][j][k] = max(table[i - 1][j][k], max(table[i][j - 1][k], table[i][j][k - 1]));
                }
            }
        }
    }

    int lcs_length = table[len1][len2][len3];

    char *actual_lcs = (char *)malloc((lcs_length + 1) * sizeof(char));
    actual_lcs[lcs_length] = '\0';

    int i = len1, j = len2, k = len3;
    while (i > 0 && j > 0 && k > 0 && lcs_length > 0) {
        if (seq1[i - 1] == seq2[j - 1] && seq1[i - 1] == seq3[k - 1]) {
            actual_lcs[--lcs_length] = seq1[i - 1];
            i--;
            j--;
            k--;
        } else if (table[i - 1][j][k] >= table[i][j - 1][k] && table[i - 1][j][k] >= table[i][j][k - 1]) {
            i--;
        } else if (table[i][j - 1][k] >= table[i - 1][j][k] && table[i][j - 1][k] >= table[i][j][k - 1]) {
            j--;
        } else {
            k--;
        }
    }

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            free(table[i][j]);
        } 
        free(table[i]);
    }
    free(table);
    
    return actual_lcs;
}


char *compare_four(char *seq1, char *seq2, char *seq3, char *seq4) {
    int len1 = strlen(seq1);
    int len2 = strlen(seq2);
    int len3 = strlen(seq3);
    int len4 = strlen(seq4);

    int ****table = (int ****)malloc((len1 + 1) * sizeof(int ***));
    for (int i = 0; i <= len1; i++) {
        table[i] = (int ***)malloc((len2 + 1) * sizeof(int **));
        for (int j = 0; j <= len2; j++) {
            table[i][j] = (int **)malloc((len3 + 1) * sizeof(int *));
            for (int k = 0; k <= len3; k++) {
                table[i][j][k] = (int *)malloc((len4 + 1) * sizeof(int));
            }
        }
    }
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            for (int k = 0; k <= len3; k++) {
                for (int l = 0; l <= len4; l++) {
                    if (i == 0 || j == 0 || k == 0 || l == 0) {
                        table[i][j][k][l] = 0;
                    } else if (seq1[i - 1] == seq2[j - 1] && seq1[i - 1] == seq3[k - 1] && seq1[i - 1] == seq4[l - 1]) {
                        table[i][j][k][l] = table[i - 1][j - 1][k - 1][l - 1] + 1;
                    } else {
                        table[i][j][k][l] = max(table[i - 1][j][k][l], max(table[i][j - 1][k][l], max(table[i][j][k - 1][l], table[i][j][k][l - 1])));
                    }
                }
            }
        }
    }

    int lcs_length = table[len1][len2][len3][len4];

    char *actual_lcs = (char *)malloc((lcs_length + 1) * sizeof(char));
    actual_lcs[lcs_length] = '\0';

    int i = len1, j = len2, k = len3, l = len4;
    while (i > 0 && j > 0 && k > 0 && l > 0 && lcs_length > 0) {
        if (seq1[i - 1] == seq2[j - 1] && seq1[i - 1] == seq3[k - 1] && seq1[i - 1] == seq4[l - 1]) {
            actual_lcs[--lcs_length] = seq1[i - 1];
            i--;
            j--;
            k--;
            l--;
        } else if (table[i - 1][j][k][l] >= table[i][j - 1][k][l] && table[i - 1][j][k][l] >= table[i][j][k - 1][l] && table[i - 1][j][k][l] >= table[i][j][k][l - 1]) {
            i--;
        } else if (table[i][j - 1][k][l] >= table[i - 1][j][k][l] && table[i][j - 1][k][l] >= table[i][j][k - 1][l] && table[i][j - 1][k][l] >= table[i][j][k][l - 1]) {
            j--;
        } else if (table[i][j][k - 1][l] >= table[i - 1][j][k][l] && table[i][j][k - 1][l] >= table[i][j - 1][k][l] && table[i][j][k - 1][l] >= table[i][j][k][l - 1]) {
            k--;
        } else {
            l--;
        }
    }

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            for (int k = 0; k <= len3; k++) {
                free(table[i][j][k]);
            }
            free(table[i][j]);
        }
        free(table[i]);
    }
    free(table);

    return actual_lcs;
}


char *compare_five(char *seq1, char *seq2, char *seq3, char *seq4, char *seq5) {
    int len1 = strlen(seq1);
    int len2 = strlen(seq2);
    int len3 = strlen(seq3);
    int len4 = strlen(seq4);
    int len5 = strlen(seq5);

    int *****table = (int *****)malloc((len1 + 1) * sizeof(int ****));
    for (int i = 0; i <= len1; i++) {
        table[i] = (int ****)malloc((len2 + 1) * sizeof(int ***));
        for (int j = 0; j <= len2; j++) {
            table[i][j] = (int ***)malloc((len3 + 1) * sizeof(int **));
            for (int k = 0; k <= len3; k++) {
                table[i][j][k] = (int **)malloc((len4 + 1) * sizeof(int *));
                for (int l = 0; l <= len4; l++) {
                    table[i][j][k][l] = (int *)malloc((len5 + 1) * sizeof(int));
                }
            }
        }
    }
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            for (int k = 0; k <= len3; k++) {
                for (int l = 0; l <= len4; l++) {
                    for (int m = 0; m <= len5; m++) {
                        if (i == 0 || j == 0 || k == 0 || l == 0 || m == 0) {
                            table[i][j][k][l][m] = 0;
                        } else if (seq1[i - 1] == seq2[j - 1] && seq1[i - 1] == seq3[k - 1] && seq1[i - 1] == seq4[l - 1] && seq1[i - 1] == seq5[m - 1]) {
                            table[i][j][k][l][m] = table[i - 1][j - 1][k - 1][l - 1][m - 1] + 1;
                        } else {
                            table[i][j][k][l][m] = max(table[i - 1][j][k][l][m], max(table[i][j - 1][k][l][m], max(table[i][j][k - 1][l][m], max(table[i][j][k][l - 1][m], table[i][j][k][l][m - 1]))));
                        }
                    }
                }
            }
        }
    }

    int lcs_length = table[len1][len2][len3][len4][len5];

    char *actual_lcs = (char *)malloc((lcs_length + 1) * sizeof(char));
    actual_lcs[lcs_length] = '\0';

    int i = len1, j = len2, k = len3, l = len4, m = len5;
    while (i > 0 && j > 0 && k > 0 && l > 0 && m > 0 && lcs_length > 0) {
        if (seq1[i - 1] == seq2[j - 1] && seq1[i - 1] == seq3[k - 1] && seq1[i - 1] == seq4[l - 1] && seq1[i - 1] == seq5[m - 1]) {
            actual_lcs[--lcs_length] = seq1[i - 1];
            i--;
            j--;
            k--;
            l--;
            m--;
        } else if (table[i - 1][j][k][l][m] >= table[i][j - 1][k][l][m] && table[i - 1][j][k][l][m] >= table[i][j][k - 1][l][m] && table[i - 1][j][k][l][m] >= table[i][j][k][l - 1][m] && table[i - 1][j][k][l][m] >= table[i][j][k][l][m - 1]) {
            i--;
        } else if (table[i][j - 1][k][l][m] >= table[i - 1][j][k][l][m] && table[i][j - 1][k][l][m] >= table[i][j][k - 1][l][m] && table[i][j - 1][k][l][m] >= table[i][j][k][l - 1][m] && table[i][j - 1][k][l][m] >= table[i][j][k][l][m - 1]) {
            j--;
        } else if (table[i][j][k - 1][l][m] >= table[i - 1][j][k][l][m] && table[i][j][k - 1][l][m] >= table[i][j - 1][k][l][m] && table[i][j][k - 1][l][m] >= table[i][j][k][l - 1][m] && table[i][j][k - 1][l][m] >= table[i][j][k][l][m - 1]) {
            k--;
        } else if (table[i][j][k][l - 1][m] >= table[i - 1][j][k][l][m] && table[i][j][k][l - 1][m] >= table[i][j - 1][k][l][m] && table[i][j][k][l - 1][m] >= table[i][j][k - 1][l][m] && table[i][j][k][l - 1][m] >= table[i][j][k][l][m - 1]) {
            l--;
        } else {
            m--;
        }
    }

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            for (int k = 0; k <= len3; k++) {
                for (int l = 0; l <= len4; l++) {
                    free(table[i][j][k][l]);
                }
                free(table[i][j][k]);
            }
            free(table[i][j]);
        }
        free(table[i]);
    }
    free(table);

    return actual_lcs;
}



void write_output(char **seqs, int seqs_num, char *lcs) {   
    int equal[seqs_num], seqs_index[seqs_num], aligned_index[seqs_num];
    char aligned_seqs[seqs_num][MAX_LEN * seqs_num + 1];       // 정렬된 것
    int lcs_len = strlen(lcs);
    int lcs_index = 0;
    memset(seqs_index, 0, sizeof(seqs_index));
    memset(aligned_index, 0, sizeof(aligned_index));
    for (int i = 0; i < seqs_num; i++) {
        memset(aligned_seqs[i], '-', sizeof(aligned_seqs[i]));
    }

    while (lcs_index < lcs_len) {
        int all_equal = 1;
        
        for (int i = 0; i < seqs_num; i++) {
            if (seqs[i][seqs_index[i]] == lcs[lcs_index]) {
                equal[i] = 1;
            } else {
                equal[i] = 0;
                all_equal = 0;
            }
        }
        if (all_equal || sum(equal, seqs_num) == 0) {
            for (int i = 0; i < seqs_num; i++) {
                if (seqs_index[i] < strlen(seqs[i])) {
                    aligned_seqs[i][aligned_index[i]] = seqs[i][seqs_index[i]];
                    seqs_index[i]++;
                }
                aligned_index[i]++;
            }
            if (all_equal) {
                lcs_index++;
            }
        } else {
            for (int i = 0; i < seqs_num; i++) {
                if (equal[i] != 1) {
                    aligned_seqs[i][aligned_index[i]] = seqs[i][seqs_index[i]];
                    seqs_index[i]++;
                }
                aligned_index[i]++;
            }
        }
    }

    for (int i = 0; i < seqs_num; i++) {
        while (seqs_index[i] < strlen(seqs[i])) {
            aligned_seqs[i][aligned_index[i]] = seqs[i][seqs_index[i]];
            seqs_index[i]++;
            aligned_index[i]++;
        }
    }

    int max_alignment_length = aligned_index[0];
    for (int i = 0; i < seqs_num; i++)
    {
        if (aligned_index[i] > max_alignment_length)
        {
            max_alignment_length = aligned_index[i];
        }
    }

    for (int i = 0; i < seqs_num; i++) {
        aligned_index[i] = max_alignment_length;
        aligned_seqs[i][max_alignment_length] = '\0';
    }


    FILE *file = fopen("hw2_output.txt", "w");  
    for (int i = 0; i < seqs_num; i++) {
        fprintf(file, "%s\n", aligned_seqs[i]);
    }

    for (int i = 0; i < max_alignment_length; i++) {
        char word = aligned_seqs[0][i];
        int same = 1;
        for (int j = 1; j < seqs_num; j++) {
            if (aligned_seqs[j][i] != word) {
                same = 0;
                break;
            }
        }
        fputc(same ? '*' : ' ', file);
    }
    fclose(file);
}


int main()
{
    char *seqs[5];  // 저장공간
    int seq_num;    // 비교 문자열 숫자
    char *lcs;

    FILE *file = fopen("hw2_input.txt", "r");
    fscanf(file, "%d", &seq_num);
    fscanf(file, "%*s");
    for (int i = 0; i < seq_num; i++) 
    {
        seqs[i] = malloc(sizeof(char) * MAX_LEN);
        fscanf(file, "%s", seqs[i]);
    }

    if (seq_num == 2) {
        lcs = compare_two(seqs[0], seqs[1]);
    } else if (seq_num == 3) {
        lcs = compare_three(seqs[0], seqs[1], seqs[2]);
    } else if (seq_num == 4) {
        lcs = compare_four(seqs[0], seqs[1], seqs[2], seqs[3]);
    } else if (seq_num == 5) {
        lcs = compare_five(seqs[0], seqs[1], seqs[2], seqs[3], seqs[4]);
    }

    printf("LCS : %s\n", lcs);
    write_output(seqs, seq_num, lcs);

    return 0;
}