/*   Foma: a finite-state toolkit and library.                                 */
/*   Copyright © 2008-2015 Mans Hulden                                         */

/*   This file is part of foma.                                                */

/*   Licensed under the Apache License, Version 2.0 (the "License");           */
/*   you may not use this file except in compliance with the License.          */
/*   You may obtain a copy of the License at                                   */

/*      http://www.apache.org/licenses/LICENSE-2.0                             */

/*   Unless required by applicable law or agreed to in writing, software       */
/*   distributed under the License is distributed on an "AS IS" BASIS,         */
/*   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  */
/*   See the License for the specific language governing permissions and       */
/*   limitations under the License.                                            */

#ifndef FOMALIB_H
#define FOMALIB_H

#ifdef  __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include "zlib.h"

#define INLINE inline

#define FEXPORT __attribute__((visibility("default")))

/* Library version */
#define MAJOR_VERSION 0
#define MINOR_VERSION 9
#define BUILD_VERSION 18
#define STATUS_VERSION "alpha"

/* Special symbols on arcs */
#define EPSILON 0
#define UNKNOWN 1
#define IDENTITY 2

/* Variants of ignore operation */
#define OP_IGNORE_ALL 1
#define OP_IGNORE_INTERNAL 2

/* Replacement direction */
#define OP_UPWARD_REPLACE    1
#define OP_RIGHTWARD_REPLACE 2
#define OP_LEFTWARD_REPLACE  3
#define OP_DOWNWARD_REPLACE  4
#define OP_TWO_LEVEL_REPLACE 5

/* Arrow types in fsmrules */
#define ARROW_RIGHT 1
#define ARROW_LEFT 2
#define ARROW_OPTIONAL 4
#define ARROW_DOTTED 8         /* This is for the [..] part of a dotted rule */
#define ARROW_LONGEST_MATCH 16
#define ARROW_SHORTEST_MATCH 32
#define ARROW_LEFT_TO_RIGHT 64
#define ARROW_RIGHT_TO_LEFT 128

/* Flag types */
#define FLAG_UNIFY 1
#define FLAG_CLEAR 2
#define FLAG_DISALLOW 4
#define FLAG_NEGATIVE 8
#define FLAG_POSITIVE 16
#define FLAG_REQUIRE 32
#define FLAG_EQUAL 64

#define NO  0
#define YES 1
#define UNK 2

#define PATHCOUNT_CYCLIC -1
#define PATHCOUNT_OVERFLOW -2
#define PATHCOUNT_UNKNOWN -3

#define M_UPPER 1
#define M_LOWER 2

#define APPLY_INDEX_INPUT 1
#define APPLY_INDEX_OUTPUT 2

/* Defined networks */
struct defined_networks {
  char *name;
  struct fsm *net;
  struct defined_networks *next;
};

/* Defined functions */
struct defined_functions {
    char *name;
    char *regex;
    int numargs;
    struct defined_functions *next;
};

struct defined_quantifiers {
    char *name;
    struct defined_quantifiers *next;
};

/* Automaton structures */

/** Main automaton structure */
struct fsm {
  char name[40];
  int arity;
  int arccount;
  int statecount;
  int linecount;
  int finalcount;
  long long pathcount;
  int is_deterministic;
  int is_pruned;
  int is_minimized;
  int is_epsilon_free;
  int is_loop_free;
  int is_completed;
  int arcs_sorted_in;
  int arcs_sorted_out;
  struct fsm_state *states;             /* pointer to first line */
  struct sigma *sigma;
  struct medlookup *medlookup;
};

/* Minimum edit distance structure */

struct medlookup {
    int *confusion_matrix;      /* Confusion matrix */
};

/** Array of states */
struct fsm_state {
    int state_no; /* State number */
    short int in ;
    short int out ;
    int target;
    char final_state ;
    char start_state ;
};

struct fsmcontexts {
    struct fsm *left;
    struct fsm *right;
    struct fsmcontexts *next;
    struct fsm *cpleft;      /* Only used internally when compiling rewrite rules */
    struct fsm *cpright;     /* ditto */
};

struct fsmrules {
    struct fsm *left;
    struct fsm *right;   
    struct fsm *right2;    /*Only needed for A -> B ... C rules*/
    struct fsm *cross_product;
    struct fsmrules *next;
    int arrow_type;
    int dotted;           /* [.A.] rule */
};

