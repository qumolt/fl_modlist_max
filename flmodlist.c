#include "flmodlist.h"

void C74_EXPORT main() {

	t_class *c;

	c = class_new("flmodlist",(method)fl_modlist_new, (method)NULL,sizeof(t_fl_modlist), 0, 0);
	class_addmethod(c, (method)fl_modlist_assist,"assist", A_CANT, 0);
	class_addmethod(c,(method)fl_modlist_int, "int", A_LONG, 0);
	class_addmethod(c,(method)fl_modlist_float, "float", A_LONG, 0);
	class_addmethod(c,(method)fl_modlist_list, "list", A_GIMME, 0);
	class_addmethod(c,(method)fl_modlist_mod_val, "mod_val", A_GIMME, 0);

	class_register(CLASS_BOX, c);
	fl_modlist_class = c; 
}

void *fl_modlist_new(t_symbol *s, short argc, t_atom *argv) 
{
	t_fl_modlist *x = (t_fl_modlist *)object_alloc(fl_modlist_class);

	inlet_new((t_object *)x, "list");
	x->m_outlet = intout((t_object *)x);

	x->mod_value = MOD_STDR;
	x->list_len = LIST_LEN_STDR;

	for (long i = 0; i < MAX_LEN_LIST; i++) {
		x->list[i] = 0;
	}
	
	return x;
}

void fl_modlist_assist(t_fl_modlist *x, void *b, long msg, long arg, char *dst)
{
	if (msg == ASSIST_INLET) {										
		switch (arg) {
		case I_INPUT: sprintf(dst, "index"); break;
		case I_LIST: sprintf(dst, "list"); break;
		}

	}
	else if (msg == ASSIST_OUTLET) {    
		switch (arg) {
		case O_OUTPUT: sprintf(dst, "extrapolated term"); break;
		}
	}
}

void fl_modlist_float(t_fl_modlist *x, double f) 
{
	fl_modlist_int(x, (long)f);
}

void fl_modlist_int(t_fl_modlist *x, long n) 
{
	if (n != n) { object_warn((t_object *)x, "wrong number"); return; }
	if (n < 0) { object_warn((t_object *)x, "input must be a positive integer"); return; }

	long list_len = x->list_len;
	long *list = x->list;
	long mod_val = x->mod_value;
	long index = n;

	long output = mod_val * ((long)(index / list_len)) + list[index % list_len];
	outlet_int(x->m_outlet, output);
}

void fl_modlist_list(t_fl_modlist *x, t_symbol *s, long argc, t_atom *argv) 
{
	long ac = argc;
	t_atom *ap = argv;
	long mod_val = x->mod_value;
	long list_len;

	list_len = min(ac, MAX_LEN_LIST);

	for (long i = 0; i < list_len; i++) {
		x->list[i] = ((long)atom_getlong(ap + i)) % mod_val;
	}

	for (long i = 1; i < list_len; i++) {
		if (x->list[i] < x->list[i - 1]) {
			x->list[i] += mod_val;
		}
	}

	x->list_len = list_len;
}

void fl_modlist_mod_val(t_fl_modlist *x, t_symbol *s, long argc, t_atom *argv)
{
	long ac = argc;
	t_atom *ap = argv;
	long mod_val;

	if (ac != 1) { object_error((t_object *)x, "1 integer"); return; }
	mod_val = (long)atom_getlong(ap);

	if (mod_val != mod_val) { object_error((t_object *)x, "wrong number"); return; }

	x->mod_value = mod_val;
}