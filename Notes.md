// type of a hashmap content
enum hValType {H_INT, H_UINT, H_VOID, H_CHAR};

// content of a hashmap
struct hVal{
	enum hValType type;
	union {
		intptr_t	i;
		uintptr_t	u;
		void		*p;
		char		*s;
	} value;
};

// hashmap
struct hMap {
	struct hVal *data;
};