struct rewrite_set {
    struct fsmrules *rewrite_rules;
    struct fsmcontexts *rewrite_contexts;
    struct rewrite_set *next;
    int rule_direction;    /* || \\ // \/ */
};

FEXPORT void fsm_clear_contexts(struct fsmcontexts *contexts);

/** Linked list of sigma */
/** number < IDENTITY is reserved for special symbols */
struct sigma {
    int number;
    char *symbol;
    struct sigma *next;
};

struct state_array {
    struct fsm_state *transitions;
};

struct fsm_trans_list {
    short int in;
    short int out;
    int target;
    struct fsm_trans_list *next;
};

struct fsm_state_list {
    _Bool used;
    _Bool is_final;
    _Bool is_initial;
    short int num_trans;
    int state_number;
    struct fsm_trans_list *fsm_trans_list;
};

struct fsm_sigma_list {
    char *symbol;
};

struct fsm_sigma_hash {
    char *symbol;
    short int sym;
    struct fsm_sigma_hash *next;
};

typedef void *fsm_read_binary_handle;

struct fsm_construct_handle {
    struct fsm_state_list *fsm_state_list;
    int fsm_state_list_size;
    struct fsm_sigma_list *fsm_sigma_list;
    int fsm_sigma_list_size;
    struct fsm_sigma_hash *fsm_sigma_hash;
    int fsm_sigma_hash_size;
    int maxstate;
    int maxsigma;
    int numfinals;
    int hasinitial;
    char *name;
};

struct apply_med_handle {
    struct astarnode {
    short int wordpos;
    int fsmstate;
    short int f;
    short int g;
    short int h;
    int in;
    int out;
    int parent;
    } *agenda;
    int bytes_per_letter_array;
    uint8_t *letterbits;
    uint8_t *nletterbits;
    int astarcount;
    int heapcount;
    int heap_size;
    int agenda_size;
    int maxdepth;
    int maxsigma;
    int wordlen;
    int utf8len;
    int cost;
    int nummatches;
    int curr_state;
    int curr_g;
    int curr_pos;
    int lines;
    int curr_agenda_offset;
    int curr_node_has_match;
    int med_limit;
    int med_cutoff;
    int med_max_heap_size;
    int nodes_expanded;
    int *cm;
    char *word;
    char *instring;
    int instring_length;
    char *outstring;
    int outstring_length;
    char *align_symbol;
    int *heap;
    int *intword;
    struct sh_handle *sigmahash;
    struct state_array *state_array;
    struct fsm *net;
    struct fsm_state *curr_ptr;
    _Bool hascm;
};

struct apply_handle {

    int ptr;
    int curr_ptr;
    int ipos;
    int opos;
    int mode;
    int printcount;
    int *numlines;
    int *statemap;
    int *marks;

    struct sigma_trie {
    int signum;
    struct sigma_trie *next;
    } *sigma_trie;

    struct sigmatch_array {
    int signumber ;
    int consumes ;
    } *sigmatch_array;

    struct sigma_trie_arrays {
    struct sigma_trie *arr;
    struct sigma_trie_arrays *next;
    } *sigma_trie_arrays;

    int binsearch;
    int indexed;
    int state_has_index;
    int sigma_size;
    int sigmatch_array_size;
    int current_instring_length;
    int has_flags;
    int obey_flags;
    int show_flags;
    int print_space;
    char *space_symbol;
    char *separator;
    char *epsilon_symbol;
    int print_pairs;
    int apply_stack_ptr;
    int apply_stack_top;
    int oldflagneg;
    int outstringtop;
    int iterate_old;
    int iterator;
    uint8_t *flagstates;
    char *outstring;
    char *instring;
    struct sigs {
    char *symbol;
    int length;
    } *sigs;
    char *oldflagvalue;
    
    struct fsm *last_net;
    struct fsm_state *gstates;
    struct sigma *gsigma;
    struct apply_state_index {
    int fsmptr;
    struct apply_state_index *next;
    } **index_in, **index_out, *iptr;

    struct flag_list {
    char *name;
    char *value;
    short neg;
    struct flag_list *next;
    } *flag_list;

    struct flag_lookup {
    int type;
    char *name;
    char *value;
    } *flag_lookup ;

