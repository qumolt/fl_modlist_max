#include "ext.h"
#include "ext_obex.h"
#include "z_dsp.h"  
#include <math.h>

#define MOD_STDR 12
#define LIST_LEN_STDR 12
#define MAX_LEN_LIST 256

enum INLETS { I_INPUT, I_LIST, NUM_INLETS };
enum OUTLETS { O_OUTPUT, NUM_OUTLETS };

typedef struct {

	t_object obj;
	
	long mod_value;
	long list[MAX_LEN_LIST];
	long list_len;

	void *m_outlet;

} t_fl_modlist;

void *fl_modlist_new(t_symbol *s, short argc, t_atom *argv);
void fl_modlist_assist(t_fl_modlist *x, void *b, long msg, long arg, char *dst);

void fl_modlist_int(t_fl_modlist *x, long n);
void fl_modlist_float(t_fl_modlist *x, double f);
void fl_modlist_list(t_fl_modlist *x, t_symbol *s, long argc, t_atom *argv);
void fl_modlist_mod_val(t_fl_modlist *x, t_symbol *s, long argc, t_atom *argv);

static t_class *fl_modlist_class;