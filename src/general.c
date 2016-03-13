#include "m_int_combo.h"

int
m_int_combo_init(m_int_combo* ic)
{
	if (ic == NULL)
		return M_INT_COMBO_E_NULL;

	m_array_init(&ic->array, 3, sizeof(intmax_t));
	ic->data = NULL;
	ic->n_values = 0;

	return M_INT_COMBO_OK;
}

int
m_int_combo_free(m_int_combo* ic)
{
	if (ic == NULL)
		return M_INT_COMBO_E_NULL;

	free(ic->data);

	return M_INT_COMBO_OK;
}

int
m_int_combo_error_string(int code, const char** out_error_string)
{
	static const char* error_strings[] = {
		"OK",
		"End",
		"Null",
		"Wrong order",
		"Unknown code"
	};

	if (out_error_string == NULL)
		return M_INT_COMBO_E_NULL;

	if (code < 0 || code > M_INT_COMBO_E_MAX)
		return M_INT_COMBO_E_UNKNOWN_CODE;

	*out_error_string = error_strings[code];
	return M_INT_COMBO_OK;
}

