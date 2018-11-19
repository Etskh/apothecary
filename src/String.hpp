class String {
public:
    String();
    String(size_t num);
    String(const char* str);

    template<class ...Types>
    String& format(Types ... args);

    const char* c_str() const;

    operator const char*() const;
private:
    std::string value;
};



template<class ...Types>
String& String::format(Types ... args) {
    const char* replacement = "{}";
    std::vector<String> vec = {args...};
    for (size_t i = 0; i < vec.size(); ++i) {
        auto occurence = value.find(replacement);
        if( occurence == std::string::npos ) {
            // empty
        }
        else {
            value.replace(occurence, strlen(replacement), vec[i]);
        }
    }
    return *this;
}
