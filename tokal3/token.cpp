#include "token.h"

#include <map>
#include <exception>

using namespace std;

list<string> token_NS::tokenize(
    const string string_to_tokenize,
    const vector<string> separators, 
    const vector<pair<string, string>>separator_pairs
    )
{

    list<string> list_tokens;

    int i_token_start;
    //int i_token_end;//One past the last char in the token

    
    bool in_quote = false;
    bool escaped = false;

    string token;

    for(int i = 0; i < string_to_tokenize.length(); i++) {
        char c = string_to_tokenize[i];
        
        
        if(token.length() == 0) {
            i_token_start = i;

            //Ignore whitespace as first token character
            if(c == ' ')
                continue;
            token = string_to_tokenize[i];
        }

        string token_with_new_char = token + c;

        if(!in_quote){
            //A whitespace always ends a token if not in quote
            if(c == ' ') {
                list_tokens.push_back(token);
                token = "";
                continue;
            }

            //Check if a quote starts
            if(c == '"') {
                in_quote = true;
                token += '"';
                continue;
            }/*

            //See if the next char by itself is in the set of separators
            auto p = set_of_separators.find(string{c});
            if(p != set_of_separators.end()) {
                list_tokens.push_back(token);
                token = "";
                continue;
            }*/

            //If there is not whitespace or start of quote, we add the character to the token
            token += c;
            /*
            //See if the token is in the set of separators
            auto p = set_of_separators.find(token);
            if(p != set_of_separators.end()) {
                list_tokens.push_back(token);
                token = "";
                continue;
            }*/
            /*
            //See if the token is in the set of separator pair starters
            auto p1 = map_of_pairstarters.find(token);
            if(p1 != map_of_pairstarters.end()) {
                string end_string = p1->second;
                size_t pos = string_to_tokenize.find(end_string, i + token.size());
                if(pos == std::string::npos)
                    throw std::runtime_error("Matching end string for token is missing.\nToken: " + token + " End string: " + end_string + " i: " + std::to_string(i));

                token = string_to_tokenize.substr(i, pos + end_string.length());
                list_tokens.push_back(token);
                token = "";
                continue;
            }
            */
        } else {//We are in a quote

        }
    }

    return list<string>();
}

token_NS::Match_statemachine::Match_statemachine()
{
    v_separators = default_vector_of_token_separators;
    v_pair_separators = default_set_of_separator_pairs;
}


string token_NS::Match_statemachine::get_matched_token()
{
    if(n != 1 || pos_separators < 0)
        throw std::runtime_error("More than one matched tokens possible: " + buffer);

    return v_separators[pos_separators];
}

string token_NS::Match_statemachine::get_matched_pair_token()
{
    if(n != 1 || pos_pairs < 0)
        throw std::runtime_error("More than one matched tokens possible: " + buffer);

    return v_pair_separators[pos_pairs].first;
}

string token_NS::Match_statemachine::get_prior_token()
{
    return buffer.substr(0, buffer.length() - 1);
}

bool token_NS::Match_statemachine::has_one_match()
{
    return n == 1;
}

bool token_NS::Match_statemachine::has_multiple_matches()
{
    return n > 1;
}

bool token_NS::Match_statemachine::match_is_pair()
{
    return n == 1 && pos_pairs != -1;
}

bool token_NS::Match_statemachine::match_is_not_pair()
{
    return n == 1 && pos_separators != -1;
}

size_t token_NS::Match_statemachine::chew_one_char(string c)
{
    buffer += c;
    //Iterate all predefined tokens too see if there is one match
    n = 0;
    size_t i = 0;
    for(auto token : v_separators) {
        if(buffer.length() <= token.length()) {
            if(!token.compare(0, buffer.length(), buffer)){//check if the buffer is a substring of the token
                n++;
                pos_separators = i;
                pos_pairs = -1;
            }
        }
        i++;
    }
    i = 0;
    for(auto pair : v_pair_separators) {
        auto token = pair.first;
        if(buffer.length() <= token.length()) {
            if(!token.compare(0, buffer.length(), buffer)) {//check if the buffer is a substring of the token
                n++;
                pos_pairs = i;
                pos_separators = -1;
            }
        }
        i++;
    }
    return n;
}
