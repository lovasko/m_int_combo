#include "m_int_combo.h"

int
m_int_combo_add(m_int_combo* ic, intmax_t lo, intmax_t hi)
{
	if (ic == NULL)
		return M_INT_COMBO_E_NULL;

	if (lo > hi)
		return M_INT_COMBO_E_ORDER;

	m_array_append(&ic->array, 1, &lo);
	m_array_append(&ic->array, 1, &hi);
	ic->n_values++;

	return M_INT_COMBO_OK;
}

static void
reset_counters(m_int_combo* ic)
{
	unsigned int i;
	void* lo;

	for (i = 0; i < ic->n_values; i++) {
		m_array_get(&ic->array, i*2, &lo);
		ic->data[i] = *(intmax_t*)lo;
	}

	ic->first = 1;
}

int
m_int_combo_finalize(m_int_combo* ic, intmax_t** out)
{
	if (ic == NULL || out == NULL)
		return M_INT_COMBO_E_NULL;

	m_array_trim(&ic->array);

	if (ic->data != NULL)
		free(ic->data);
	ic->data = malloc(sizeof(intmax_t) * ic->n_values);

	reset_counters(ic);

	*out = ic->data;
	return M_INT_COMBO_OK;
}

int
m_int_combo_next(m_int_combo* ic)
{
	unsigned int idx;
	void* lo;
	void* hi;

	if (ic == NULL)
		return M_INT_COMBO_E_NULL;

	if (ic->first == 1) {
		ic->first = 0;
		return M_INT_COMBO_OK;
	}

	idx = 0;
	while (idx != ic->n_values) {
		ic->data[idx]++;
		m_array_get(&ic->array, idx*2 + 1, &hi);
		if (ic->data[idx] > *(intmax_t*)hi) {
			m_array_get(&ic->array, idx*2, &lo);
			ic->data[idx] = *(intmax_t*)lo;
			idx++;
		}
		else
			return M_INT_COMBO_OK;
	}

	return M_INT_COMBO_END;
}

int
m_int_combo_reset(m_int_combo* ic)
{
	if (ic == NULL)
		return M_INT_COMBO_E_NULL;

	reset_counters(ic);

	return M_INT_COMBO_OK;
}
