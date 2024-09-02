
typedef struct word_list
{
	struct word_list	*next;
	WORD_DESC			*word;
}						WORD_LIST;

typedef struct word_desc
{
	char *word; /* Zero terminated string. */
	int flags;  /* Flags associated with this word. */
}						WORD_DESC;

typedef struct redirect
{
	struct redirect *next; /* Next element, or NULL. */
	REDIRECTEE			redirector;
	/* Descriptor or varname to be redirected. */
	int rflags;                     /* Private flags for this redirection */
	int flags;                      /* Flag value for `open'. */
	enum r_instruction instruction; /* What to do with the information. */
	REDIRECTEE redirectee;          /* File descriptor or filename */
	char *here_doc_eof;             /* The word that appeared in <<foo. */
}						REDIRECT;