    struct searchstack {
    int offset;
    struct apply_state_index *iptr;
    int state_has_index;
    int opos;
    int ipos;
    int visitmark;
    char *flagname;
    char *flagvalue;
    int flagneg;
    } *searchstack ;
};


/* Automaton functions operating on fsm_state */
int add_fsm_arc(struct fsm_state *fsm, int offset, int state_no, int in, int out, int target, int final_state, int start_state);
struct fsm_state *fsm_state_copy(struct fsm_state *fsm_state, int linecount);

/* Functions for constructing a FSM arc-by-arc */
/* At the end of the constructions, the flags are updated automatically */

/* Call fsm_state_init with the alphabet size to initialize the new machine */
struct fsm_state *fsm_state_init(int sigma_size);

/* Call set current state before calling fsm_state_add_arc */
void fsm_state_set_current_state(int state_no, int final_state, int start_state);

/* Add an arc */
void fsm_state_add_arc(int state_no, int in, int out, int target, int final_state, int start_state);

/* Call fsm_state_close() when done with arcs to a state */
void fsm_state_close(struct fsm *net);

/* Call this when done with entire FSM */
void fsm_state_end_state();

struct state_array *map_firstlines(struct fsm *net);

FEXPORT void fsm_count(struct fsm *net);

void fsm_sort_lines(struct fsm *net);
void fsm_update_flags(struct fsm *net, int det, int pru, int min, int eps, int loop, int completed);

int sort_cmp(const void *a, const void *b);

int find_arccount(struct fsm_state *fsm);

/* Internal int stack */
int int_stack_isempty();
int int_stack_isfull();
void int_stack_clear();
int int_stack_find (int entry);
void int_stack_push(int c);
int int_stack_pop();
int int_stack_status();
int int_stack_size();

/* Internal ptr stack */
int ptr_stack_isempty();
void ptr_stack_clear();
void *ptr_stack_pop();
int ptr_stack_isfull();
void ptr_stack_push(void *ptr);

/* Sigma functions */
FEXPORT int sigma_add (char *symbol, struct sigma *sigma);
FEXPORT int sigma_add_number(struct sigma *sigma, char *symbol, int number);
FEXPORT int sigma_add_special (int symbol, struct sigma *sigma);
FEXPORT struct sigma *sigma_remove(char *symbol, struct sigma *sigma);
FEXPORT struct sigma *sigma_remove_num(int num, struct sigma *sigma);

int sigma_find (char *symbol, struct sigma *sigma);
int sigma_find_number (int number, struct sigma *sigma);
int sigma_substitute(char *orig, char *sub, struct sigma *sigma);
FEXPORT char *sigma_string(int number, struct sigma *sigma);
int sigma_sort (struct fsm *net);
void sigma_cleanup (struct fsm *net, int force);
FEXPORT struct sigma *sigma_create ();
int sigma_size(struct sigma *sigma);
FEXPORT int sigma_max(struct sigma *sigma);
struct fsm_sigma_list *sigma_to_list(struct sigma *sigma);

/* Debug */
void xprintf(char *string);

/* UTF8 */
unsigned char *utf8code16tostr(char *str);
int utf8iscombining(unsigned char *s);
int utf8skip(char *str);
int utf8strlen(char *str);
int ishexstr(char *str);
void decode_quoted(char *s);
void dequote_string(char *s);
char *remove_trailing(char *s, char c);
char *escape_string(char *string, char chr);
char *xstrrev(char *str);

/* Flag-related */
int flag_check(char *sm);
char *flag_get_name(char *string);
char *flag_get_value(char *string);
int flag_get_type(char *string);

/* Misc */
char *trim(char *string);
void strip_newline(char *s);
char *streqrep(char *s, char *oldstring, char *newstring);
char *xxstrndup(const char *s, size_t n);
char *xxstrdup(const char *s);
FEXPORT void *xxmalloc(size_t size);
void *xxcalloc(size_t nmemb, size_t size);
void *xxrealloc(void *ptr, size_t size);
void xxfree(void *ptr);
int next_power_of_two(int v);
unsigned int round_up_to_power_of_two(unsigned int v);

