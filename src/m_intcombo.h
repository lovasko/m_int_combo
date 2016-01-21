#ifndef M_INTCOMBO_H
#define M_INTCOMBO_H

#include <stdint.h>
#include <m_array.h>

#define M_INTCOMBO_OK             0
#define M_INTCOMBO_END            1
#define M_INTCOMBO_E_NULL         2
#define M_INTCOMBO_E_ORDER        3
#define M_INTCOMBO_E_UNKNOWN_CODE 4
#define M_INTCOMBO_E_MAX          4

struct m_intcombo {
	struct m_array array;
	intmax_t* data;
	unsigned int n_values;
	int first;
};

int m_intcombo_init(struct m_intcombo* ic);
int m_intcombo_add(struct m_intcombo* ic, intmax_t lo, intmax_t hi);
int m_intcombo_finalize(struct m_intcombo* ic, intmax_t** out);
int m_intcombo_next(struct m_intcombo* ic);
int m_intcombo_reset(struct m_intcombo* ic);
int m_intcombo_free(struct m_intcombo* ic);
int m_intcombo_error_string(int code, char** out_error_string);

#endif

