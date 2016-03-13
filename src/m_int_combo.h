#ifndef M_INT_COMBO_H
#define M_INT_COMBO_H

#include <stdint.h>
#include <m_array.h>

#define M_INT_COMBO_OK             0
#define M_INT_COMBO_END            1
#define M_INT_COMBO_E_NULL         2
#define M_INT_COMBO_E_ORDER        3
#define M_INT_COMBO_E_UNKNOWN_CODE 4
#define M_INT_COMBO_E_MAX          4

typedef struct m_int_combo {
	m_array array;
	intmax_t* data;
	unsigned int n_values;
	int first;
} m_int_combo;

int m_int_combo_init(m_int_combo* ic);
int m_int_combo_free(m_int_combo* ic);
int m_int_combo_add(m_int_combo* ic, intmax_t lo, intmax_t hi);
int m_int_combo_finalize(m_int_combo* ic, intmax_t** out);
int m_int_combo_next(m_int_combo* ic);
int m_int_combo_reset(m_int_combo* ic);
int m_int_combo_error_string(int code, const char** out_error_string);

#endif

