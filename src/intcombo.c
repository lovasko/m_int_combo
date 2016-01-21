#include "m_intcombo.h"

int
m_intcombo_init(struct m_intcombo* ic)
{
	if (ic == NULL)
		return M_INTCOMBO_E_NULL;

	m_array_init(&ic->array, 3, sizeof(intmax_t));
	ic->data = NULL;
	ic->n_values = 0;

	return M_INTCOMBO_OK;
}

int
m_intcombo_add(struct m_intcombo* ic, intmax_t lo, intmax_t hi)
{
	if (ic == NULL)
		return M_INTCOMBO_E_NULL;

	if (lo > hi)
		return M_INTCOMBO_E_ORDER;

	m_array_append(&ic->array, 1, &lo);
	m_array_append(&ic->array, 1, &hi);
	ic->n_values++;

	return M_INTCOMBO_OK;
}

static void
reset_counters(struct m_intcombo* ic)
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
m_intcombo_finalize(struct m_intcombo* ic, intmax_t** out)
{
	if (ic == NULL || out == NULL)
		return M_INTCOMBO_E_NULL;

	m_array_trim(&ic->array);

	if (ic->data != NULL)
		free(ic->data);
	ic->data = malloc(sizeof(intmax_t) * ic->n_values);

	reset_counters(ic);

	*out = ic->data;
	return M_INTCOMBO_OK;
}

int
m_intcombo_next(struct m_intcombo* ic)
{
	unsigned int idx;
	void* lo;
	void* hi;

	if (ic == NULL)
		return M_INTCOMBO_E_NULL;

	if (ic->first == 1) {
		ic->first = 0;
		return M_INTCOMBO_OK;
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
			return M_INTCOMBO_OK;
	}

	return M_INTCOMBO_END;
}

int
m_intcombo_reset(struct m_intcombo* ic)
{
	if (ic == NULL)
		return M_INTCOMBO_E_NULL;

	reset_counters(ic);

	return M_INTCOMBO_OK;
}

int
m_intcombo_free(struct m_intcombo* ic)
{
	if (ic == NULL)
		return M_INTCOMBO_E_NULL;

	free(ic->data);

	return M_INTCOMBO_OK;
}

int
m_intcombo_error_string(int code, char** out_error_string)
{
	char* strings[] = {
		"OK",
		"End",
		"Null",
		"Wrong order",
		"Unknown code"
	};

	if (out_error_string == NULL)
		return M_INTCOMBO_E_NULL;

	if (code < 0 || code > M_INTCOMBO_E_MAX)
		return M_INTCOMBO_E_UNKNOWN_CODE;

	*out_error_string = strings[code];
	return M_INTCOMBO_OK;
}

