/*
 * algorithms.h
 */

#ifndef ALGORITHMS_H___
#define ALGORITHMS_H___

int find_string(char *mathops, char ch);
int first_ops_item(char *ops_item, size_t len, char *mathops, size_t mathops_len);
int next_ops_item(char *ops_item, size_t len, char *mathops, size_t mathops_len);
int find_string(char *avail_ops, char ch);
int first_lnums_permutation(long *nums, size_t len);
int next_lnums_permutation(long *nums, size_t len);

#endif /* ALGORITHMS_H___ */

