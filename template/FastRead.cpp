
{
	const int BUFFER_LEN = 1024 * 1024 * 5;
	static char buffer[BUFFER_LEN];
	char *ptr = buffer, *buf_end = ptr + 1;
#define PTR_NEXT() \
	{ \
		ptr ++; \
		if (ptr == buf_end) \
		{ \
			ptr = buffer; \
			buf_end = buffer + fread(buffer, 1, BUFFER_LEN, fin); \
		} \
	}
#define READ_INT(_x_) \
	{ \
		while ((*ptr < '0' || *ptr > '9') && *ptr != '-') \
		PTR_NEXT(); \
		bool _nega_ = false; \
		if (*ptr == '-') \
		{ \
			_nega_ = true; \
			PTR_NEXT(); \
		} \
		int register _n_ = 0; \
		while (*ptr >= '0' && *ptr <= '9') \
		{ \
			_n_ = _n_ * 10 + *ptr - '0'; \
			PTR_NEXT(); \
		} \
		if (_nega_) \
		_n_ = - _n_; \
		(_x_) = (_n_); \
	}
#define READ_STR(_s_) \
	{ \
		while ((*ptr < 'A' || *ptr > 'Z') && (*ptr < 'a' || *ptr > 'z')) \
		PTR_NEXT(); \
		char *_p_ = (_s_); \
		while ((*ptr >= 'A' && *ptr <= 'Z') || (*ptr >= 'a' && *ptr <= 'z')) \
		{ \
			*(_p_ ++) = *ptr; \
			PTR_NEXT(); \
		} \
		*_p_ = 0; \
	}
#define READ_DOUBLE(_d_) \
	{ \
		while ((*ptr < '0' || *ptr > '9') && *ptr != '.') \
		PTR_NEXT(); \
		double register _r_ = 0, _c_ = 1; \
		bool _f_ = 0; \
		while ((*ptr >= '0' && *ptr <= '9') || *ptr == '.') \
		{ \
			if (*ptr == '.') \
			_f_ = 1; \
			else \
			{ \
				if (_f_) \
				{ \
					_c_ *= 0.1; \
					_r_ += (*ptr - '0') * _c_; \
				} \
				else _r_ = _r_ * 10 + *ptr - '0'; \
			} \
			PTR_NEXT(); \
		} \
		(_d_) = _r_; \
	}
	PTR_NEXT();

#undef PTR_NEXT
#undef READ_INT
#undef READ_STR
#undef READ_DOUBLE
}
