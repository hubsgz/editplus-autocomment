
struct StringArr
{
    char *data;
    struct StringArr *next;
};

struct StringArr *newStringArr();
struct StringArr *StringArrAdd(struct StringArr *node, char *str);
void StringArrFree(struct StringArr *head);
int StringArrMaxLen(struct StringArr *head);
void StringArrPrint(struct StringArr *head);
