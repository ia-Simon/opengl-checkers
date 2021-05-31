class Selector {
    size_t val;
    size_t size;

public:
    Selector() {}
    
    Selector(size_t max_size) {
        val = 0;
        size = max_size;
    }
    size_t get_val() { return val; }

    void set_size(size_t max_size) { 
        size = max_size; 
        if(val >= size) 
            val = 0;
    }

    void next() {
        if(++val >= size) 
            val = 0;
    }

    void prev() {
        if(--val >= size) 
            val = size - 1;
    }
};

