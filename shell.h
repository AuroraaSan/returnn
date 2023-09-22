#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @n: the number field
 * @s: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int n;
	char *s;
	struct liststr *next;
} lst_t;

/**
 * struct PassInfo - consists of pseudo-arguments for function calls
 * @argument: string generated containing arguments
 * @a_value: array of strings generated from argument
 * @path: string path for the current command
 * @a_counter: argument count
 * @error_count: error count
 * @error_number: error code for exit() calls
 * @count_this_line: flag indicating whether to count this line of input
 * @file_name: program filename
 * @environment_list: linked list, local copy of environment variables
 * @environ: custom modified copy of environment variable
 * @hist: history node
 * @alias_node: alias node
 * @environment_changed: set if environment was changed
 * @return_status: return status of the last executed command
 * @cmd_buffer: address of pointer to command_buffer
 * @cmd_buffer_type: command type (||, &&, ;)
 * @read_file_descriptor: file descriptor from which to read line input
 * @history_line_count: history line number count
 */
typedef struct PassInfo
{
	char *argument;
	char **a_value;
	char *path;
	int a_counter;
	unsigned int error_count;
	int error_number;
	int count_this_line;
	char *file_name;
	lst_t *environment_list;
	char **environ;
	lst_t *hist;
	lst_t *alias_node;
	int environment_changed;
	int return_status;
	char **cmd_buffer;   /* it is a pointer*/
	int cmd_buffer_type; /*type of cmd*/
	int read_file_descriptor;
	int history_line_count;
} PassInfo_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builting - contains a builtin string and related function
 * @typo: the builtin command flag
 * @function: the function
 */
typedef struct builting
{
	char *typo;
	int (*function)(PassInfo_t *);
} table_t;



/*         str_error.c functions prototypes          */
void print_error(char *);
int error_char(char);
int write_to_fd(char c, int file_d);
int print_to_fd(char *s, int file_d);



/* hsh.c */
int hsh(PassInfo_t *, char **);
int builtinFind(PassInfo_t *);
void cmdFind(PassInfo_t *);
void cmdFork(PassInfo_t *);


/* path.c */
int check_ex_commad(PassInfo_t *, char *);
char *characters_duplicate(char *, int, int);
char *get_path(PassInfo_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_w(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* string_handling_4.c */
char **string_to_word(char *, char *);
char **string_to_word_ecounter(char *, char);

/* functions_for_memory.c */
char *_set_memory(char *, char, unsigned int);
void free_string(char **);
void *_memory_reallocate(void *, unsigned int, unsigned int);

/* functions_for_memory_2.c */
int free_pointer(void **);

/* additional.c */
int mode_interact(PassInfo_t *);
int is_char_delim(char, char *);
int _is_char_alphabatic(int);
int _str_to_int(char *);

/* print_comment_handling.c */
int _str_to_int_witherror(char *);
void error_handling(PassInfo_t *, char *);
int decimal_print(int, int);
char *number_to_str(long int, int, int);
void comments_handling(char *);

/*  emulators1.c */
int _xit(PassInfo_t *);
int _cd(PassInfo_t *);
int _help(PassInfo_t *);

/* toem_builtin1.c */
int _myhistory(PassInfo_t *);
int _myalias(PassInfo_t *);

/*toem_getline.c */
ssize_t get_input(PassInfo_t *);
int _getline(PassInfo_t *, char **, size_t *);
void sigintHandler(int);

/* information.c */
void clear_shell_info(PassInfo_t *);
void set_shell_info(PassInfo_t *, char **);
void free_shell_info(PassInfo_t *, int);

/* enviroment.c */
int print_env(PassInfo_t *);
char *get_env_value(PassInfo_t *, const char *);
int set_env_var(PassInfo_t *);
int unset_env_var(PassInfo_t *);
int populate_env_lst(PassInfo_t *);

/* envitoment2.c */
char **copy_environ_to_string_array(PassInfo_t *); 
int delete_env_var(PassInfo_t *, char *);
int set_env_variable(PassInfo_t *, char *, char *);

/* toem_history.c */
char *get_history_file(PassInfo_t *info);
int write_history(PassInfo_t *info);
int read_history(PassInfo_t *info);
int build_history_list(PassInfo_t *info, char *buf, int linecount);
int renumber_history(PassInfo_t *info);

/* list_handling.c */
lst_t *node_addition_start(lst_t **, const char *, int);
lst_t *add_nodeto_end(lst_t **, const char *, int);
size_t print_lst_str(const lst_t *);
int delete_node(lst_t **, unsigned int);
void free_lst(lst_t **);


/* lists_handling_ctd.c */
size_t get_length(const lst_t *);
char **lst_to_strings(lst_t *);
size_t print_lst(const lst_t *);
lst_t *nd_starts_w(lst_t *, char *, char);
ssize_t get_index_of_node(lst_t *, lst_t *);

/* toem_vars.c */
int is_chain(PassInfo_t *, char *, size_t *);
void check_chain(PassInfo_t *, char *, size_t *, size_t, size_t);
int replace_alias(PassInfo_t *);
int replace_vars(PassInfo_t *);
int replace_string(char **, char *);

#endif
