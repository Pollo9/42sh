/*
** common.h for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Jul 30 03:59:48 2006 Seblu
** Last update Wed Oct 11 16:56:07 2006 seblu
*/

#ifndef COMMON_H_
# define COMMON_H_

/*!
** Merge strings
**
** @param n number of string to merge
** @param s1 First string to merge
**
** @return malloced string merged
** @warning the returned string must be freed by the caller
*/
char            *strmerge(int n, const char *s1, ...);

/*!
** Merge a vector of string
**
** @param vtable strings to merge
**
** @return a string merged from @arg vtable
*/
char            *strvmerge(const char * const *vtable);

/*!
** Return a malloc copy of the given, conserving only the basename
**
** @param path path where basename will be extracted
**
** @return malloced basename
** @warning Not use the standard function for reason of vicious
** definition in manuel.
*/
char		*basename(const char *path);

/*!
** Duplicate a string for @arg n characteres
**
** @param str string to duplicate
** @param n number of caractere to duplicate
**
** @return a new malloced string
*/
char            *strndup(const char *str, size_t n);

/*!
** Compute if string is composed only by digit
**
** @param str string to test
**
** @return boolean result
*/
int		isdigitstr(const char *str);

/*!
** Add @arg str at the end of @arg vector. vector is a
** table of char *, where the last element is NULL.
** if @arg str is NULL, nothing is done
**
** @param vector first vector
** @param str string to add at the end of vector
**
** @return the new vector. You should not think that have the
** same address that @arg vector
*/
char		**strvectoradd(char **vector, char *str);

#endif