/* Define functions */
FEXPORT struct defined_networks *defined_networks_init(void);
FEXPORT struct defined_functions *defined_functions_init(void);
struct fsm *find_defined(struct defined_networks *def, char *string);
char *find_defined_function(struct defined_functions *deff, char *name, int numargs);
FEXPORT int add_defined(struct defined_networks *def, struct fsm *net, char *string);
FEXPORT int add_defined_function (struct defined_functions *deff, char *name, char *regex, int numargs);
int remove_defined (struct defined_networks *def, char *string);

/********************/
/* Basic operations */
/********************/

FEXPORT char *fsm_get_library_version_string();

FEXPORT struct fsm *fsm_determinize(struct fsm *net);
FEXPORT struct fsm *fsm_epsilon_remove(struct fsm *net);
FEXPORT struct fsm *fsm_find_ambiguous(struct fsm *net, int **extras);
FEXPORT struct fsm *fsm_minimize(struct fsm *net);
FEXPORT struct fsm *fsm_coaccessible(struct fsm *net);
FEXPORT struct fsm *fsm_topsort(struct fsm *net);
FEXPORT void fsm_sort_arcs(struct fsm *net, int direction);
FEXPORT struct fsm *fsm_mark_ambiguous(struct fsm *net);
FEXPORT struct fsm *fsm_sequentialize(struct fsm *net);
FEXPORT struct fsm *fsm_bimachine(struct fsm *net);

