
#include <string>
#include <set>
#include <list>
#include <utility>
#include <vector>
#include <typeinfo>

namespace token_NS {
    using namespace std;
    
    /** Tokenizes a string.
    *
    *   Each separator in the provided set is treated as a new and separate token.
    *
    * \param string_to_tokenize The string to tokenize.
    * \param separators A set of strings which always make up a new token.
    * \param separator_pairs A set of string pairs, which always start and end a token, whatever is in between.
    *
    * \returns Returns a list of strings which each token in order from the beginning.
    */
    list<string> tokenize(const string string_to_tokenize, const vector<string>separators, const vector<pair<string, string>>separator_pairs);

    const vector<string> default_vector_of_token_separators{
        ";",
        ":",
        "=",
        "!",
        "^",
        "+",
        "-",
        "\n",
        "|",
        "*",
        "/",
        "\\",
        ",",
        "#",
        "@",
        "?",
        "==",
        "<",
        ">",
        "<=",
        ">=",
        
    };

    const vector<pair<string, string>> default_set_of_separator_pairs = {
        {"/*","*/"},
        {"//","\n"},
    };

    class Match_statemachine
    {
    public:
        string buffer;
        size_t pos_start;
        size_t pos_now;

        Match_statemachine();
        vector<string> v_separators;
        vector<pair<string, string>> v_pair_separators;

        size_t chew_one_char(string c);
        string get_matched_token();
        string get_matched_pair_token();
        string get_prior_token();
        bool has_one_match();
        bool has_multiple_matches();
        bool match_is_pair();
        bool match_is_not_pair();
    private:
        size_t n = 0;
        size_t pos_separators = -1;
        size_t pos_pairs = -1;
    };
}