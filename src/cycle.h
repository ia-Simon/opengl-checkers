typedef struct Value {
    size_t num;
    struct Value *prev;
    struct Value *next;
} Value;

class Cycle {
    Value *value;

    public:
        Cycle() {}
        
        Cycle(size_t size) {
            Value *first = new Value;
            first->num = 0;
            value = first;
            for(size_t i = 1; i < size; i++) {
                Value *aux = new Value;
                aux->num = i;
                aux->prev = value;
                value->next = aux;
                value = aux;
            }
            first->prev = value;
            value->next = first;
            value = first;
        }

        void next() {
            value = value->next;
        }

        void prev() {
            value = value->prev;
        }

        size_t get_value() {
            return value->num;
        }
};