FEXPORT struct fsm *fsm_parse_regex(char *regex, struct defined_networks *defined_nets, struct defined_functions *defined_funcs);
FEXPORT struct fsm *fsm_reverse(struct fsm *net);
FEXPORT struct fsm *fsm_invert(struct fsm *net);
FEXPORT struct fsm *fsm_lower(struct fsm *net);
FEXPORT struct fsm *fsm_upper(struct fsm *net);
FEXPORT struct fsm *fsm_kleene_star(struct fsm *net);
FEXPORT struct fsm *fsm_kleene_plus(struct fsm *net);
FEXPORT struct fsm *fsm_optionality(struct fsm *net);
FEXPORT struct fsm *fsm_boolean(int value);
FEXPORT struct fsm *fsm_concat(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_concat_n(struct fsm *net1, int n);
FEXPORT struct fsm *fsm_concat_m_n(struct fsm *net1, int m, int n);
FEXPORT struct fsm *fsm_union(struct fsm *net_1, struct fsm *net_2);
FEXPORT struct fsm *fsm_priority_union_upper(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_priority_union_lower(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_intersect(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_compose(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_lenient_compose(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_cross_product(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_shuffle(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_precedes(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_follows(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_symbol(char *symbol);
FEXPORT struct fsm *fsm_explode(char *symbol);
FEXPORT struct fsm *fsm_escape(char *symbol);
FEXPORT struct fsm *fsm_copy(struct fsm *net);
FEXPORT struct fsm *fsm_complete(struct fsm *net);
FEXPORT struct fsm *fsm_complement(struct fsm *net);
FEXPORT struct fsm *fsm_term_negation(struct fsm *net1);
FEXPORT struct fsm *fsm_minus(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_simple_replace(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_context_restrict(struct fsm *X, struct fsmcontexts *LR);
FEXPORT struct fsm *fsm_contains(struct fsm *net);
FEXPORT struct fsm *fsm_contains_opt_one(struct fsm *net);
FEXPORT struct fsm *fsm_contains_one(struct fsm *net);
FEXPORT struct fsm *fsm_ignore(struct fsm *net1, struct fsm *net2, int operation);
FEXPORT struct fsm *fsm_quotient_right(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_quotient_left(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_quotient_interleave(struct fsm *net1, struct fsm *net2);
FEXPORT struct fsm *fsm_substitute_label(struct fsm *net, char *original, struct fsm *substitute);
FEXPORT struct fsm *fsm_substitute_symbol(struct fsm *net, char *original, char *substitute);
FEXPORT struct fsm *fsm_universal();
FEXPORT struct fsm *fsm_empty_set();
FEXPORT struct fsm *fsm_empty_string();
FEXPORT struct fsm *fsm_identity();
FEXPORT struct fsm *fsm_quantifier(char *string);
FEXPORT struct fsm *fsm_logical_eq(char *string1, char *string2);
FEXPORT struct fsm *fsm_logical_precedence(char *string1, char *string2);
FEXPORT struct fsm *fsm_lowerdet(struct fsm *net);
FEXPORT struct fsm *fsm_lowerdeteps(struct fsm *net);
FEXPORT struct fsm *fsm_markallfinal(struct fsm *net);
FEXPORT struct fsm *fsm_extract_nonidentity(struct fsm *net);
FEXPORT struct fsm *fsm_extract_ambiguous_domain(struct fsm *net);
FEXPORT struct fsm *fsm_extract_ambiguous(struct fsm *net);
FEXPORT struct fsm *fsm_extract_unambiguous(struct fsm *net);
FEXPORT struct fsm *fsm_sigma_net(struct fsm *net);
FEXPORT struct fsm *fsm_sigma_pairs_net(struct fsm *net);
FEXPORT struct fsm *fsm_equal_substrings(struct fsm *net, struct fsm *left, struct fsm *right);
FEXPORT struct fsm *fsm_letter_machine(struct fsm *net);
FEXPORT struct fsm *fsm_mark_fsm_tail(struct fsm *net, struct fsm *marker);
FEXPORT struct fsm *fsm_add_loop(struct fsm *net, struct fsm *marker, int finals);
FEXPORT struct fsm *fsm_add_sink(struct fsm *net, int final);
FEXPORT struct fsm *fsm_left_rewr(struct fsm *net, struct fsm *rewr);
FEXPORT struct fsm *fsm_flatten(struct fsm *net, struct fsm *epsilon);
FEXPORT struct fsm *fsm_unflatten(struct fsm *net, char *epsilon_sym, char *repeat_sym);   
FEXPORT struct fsm *fsm_close_sigma(struct fsm *net, int mode);
FEXPORT char *fsm_network_to_char(struct fsm *net);

/* Remove those symbols from sigma that have the same distribution as IDENTITY */
FEXPORT void fsm_compact(struct fsm *net);

FEXPORT int flag_build(int ftype, char *fname, char *fvalue, int fftype, char *ffname, char *ffvalue);

/* Eliminate flag diacritics and return equivalent FSM          */
/* with name = NULL the function eliminates all flag diacritics */
FEXPORT struct fsm *flag_eliminate(struct fsm *net, char *name);

/* Enforce twosided flag diacritics */
FEXPORT struct fsm *flag_twosided(struct fsm *net);

/* Compile a rewrite rule */
FEXPORT struct fsm *fsm_rewrite();

/* Boolean tests */
FEXPORT int fsm_isempty(struct fsm *net);
FEXPORT int fsm_isfunctional(struct fsm *net);
FEXPORT int fsm_isunambiguous(struct fsm *net);
FEXPORT int fsm_isidentity(struct fsm *net);
FEXPORT int fsm_isuniversal(struct fsm *net);
FEXPORT int fsm_issequential(struct fsm *net);
FEXPORT int fsm_equivalent(struct fsm *net1, struct fsm *net2);

/* Test if a symbol occurs in a FSM */
/* side = M_UPPER (upper side) M_LOWER (lower side), M_UPPER+M_LOWER (both) */
FEXPORT int fsm_symbol_occurs(struct fsm *net, char *symbol, int side);

/* Merges two alphabets destructively */
FEXPORT void fsm_merge_sigma(struct fsm *net1, struct fsm *net2);

/* Copies an alphabet */

FEXPORT struct sigma *sigma_copy(struct sigma *sigma);

/* Create empty FSM */
FEXPORT struct fsm *fsm_create(char *name);
FEXPORT struct fsm_state *fsm_empty();

/* Frees alphabet */
FEXPORT int fsm_sigma_destroy(struct sigma *sigma);

/* Frees a FSM, associated data such as alphabet and confusion matrix */
FEXPORT int fsm_destroy(struct fsm *net);

/* IO functions */
FEXPORT struct fsm *read_att(char *filename);
FEXPORT int net_print_att(struct fsm *net, FILE *outfile);
FEXPORT struct fsm *fsm_read_prolog(char *filename);
FEXPORT char *file_to_mem(char *name);
FEXPORT struct fsm *fsm_read_binary_file(char *filename);
FEXPORT struct fsm *fsm_read_binary_file_multiple(fsm_read_binary_handle fsrh);
FEXPORT fsm_read_binary_handle fsm_read_binary_file_multiple_init(char *filename);
FEXPORT struct fsm *fsm_read_text_file(char *filename);
FEXPORT struct fsm *fsm_read_spaced_text_file(char *filename);
FEXPORT int fsm_write_binary_file(struct fsm *net, char *filename);
FEXPORT int load_defined(struct defined_networks *def, char *filename);
FEXPORT int save_defined(struct defined_networks *def, char *filename);
FEXPORT int save_stack_att();
FEXPORT int foma_write_prolog(struct fsm *net, char *filename);
FEXPORT int foma_net_print(struct fsm *net, gzFile outfile);

/* Lookups */

/* Frees memory alloced by apply_init */
FEXPORT void apply_clear(struct apply_handle *h);
/* To be called before applying words */
FEXPORT struct apply_handle *apply_init(struct fsm *net);
FEXPORT struct apply_med_handle *apply_med_init(struct fsm *net);
FEXPORT void apply_med_clear(struct apply_med_handle *h);

FEXPORT void apply_med_set_heap_max(struct apply_med_handle *medh, int max);
FEXPORT void apply_med_set_med_limit(struct apply_med_handle *medh, int max);
FEXPORT void apply_med_set_med_cutoff(struct apply_med_handle *medh, int max);
FEXPORT int apply_med_get_cost(struct apply_med_handle *medh);
FEXPORT void apply_med_set_align_symbol(struct apply_med_handle *medh, char *align);
FEXPORT char *apply_med_get_instring(struct apply_med_handle *medh);
FEXPORT char *apply_med_get_outstring(struct apply_med_handle *medh);

FEXPORT char *apply_down(struct apply_handle *h, char *word);
FEXPORT char *apply_up(struct apply_handle *h, char *word);
FEXPORT char *apply_med(struct apply_med_handle *medh, char *word);
FEXPORT char *apply_upper_words(struct apply_handle *h);
FEXPORT char *apply_lower_words(struct apply_handle *h);
FEXPORT char *apply_words(struct apply_handle *h);
FEXPORT char *apply_random_lower(struct apply_handle *h);
FEXPORT char *apply_random_upper(struct apply_handle *h);
FEXPORT char *apply_random_words(struct apply_handle *h);
/* Reset the iterator to start anew with enumerating functions */
FEXPORT void apply_reset_enumerator(struct apply_handle *h);
FEXPORT void apply_index(struct apply_handle *h, int inout, int densitycutoff, int mem_limit, int flags_only);
FEXPORT void apply_set_show_flags(struct apply_handle *h, int value);
FEXPORT void apply_set_obey_flags(struct apply_handle *h, int value);
FEXPORT void apply_set_print_space(struct apply_handle *h, int value);
FEXPORT void apply_set_print_pairs(struct apply_handle *h, int value);
FEXPORT void apply_set_space_symbol(struct apply_handle *h, char *space);
FEXPORT void apply_set_separator(struct apply_handle *h, char *symbol);
FEXPORT void apply_set_epsilon(struct apply_handle *h, char *symbol);
    
/* Minimum edit distance & spelling correction */
FEXPORT void fsm_create_letter_lookup(struct apply_med_handle *medh, struct fsm *net);
FEXPORT void cmatrix_init(struct fsm *net);
FEXPORT void cmatrix_default_substitute(struct fsm *net, int cost);
FEXPORT void cmatrix_default_insert(struct fsm *net, int cost);
FEXPORT void cmatrix_default_delete(struct fsm *net, int cost);
FEXPORT void cmatrix_set_cost(struct fsm *net, char *in, char *out, int cost);
FEXPORT void cmatrix_print(struct fsm *net);
FEXPORT void cmatrix_print_att(struct fsm *net, FILE *outfile);

/* Lexc */
  FEXPORT struct fsm *fsm_lexc_parse_file(char *myfile, int verbose);
  FEXPORT struct fsm *fsm_lexc_parse_string(char *mystring, int verbose);

/*************************/
/* Construction routines */
/*************************/

FEXPORT struct fsm_construct_handle *fsm_construct_init(char *name);
FEXPORT void fsm_construct_set_final(struct fsm_construct_handle *handle, int state_no);
FEXPORT void fsm_construct_set_initial(struct fsm_construct_handle *handle, int state_no);
FEXPORT void fsm_construct_add_arc(struct fsm_construct_handle *handle, int source, int target, char *in, char *out);
FEXPORT void fsm_construct_add_arc_nums(struct fsm_construct_handle *handle, int source, int target, int in, int out);
FEXPORT int fsm_construct_add_symbol(struct fsm_construct_handle *handle, char *symbol);
FEXPORT int fsm_construct_check_symbol(struct fsm_construct_handle *handle, char *symbol);
FEXPORT void fsm_construct_copy_sigma(struct fsm_construct_handle *handle, struct sigma *sigma);
FEXPORT struct fsm *fsm_construct_done(struct fsm_construct_handle *handle);


/******************/
/* String hashing */
/******************/

struct sh_handle {
    struct sh_hashtable *hash;
    int lastvalue;
};

struct sh_hashtable {
    char *string;
    int value;
    struct sh_hashtable *next;
};

struct sh_handle *sh_init();
void sh_done(struct sh_handle *sh);
char *sh_find_string(struct sh_handle *sh, char *string);
char *sh_find_add_string(struct sh_handle *sh, char *string, int value);
char *sh_add_string(struct sh_handle *sh, char *string, int value);
int sh_get_value(struct sh_handle *sh);

/*********************/
/* Trie construction */
/*********************/

struct trie_hash {
    char *insym;
    char *outsym;
    unsigned int sourcestate;
    unsigned int targetstate;
    struct trie_hash *next;
};

struct trie_states {
    _Bool is_final;
};

struct fsm_trie_handle {
    struct trie_states *trie_states;
    unsigned int trie_cursor;
    struct trie_hash *trie_hash;
    unsigned int used_states;
    unsigned int statesize;
    struct sh_handle *sh_hash;
};

FEXPORT struct fsm_trie_handle *fsm_trie_init();
FEXPORT struct fsm *fsm_trie_done(struct fsm_trie_handle *th);
FEXPORT void fsm_trie_add_word(struct fsm_trie_handle *th, char *word);
FEXPORT void fsm_trie_end_word(struct fsm_trie_handle *th);
FEXPORT void fsm_trie_symbol(struct fsm_trie_handle *th, char *insym, char *outsym);

/***********************/
/* Extraction routines */
/***********************/

struct fsm_read_handle {
    struct fsm_state *arcs_head;
    struct fsm_state **states_head;
    struct fsm_state *arcs_cursor;
    int *finals_head;
    int *finals_cursor;
    struct fsm_state **states_cursor;
    int *initials_head;
    int *initials_cursor;
    int current_state;
    struct fsm_sigma_list *fsm_sigma_list;
    int sigma_list_size;
    struct fsm *net;
    unsigned char *lookuptable;
    _Bool has_unknowns;
};

FEXPORT struct fsm_read_handle *fsm_read_init(struct fsm *net);
FEXPORT void fsm_read_reset(struct fsm_read_handle *handle);
FEXPORT int fsm_read_is_final(struct fsm_read_handle *h, int state);
FEXPORT int fsm_read_is_initial(struct fsm_read_handle *h, int state);
FEXPORT int fsm_get_num_states(struct fsm_read_handle *handle);
FEXPORT int fsm_get_has_unknowns(struct fsm_read_handle *handle);
/* Move iterator one arc forward. Returns 0 on no more arcs */
FEXPORT int fsm_get_next_arc(struct fsm_read_handle *handle);
FEXPORT int fsm_get_arc_source(struct fsm_read_handle *handle);
FEXPORT int fsm_get_arc_target(struct fsm_read_handle *handle);
FEXPORT char *fsm_get_arc_in(struct fsm_read_handle *handle);
FEXPORT char *fsm_get_arc_out(struct fsm_read_handle *handle);
FEXPORT int fsm_get_arc_num_in(struct fsm_read_handle *handle);
FEXPORT int fsm_get_arc_num_out(struct fsm_read_handle *handle);
FEXPORT int fsm_get_symbol_number(struct fsm_read_handle *handle, char *symbol);

/* Iterates over initial and final states, returns -1 on end */
FEXPORT int fsm_get_next_initial(struct fsm_read_handle *handle);
FEXPORT int fsm_get_next_final(struct fsm_read_handle *handle);
FEXPORT int fsm_get_next_state(struct fsm_read_handle *handle);
FEXPORT int fsm_get_next_state_arc(struct fsm_read_handle *handle);

/* Frees memory associated with a read handle */
FEXPORT void fsm_read_done(struct fsm_read_handle *handle);

#ifdef  __cplusplus
}
#endif

#endif /* FOMALIB_H */
