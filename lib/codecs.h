/* Function parameters for encoding functions */
#define BASE64_ENC_PARAMS			\
	( struct base64_state	*	state	\
	, const char		*const	src	\
	, size_t			srclen	\
	, char			*const	out	\
	, size_t		*const	outlen	\
	)

/* Function parameters for decoding functions */
#define BASE64_DEC_PARAMS			\
	( struct base64_state	*	state	\
	, const char		*const	src	\
	, size_t			srclen	\
	, char			*const	out	\
	, size_t		*const	outlen	\
	)

/* Function signature for encoding functions */
#define BASE64_ENC_FUNCTION(arch)		\
	void					\
	base64_stream_encode_ ## arch		\
	BASE64_ENC_PARAMS

/* Function signature for decoding functions */
#define BASE64_DEC_FUNCTION(arch)		\
	int					\
	base64_stream_decode_ ## arch		\
	BASE64_DEC_PARAMS

/* Cast away unused variable, silence compiler */
#define UNUSED(x)		((void)(x))

/* Stub function when encoder arch unsupported */
#define BASE64_ENC_STUB				\
	UNUSED(state);				\
	UNUSED(src);				\
	UNUSED(srclen);				\
	UNUSED(out);				\
						\
	*outlen = 0;

/* Stub function when decoder arch unsupported */
#define BASE64_DEC_STUB				\
	UNUSED(state);				\
	UNUSED(src);				\
	UNUSED(srclen);				\
	UNUSED(out);				\
	UNUSED(outlen);				\
						\
	return -1;

struct codec
{
	void (* enc) BASE64_ENC_PARAMS;
	int  (* dec) BASE64_DEC_PARAMS;
};

void codec_choose (struct codec *, int flags);

/* These tables are used by all codecs
 * for fallback plain encoding/decoding: */
extern const unsigned char base64_table_enc[];
extern const unsigned char base64_table_dec[];
